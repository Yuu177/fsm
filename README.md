# FSM: A Simple Finite-State Machine

这个仓库基于查表法原理，实现了一个非常简单的有限状态机类。只转移状态，不执行任何动作。

## Example

我们下面以电机的状态为例子：我们要启动和停止电机，以及改变电机的速度。

![Motor](./.README.assets/Motor.png)

```c++
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

```

