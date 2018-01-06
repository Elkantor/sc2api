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

    // link our getters and setter to the object property
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("difficulty").ToLocalChecked(), SC2PlayerSetup::HandleGetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("race").ToLocalChecked(), SC2PlayerSetup::HandleGetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("type").ToLocalChecked(), SC2PlayerSetup::HandleGetters);

    target->Set(Nan::New("SC2PlayerSetup").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(SC2PlayerSetup::New) {
    // throw an error if constructor is called without new keyword
    if(!info.IsConstructCall()) {
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - called without new keyword").ToLocalChecked());
    }

    SC2PlayerSetup* player_setup = new SC2PlayerSetup();
    player_setup->Wrap(info.Holder());
    player_setup->player_setup_ = new sc2::PlayerSetup();

    if(info.Length() < 1) {
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - expected at least 1 argument (a JSON Object)").ToLocalChecked());
    }

    if(!info[0]->IsObject()){
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - expected argument 1 to be a JSON Object").ToLocalChecked());
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

    if(type == "Participant"){
        player_setup->player_setup_->type = sc2::PlayerType::Participant;
    }else if(type == "Computer"){
        player_setup->player_setup_->type = sc2::PlayerType::Computer;
    }else if(type == "Observer"){
        player_setup->player_setup_->type = sc2::PlayerType::Observer;
    }else{
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - the type must be one of this string : 'Participant', 'Computer' or 'Observer'").ToLocalChecked());
    }

    if(race == "Terran"){
        player_setup->player_setup_->race = sc2::Race::Terran;
    }else if(race == "Protoss"){
        player_setup->player_setup_->race = sc2::Race::Protoss;
    }else if(type == "Zerg"){
        player_setup->player_setup_->race = sc2::Race::Zerg;
    }else{
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - the race must be one of this string : 'Terran', 'Protoss' or 'Zerg'").ToLocalChecked());
    }

    if(difficulty == "VeryEasy"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::VeryEasy;
    }else if(difficulty == "Easy"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::Easy;
    }else if(difficulty == "Medium"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::Medium;
    }else if(difficulty == "MediumHard"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::MediumHard;
    }else if(difficulty == "Hard"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::Hard;
    }else if(difficulty == "HardVeryHard"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::HardVeryHard;
    }else if(difficulty == "VeryHard"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::VeryHard;
    }else if(difficulty == "CheatVision"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::CheatVision;
    }else if(difficulty == "CheatMoney"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::CheatMoney;
    }else if(difficulty == "CheatInsane"){
        player_setup->player_setup_->difficulty = sc2::Difficulty::CheatInsane;
    }else{
        return Nan::ThrowError(Nan::New("SC2PlayerSetup::New - the difficulty must be one of this string : 'Easy', 'Medium' or 'MediumHard', 'Hard', 'HardVeryHard', 'VeryHard', 'CheatVision', 'CheatMoney', 'CheatInsane'").ToLocalChecked());
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
        player_setup->player_setup_->agent = agent->agent_;
    }


    info.GetReturnValue().Set(info.Holder());
}

NAN_GETTER(SC2PlayerSetup::HandleGetters) {
    SC2PlayerSetup* self = Nan::ObjectWrap::Unwrap<SC2PlayerSetup>(info.This());

    std::string property_name = std::string(*Nan::Utf8String(property));
    if (property_name == "difficulty") {
        int player_difficulty = self->player_setup_->difficulty;
        switch(player_difficulty){
            case 1: 
                info.GetReturnValue().Set(Nan::New("VeryEasy").ToLocalChecked());
                break;
            case 2:
                info.GetReturnValue().Set(Nan::New("Easy").ToLocalChecked());
                break;
            case 3:
                info.GetReturnValue().Set(Nan::New("Medium").ToLocalChecked());
                break;
            case 4:
                info.GetReturnValue().Set(Nan::New("MediumHard").ToLocalChecked());
                break;
            case 5:
                info.GetReturnValue().Set(Nan::New("Hard").ToLocalChecked());
                break;
            case 6:
                info.GetReturnValue().Set(Nan::New("HardVeryHard").ToLocalChecked());
                break;
            case 7:
                info.GetReturnValue().Set(Nan::New("VeryHard").ToLocalChecked());
                break;
            case 8:
                info.GetReturnValue().Set(Nan::New("CheatVision").ToLocalChecked());
                break;
            case 9:
                info.GetReturnValue().Set(Nan::New("CheatMoney").ToLocalChecked());
                break;
            case 10:
                info.GetReturnValue().Set(Nan::New("CheatInsane").ToLocalChecked());
                break;
            default:
                break;
        }   
    } else if (property_name == "race") {
        switch(self->player_setup_->race){
            case sc2::Race::Terran:
                info.GetReturnValue().Set(Nan::New("Terran").ToLocalChecked());
                break;
            case sc2::Race::Zerg:
                info.GetReturnValue().Set(Nan::New("Zerg").ToLocalChecked());
                break;
            case sc2::Race::Protoss:
                info.GetReturnValue().Set(Nan::New("Protoss").ToLocalChecked());
                break;
            case sc2::Race::Random:
                info.GetReturnValue().Set(Nan::New("Random").ToLocalChecked());
                break;
            default:
                break;
        }
    } else if (property_name == "type") {
        int player_type = self->player_setup_->type;
        switch(player_type){
            case 1:
                info.GetReturnValue().Set(Nan::New("Participant").ToLocalChecked());
                break;
            case 2:
                info.GetReturnValue().Set(Nan::New("Computer").ToLocalChecked());
                break;
            case 3:
                info.GetReturnValue().Set(Nan::New("Observer").ToLocalChecked());
                break;
            default:
                break;
        }
    } else {
        info.GetReturnValue().Set(Nan::Undefined());
    }
}