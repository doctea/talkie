#include <SoftwareSerial.h>
SoftwareSerial ss(7, 8); // rx, tx
#define OUTPUT_SERIAL ss

void setup_voice() {
  OUTPUT_SERIAL.begin(115200);
  
}

class Voice {  
public: 

  void loop() {
    bool done = false;
    while ( OUTPUT_SERIAL.available() ) {
      char rc = OUTPUT_SERIAL.read();
      Serial.print("received: ");
      Serial.print(rc);
      Serial.print(" (");
      Serial.println((byte)rc);
      Serial.println(")");
      if ( rc == 0x4F ) {  
        done = true;
        break;
      }
    }
  }

  void send_text_command_cache_test_1() {
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(0x14);
    OUTPUT_SERIAL.write(0x31);
    //OUTPUT_SERIAL.write(0x03);
    OUTPUT_SERIAL.write(0b00110001);
    OUTPUT_SERIAL.write(0xB6);
    OUTPUT_SERIAL.write(0xCE);
    OUTPUT_SERIAL.write(0xBB);
    OUTPUT_SERIAL.write(0xBA);
    OUTPUT_SERIAL.write(0xB4);
    OUTPUT_SERIAL.write(0xE6);
    OUTPUT_SERIAL.write(0xBA);
    OUTPUT_SERIAL.write(0xF3);
    OUTPUT_SERIAL.write(0xD2);
    OUTPUT_SERIAL.write(0xBB);
    OUTPUT_SERIAL.write(0xC6);
    OUTPUT_SERIAL.write(0xF0);
    OUTPUT_SERIAL.write(0xB2);
    OUTPUT_SERIAL.write(0xA5);
    OUTPUT_SERIAL.write(0xB7);
    OUTPUT_SERIAL.write(0xC5);
    OUTPUT_SERIAL.write(0xA1);
    OUTPUT_SERIAL.write(0xA3);
  }

  void send_text_command_cache_test_2() {
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(0x12);
    OUTPUT_SERIAL.write(0x31);
    OUTPUT_SERIAL.write(0b00110000);
    OUTPUT_SERIAL.write(0xB4);
    OUTPUT_SERIAL.write(0xF2);
    OUTPUT_SERIAL.write(0xC2);
    OUTPUT_SERIAL.write(0xD2);
    OUTPUT_SERIAL.write(0xCB);
    OUTPUT_SERIAL.write(0xB3);
    OUTPUT_SERIAL.write(0xD0);
    OUTPUT_SERIAL.write(0xF2);
    OUTPUT_SERIAL.write(0xB5);
    OUTPUT_SERIAL.write(0xC4);
    OUTPUT_SERIAL.write(0xD2);
    OUTPUT_SERIAL.write(0xBB);
    OUTPUT_SERIAL.write(0xB6);
    OUTPUT_SERIAL.write(0xCE);
    OUTPUT_SERIAL.write(0xCE);
    OUTPUT_SERIAL.write(0xC4);
  }

  void send_text_command_cache_test_3() {
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(0x10);
    OUTPUT_SERIAL.write(0x31);
    //OUTPUT_SERIAL.write(0x03);
    OUTPUT_SERIAL.write(0b00010000);
    OUTPUT_SERIAL.write(0xB4);
    OUTPUT_SERIAL.write(0xCB);
    OUTPUT_SERIAL.write(0xB9);
    OUTPUT_SERIAL.write(0xA6);
    OUTPUT_SERIAL.write(0xC4);
    OUTPUT_SERIAL.write(0xDC);
    OUTPUT_SERIAL.write(0xBF);
    OUTPUT_SERIAL.write(0xC9);
    OUTPUT_SERIAL.write(0xD2);
    OUTPUT_SERIAL.write(0xD4);
    OUTPUT_SERIAL.write(0xBD);
    OUTPUT_SERIAL.write(0xAB);
    OUTPUT_SERIAL.write(0xB1);
    OUTPUT_SERIAL.write(0xBB);
  }


  void send_text_command_cache_test_4() {
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(0x16);
    OUTPUT_SERIAL.write(0x31);
    //OUTPUT_SERIAL.write(0x03);
    OUTPUT_SERIAL.write(0b00010000);
    OUTPUT_SERIAL.write(0xB1);
    OUTPUT_SERIAL.write(0xBE);
    OUTPUT_SERIAL.write(0xB0);
    OUTPUT_SERIAL.write(0xB4);
    OUTPUT_SERIAL.write(0xBF);
    OUTPUT_SERIAL.write(0xCD);
    OUTPUT_SERIAL.write(0xBB);
    OUTPUT_SERIAL.write(0xA7);
    OUTPUT_SERIAL.write(0xCF);
    OUTPUT_SERIAL.write(0xA3);
    OUTPUT_SERIAL.write(0xCD);
    OUTPUT_SERIAL.write(0xFB);
    OUTPUT_SERIAL.write(0xB5);
    OUTPUT_SERIAL.write(0xC4);
    OUTPUT_SERIAL.write(0xCB);
    OUTPUT_SERIAL.write(0xB7);
    OUTPUT_SERIAL.write(0xD0);
    OUTPUT_SERIAL.write(0xF2);
    OUTPUT_SERIAL.write(0xB7);
    OUTPUT_SERIAL.write(0xD6);
  }

  void send_text_command_cache_test_5() {
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(0x01);
    OUTPUT_SERIAL.write(0x32);
    //OUTPUT_SERIAL.write(0x03);
    //OUTPUT_SERIAL.write(0x01);
    OUTPUT_SERIAL.write(0b00010001);

    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(0x01);
    OUTPUT_SERIAL.write(0x32);
    //OUTPUT_SERIAL.write(0x03);
    //OUTPUT_SERIAL.write(0x01);
    OUTPUT_SERIAL.write(0b00110001);
    
  }
  

  void cache_text(char* msg) {
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x0);
    OUTPUT_SERIAL.write(2 + strlen(msg));
    OUTPUT_SERIAL.write(0x31);
    OUTPUT_SERIAL.write((byte)0x01);
    OUTPUT_SERIAL.write(msg);
    Serial.print ("cached ");
    Serial.println(msg);
  }

  void play_cache(int place) {
    send_text_command_cache_test_3();
    /*
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x0);
    //OUTPUT_SERIAL.write(2 + strlen(msg));
    OUTPUT_SERIAL.write(0x32);
    //OUTPUT_SERIAL.write((byte)0x0);
    //OUTPUT_SERIAL.write(msg);
    OUTPUT_SERIAL.write(place);*/
  }

  void speak(char* msg) {
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x0);
    OUTPUT_SERIAL.write(2 + strlen(msg));
    OUTPUT_SERIAL.write(0x01);
    OUTPUT_SERIAL.write((byte)0x0);
    OUTPUT_SERIAL.write(msg);
  }
  
  void waitForSpeech(unsigned long timeout = 20000) {
    unsigned long start = millis();
    bool done = false;
    while ( ! done && (millis() - start) < timeout ) {
      while ( OUTPUT_SERIAL.available() ) {
        char rc = OUTPUT_SERIAL.read();
        Serial.print("received: ");
        Serial.println(rc);
        if ( rc == 0x4F ) {  
          done = true;
          break;
        }
      }
    }
  }

  void gate_on() {
    //speak("[x0][t6][v10][s6][m51][g2][h2][n1]Beat!");
    //speak("[m55][t5][n2][s6]Beat!");
    char buf[64];
    static byte count = 1;
    //sprintf( buf, "[m55][t5][n2][s6]Check %d. Battery is %d percent charged.", count, random(1, 100));
    sprintf(buf, "%d", count++);
    
    if (count>4) count = 1;
    //speak("Beat!");
    //speak(buf);
    //play_cache(count);
    //send_text_command_cache_test_5();
    Serial.println("spoke");
  }
  void gate_off() {
    //speak("[x0]");
  }
};
