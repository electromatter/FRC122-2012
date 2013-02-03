#ifndef JOYTOGGLE_H
#define JOYTOGGLE_H

#include "WPILib.h"

class JoyToggle {
public:
  JoyToggle(Joystick& joy, const int& button, const bool& defaultState = false);
  virtual ~JoyToggle();
  bool get();
  void set(const bool& state);
  void reset();
  void tick();
private:
  bool m_debounce;
  bool m_state;
  bool m_defaultState;
  int m_button;
  Joystick& m_joy;
};

#endif
