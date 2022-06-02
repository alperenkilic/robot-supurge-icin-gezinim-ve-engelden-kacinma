int encoder_pin_1 = 7; // pulse output from the module
int encoder_pin_2 = 13; // pulse output from the module
unsigned int rpm_1; // rpm reading
unsigned int rpm_2; // rpm reading
volatile byte pulses_1; // number of pulses
volatile byte pulses_2; // number of pulses
unsigned long timeold;
// number of pulses per revolution
// based on your encoder disc
unsigned int pulsesperturn = 20;
void counter()
{
   //Update count
   pulses_1++;
   pulses_2++;
}
void setup()
{
   Serial.begin(9600);
   pinMode(encoder_pin_1, INPUT);
    pinMode(encoder_pin_2, INPUT);
   //Interrupt 0 is digital pin 2
   //Triggers on Falling Edge (change from HIGH to LOW)
   attachInterrupt(0, counter, FALLING);
   // Initialize
   pulses_1 = 0;
   pulses_2 = 0;
   rpm_1 = 0;
   rpm_2 = 0;
   timeold = 0;
}
void loop()
{
   if (millis() - timeold >= 1000) {
      //Don't process interrupts during calculations
      detachInterrupt(0);
      rpm_1 = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses_1;
      rpm_2 = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses_2;
      timeold = millis();
      pulses_1 = 0;
      pulses_2 = 0;
      Serial.print("RPM1 = ");
      Serial.println(rpm_1,DEC);
       Serial.print("RPM2 = ");
      Serial.println(rpm_2,DEC);     
      //Restart the interrupt processing
      attachInterrupt(0, counter, FALLING);
   }
} 
