/*
  SparkFun Keypad Example Code
  by: Jim Lindblom
  SparkFun Electronics
  date: 4/26/11
  license: Creative Commons Share-Alike attribution v3.0
  
  edited by: chebe
  chebe.dreamwidth.org
  date: 13th October 2011
  
  Stripped down code to just detecting button presses. 
  Also added some extra checks to cut out false 
  left/right presses when pressing down.
  
  More complete version of this code can be found at
  http://chebe.dreamwidth.org/60887.html
  
  The circuit:
  SparkFun Keypad                Arduino
  -----------------------------------------
    Wire 1 (NC) ------------- No connection
   Wire 2 (LEDR) ----------------- D3
    Wire 3 (GND) ------------------GND
   Wire 4 (P5.1) ----------------- D5
   Wire 5 (P5.3) ----------------- D6
   Wire 6 (P5.2) ----------------- D7
*/


/* getButtonState() will return a uint8_t representing the status
  of the SparkFun button pad. The meaning of the return value is:
  0x01: Down
  0x02: Up
  0x04: Flame
  0x08: Right
  0x10: Left
*/
uint8_t getButtonState()
{
  // Initially set all buttons as inputs, and pull them up
  pinMode(p52, INPUT);
  digitalWrite(p52, HIGH);
  pinMode(p51, INPUT);
  digitalWrite(p51, HIGH);
  pinMode(p53, INPUT);
  digitalWrite(p53, HIGH);
  delay(5);
 
  // Read the d/u/flame buttons
  // When not pressed, reads 1
  // When pressed, reads 0
  if (!digitalRead(p53) && digitalRead(p52) && digitalRead(p51)) // 1,1,0
    return 0x01;  // Down
  if (!digitalRead(p52) && digitalRead(p51) && digitalRead(p53)) // 1,0,1
    return 0x02;  // Up
  if (!digitalRead(p51) && digitalRead(p52) && digitalRead(p53)) // 0,1,1
    return 0x04;  // Flame
  
  // Read right button
  pinMode(p52, OUTPUT);  // set p52 to output, set low
  digitalWrite(p52, LOW);
  delay(3); //debounce
  if (!digitalRead(p53) && digitalRead(p51) && !digitalRead(p52)) // 1,0,0
  { 
    delay(3); // experimental to debounce some downs being picked up as rights
    if (!digitalRead(p53) && digitalRead(p51) && !digitalRead(p52))
    {
      return 0x08;  // Right
    }
  }
  pinMode(p52, INPUT);  // set p52 back to input and pull-up
  digitalWrite(p52, HIGH);
  
  // Read left button
  pinMode(p51, OUTPUT);  // Set p51 to output and low
  digitalWrite(p51, LOW);
  delay(3); //debounce
  if (!digitalRead(p53) && digitalRead(p52) && !digitalRead(p51)) // 0,1,0
  {
    delay(3); // experimental to debounce some downs being picked up as lefts
    if (!digitalRead(p53) && digitalRead(p52) && !digitalRead(p51))
    {
      return 0x10;  // Left
    }
  }
  pinMode(p51, INPUT);  // Set p51 back to input and pull-up
  pinMode(p51, HIGH);
  
  return 0;
}

