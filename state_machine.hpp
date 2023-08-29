#ifndef STATE_MACHINE
#define STATE_MACHINE

#include <unordered_map>

namespace fsm {

// State 如果不为基本变量需要重载 =
template <typename State, typename Event>
class StateMachine {
 public:
  explicit StateMachine(State init_state) : current_state_(init_state) {}

  void AddTransition(State from_state, Event event, State to_state) {
    transition_table_[from_state][event] = to_state;
  }

  void ProcessEvent(Event event) {
    auto transition = transition_table_[current_state_];
    if (transition.find(event) == transition.end()) {
      return;
    }
    current_state_ = transition[event];
  }

  State GetCurrentState() const {
    return current_state_;
  }

 private:
  State current_state_;
  std::unordered_map<State, std::unordered_map<Event, State>> transition_table_;
};

}  // namespace fsm

#endif  // STATE_MACHINE
