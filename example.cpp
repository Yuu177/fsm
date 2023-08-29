#include <cassert>
#include <iostream>

#include "state_machine.hpp"

enum class State {
  ST_IDLE,
  ST_START,
  ST_CHANGE_SPEED,
  ST_STOP
};

enum class Event {
  SetSpeed,
  Halt,
};

int main() {
  fsm::StateMachine<State, Event> sm(State::ST_IDLE);
  sm.AddTransition(State::ST_IDLE, Event::SetSpeed, State::ST_START);
  sm.AddTransition(State::ST_START, Event::SetSpeed, State::ST_CHANGE_SPEED);
  sm.AddTransition(State::ST_START, Event::Halt, State::ST_STOP);
  sm.AddTransition(State::ST_CHANGE_SPEED, Event::Halt, State::ST_STOP);

  assert(sm.GetCurrentState() == State::ST_IDLE);

  sm.ProcessEvent(Event::SetSpeed);
  assert(sm.GetCurrentState() == State::ST_START);

  sm.ProcessEvent(Event::SetSpeed);
  assert(sm.GetCurrentState() == State::ST_CHANGE_SPEED);

  sm.ProcessEvent(Event::Halt);
  assert(sm.GetCurrentState() == State::ST_STOP);

  std::cout << "Test passed" << std::endl;
  return 0;
}
