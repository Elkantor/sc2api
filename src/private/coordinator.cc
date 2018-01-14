#include <node.h>
#include "nan.h"
#include "coordinator.h"
#include "player_setup.h"
#include "agent.h"
#include "bot.h"
#include <windows.h>
#include <sc2utils/sc2_manage_process.h>

class CoordinatorAsyncWorker : public Nan::AsyncWorker {
public:
    bool throws_error_;
    sc2::Coordinator* coordinator_;
    bool result;

    CoordinatorAsyncWorker(sc2::Coordinator* coordinator, bool throws_error, Nan::Callback *callback)
    : Nan::AsyncWorker(callback) {
        this->throws_error_ = throws_error;
        this->coordinator_ = coordinator;
    }

    void Execute() {
        if (throws_error_) {
            this->SetErrorMessage("An error occured!");
            return;
        }

        // mimic long running task
        result = coordinator_->Update();
    }

    void HandleOKCallback() {
        Nan::HandleScope scope;
        v8::Local<v8::Value> argv[] = {
            Nan::New(result)
        };
        callback->Call(1, argv);
    }

    void HandleErrorCallback() {
        Nan::HandleScope scope;
        v8::Local<v8::Value> argv[] = {
            Nan::New(this->ErrorMessage()).ToLocalChecked() // return error message
        };
        callback->Call(1, argv);
    }
};

Nan::Persistent<v8::FunctionTemplate> SC2Coordinator::constructor;

NAN_MODULE_INIT(SC2Coordinator::Init) {
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SC2Coordinator::New);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("SC2Coordinator").ToLocalChecked());

    // link our getters and setter to the object property
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("participants").ToLocalChecked(), SC2Coordinator::HandleGetters, SC2Coordinator::HandleSetters);

    Nan::SetPrototypeMethod(ctor, "loadSettings", LoadSettings);
    Nan::SetPrototypeMethod(ctor, "launchStarcraft", LaunchStarcraft);
    Nan::SetPrototypeMethod(ctor, "update", Update);

    target->Set(Nan::New("SC2Coordinator").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(SC2Coordinator::New) {
    // throw an error if constructor is called without new keyword
    if(!info.IsConstructCall()) {
        return Nan::ThrowError(Nan::New("SC2Coordinator::New - called without new keyword").ToLocalChecked());
    }

    // expect exactly 0 arguments
    if(info.Length() != 0) {
        return Nan::ThrowError(Nan::New("SC2Coordinator::New - constructor expected 0 argument").ToLocalChecked());
    }

    // create a new instance and wrap our javascript instance
    SC2Coordinator* coordinator = new SC2Coordinator();
    coordinator->Wrap(info.Holder());
    coordinator->sc2_coordinator_ = new sc2::Coordinator();

    // return the wrapped javascript instance
    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(SC2Coordinator::LoadSettings) {
  // unwrap this SC2Coordinator
  SC2Coordinator* self = Nan::ObjectWrap::Unwrap<SC2Coordinator>(info.This());

  // expect at least 1 argument (the)
  if(info.Length() < 1) {
      return Nan::ThrowError(Nan::New("SC2Coordinator::LoadSettings - expected argument(s): string path_exe (path of the starcraft 2 executable), bool realtime (wether to run starcraft 2 in realtime or not), string map_path (which map to run)").ToLocalChecked());
  }

  // expect argument to be a JSON Object
  if(!info[0]->IsObject()){
      return Nan::ThrowError(Nan::New("SC2Coordinator::LoadSettings - expected argument to be a JSON Object").ToLocalChecked());
  }
  v8::Local<v8::Object> settingsObj = info[0]->ToObject();

  v8::Local<v8::String> path_exe_prop = Nan::New("path_exe").ToLocalChecked();
  v8::Local<v8::String> realtime_prop = Nan::New("realtime").ToLocalChecked();
  v8::Local<v8::String> map_prop = Nan::New("map").ToLocalChecked();

  std::string path_exe = "";
  bool realtime = false;
  std::string map = "";

  if (Nan::HasOwnProperty(settingsObj, path_exe_prop).FromJust()) {
      v8::Local<v8::Value> path_exe_value = Nan::Get(settingsObj, path_exe_prop).ToLocalChecked();
      path_exe = std::string(*Nan::Utf8String(path_exe_value->ToString()));
  }

  if (Nan::HasOwnProperty(settingsObj, realtime_prop).FromJust()) {
      v8::Local<v8::Value> realtime_value = Nan::Get(settingsObj, realtime_prop).ToLocalChecked();
      realtime = realtime_value->BooleanValue();
  }

  if (Nan::HasOwnProperty(settingsObj, map_prop).FromJust()) {
      v8::Local<v8::Value> map_value = Nan::Get(settingsObj, map_prop).ToLocalChecked();
      map = std::string(*Nan::Utf8String(map_value->ToString()));
  }

  std::string settings = " -e " + path_exe;
  if(realtime){
    self->sc2_coordinator_->SetRealtime(realtime);
  }
  if(map != ""){
    self->map_ = map;
  }
  
  char* settings_chain[] = {(char*)settings.c_str()};
  self->sc2_coordinator_->LoadSettings(2, settings_chain);
  info.GetReturnValue().Set(Nan::New(settings.c_str()).ToLocalChecked());
}

NAN_METHOD(SC2Coordinator::LaunchStarcraft){
    SC2Coordinator* self = Nan::ObjectWrap::Unwrap<SC2Coordinator>(info.This());
    sc2::Agent* agent;
    v8::Local<v8::Array> array = Nan::New(self->participants_);
    std::vector<sc2::PlayerSetup> participants;
    for(int i = 0; i < array->Length(); i++){
        v8::Local<v8::Object> obj = array->Get(i)->ToObject();
        SC2PlayerSetup* player_setup = Nan::ObjectWrap::Unwrap<SC2PlayerSetup>(obj);
        participants.push_back(*(player_setup->player_setup_));
    }
    self->sc2_coordinator_->SetParticipants(participants);
    self->sc2_coordinator_->LaunchStarcraft();
    self->sc2_coordinator_->StartGame(self->map_);
}

NAN_METHOD(SC2Coordinator::Update) {
    SC2Coordinator* self = Nan::ObjectWrap::Unwrap<SC2Coordinator>(info.This());

    // starting the async worker
    Nan::AsyncQueueWorker(new CoordinatorAsyncWorker(
        self->sc2_coordinator_,
        false,
        new Nan::Callback(info[0].As<v8::Function>())
    ));    

    // return the wrapped javascript instance
    info.GetReturnValue().Set(Nan::New(true));
}

NAN_GETTER(SC2Coordinator::HandleGetters) {
  SC2Coordinator* self = Nan::ObjectWrap::Unwrap<SC2Coordinator>(info.This());

  std::string propertyName = std::string(*Nan::Utf8String(property));
  if (propertyName == "participants") {
    info.GetReturnValue().Set(Nan::New(self->participants_));
  }else {
    info.GetReturnValue().Set(Nan::Undefined());
  }
}

NAN_SETTER(SC2Coordinator::HandleSetters) {
    SC2Coordinator* self = Nan::ObjectWrap::Unwrap<SC2Coordinator>(info.This());

    std::string propertyName = std::string(*Nan::Utf8String(property));
    if (propertyName == "participants") {
        if(!value->IsArray()){
            return Nan::ThrowError(Nan::New("SC2Coordinator::participants - expected argument to be an array of SC2PlayerSetup objects").ToLocalChecked());
        }
        self->participants_.Reset(v8::Local<v8::Array>::Cast(value));
        info.GetReturnValue().Set(Nan::New(self->participants_));
    }else{
        info.GetReturnValue().Set(Nan::Undefined());
    }
}
