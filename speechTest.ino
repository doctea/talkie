#include "Voice.hpp"
#define Envelope Voice
#include "GateInput.hpp"
#include "ParameterInput.hpp"

Voice voice = Voice();
AnalogGateInput gate = AnalogGateInput(A0, voice);

AnalogParameterInput param = AnalogParameterInput(A1, voice);

void setup() {
  Serial.begin(115200);
  setup_voice();
  //voice.cache_text("this is a test of trying to cache some speech i wonder if it is going to work?");
  /*voice.send_text_command_cache_test_1();
  delay(250);
  voice.send_text_command_cache_test_2();
  delay(250);
  voice.send_text_command_cache_test_3();
  delay(250);
  voice.send_text_command_cache_test_4();
  delay(250);
  voice.send_text_command_cache_test_5();*/

  voice.cache_text(0, "[x0][t6][v10][s6][m51][g2][h2][n1]Hello!");
  voice.cache_text(1, "[x0][t6][v10][s6][m51][g2][h2][n1]BEAT!");
  voice.cache_text(2, "[x0][t6][v10][s6][m51][g2][h2][n1]BOOSH!");
  voice.cache_text(3, "[x0][t6][v10][s6][m51][g2][h2][n1]FAP!");
  
  //voice.speak("[x0][t6][v10][s6][m51][g2][h2][n1]Hello! I force 2d is the greatest.");
  
  //unused();
  Serial.println("did startup");
  delay(2500);
}

void loop() {
  param.loop();
  gate.loop();

  voice.loop();
  //Serial.println("looped");
}


void unused() {
  char buf[64];

  voice.speak("[x0][t6][v5][s6][m51][g2][h2][n1]Hello! I force 2d is the greatest.");
  Serial.println("spoke");
  voice.waitForSpeech();

  /*for (int i = 101; i < 126; i++) { // message tones
    sprintf(buf, "[x1]sound%d", i);
    speak(buf);
    waitForSpeech();  
  }
  for (int i = 201; i < 226; i++) { // ring tones
    sprintf(buf, "[x1]sound%d", i);
    speak(buf);
    waitForSpeech();  
  }
  for (int i = 301; i < 331; i++) { // alarm tones
    sprintf(buf, "[x1]sound%d", i);
    speak(buf);
    waitForSpeech();
  }*/

  int count = 1;
  while ( true ) {
    sprintf( buf, "[m55][t5][n2][s6]Check %d. Battery is %d percent charged.", count, random(1, 100));
    voice.speak(buf);
    voice.waitForSpeech();
    if ( count++ % 10 == 0 ) {
      voice.speak("[s0]I'm feeling sleepy");
      voice.waitForSpeech();
    }
    delay(1000);
    Serial.println("innerlooped");
  }
}
