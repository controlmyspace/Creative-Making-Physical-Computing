// C++ code
//
void setup()
{
  pinMode(13, OUTPUT);//green light
  pinMode(12, OUTPUT);//yellow light
  pinMode(11, OUTPUT);//red light 
}

void loop()
{

  digitalWrite(13, HIGH); //GREEN
  delay(5000); // on for 5 seconds
  digitalWrite(13, LOW);
  delay(250); // off for 0.25 seconds
  
  digitalWrite(12, HIGH);//YELLOW
  delay(5000); // on for 5 seconds
  digitalWrite(12, LOW);
  delay(250); // off for 0.25 seconds
  
  digitalWrite(11, HIGH);//RED
  delay(5000); // on for 5 seconds
  digitalWrite(11, LOW);
  delay(250); // off for 0.25 seconds
  
  
}
