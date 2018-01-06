#include <node.h>
#include "nan.h"
#include "agent.h"

Nan::Persistent<v8::FunctionTemplate> SC2Agent::constructor;

NAN_MODULE_INIT(SC2Agent::Init) {
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(SC2Agent::New);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("SC2Agent").ToLocalChecked());

    target->Set(Nan::New("SC2Agent").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(SC2Agent::New) {
    // throw an error if constructor is called without new keyword
    if(!info.IsConstructCall()) {
        return Nan::ThrowError(Nan::New("SC2Agent::New - called without new keyword").ToLocalChecked());
    }

    // expect exactly 1 argument
    if(info.Length() != 1) {
        return Nan::ThrowError(Nan::New("SC2Agent::New - expected argument x").ToLocalChecked());
    }

    // expect arguments to be numbers
    if(!info[0]->IsNumber()) {
        return Nan::ThrowError(Nan::New("SC2Agent::New - expected argument to be number").ToLocalChecked());
    }

    // create a new instance and wrap our javascript instance
    SC2Agent* agent = new SC2Agent();
    agent->Wrap(info.Holder());

    // initialize it's values
    agent->x = info[0]->NumberValue();

    // return the wrapped javascript instance
    info.GetReturnValue().Set(info.Holder());
}
