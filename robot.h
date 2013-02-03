#ifndef ROBOT_H
#define ROBOT_H

#include "WPILib.h"
#include "JoyToggle.h"

class Robot : public SimpleRobot {
public:
  Robot();
  virtual ~Robot();
  void Disabled();
  void Autonomous();
  void OperatorControl();
private:
  RobotDrive m_drive;
  Joystick m_Joperator,m_Jdrive;
  Relay m_light, m_pipe;
  DigitalInput m_DpipeUp, m_DpipeDown;
  Encoder m_Eleft, m_Eright;
  Jaguar m_cannonRight, m_cannonLeft,
         m_elevator, m_bowl;
  Servo m_Scamera;
  Victor m_table;
  AnalogChannel m_Aball, m_Abowl;
  JoyToggle m_JTlight, m_JTelevator,
            m_JTspeed, m_JTdrive;
  float m_camY;
  int m_fire;
  //REL 8 - Pipe..
  //REL 3 - Camera Light..
  //PWM 10 - Camera servo.
  //PWM 8 - Bowl.
  //PWM 6 - Elevator.
  //PWM 5 - Turn Table.
  //PWM 4 - Cannon L.
  //PWM 3 - Cannon R.
  //PWM 2 - Left Drive..
  //PWM 1 - Right Drive..
  //DI 14 - Pipe Up Limit..
  //DI 13 - Pipe Down Limit..
  //DI 4 - Encoder Right B..
  //DI 3 - Encoder Left B..
  //DI 2 - Encoder Right A..
  //DI 1 - Encoder Left A..
  //AI 7 - Ball Detect.
  //AI 5 - Bowl Detect. 0.03 - 0.9
};

#endif
