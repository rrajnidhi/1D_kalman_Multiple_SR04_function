#define trigPin1 3
#define echoPin1 2
#define trigPin2 5
#define echoPin2 4


float duration, distance, RightSensor,LeftSensor;


void setup()
{
Serial.begin (9600);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
}

void loop() 
{

RightSensor = SonarSensor(trigPin1, echoPin1);

LeftSensor = SonarSensor(trigPin2, echoPin2);

Serial.print(LeftSensor);
Serial.print(",");
Serial.println(RightSensor);
}

float SonarSensor(int trigPin,int echoPin)
{
float dist;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;
distance= kal_fun(dist);
return distance;

}

float kal_fun(float dist)
  {
  // kalman variables
float R = 2.92E-03;  // measuement variance; determined using excel and reading samples of raw sensor data which is constant
float Q = 1e-4;  //arbitaryly determined for this case. -5,-7(not working),-3(working)
float Pc = 0.0;
float G = 0.0;
float P = 1.0;
float Xp = 0.0;
float Zp = 0.0;
float Xe = 0.0;

  
  // kalman process
  Pc = P + Q;       //Predict covariance
  Xp = Xe;
  G = Pc/(Pc + R);    // kalman gain
  Zp = Xp;
  Xe = G*(dist-Zp)+Xp;   // the kalman State estimate of the sensor voltage
  P = (1-G)*Pc;             //update covarience  
  return Xe;
  }
