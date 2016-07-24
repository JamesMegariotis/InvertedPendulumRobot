
%Take inputs from pololu website to draw curves of the dc motor.

StallTorque = input('Please enter the stall torque in oz-inch : ');
StallCurrent = input('Please enter the stall current in mA : ');
RatedVoltage = input('Please enter the rated voltage in Volts : ');
FreeRunCurrent = input('Please enter the free run currennt in mA : ');
FreeRunSpeed = input('Please enter the free run speed in RPM : ');
Resistance = RatedVoltage / StallCurrent;

torque1 = 0;
torque2 = StallTorque; % oz-inch *  (1/141.611932278)= N-m;

current1 = FreeRunCurrent; % / 1000; %mA to Amps
current2 = StallCurrent;   %/ 1000; %mA to Amps

speed1 = FreeRunSpeed;     %RPM = 1/9.5493 radians per sec
speed2 = 0;

line([torque1 torque2], [current1 current2]);
line([torque1 torque2], [speed1 speed2]);

totSamples = 200; %will break the torque into 200 discrete values

redlineY = zeros( 1,totSamples);
redlineX = zeros( 1,totSamples);
bluelineY = zeros( 1,totSamples);
bluelineX = zeros( 1,totSamples);
greenlineY = zeros( 1,totSamples);
greenlineX = zeros( 1,totSamples);
orangelineY = zeros( 1,totSamples);
orangelineX = zeros( 1,totSamples);

%a = (torque2 - torque1)/totSamples;
%looper = 1, torque = torque1, looper = 2, torque = torque1 + (t2-t1)/FS
Index = 1;
maxPwrIndex = 1;
maxEffIndex = 1;
lastEff = 0;
lastPwr = 0;

for T = torque1:(torque2 - torque1)/totSamples:torque2
   bluelineY(Index) =  (((speed2 - speed1) / (torque2 - torque1)) * (T - torque1)) + (speed1);
   bluelineX(Index) = T;
   
   redlineY(Index) = (((current2 - current1) / (torque2 - torque1)) * (T - torque1)) + (current1);
   redlineX(Index) = T;
   
   orangelineY(Index) = bluelineY(Index) * T; %Speed into Torque to give the Output power curve
   orangelineX(Index) = T;
   if orangelineY(Index) > lastPwr
       maxPwrIndex = Index;
       lastPwr = orangelineY(Index);
   end
   greenlineY(Index) = orangelineY(Index) / ((redlineY(Index)) * RatedVoltage); %Output power divided by curent line * Voltage (power).
   greenlineX(Index) = T;
   if greenlineY(Index) > lastEff
       maxEffIndex = Index;
       lastEff = greenlineY(Index);
   end
   
   Index = Index + 1;
end


fprintf('Resistance of motor = %f\n', Resistance)
fprintf('Peak Output Power %f @ Current = %f, Torque = %f\n', orangelineY(maxPwrIndex), redlineY(maxPwrIndex), orangelineX(maxPwrIndex))
fprintf('Peak Efficiency %f @ Current = %f, Torque = %f\n', greenlineY(maxEffIndex), redlineY(maxEffIndex), orangelineX(maxEffIndex))

dim1 = 2;
dim2 = 2;
subplot(dim1,dim2,1);
plot(redlineX, Resistance*redlineY);
title('Volts vs. Torque');
legend('Current');
xlabel('Torque (oz-in)');
ylabel('Current mA');
grid on;
subplot(dim1,dim2,2);
plot(bluelineX, bluelineY);
title('Speed vs. Torque');
legend('Speed');
xlabel('Torque (oz-in)');
ylabel('Speed (RPM)');
grid on;
subplot(dim1,dim2,3);
plot(orangelineX, orangelineY);
title('Output power');
legend('Output Power');
ylabel('Output Power (Speed*Torque)');
xlabel('Torque (oz-in)');
grid on;
subplot(dim1,dim2,4);
plot( greenlineX, greenlineY);
title('Power Efficiency');
legend('Power Efficiency');
ylabel('Power Efficiency (Output Pwr/Input Pwr)');
xlabel('Torque (oz-in)');
grid on;

for i = 1:length(redlineY)
    r2d2(i)=redlineY(end-(i-1));
end
figure
plot(Resistance*r2d2, bluelineY);
title('Volts vs. Torque');
