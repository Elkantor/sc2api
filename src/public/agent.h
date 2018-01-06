#include <nan.h>
#include <sc2api/sc2_api.h>

class SC2Agent : public Nan::ObjectWrap {
public:
    double x;
    sc2::Agent* agent_;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);

    static Nan::Persistent<v8::FunctionTemplate> constructor;

protected:
    
};
