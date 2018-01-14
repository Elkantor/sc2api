#include <node.h>
#include "bot.h"
#include "nan.h"
#include "agent.h"
#include <sc2api/sc2_api.h>

void delay(int iterations) {
  // use volatile to prevent compiler from optimizing empty loop
  for (volatile int i = 0; i < iterations; i++);
}

class BotAsyncWorker : public Nan::AsyncWorker {
public:
  bool throwsError;

  BotAsyncWorker(bool throwsError, Nan::Callback *callback)
    : Nan::AsyncWorker(callback) {

    this->throwsError = throwsError;
  }

  void Execute() {
    if (throwsError) {
      this->SetErrorMessage("An error occured!");
      return;
    }

    // mimic long running task
    delay(200);
  }

  void HandleOKCallback() {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[] = {
      Nan::Null() // no error occured
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

void SC2Bot::OnGameStart(){
    // starting the async worker
    Nan::AsyncQueueWorker(new BotAsyncWorker(
        true,
        new Nan::Callback(Nan::New<v8::Function>(this->sc2_agent_->peristent_onGameStart_))
    ));
    // v8::Local<v8::Function> callback = Nan::New(sc2_agent_->peristent_onGameStart_);
    // Nan::AsyncQueueWorker(new BotAsyncWorker(
    //     false,
    //     new Nan::Callback(callback)
    // ));
}

void SC2Bot::OnStep(){}
