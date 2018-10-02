#include "FiniteStateMachine.h" 

//FINITE STATE
State::State( void (*updateFunction)() ){
    userEnter = 0;
    userUpdate = updateFunction;
    userExit = 0;
}

State::State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)() ){
    userEnter = enterFunction;
    userUpdate = updateFunction;
    userExit = exitFunction;
}

//what to do when entering this state
void State::enter(){
    if (userEnter){
        userEnter();
    }
}

//what to do when this state updates
void State::update(){
    if (userUpdate){
        userUpdate();
    }
}

//what to do when exiting this state
void State::exit(){
    if (userExit){
        userExit();
    }
}

// Done with states, Define the whole machine.

FiniteStateMachine::FiniteStateMachine(void){
    currentState =  NULL;
}

void FiniteStateMachine::begin(State& state){
    currentState = &state;
    currentState->enter();
    stateChangeTime = millis();
}

void FiniteStateMachine::update() {
     currentState->update();
}

void FiniteStateMachine::transitionTo(State& state){
    currentState->exit();
    currentState = &state;
    currentState->enter();
    stateChangeTime = millis();
}

State& FiniteStateMachine::getCurrentState() {
    return *currentState;
}

//check if state is equal to the currentState
boolean FiniteStateMachine::isInState( State &state ) const {
    if (&state == currentState) {
        return true;
    } else {
        return false;
    }
}

unsigned long FiniteStateMachine::timeInCurrentState() { 
    return( millis() - stateChangeTime ); 
}

