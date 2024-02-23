/*
  This Code for educational purposes, was developed by MJRovai 
  based on information from:
  https://wiki.seeedstudio.com/grove_vision_ai_v2_software_support/

  Using the XIAO BLE SENSE to show inference result in its RGB LED
*/

#include <Seeed_Arduino_SSCMA.h>

SSCMA AI;

void setup()
{
    AI.begin();

    Serial.begin(115200);
    while (!Serial);
    Serial.println("Inferencing - Grove AI V2 / XIAO Sense with RGB LEDs");

    // Pins for the built-in RGB LEDs
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);

    // Ensure the LEDs are OFF by default.
    // Note: The RGB LEDs are ON when the pin is LOW, OFF when HIGH.
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
}

void loop()
{
    if (!AI.invoke())
    {
      Serial.println("\nInvoke Success");
      Serial.print("Latency [ms]: prepocess=");
      Serial.print(AI.perf().prepocess);
      Serial.print(", inference=");
      Serial.print(AI.perf().inference);
      Serial.print(", postpocess=");
      Serial.println(AI.perf().postprocess);

      int pred_index = AI.classes()[0].target;
      Serial.print("Result= Label: ");
      Serial.print(pred_index);
      Serial.print(", score=");
      Serial.println(AI.classes()[0].score);
      
      turn_on_leds(pred_index);      
    }
}

/**
 * @brief      turn_off_leds function - turn-off all RGB LEDs
 */
void turn_off_leds(){
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
}

/**
 * @brief      turn_on_leds function used to turn on the RGB LEDs
 * @param[in]  pred_index     
 *             label 0: [0] ==> Red ON
 *             label 1: [1] ==> Green ON 
 *             label 2: [2] ==> Blue ON
 *             label 3: [3] ==> ALL OFF
 */
void turn_on_leds(int pred_index) {
  switch (pred_index)
  {
    case 0:
      turn_off_leds();
      digitalWrite(LEDR, LOW);
      break;

    case 1:
      turn_off_leds();
      digitalWrite(LEDG, LOW);
      break;
    
    case 2:
      turn_off_leds();
      digitalWrite(LEDB, LOW);
      break;

    case 3:
      turn_off_leds();
      break;
  }
}
