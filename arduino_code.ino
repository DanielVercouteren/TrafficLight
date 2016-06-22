#define SOUND_SENSOR A0

#define BUTTON_GREEN 8
#define BUTTON_YELLOW 9
#define BUTTON_RED 10

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

#define LED_GREEN_STOP 22
#define LED_YELLOW_STOP 24
#define LED_RED_STOP 26

int buttonState = 0;
int telling = 0;
int puntenAantal = 0;

void setup(){
  Serial.begin(9600);

  //Zet de knoppen op input
  pinMode(BUTTON_GREEN, INPUT);
  pinMode(BUTTON_YELLOW, INPUT);
  pinMode(BUTTON_RED, INPUT);
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
    feedbackLED(value);

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
      puntenAantal += 1;
    }
    sevenSegment(puntenAantal);     
    delay(300);
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
}

int checkCorrectheid(int value, int state){
  int punten = 0;
  
  
  if(state = 0){
    //Geen button ingedrukt
    Serial.println("Geen button is ingedrukt");
  }else if(state = 1){
    //Rode button ingedrukt, max volume is 8
    if(value <= 8){
      Serial.println("Volume zit onder de max.");
      punten += 1;
    }else{
      Serial.println("Volume zit boven de max.");
    }
  }else if(state = 2){
    //Oranje button is ingedrukt, max volume is 14
    if(value <= 14){
      Serial.println("Volume zit onder de max.");
      punten += 1;
    }else{
      Serial.println("Volume zit boven de max");
    }
  }else if(state = 3){
    //Rode button is ingedrukt, max volume is 50
    if(value <= 50){
      Serial.println("Volume zit onder de max.");
      punten += 1;
    }else{
      Serial.println("Volume zit boven de max!");
    }
  }
  return punten;
}

void feedbackLED(int waarde){
  //Zet alle feedback LEDs uit
  for(int i = 25; i < 55; i = i + 2){
    digitalWrite(i, LOW);
  }

  //Controleer de waarde en zet de LEDs aan op basis van deze waarde

  //Groene LEDs
  if(waarde > 5){
    digitalWrite(LED_GREEN_1, HIGH);
    digitalWrite(LED_GREEN_2, HIGH);
  }if(waarde > 6){
    digitalWrite(LED_GREEN_3, HIGH);
  }if(waarde > 7){
    digitalWrite(LED_GREEN_4, HIGH);
  }if(waarde > 8){
    digitalWrite(LED_GREEN_5, HIGH);
  }

  //Gele LEDs
  if(waarde > 9){
    digitalWrite(LED_YELLOW_1, HIGH);
  }if(waarde > 11){
    digitalWrite(LED_YELLOW_2, HIGH);
  }if(waarde > 13){
    digitalWrite(LED_YELLOW_3, HIGH);
  }if(waarde > 15){
    digitalWrite(LED_YELLOW_4, HIGH);
  }if(waarde > 16){
    digitalWrite(LED_YELLOW_5, HIGH);
  }

  //Rode LEDs
  if(waarde > 20){
    digitalWrite(LED_RED_1, HIGH);
  }if(waarde > 28){
    digitalWrite(LED_RED_2, HIGH);
  }if(waarde > 37){
    digitalWrite(LED_RED_3, HIGH);
  }if(waarde > 47){
    digitalWrite(LED_RED_4, HIGH);
  }if(waarde > 58){
    digitalWrite(LED_RED_5, HIGH);
  }  
}

void sevenSegment(int punten){
  //Lol doe nog maar even niks
}

