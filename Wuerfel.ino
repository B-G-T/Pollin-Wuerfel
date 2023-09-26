#include <avr/sleep.h>

const byte VERZOEGERUNG = 10;

void setup() {
  
  pinMode(PB0, INPUT);// declaring button pin as input

  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  //Setzen der Register fuer Pin-Change-Interrupt Pin PB3
  //Loeschen des Global Interrupt Enable Bits (I) im Status Register (SREG)
  SREG &= 0x7F; //entspricht "cli();"
  //Setze des Pin Change Interrupt Enable Bit
  GIMSK |= (1 << PCIE);
  //Setzen des Pin Change Enable Mask Bit 0 (PCINT0)  ==> Pin PB0
  PCMSK |= (1 << PCINT0);
  //Setzen des Global Interrupt Enable Bits (I) im Status Register (SREG)
  SREG |= 0x80; //entspricht "sei();"
  
}



void loop() {

  byte rounds = 0;

  uint32_t x = 600000;
  while (digitalRead(PB0) == LOW) {
    rounds = 0;
    x--;
    if (x == 0) {
      digitalWrite(1, LOW);
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      
      gotoSleep();
    }
  }

  // randomSeed(micros()); // to increase randomness
  rounds++;

  digitalWrite(4, LOW);

  digitalWrite(1, HIGH);
  delay(VERZOEGERUNG);
  digitalWrite(1, LOW);
 
  digitalWrite(2, HIGH);
  delay(VERZOEGERUNG);
  digitalWrite(2, LOW);
 
  digitalWrite(3, HIGH);
  delay(VERZOEGERUNG);
  digitalWrite(3, LOW);
 
  digitalWrite(4, HIGH);
  delay(VERZOEGERUNG);
  digitalWrite(4, LOW);
 
  byte num;
  
  if (rounds == 5) {
            if (random(1, 101) > 66 ) num = 6;
  } else {
    num = random(1, 7);
  }

  digitalWrite(1, num > 1 ? HIGH : LOW);
  digitalWrite(3, num > 3 ? HIGH : LOW);
  digitalWrite(2, num == 6 ? HIGH : LOW);
  digitalWrite(4, num % 2 == 1 ? HIGH : LOW);

}

void gotoSleep()
{
  ADCSRA &= ~_BV(ADEN); //ADC ausschalten

  MCUCR |= (1 << SM1) & ~(1 << SM0); //Sleep Modus = Power Down
  MCUCR |= _BV(SE); //Sleep Enable setzen
  sleep_cpu(); //Schlafe ....
  MCUCR &= ~(1 << SE); //Sleep Disable setzen
}

//Interrupt Serviceroutine (Pin-Change-Interrupt)
ISR(PCINT0_vect)
{
}
