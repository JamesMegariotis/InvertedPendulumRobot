
# **Two Wheel Inverted Pendulum Robot**
#### For Submission: Matlab & Simulink Low Cost Hardware Challenge
#### Author: James Megariotis

##### Click Here For Video Description of Submission:
[![Inverted Pendulum Robot Submission Video](https://img.youtube.com/vi/bBDBOt8wlIQ/0.jpg)](https://www.youtube.com/watch?v=bBDBOt8wlIQ)

###Instructions for Standalone Use:
________________________________

1. Either Simulink model in which the file name ends with "Standalone" is ready for deployment onto an Arduino Mega 2560. A few steps must be take to ensure deployment to the Arduino.

  - The Files contained in the ReadQuadratureEncoders_S-function_Files folder must be included in the (moved to the) working directory where the Standalone file is located.
  
    **OR**
  - The read_quad_encoder block in the "Standalone" file must be built before the model is deployed.

2. When ready, use the "deploy to hardware" button on the simulink toolbar. Simulation mode must be set to "Normal". Errors will occur in any other mode.



###Instructions for External Mode Use:
___________________________________

1. If designing your own system using the blocks in the "ControllerDesignLab" file. The signals in the model can be viewed in real time for debugging and calibration purposes using External Mode in The Simulation Mode dropdown menu. 
2. Just connect a scope to any signal and run model in external mode.

  _For More Information See:_ [Matlab External Mode Tutorial](http://www.mathworks.com/help/supportpkg/arduino/ug/tune-and-monitor-model-running-on-arduino-mega-2560-hardware.html)


###Notes to Users:
_______________

These files can be run and deployed on either an Adruino Mega 2560 or Arduino Due. They were all tested on both platforms, but performance tends to be more stable on the Mega. Also all hardware is 5V, so the Mega became microcontroller of choice.


###File Descriptions:
__________________

- *InvertedPendulumRobot_LQRControl_Standalone.slx*:

  Implements a state feedback linear quadratic regulator for control of the inverted pendulum robot. Ready for deployment.


- *InvertedPendulumRobot_LQRControl_w_YawRate_Standalone.slx*: 

  Implements the same system as above file but with speed correction blocks to compensate for motor speed differences. Ready for deployment. Speed correction blocks may require minor calibration via gain.


- *InvertedPendulumRobot_ControllerDesignLab.slx*: 

  Contains the main blocks used to construct the control system. These blocks can be used to design alternate control schemes. Blocks include read_quad_encoder for outputting encoder tick count, BNO055 IMU block for acquiring IMU data, Motor Driver block for use with 12V motors and sabertooth dual 12A motor driver (easily adapted to other pwm motor drivers).


- *BNO055_IMU_RegisterMap_AvailableOutputs.slx*: 

  Contains addition blocks mapped to IMU registers. Output blocks can output properly scaled IMU outputs. Outputs include quaternions, magnetometer data, euler angles, gyroscope data, and acceleration data. These can be used in the IMU(BNO-055) block from the 3 above files if additional ouputs are needed.


- *StateSpace_ControllerDesign.m*: 

  Matlab Script used for LQR controller design. Constants can be modified for implemtation on any inverted pendulum system. The Q and R values can be modified along with the Timestep value for controller performance tuning. Outputs state trajectory plot along with a plot of the control input (voltage) to more easily visualize control response. The values of the K gain matrix can then be used for the K_LQR gain block. The values may require slight calibration, specifically the value in the K(4) position (controlling tilt angular velocity) may need to be significantly reduced or set to 0 due to gyroscope noise.


- *PololuMotor_PerformaceModeling.m*: 

  A scipt for estimating the performance of pololu motors and motor constants (torque and back emf constants).


- *ReadQuadratureEncoders_S-function_Files (Folder)*: 

  contains s-function builder output files necessary for the operation of the read_quad_encoders block in the top 3 .slx files. Files within folder must be in same folder as model for deployment.


- *Models for 3D Printing (Folder)*: 

  contains all files designed and printed for the robot's construction.
