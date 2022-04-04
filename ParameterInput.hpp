char NEXT_PARAMETER_NAME = 'W';

class ParameterInput {
  public:
    int inputPin;
    Envelope *target;
    char name;
    bool debug = true;

    ParameterInput() {
      name = NEXT_PARAMETER_NAME++;
    }

    void setDebug() {
      debug = !debug;
    }

    virtual void read() {};
    void loop() {
      read();
    }
};

class DigitalParameterInput : public ParameterInput  {
  
  bool lastValue = false;

  public:
    using Callback = void (*)(bool);
    Callback callback;
    DigitalParameterInput(int in_inputPin, Callback in_callback) : ParameterInput() {
      inputPin = in_inputPin;
      callback = in_callback;
      pinMode(inputPin, INPUT);
    }
    DigitalParameterInput(int in_inputPin, Envelope &in_target) : ParameterInput() {
      inputPin = in_inputPin;
      target = &in_target;
    }
  
    void read() {
      // todo: debouncing
      bool currentValue = digitalRead(inputPin);
      if (currentValue != lastValue) {
        if (callback != NULL)
          callback(currentValue);
        if (target)
          target->setParamValueA(currentValue);
        lastValue = currentValue;
        //return currentValue;
      }
    }
};

class AnalogParameterInput : public ParameterInput {
  int inputPin;

  int lastValue = 0;
  byte envelope_number = 0xff;

  public:
    using Callback = void (*)(float);
    Callback callback;

    bool inverted = false;
    int sensitivity = 4;
      
    AnalogParameterInput(int in_inputPin, Callback in_callback, int in_sensitivity = 3) : ParameterInput() {
      inputPin = in_inputPin;
      callback = in_callback;
      sensitivity = in_sensitivity;
      pinMode(inputPin, INPUT);
    }
    AnalogParameterInput(int in_inputPin, Envelope &in_target, int in_sensitivity = 3) : ParameterInput() {
      inputPin = in_inputPin;
      target = &in_target;
      sensitivity = in_sensitivity;
      pinMode(inputPin, INPUT);
    }
    AnalogParameterInput(int in_inputPin, byte in_envelope_number, int in_sensitivity = 3) : ParameterInput() {
      inputPin = in_inputPin;
      envelope_number = in_envelope_number;
      sensitivity = in_sensitivity;
      pinMode(inputPin, INPUT);
    }

    void setInverted(bool invert = true) {
      inverted = invert;
    }

    void loop () {
      read();
    }

    float get_normal_value(int value) {
      if (inverted)
        return 1.0f - ((float)value / 1023.0f);
      else 
        return (float)value / 1023.0f;
    }

    void read() {
      int currentValue = analogRead(inputPin);
      if (abs(currentValue - lastValue) > sensitivity) {
        lastValue = currentValue;
        float normal = get_normal_value(currentValue);
        if (callback != NULL) {
          if (debug) {
            Serial.print(name);
            Serial.print(F(": calling callback("));
            Serial.print(normal);
            Serial.println(F(")"));
          }      
          callback(normal);
        }
        if (target) {
          if (debug) {
            Serial.print(name);
            Serial.print(F(": calling target setParamValueA("));
            Serial.print(normal);
            Serial.print(F(")"));
            if (inverted) Serial.print(F(" - inverted"));
            Serial.println();
          }
          target->setParamValueA(normal);
        }
        //if (envelope_number!=0xff)
          //envelopes[envelope_number]->setParamValueA(get_normal_value(currentValue));
        //return currentValue;
      }
    }
};
