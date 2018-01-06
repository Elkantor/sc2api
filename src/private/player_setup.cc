#include <node.h>
#include "nan.h"
#include "player_setup.h"
#include "agent.h"

Nan::Persistent<v8::FunctionTemplate> SC2PlayerSetup::constructor;

NAN_MODULE_INIT(SC2PlayerSetup::Init) {
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SC2PlayerSetup::New);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("SC2PlayerSetup").ToLocalChecked());

    target->Set(Nan::New("SC2PlayerSetup").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(SC2PlayerSetup::New) {
    // throw an error if constructor is called without new keyword
    if(!info.IsConstructCall()) {
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - called without new keyword").ToLocalChecked());
    }

    SC2PlayerSetup* player_setup = new SC2PlayerSetup();
    player_setup->Wrap(info.Holder());

    if(info.Length() > 0) {
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - expected argument to be a JSON Object").ToLocalChecked());
    }

    if(!info[0]->IsObject()){
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - expected argument to be a JSON Object").ToLocalChecked());
    }

    v8::Local<v8::Object> player_setup_json = info[0]->ToObject();

    v8::Local<v8::String> type_prop = Nan::New("type").ToLocalChecked();
    v8::Local<v8::String> race_prop = Nan::New("race").ToLocalChecked();
    v8::Local<v8::String> difficulty_prop = Nan::New("difficulty").ToLocalChecked();

    std::string type = "";
    std::string race = "";
    std::string difficulty = "";

    if (Nan::HasOwnProperty(player_setup_json, type_prop).FromJust()) {
      v8::Local<v8::Value> type_value = Nan::Get(player_setup_json, type_prop).ToLocalChecked();
      type = std::string(*Nan::Utf8String(type_value->ToString()));
    }

    if (Nan::HasOwnProperty(player_setup_json, race_prop).FromJust()) {
        v8::Local<v8::Value> race_value = Nan::Get(player_setup_json, race_prop).ToLocalChecked();
        race = std::string(*Nan::Utf8String(race_value->ToString()));
    }

    if (Nan::HasOwnProperty(player_setup_json, difficulty_prop).FromJust()) {
        v8::Local<v8::Value> difficulty_value = Nan::Get(player_setup_json, difficulty_prop).ToLocalChecked();
        difficulty = std::string(*Nan::Utf8String(difficulty_value->ToString()));
    }

    if(info.Length() == 2){
        if(!info[1]->IsObject()){
            return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - expected argument 2 to be a SC2Agent").ToLocalChecked());
        }
        Nan::MaybeLocal<v8::Object> agent_js = Nan::To<v8::Object>(info[1]);
        if(agent_js.IsEmpty()){
            return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - argument  2 must be a SC2Agent Object").ToLocalChecked());
        }
        SC2Agent* agent = Nan::ObjectWrap::Unwrap<SC2Agent>(agent_js.ToLocalChecked());
    }

    info.GetReturnValue().Set(info.Holder());
}