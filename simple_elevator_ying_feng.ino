const int  LED1 = 8; 
const int  LED2 = 9;
const int  LED3 = 10;

#define INPUT_TRAVEL 7
int Button_Travel = 0; // the button can be toggled later
#define INPUT_SELECT 6
int Button_Select = 0; // the button can be toggled later

int timer = 100;
int ledCount = 3;
int ledPins[] = {LED1,LED2,LED3};

#define SOUND_PIN 2 // the pin for buzzer 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int tempi[] = {4, 8, 8, 4, 4, 4, 4, 4};

void setup() {
  Serial.begin(9600); // initial the serial port 
  pinMode(LED1, OUTPUT); // F0
  pinMode(LED2, OUTPUT); // F1
  pinMode(LED3, OUTPUT); // F2
  pinMode(SOUND_PIN, OUTPUT);
  pinMode(INPUT_TRAVEL, INPUT); // for travelling between floors
  pinMode(INPUT_SELECT, INPUT); // for stopping at each floor
}

void loop() {
  Button_Travel = digitalRead(INPUT_TRAVEL);
  Button_Select = digitalRead(INPUT_SELECT);
  
  if (Button_Travel == LOW && Button_Select == LOW) {         // the lift stops by F0 
    digitalWrite(LED1, HIGH); 
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    Serial.println("You are at the ground floor.");
    s1();
  }
  else if (Button_Travel == HIGH && Button_Select == LOW) {   // the lift stops by F1
    digitalWrite(LED1, LOW); 
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    Serial.println("You are at the first floor."); 
    s2();
  }
  else if (Button_Travel == HIGH && Button_Select == HIGH) {  // the lift stops by F2
    digitalWrite(LED1, LOW); 
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    Serial.println("You are at the second floor.");
    s3();
  }
  else if (Button_Travel == LOW && Button_Select == HIGH) {   // the lift travels between F0, F1 and F2
    Serial.println("The lift are traveling.");
    for (int thisPin = 0; thisPin < ledCount; thisPin++) {
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
    digitalWrite(ledPins[thisPin], LOW);
    }
    for (int thisPin = ledCount - 1; thisPin >= 0; thisPin--) {
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
    digitalWrite(ledPins[thisPin], LOW);
    }
  }
}


// the beeping sounds for each floor, no sound when travelling between floors
void s1() {
 if (Button_Travel == LOW && Button_Select == LOW) { 
    for (int thisNote = 0; thisNote < 3; thisNote++) {
      int tempo = 1000 /tempi[thisNote];
    tone(SOUND_PIN, melody[thisNote], tempo);
    int pauseBetweenNotes = tempo * 2;
    delay(pauseBetweenNotes);
    noTone(SOUND_PIN);
    }
 }
}

void s2() {
 if (Button_Travel == HIGH && Button_Select == LOW) { 
    for (int thisNote = 3; thisNote < 6; thisNote++) {
      int tempo = 1000 /tempi[thisNote];
    tone(SOUND_PIN, melody[thisNote], tempo);
    int pauseBetweenNotes = tempo * 2;
    delay(pauseBetweenNotes);
    noTone(SOUND_PIN);
    }
 }
}


void s3() {
 if (Button_Travel == HIGH && Button_Select == HIGH) { 
    for (int thisNote = 4; thisNote < 8; thisNote++) {
      int tempo = 1000 /tempi[thisNote];
    tone(SOUND_PIN, melody[thisNote], tempo);
    int pauseBetweenNotes = tempo * 2;
    delay(pauseBetweenNotes);
    noTone(SOUND_PIN);
    }
 }
}


