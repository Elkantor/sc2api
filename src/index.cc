#include <node.h>
#include <nan.h>
#include "coordinator.h"
#include "agent.h"
#include "player_setup.h"

NAN_MODULE_INIT(InitModule) {
  SC2Coordinator::Init(target);
  SC2Agent::Init(target);
  SC2PlayerSetup::Init(target);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, InitModule);
