#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int dt=10;
Servo servo;
int prev=0;
void setup() {

mlx.begin();
  
pinMode(TRIGGER_PIN,OUTPUT);
pinMode(ECHO_PIN,INPUT);
Serial.begin(9600);
servo.attach(10);
}

void loop() {

servo.write(0);

delay(50);

unsigned int uS = sonar.ping();

digitalWrite(ECHO_PIN,LOW);

Serial.print("Ping: ");

Serial.print(uS / US_ROUNDTRIP_CM);

Serial.println("cm");

//Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
Serial.print("\t Your Temperature = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");    
if (mlx.readObjectTempC()>40)
{
  Serial.println("You are ill, go to doctor");
}
Serial.println();

if((uS / US_ROUNDTRIP_CM)<10&&(uS / US_ROUNDTRIP_CM)>0&&uS<prev)
{
  servo.write(90);
  delay(1000);
  Serial.println("Your hand has been sanitised");
}
else
{
  Serial.println("Place your hand and remove after santising");
}
servo.write(0);
prev=uS;
Serial.println("---------");
Serial.println();
delay(2000);

}
