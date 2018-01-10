#include <nan.h>
#include <sc2api/sc2_api.h>

class SC2Coordinator : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(LoadSettings);
  static NAN_METHOD(SetParticipants);
  static NAN_GETTER(HandleGetters);
  static NAN_SETTER(HandleSetters);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

private:
    sc2::Coordinator* sc2_coordinator_;
    std::string map_;
    std::vector<class SC2PlayerSetup*>* participants_;
};
