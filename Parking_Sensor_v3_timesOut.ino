//Pin def for ultrasonic sensor connections
const int trigPin = 2;    // Trigger pin of the ultrasonic sensor
const int echoPin = 3;    // Echo pin of the ultrasonic sensor

//Pin def for the LEDs
const int greenLedPin = 8;   // Green LED pin
const int yellowLedPin = 9;  // Yellow LED pin
const int redLedPin = 10;     // Red LED pin

//Distance threshold def 
const int greenThreshold = 100;   // Greater than 1 meter (in cm)
const int yellowThreshold = 100;  // Less than 1 meter (in cm)
const int redThreshold = 25;      // At or less than 20cm (in cm)
const int catchThreshold = 200;
int parked = 0;
int parkConfirmed = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance_cm = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if (parked == 0)
  {
     //led trigger based on measured distance
     if (distance_cm > catchThreshold) //NO CAR
     {
      digitalWrite(greenLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(redLedPin, LOW);
      parkConfirmed = 0;
     } 
     else if (distance_cm > redThreshold && distance_cm < greenThreshold) //BRAKE
     {
      digitalWrite(greenLedPin, LOW);
      digitalWrite(yellowLedPin, HIGH);
      digitalWrite(redLedPin, LOW);
      parkConfirmed;
    } 
    else if (distance_cm > greenThreshold && distance_cm < catchThreshold) //FAR
    {
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(redLedPin, LOW); 
      parkConfirmed = 0;
    } 
    else if (distance_cm <= redThreshold) //PAARKED 
    {
      digitalWrite(greenLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(redLedPin, HIGH);
      parkConfirmed++;
      if (parkConfirmed == 500)
      {
        parked = 1;
      }
    }
  }
  else if (parked == 1)
  {
      digitalWrite(greenLedPin, LOW);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(redLedPin, LOW);
      delay(10000);
      parkConfirmed = 0;
      if(distance_cm > catchThreshold) //make catchThresh. 100 foe debug
      {
        parked = 0;
      }
  }

  Serial.print("parked: ");
  Serial.println(parked);
  Serial.print("parkConfired: ");
  Serial.println(parkConfirmed);
  delay(100); //rapid read prevention
}
