#include <nan.h>
#include <sc2api/sc2_api.h>

class SC2PlayerSetup : public Nan::ObjectWrap {
public:
    sc2::PlayerSetup* player_setup_;
    Nan::Persistent<v8::Object> persistent_agent_;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    static NAN_METHOD(SetAgent);
    static NAN_METHOD(TestAsynch);    
    static NAN_GETTER(HandleGetters);
    static Nan::Persistent<v8::FunctionTemplate> constructor;

private:
    
};
