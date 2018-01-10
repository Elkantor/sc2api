#include <nan.h>
#include <sc2api/sc2_api.h>

class SC2PlayerSetup : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(SetAgent);
  static NAN_GETTER(HandleGetters);
  static Nan::Persistent<v8::FunctionTemplate> constructor;

private:
    sc2::PlayerSetup* player_setup_;
    Nan::Persistent<v8::Object> persistent_agent_;
};
