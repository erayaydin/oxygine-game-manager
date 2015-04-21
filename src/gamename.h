#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(GameName, GmGame);
class GameName: public Actor
{
public:
    GameName();

    void init();

private:
    void update(const UpdateState& us);
};