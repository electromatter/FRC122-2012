#include "JoyToggle.h"

JoyToggle::JoyToggle(Joystick& joy, const int& button, const bool& defaultState) : m_debounce(false), m_state(defaultState),
    m_defaultState(defaultState), m_button(button), m_joy(joy) {
}

JoyToggle::~JoyToggle() {
}

bool JoyToggle::get() {
  return m_state;
}

void JoyToggle::set(const bool& state) {
  m_debounce = false;
  m_state = state;
}

void JoyToggle::reset() {
  m_debounce = false;
  m_state = m_defaultState;
}

void JoyToggle::tick() {
  bool s;
  if(m_debounce != (s = m_joy.GetRawButton(m_button))) {
    if((m_debounce = s)) {
      m_state = !m_state;
    }
  }
}
