#pragma once

#include <sc2api/sc2_agent.h>
 
class SC2Bot : public sc2::Agent{

public:
    class SC2Agent* sc2_agent_;

    SC2Bot(class SC2Agent& agent);
    virtual void OnGameStart() final;
    virtual void OnStep() final;
    
};
