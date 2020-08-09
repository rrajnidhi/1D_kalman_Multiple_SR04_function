
#define echoPinA 2
#define trigPinA 3

#define echoPinB 4
#define trigPinB 5

long duration;
float distance;

// kalman variables
float R = 2.92E-03;  // measuement variance; determined using excel and reading samples of raw sensor data which is constant
float Q = 1e-4;  //arbitaryly determined for this case. -5,-7(not working),-3(working)
float Pc = 0.0;
float G = 0.0;
float P = 1.0;
float Xp = 0.0;
float Zp = 0.0;
float Xe = 0.0;

float dist_fun (int trigPin, int echoPin) // sr04 dist mesarmnt function declaration 
{
  float dist;
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  dist = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  return dist;
}

float kal_fun(float dist)
  {
  // kalman process
  Pc = P + Q;       //Predict covariance
  Xp = Xe;
  G = Pc/(Pc + R);    // kalman gain
  Zp = Xp;
  Xe = G*(dist-Zp)+Xp;   // the kalman State estimate of the sensor voltage
  P = (1-G)*Pc;             //update covarience  
  return Xe;
  }

void setup() 
{
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT); 
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT); 
  Serial.begin(9600);
}

void loop() 
{
float a,b,c,d;
a= dist_fun(trigPinA,echoPinA);
b= kal_fun(a);
Serial.println(b);
//Serial.print(",");
//delay(20);
//c= dist_fun(trigPinB,echoPinB);
//d= kal_fun(c);
//Serial.println(d);


}
