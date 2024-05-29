









int i = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(1025000);
}








void loop() {
  // put your main code here, to run repeatedly:56
  long t0 = micros();
 // Serial1.print((char)(i+'A'));
  while(!Serial1.available());
  i++;
  char r = Serial1.read();
  t0 = micros() - t0;
Serial1.print(r);
if (i>26)
{
    i=0;
    //Serial1.print(r);
    
}

  
 /*if (r != (char)(i+'A'))
 {
    Serial.print("Error - ");
    Serial.print(r);
    Serial.print(" != ");
    Serial.println((char)(i+'A')); 
 }
  */
}
