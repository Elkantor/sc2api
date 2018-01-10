#include <node.h>
#include "bot.h"
#include "nan.h"
#include "agent.h"
#include <sc2api/sc2_api.h>


class BotAsyncWorker : public Nan::AsyncWorker{

public:
    bool throws_error_;

    BotAsyncWorker(bool throws_error, Nan::Callback* callback) : Nan::AsyncWorker(callback){
        this->throws_error_ = throws_error;
    }

    void Execute(){
        if(throws_error_){
            this->SetErrorMessage("An error occured !");
            return;
        }

    }

    void HandleOKCallback(){
        Nan::HandleScope scope;
        v8::Local<v8::Value> argv[] = {
            Nan::Null()
        };
        callback->Call(1, argv);
    }

    void HandleErrorCallback(){
        Nan::HandleScope scope;
        v8::Local<v8::Value> argv[] = {
            Nan::New(this->ErrorMessage()).ToLocalChecked(), // return error message
        };
        callback->Call(2, argv);
    }
};

SC2Bot::SC2Bot(SC2Agent &agent){
    sc2_agent_ = &agent;
}

void SC2Bot::OnGameStart(){
    // v8::Local<v8::Function> callback = Nan::New(sc2_agent_->peristent_onGameStart_);
    // Nan::AsyncQueueWorker(new BotAsyncWorker(
    //     false,
    //     new Nan::Callback(callback)
    // ));
}

void SC2Bot::OnStep(){}
