#include <node.h>
#include "nan.h"
#include "agent.h"
#include "bot.h"

Nan::Persistent<v8::FunctionTemplate> SC2Agent::constructor;

NAN_MODULE_INIT(SC2Agent::Init) {
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SC2Agent::New);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("SC2Agent").ToLocalChecked());

    //Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("onGameStart").ToLocalChecked(), SC2Agent::HandleGetters, SC2Agent::HandleSetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("onGameStart").ToLocalChecked(), SC2Agent::HandleGetters, SC2Agent::HandleSetters);

    //Nan::SetPrototypeMethod(ctor, "onGameStart", OnGameStart);

    target->Set(Nan::New("SC2Agent").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(SC2Agent::New) {
    // throw an error if constructor is called without new keyword
    if(!info.IsConstructCall()) {
        return Nan::ThrowError(Nan::New("SC2Agent::New - called without new keyword").ToLocalChecked());
    }

    // expect exactly 0 argument
    if(info.Length() != 0) {
        return Nan::ThrowError(Nan::New("SC2Agent::New - constructor expected 0 argument").ToLocalChecked());
    }

    // create a new instance and wrap our javascript instance
    SC2Agent* agent = new SC2Agent();
    agent->Wrap(info.Holder());

    // return the wrapped javascript instance
    info.GetReturnValue().Set(info.Holder());
}

NAN_GETTER(SC2Agent::HandleGetters) {
  SC2Agent* self = Nan::ObjectWrap::Unwrap<SC2Agent>(info.This());

  std::string propertyName = std::string(*Nan::Utf8String(property));
  if (propertyName == "onGameStart") {
    info.GetReturnValue().Set(Nan::New(self->peristent_onGameStart_));
  }else {
    info.GetReturnValue().Set(Nan::New("ko").ToLocalChecked());
  }
}

NAN_SETTER(SC2Agent::HandleSetters) {
    SC2Agent* self = Nan::ObjectWrap::Unwrap<SC2Agent>(info.This());

    std::string propertyName = std::string(*Nan::Utf8String(property));
    if (propertyName == "onGameStart") {
        SC2Agent* self = Nan::ObjectWrap::Unwrap<SC2Agent>(info.This());
        if(!value->IsFunction()){
            return Nan::ThrowError(Nan::New("SC2Agent::OnGameStart - expected argument to be a function").ToLocalChecked());
        }
        self->peristent_onGameStart_.Reset(Nan::To<v8::Function>(value).ToLocalChecked());
        info.GetReturnValue().Set(Nan::New(self->peristent_onGameStart_));
    }
}