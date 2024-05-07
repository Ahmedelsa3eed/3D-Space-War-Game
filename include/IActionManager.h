#pragma once

class IActionManager : public IActionManager
{
public:
    virtual void notifyClockTick() = 0;
};
