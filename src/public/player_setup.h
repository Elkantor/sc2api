#include <nan.h>
#include <sc2api/sc2_api.h>

class SC2PlayerSetup : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_GETTER(HandleGetters);
  static NAN_SETTER(HandleSetters);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

private:
    sc2::PlayerSetup* player_setup_;
};
