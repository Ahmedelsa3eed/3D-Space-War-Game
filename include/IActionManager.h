#pragma once

class IActionManager
{
public:
    virtual void notifyClockTick() = 0;
};
