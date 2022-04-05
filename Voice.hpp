// https://www.voltlog.com/pub/Iflytek-XFS5152CE_english_datasheet.pdf
// https://forum.arduino.cc/t/text-to-speech-project/303514/11

#include <SoftwareSerial.h>
SoftwareSerial ss(7, 8); // rx, tx
#define OUTPUT_SERIAL ss

void setup_voice() {
  //OUTPUT_SERIAL.begin(115200);

  char format[40];
  //sprintf(format, "[h2][m52][t%i][n0][s%i][v10][g2][p0]", 5, 5); //param_tone, param_speed);
  //Serial.print("Sending format ");
  //Serial.println(format);
  //voice.speak(buf);//OUTPUT_SERIAL.print(format);
}

class Voice {  
public: 

  Voice () {
      OUTPUT_SERIAL.begin(115200);
      char format[40];
      sprintf(format, "[h2][m52][t%i][n0][s%i][v10][g2][p0]hello", 5, 5); //param_tone, param_speed);
      Serial.print("Sending format ");
      Serial.println(format);
      speak(format);
      //voice.speak(buf);//OUTPUT_SERIAL.print(format);
  }

  byte param_speed = 3;
  byte param_tone = 5;

  char words[10][10] = {
    //"better", "faster", "harder", "danger", "fire"
    //"You're", "not ", "alone", ", Powers", ", ", "don't ", "think ", "you ", "are", ". ", "These ", "are ", "the ", "voices ", "of ", "time", ", ", "and ", "they're ", "all ", "saying ", "goodbye ", "to ", "you ", "... ", "every ", "particle ", "in ", "your ", "body", ", ", "every ", "grain ", "of ", "sand", "every ", "galaxy ", "carries ", "the ", "same ", "signature ", "... ", "you ", "know ", "what ", "the ", "time ", "is ";
  };

  char word[20];
  char *get_next_word() {
    static int pointer;
    static const char *words = "Deep Time: 1,000,000 mega-years. I saw the Milky Way, a wheeling carousel of fire, and Earth's remote descendants, countless races inhabiting every stellar system in the galaxy. The dark intervals between the stars were a continuously flickering field of light, a gigantic phosphorescent ocean, filled with the vibrating pulses of electromagnetic communication pathways. To cross the enormous voids between the stars they have progressively slowed their physiological time, first ten, then a hundred-fold, so accelerating stellar and galactic time. Space has become alive with transient swarms of comets and meteors, the constellations have begun to dislocate and shift, the slow majestic rotation of the universe itself is at last visible.";
    static const int len = strlen(words);

    int i = 0;
    for (i = 0 ; i < len ; i++) {
      word[i] = words[pointer+i];
      if (word[i]==' ' || word[i]=='\0') { //i+pointer>=len) { //strlen(words)) {
        pointer = pointer+i+1;
        word[i+1] = '\0';
        if (i+pointer>len)
          pointer = 0;
        Serial.println(word);
        return word[0];
      }
    }
    word[i] = '\0';
    pointer = 0;
    return word[0];
  }

  char *get_next_sentence() {
    static int pointer;
    static char *words = "Deep Time. 1,000,000 mega-years. I saw the Milky Way, a wheeling carousel of fire, and Earth's remote descendants, countless races inhabiting every stellar system in the galaxy. The dark intervals between the stars were a continuously flickering field of light, a gigantic phosphorescent ocean, filled with the vibrating pulses of electromagnetic communication pathways. To cross the enormous voids between the stars they have progressively slowed their physiological time, first ten, then a hundred-fold, so accelerating stellar and galactic time. Space has become alive with transient swarms of comets and meteors, the constellations have begun to dislocate and shift, the slow majestic rotation of the universe itself is at last visible. ";
    static const int len = strlen(words);

    words[len-1] = '\0';    // ensure that we end on a string termination.
    if (pointer>=len) pointer = 0;
    for (int i = 0 ; i < len-1 ; i++) {
      //if ((words[i+pointer]==',' && words[i+pointer+1]==' ') || words[i+pointer]=='.'  words[i+pointer]=='\0') {
      if(pointer+i==len-1 || words[pointer+i]=='\0' || (words[i+pointer]==' ' && (words[i+pointer-1]==',' || words[i+pointer-1]=='.'))) {
        //pointer+=i;
        words[i+pointer] = '\0';
        char *start = &words[pointer];
        Serial.println(start);
        pointer += i+1;
        return start;
      }
    }
  }

  void setParamValueA(float normal) {
    char buf[128];
    param_speed = 10 * normal;
    sprintf(buf, "[s%i]", param_speed);
    //OUTPUT_SERIAL.print(buf);
    //speak(buf);
  }
  void setParamValue(byte parameter_number, float normal) {
    char buf[128];
    if (parameter_number==0) {
      param_speed = 10 * normal;
      //sprintf(buf, "[s%i]", param_speed);
      //Serial.print(buf);
      //OUTPUT_SERIAL.print(buf);
      //speak(buf);
    } else if (parameter_number==1) {
      param_tone = 10 * normal;
      //sprintf(buf, "[t%i]", param_tone);
      //speak(buf);
      //Serial.print(buf);
      //OUTPUT_SERIAL.print(buf);
    }
  }
  

  void loop() {
    bool done = false;
    while ( OUTPUT_SERIAL.available() ) {
      char rc = OUTPUT_SERIAL.read();
      Serial.print("received: ");
      Serial.print(rc);
      Serial.print(" (");
      Serial.print((byte)rc);
      Serial.println(")");
      if ( rc == 0x4F ) {  
        done = true;
        speaking = false;
        break;
      }
    }
  }


  void cache_text(byte location, char* msg) {
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x0);
    OUTPUT_SERIAL.write(2 + strlen(msg));
    OUTPUT_SERIAL.write(0x31);
    //OUTPUT_SERIAL.write((byte)0x00);
    //OUTPUT_SERIAL.write((location << 4) | 0x00);
    OUTPUT_SERIAL.write(0b00110011);
    OUTPUT_SERIAL.write(msg);
    Serial.print ("cached ");
    Serial.println(msg);
  }

  void play_cache(byte location) {
    //send_text_command_cache_test_3();
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x0);
    OUTPUT_SERIAL.write(2); // + strlen(msg));
    OUTPUT_SERIAL.write(0x32);
    //OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(0b00110011);
    //OUTPUT_SERIAL.write((location << 4) | 0x00);
    //OUTPUT_SERIAL.write(msg);
  }

  void speak(char* msg) {
    speaking = true;
    //static char *format = "[h2][m52][t0][n0][s3][v10][g2][p0]";
    static char format[40];// = "[h2][m52][t%i][n0][s%i][v10][g2][p0]asdfasdf";
    /*sprintf(format, "[h2][m52][t%i][n0][s%i][v10][g2][p0]", param_tone, param_speed);
    Serial.print("Sending format ");
    Serial.println(format);*/
    sprintf(format, "[t%i][s%i]", param_tone, param_speed);
    OUTPUT_SERIAL.write(0xFD);
    OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(2 + strlen(msg) + strlen(format));
    OUTPUT_SERIAL.write(0x01);
    OUTPUT_SERIAL.write((byte)0x00);
    OUTPUT_SERIAL.write(format);
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

  bool speaking = false;
  void gate_on() {
    //speak("[x0][t6][v10][s6][m51][g2][h2][n1]Beat!");
    //speak("Beat![m55][t5][n2][s6]");
    //char buf[64];
    static byte count = 0;
    //sprintf( buf, "[m55][t5][n2][s6]Check %d. Battery is %d percent charged.", count, random(1, 100));
    //sprintf(buf, "%d", count++);
    if (count>sizeof(words)/10) count = 0;
    //speak(words[count++]);

    if (!speaking) {
      //get_next_word();
      //speak(word); //*get_next_word());
      speak(get_next_sentence());
      Serial.println("spoke");
    }
    //speak("Beat!");
    //speak(buf);
    //play_cache(count);
    //send_text_command_cache_test_5();
  }
  void gate_off() {
    //speak("[x0]");
  }
};
