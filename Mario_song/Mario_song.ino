#define PINREF 15
#define LEDPIN 2
#define CHANNEL 0
#include <pitches.h>

void tone (int melody, int duration){
  int pwm;
  float a = 0.65;
  ledcWriteTone(CHANNEL, melody);
  pwm = 0.65*melody;
  ledcWrite(1,pwm);
  Serial.println(pwm);
  delay(duration);
  return;
}

void noTone (){
  ledcWriteTone(CHANNEL, 0);
  return; 
}

int Mario_melody[] = {
  NOTE_E4, NOTE_E4, REST, NOTE_E4, 
  REST, NOTE_C4, NOTE_E4, REST,
  NOTE_G4, REST, REST, NOTE_G3, REST,
  
  NOTE_C4, REST, REST, NOTE_G3,
  REST, NOTE_E3, REST,
  REST, NOTE_A3, REST, NOTE_B3,   
  REST, NOTE_AS3, NOTE_A3, REST,
  
  NOTE_G3, NOTE_E4, NOTE_G4,
  NOTE_A4, REST, NOTE_F4, NOTE_G4, 
  REST, NOTE_E4, REST, NOTE_C4, 
  NOTE_D4, NOTE_B3, REST
};

int Mario_Notes[] = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 2, 4, 2, 2,
  
  4, 4, 4, 4,
  2, 4, 4,
  4, 4, 4, 4,  
  4, 4, 4, 4,
  
  4, 2, 4,
  4, 4, 4, 4,
  4, 4, 4, 4, 
  4, 4, 2
  };
  
const int num_elements_in_arr = sizeof(Mario_Notes)/sizeof(Mario_Notes[0]);

void setup() {
  Serial.begin(9600);
  ledcAttachPin(2,CHANNEL);
  ledcAttachPin(4,1);
  ledcSetup(CHANNEL,440, 12);
  ledcSetup(1,400, 8);
}

void loop() {
  
      // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < num_elements_in_arr; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 200/Mario_Notes[thisNote];
    tone(Mario_melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone();
  }
  
}
