#pragma once

#include <sc2api/sc2_agent.h>
 
class SC2Bot : public sc2::Agent{

public:
    class SC2Agent* sc2_agent_;
    
    virtual void OnGameStart() final;
    virtual void OnStep() final;
    
};
