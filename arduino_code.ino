//Define geluidssensor, knoppen, LEDs en display pins
#define SOUND_SENSOR A0

#define BUTTON_GREEN 10
#define BUTTON_YELLOW 9
#define BUTTON_RED 8

#define BUTTON_PAUSE 7

#define LED_GREEN_1 25
#define LED_GREEN_2 27
#define LED_GREEN_3 29
#define LED_GREEN_4 31
#define LED_GREEN_5 33
#define LED_YELLOW_1 35
#define LED_YELLOW_2 37
#define LED_YELLOW_3 39
#define LED_YELLOW_4 41
#define LED_YELLOW_5 43
#define LED_RED_1 45
#define LED_RED_2 47
#define LED_RED_3 49
#define LED_RED_4 51
#define LED_RED_5 53

#define LED_GREEN_STOP 11
#define LED_YELLOW_STOP 12
#define LED_RED_STOP 13

#define segA 30
#define segB 32
#define segC 34
#define segD 36
#define segE 38
#define segF 40
#define segG 42
#define d1 22
#define d2 24
#define d3 26
#define d4 28


int buttonState = 0;
int telling = 0;
int puntenAantal = 0;

void setup(){
  Serial.begin(9600);

  //Zet de knoppen op input
  pinMode(BUTTON_GREEN, INPUT);
  pinMode(BUTTON_YELLOW, INPUT);
  pinMode(BUTTON_RED, INPUT);
  pinMode(BUTTON_PAUSE, INPUT);
  //Zet de geluidssensor op input
  pinMode(SOUND_SENSOR, INPUT);

  //Zet de feedback LEDs op output
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_GREEN_2, OUTPUT);
  pinMode(LED_GREEN_3, OUTPUT);
  pinMode(LED_GREEN_4, OUTPUT);
  pinMode(LED_GREEN_5, OUTPUT);
  pinMode(LED_YELLOW_1, OUTPUT);
  pinMode(LED_YELLOW_2, OUTPUT);
  pinMode(LED_YELLOW_3, OUTPUT);
  pinMode(LED_YELLOW_4, OUTPUT);
  pinMode(LED_YELLOW_5, OUTPUT);
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);
  pinMode(LED_RED_3, OUTPUT);
  pinMode(LED_RED_4, OUTPUT);
  pinMode(LED_RED_5, OUTPUT);
  
  //Zet de stoplicht LEDs op output
  pinMode(LED_GREEN_STOP, OUTPUT);
  pinMode(LED_YELLOW_STOP, OUTPUT);
  pinMode(LED_RED_STOP, OUTPUT);  

  //Zet alle segmenten op output
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
}

void loop(){
  //Controleer of er een knop is ingedrukt
  //Knipper anders de oranje LED
  while(buttonState != 0){
    //Check of er een knop wordt ingedrukt
    checkButtons();
     
    //Value geeft de waarde van de sensor terug.
    //Value kan omgezet worden in dB maar is voor dit project niet nodig.
    int value;
    value = analogRead(SOUND_SENSOR);

    //Zet de feedback LEDs aan op basis van de waarde van de geluidssensor
    feedbackLED(value, buttonState);

    /*
     * Controleer of het geluid onder de verplichte waarde zit
     * Als dit zo is komt er 1 punt bij de telling
     * Als de telling gelijk is aan 100 (30 seconden op of onder de juiste waarde)
     * voeg dan een punt toe aan het totaal puntenAantal
     * Zet de 7 segment aan op het punten aantal
     */
    telling += checkCorrectheid(value, buttonState);
    if(telling == 100){
      telling = 0;
      puntenAantal += 10;
    }
    changeDisplayNumbers(puntenAantal);
  }
  checkButtons();
  
  for(int i = 25; i < 55; i = i + 2){
    digitalWrite(i, LOW);
  }

  digitalWrite(LED_YELLOW_STOP, HIGH);
  delay(1200);
  digitalWrite(LED_YELLOW_STOP, LOW);
  delay(1200);
  
}

void checkButtons(){
  //Controleer of er een knop ingedrukt wordt
  //Zet het stoplicht LED aan op basis van de knop die ingedrukt wordt
  if(digitalRead(BUTTON_GREEN) == HIGH){  //Groene knop is ingedrukt
    buttonState = 3;
    digitalWrite(LED_GREEN_STOP, HIGH);
    digitalWrite(LED_YELLOW_STOP, LOW);
    digitalWrite(LED_RED_STOP, LOW);
  }else if(digitalRead(BUTTON_YELLOW) == HIGH){ //Gele knop is ingedrukt
    buttonState = 2;
    digitalWrite(LED_GREEN_STOP, LOW);
    digitalWrite(LED_YELLOW_STOP, HIGH);
    digitalWrite(LED_RED_STOP, LOW);
  }else if(digitalRead(BUTTON_RED) == HIGH){ //Rode knop is ingedrukt
    buttonState = 1;
    digitalWrite(LED_GREEN_STOP, LOW);
    digitalWrite(LED_YELLOW_STOP, LOW);
    digitalWrite(LED_RED_STOP, HIGH);
  }

  if(digitalRead(BUTTON_PAUSE) == HIGH){
    //Als de pauzeknop in wordt gedrukt, zet dan het pauzeprogramma aan.
    //Dit betekent: alle LEDs uit en de oranje LED vervolgens laten knipperen
    buttonState = 0;
    digitalWrite(LED_GREEN_STOP, LOW);
    digitalWrite(LED_YELLOW_STOP, LOW);
    digitalWrite(LED_RED_STOP, LOW);
  }
}

int checkCorrectheid(int value, int state){
  if(state = 1 && value <= 9){
    return 1;
  }else if(state = 2 && value <= 16){
    return 1;
  }else if(state = 3 && value <= 50){
    return 1;
  }else{
    return 0;
  }
}

void feedbackLED(int waarde, int state){
  //Zet alle feedback LEDs uit
  for(int i = 25; i < 55; i = i + 2){
    digitalWrite(i, LOW);
  }

  /*Controleer de waarde en zet de LEDs aan op basis van deze waarde
  * Als de rode knop is ingedrukt mag er niet gepraat worden.
  * Met een waarde onder de 9 is het goed, boven de 9 is te hard.
   */
  if(state == 1){
    //Groene LEDs  
    if(waarde > 3){
      digitalWrite(LED_GREEN_1, HIGH);
      digitalWrite(LED_GREEN_2, HIGH);
    }if(waarde > 5){
      digitalWrite(LED_GREEN_3, HIGH);
    }if(waarde > 7){
      digitalWrite(LED_GREEN_4, HIGH);
    }if(waarde > 8){
      digitalWrite(LED_GREEN_5, HIGH);
    }
  
    //Gele LEDs
    if(waarde > 10){
      digitalWrite(LED_YELLOW_1, HIGH);
      digitalWrite(LED_YELLOW_2, HIGH);
    }if(waarde > 11){
      digitalWrite(LED_YELLOW_3, HIGH);
      digitalWrite(LED_YELLOW_4, HIGH);
    }if(waarde > 12){
      digitalWrite(LED_YELLOW_5, HIGH);
    }
  
    //Rode LEDs
    if(waarde > 13){
      digitalWrite(LED_RED_1, HIGH);
    }if(waarde > 16){
      digitalWrite(LED_RED_2, HIGH);
    }if(waarde > 21){
      digitalWrite(LED_RED_3, HIGH);
    }if(waarde > 27){
      digitalWrite(LED_RED_4, HIGH);
    }if(waarde > 34){
      digitalWrite(LED_RED_5, HIGH);
    }  
  }
  
  /*Controleer de waarde en zet de LEDs aan op basis van deze waarde
  * Als de gele knop is ingedrukt mag er zacht overlegd worden.
  * Met een waarde onder de 9 is het goed, boven de 9 is te hard.
  */
  if(state == 2){
    //Groene LEDs  
    if(waarde > 3){
      digitalWrite(LED_GREEN_1, HIGH);
    }if(waarde > 6){
      digitalWrite(LED_GREEN_2, HIGH);
    }if(waarde > 10){
      digitalWrite(LED_GREEN_3, HIGH);
    }if(waarde > 12){
      digitalWrite(LED_GREEN_4, HIGH);
    }if(waarde > 16){
      digitalWrite(LED_GREEN_5, HIGH);
    }
  
    //Gele LEDs
    if(waarde > 17){
      digitalWrite(LED_YELLOW_1, HIGH);
      digitalWrite(LED_YELLOW_2, HIGH);
    }if(waarde > 19){
      digitalWrite(LED_YELLOW_3, HIGH);
      digitalWrite(LED_YELLOW_4, HIGH);
    }if(waarde > 21){
      digitalWrite(LED_YELLOW_5, HIGH);
    }
  
    //Rode LEDs
    if(waarde > 22){
      digitalWrite(LED_RED_1, HIGH);
    }if(waarde > 27){
      digitalWrite(LED_RED_2, HIGH);
    }if(waarde > 33){
      digitalWrite(LED_RED_3, HIGH);
    }if(waarde > 40){
      digitalWrite(LED_RED_4, HIGH);
    }if(waarde > 48){
      digitalWrite(LED_RED_5, HIGH);
    }  
  }

  /*Controleer de waarde en zet de LEDs aan op basis van deze waarde
  * Als de groene knop is ingedrukt mag er  gepraat worden.
  * Met een waarde onder de 50 is het goed, boven de 50 is te hard.
  */
  if(state == 3){
    //Groene LEDs  
    if(waarde > 3){
      digitalWrite(LED_GREEN_1, HIGH);
    }if(waarde > 13){
      digitalWrite(LED_GREEN_2, HIGH);
    }if(waarde > 23){
      digitalWrite(LED_GREEN_3, HIGH);
    }if(waarde > 33){
      digitalWrite(LED_GREEN_4, HIGH);
    }if(waarde > 43){
      digitalWrite(LED_GREEN_5, HIGH);
    }
  
    //Gele LEDs
    if(waarde > 50){
      digitalWrite(LED_YELLOW_1, HIGH);
      digitalWrite(LED_YELLOW_2, HIGH);
    }if(waarde > 55){
      digitalWrite(LED_YELLOW_3, HIGH);
      digitalWrite(LED_YELLOW_4, HIGH);
    }if(waarde > 60){
      digitalWrite(LED_YELLOW_5, HIGH);
    }
  
    //Rode LEDs
    if(waarde > 62){
      digitalWrite(LED_RED_1, HIGH);
    }if(waarde > 65){
      digitalWrite(LED_RED_2, HIGH);
    }if(waarde > 69){
      digitalWrite(LED_RED_3, HIGH);
    }if(waarde > 74){
      digitalWrite(LED_RED_4, HIGH);
    }if(waarde > 80){
      digitalWrite(LED_RED_5, HIGH);
    }  
  }
}

void changeDisplayNumbers(int number){
  int a = 0;
  int b = 0;
  int c = 0;
  int d = 0;
  
  //Alle getallen moeten gecontroleerd worden
  if(number < 10){
    d = number;
  }else if(number >= 10 && number < 100){
    c = number / 10;
  }else if(number >= 100 && number < 1000){
    b = number / 100;
    c = (number % 100) / 10;
  }else{
    a = number / 1000;
    b = (number % 1000) / 100;
    c = ((number % 1000) % 100) / 10;
  }
  displayNumber(a, b, c, d);
}

void displayNumber(int a,int b,int c,int d){
    writeDisplay(1,a);
    writeDisplay(2,b);
    writeDisplay(3,c);
    writeDisplay(4,d);
}

void writeDisplay(int d,int l){
  switch (d) {
    case 0: digitalWrite(d1, LOW); //case 0 - All ON
            digitalWrite(d2, LOW);
            digitalWrite(d3, LOW);
            digitalWrite(d4, LOW);
            break;
    case 1: digitalWrite(d1, LOW);//case 1 - Digit Number 1
            digitalWrite(d2, HIGH);
            digitalWrite(d3, HIGH);
            digitalWrite(d4, HIGH);
            break;
    case 2: digitalWrite(d1, HIGH);//case 1 - Digit Number 2
            digitalWrite(d2, LOW);
            digitalWrite(d3, HIGH);
            digitalWrite(d4, HIGH);
            break;
    case 3: digitalWrite(d1, HIGH);//case 1 - Digit Number 3
            digitalWrite(d2, HIGH);
            digitalWrite(d3, LOW);
            digitalWrite(d4, HIGH);
            break;
    case 4: digitalWrite(d1, HIGH);//case 1 - Digit Number 4
            digitalWrite(d2, HIGH);
            digitalWrite(d3, HIGH);
            digitalWrite(d4, LOW);
            break;
  }

  switch (l){
    case 0: 
      zero();
      break;
    case 1: 
      one();
      break;
    case 2: 
      two();
      break;
    case 3:
      three();
      break;
    case 4: 
      four();
      break;
    case 5: 
      five();
      break;
    case 6: 
      six();
      break;
    case 7: 
      seven();
      break;
    case 8: 
      eight();
      break;
    case 9: 
      nine();
      break;
  }
  delayMicroseconds(5000);
}

void zero(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);

}
void one(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void two(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}
void three(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}
void four(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
void five(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
void six(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
void seven(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}
void eight(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
void nine(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
