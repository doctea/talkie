#include "Display.h"

#include "Voice.hpp"
#define Envelope Voice
#include "GateInput.hpp"
#include "ParameterInput.hpp"


Voice voice = Voice();
AnalogGateInput gate = AnalogGateInput(A0, voice);

AnalogParameterInput param0 = AnalogParameterInput(A1, voice, (byte)0, 6);
AnalogParameterInput param1 = AnalogParameterInput(A2, voice, (byte)1, 6);

void setup() {
  Serial.begin(115200);
  Serial.println("starting setup..");
  setup_display();
  setup_voice();
  //tft.println("voice setup");
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
  Serial.println(F("did startup"));
  tft.println("did startup");
  delay(250);
}

void loop() {
  Serial.println(F("loop started"));
  
  param0.loop();
  param1.loop();
  gate.loop();
  
  voice.loop();

  static int counter = 0;
  if (counter%10000) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0,0);
  }
  tft.print("yo ");
  tft.println(counter);
  counter++;

  Serial.println("looped");
}
