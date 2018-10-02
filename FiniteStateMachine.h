#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H
#include <Arduino.h>

#define FSM FiniteStateMachine

class State {
    public:
        State( void (*updateFunction)() );
        State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() );
        void enter();
        void update();
        void exit();
    private:
        void (*userEnter)();
        void (*userUpdate)();
        void (*userExit)();
};

class FiniteStateMachine {
    public:
        FiniteStateMachine();       
        void begin( State& state );
        void update();
        void transitionTo( State& state );
        State& getCurrentState();
        boolean isInState( State &state ) const;
        unsigned long timeInCurrentState();
    private:
        State*  currentState;
        unsigned long stateChangeTime;
};

#endif