#include <nan.h>
#include <sc2api/sc2_api.h>

class SC2Agent : public Nan::ObjectWrap {
public:
    class SC2Bot* agent_;
    Nan::Persistent<v8::Function> peristent_onGameStart_;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    //static NAN_METHOD(OnGameStart);
    static NAN_SETTER(HandleSetters);
    static NAN_GETTER(HandleGetters);
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    
};
