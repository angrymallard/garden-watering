//Solar panel powers up the microcontroller when the sun rises. There is no battery.
//Program waits several hours for the sun to be directly overhead, then opens up to 3 solenoid valves.
//If the sun isn't overhead-ish, the panel can't provide enough energy to activate the valves fully. 

#include <avr/sleep.h>
// Utility macros
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC

int led0 = 0;  //green status LED
int switch1 = 1;  //module 1 with relay
int switch2 = 2;  //module 2 WITHOUT RELAY
int switch3 = 3;  //module 3 WITHOUT RELAY
int j = 0; //counting variable

void setup() {                
  pinMode(led0, OUTPUT);     
  pinMode(switch1, OUTPUT);     
  pinMode(switch2, OUTPUT);     
  pinMode(switch3, OUTPUT);     
  digitalWrite(led0, HIGH);  //turn on green status LED
  delay(5000);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void loop() {
  //initial delay to let the sun rise
  while (j < 28800) { //3600 sec/hour * 8 hours = 28800 sec
    delay(1000);
    j++;
  }
  j = 0;
  
  //turn on the first switch for three minutes
  digitalWrite(switch1, HIGH);
  while (j < 110) { //180 seconds = 3 minutes
    delay(1000);
    j++;
  }
  j = 0;
  digitalWrite(switch1, LOW);
  //turn on the second switch
  digitalWrite(switch2, HIGH);
  while (j < 180) { //180 seconds = 3 minutes
    delay(1000);
    j++;
  }
  j = 0;
  digitalWrite(switch2, LOW);
  //turn on the third switch
  digitalWrite(switch3, HIGH);
  while (j < 180) { //180 seconds = 3 minutes
    delay(1000);
    j++;
  }
  j = 0;
  digitalWrite(switch3, LOW);

  //blink the status LED to show the process is complete
  while(1) {
    digitalWrite(led0, LOW);
    delay(1000);
    digitalWrite(led0, HIGH);
    delay(1000);
  }
}

//put the microcontroller to sleep
void go_to_sleep() {
  digitalWrite(led0, LOW);
  digitalWrite(switch1, LOW);
  digitalWrite(switch2, LOW);
  digitalWrite(switch3, LOW);
  adc_disable();
  pinMode(led0, INPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  sleep_enable();
  sleep_cpu();
}
