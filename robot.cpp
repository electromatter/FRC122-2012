#include "robot.h"

/**/
  //REL 8 - Pipe.
  //REL 3 - Camera Light.
  //PWM 10 - Camera servo.
  //PWM 8 - Bowl.
  //PWM 6 - Elevator.
  //PWM 5 - Turn Table.
  //PWM 4 - Cannon L.
  //PWM 3 - Cannon R.
  //PWM 2 - Left Drive.
  //PWM 1 - Right Drive.
  //DI 14 - Pipe Up Limit.
  //DI 13 - Pipe Down Limit.
  //DI 4 - Encoder Right B.
  //DI 3 - Encoder Left B.
  //DI 2 - Encoder Right A.
  //DI 1 - Encoder Left A.
  //AI 7 - Ball Detect.
  //AI 5 - Bowl Detect. 0.03 - 0.9

Robot::Robot() : m_drive(1, 2), m_Joperator(2), m_Jdrive(1),
                 m_light(3), m_pipe(8),
                 m_DpipeUp(14), m_DpipeDown(13),
                 m_Eleft(1, 3), m_Eright(2, 4),
                 m_cannonRight(3), m_cannonLeft(4),
                 m_elevator(6), m_bowl(8),
                 m_Scamera(10), m_table(5),
                 m_Aball(7), m_Abowl(5), m_JTlight(m_Joperator, 7), m_JTelevator(m_Joperator, 8),
                 m_JTspeed(m_Joperator, 9), m_JTdrive(m_Joperator, 10), m_camY(0.5), m_fire(0) {
  m_drive.SetExpiration(0.1);
}

Robot::~Robot() {
}

void Robot::Disabled() {
}

void Robot::Autonomous() {
/*  myRobot.SetSafetyEnabled(false);
  myRobot.Drive(-0.5, 0.0);
  Wait(2.0);
  myRobot.Drive(0.0, 0.0);*/
}

void Robot::OperatorControl() {
  m_JTelevator.reset();
  m_JTlight.reset();
  m_JTspeed.reset();
  m_JTdrive.reset();
  m_camY = 0.5f;
  m_fire = 0;

  while (IsOperatorControl()) {
	Relay::Value pipe = Relay::kOff;
	float cannon = 0;
	float bowl = 0;
	
    if((m_Joperator.GetRawButton(1) || m_Jdrive.GetRawButton(1)) && m_fire==0 && m_cannonLeft.Get()>0.1f) {
    	m_fire = 1;
    }

    //m_Abowl.GetVoltage() <= 0.03 -> reached the top
    //m_Abowl.GetVoltage() >= 0.9 -> reached the bottom
   
    if(m_fire) {
        if(m_fire==1) {
          if(m_Abowl.GetVoltage() > 0.03) {
            bowl = -1;
          } else {
            m_fire = 2;
          }
        } else if(m_fire==2) {
          if(m_Abowl.GetVoltage() < 0.9) {
            bowl = 1;
          } else {
            m_fire = 0;
          }
        } else {
          m_fire = 0;
        }
    } else {
      if(m_Abowl.GetVoltage() < 0.9) {
        bowl = 1;
      }
    }
    
    //Tick All States
    m_JTlight.tick();
    m_JTelevator.tick();
    if(m_fire==0)
      m_JTspeed.tick();
    m_JTdrive.tick();
    
    m_light.Set(m_JTlight.get()?Relay::kForward:Relay::kOff);
    m_elevator.Set(m_JTelevator.get()&&!m_fire?-1.f:0.f);
    
    if(m_JTspeed.get()) {
      cannon = (1.f + m_Joperator.GetRawAxis(4)) / 2.f;
      cannon *= 0.75f;
    }

    if(m_Joperator.GetRawButton(11) && m_DpipeUp.Get()) {
      pipe = Relay::kReverse;
    }
    
    if(m_Joperator.GetRawButton(12) && m_DpipeDown.Get()) {
      pipe = Relay::kForward;
    }
    
    m_cannonLeft.Set(cannon);
    m_cannonRight.Set(cannon);
    
    m_table.Set(m_Joperator.GetRawAxis(5));
    
    if(m_Joperator.GetRawAxis(6)>0.1f||m_Joperator.GetRawAxis(6)<-0.1f)
      m_camY -= m_Joperator.GetRawAxis(6)*0.15f;
    
    if(m_camY<0.5f) m_camY = 0.5f;
    if(m_camY>1.f) m_camY = 1.f;
    
    m_Scamera.Set(m_camY);
    
    m_bowl.Set(bowl);
    m_pipe.Set(pipe);
    
    if(m_JTdrive.get()) {
      m_drive.ArcadeDrive(m_Jdrive.GetRawAxis(1), m_Jdrive.GetRawAxis(2), false);
    } else {
      m_drive.TankDrive(-m_Joperator.GetRawAxis(2), m_Jdrive.GetRawAxis(2), false);
    }
    
    Wait(0.005);
  }

}

