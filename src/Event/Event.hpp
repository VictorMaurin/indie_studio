/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Event
*/

#ifndef EVT_RECEIVER_HPP
#define EVT_RECEIVER_HPP

#include <irrlicht.h>
#include "driverChoice.h"

class MyEventReceiver : public irr::IEventReceiver
{
public:
    virtual bool OnEvent(const irr::SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0)
        {
            JoystickState = event.JoystickEvent;
        }

        return false;
    }

    const irr::SEvent::SJoystickEvent& GetJoystickState(void) const
    {
        return JoystickState;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    MyEventReceiver()
    {
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    irr::SEvent::SJoystickEvent JoystickState;
};

#endif // !EVT_RECEIVER_HPP