#include "riot_arduino_uno.h"

riot_arduino_uno_sinks* riot_arduino_uno_sinks_create() {
  riot_arduino_uno_sinks *sinks = xmalloc(sizeof(riot_arduino_uno_sinks));
  return sinks;
}

riot_arduino_uno_sources* riot_arduino_uno_sources_create() {
  riot_arduino_uno_sources *sources = xmalloc(sizeof(riot_arduino_uno_sources));
  return sources;
};

/**
  On the Arduino board, digital pins are also used
  for the analog output (software PWM).  Analog input
  pins are a separate set. We use these pin numbers when
  referring to input/output pins. We can later try to make
  use of arduino.h here

  ATMEL ATMEGA8 & 168 / ARDUINO

                    +-\/-+
              PC6  1|    |28  PC5 (AI 5)
        (D 0) PD0  2|    |27  PC4 (AI 4)
        (D 1) PD1  3|    |26  PC3 (AI 3)
        (D 2) PD2  4|    |25  PC2 (AI 2)
   PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
        (D 4) PD4  6|    |23  PC0 (AI 0)
              VCC  7|    |22  GND
              GND  8|    |21  AREF
              PB6  9|    |20  AVCC
              PB7 10|    |19  PB5 (D 13)
   PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
   PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
        (D 7) PD7 13|    |16  PB2 (D 10) PWM
        (D 8) PB0 14|    |15  PB1 (D 9) PWM
                    +----+

  (PWM+ indicates the additional PWM pins on the ATmega168.)
*/
static const uint8_t D0 = 0;
static const uint8_t D1 = 1;
static const uint8_t D2 = 2;
static const uint8_t D3 = 3;
static const uint8_t D4 = 4;
static const uint8_t D5 = 5;
static const uint8_t D6 = 6;
static const uint8_t D7 = 7;
static const uint8_t D8 = 8;
static const uint8_t D9 = 9;
static const uint8_t D10 = 10;
static const uint8_t D11 = 11;
static const uint8_t D12 = 12;
static const uint8_t D13 = 13;
// Analog pins A0 to A5/A7 are already declared in Arduino.h

byte riot_arduino_uno_write_to_D0(byte value) {
  pinMode(D0, OUTPUT);
  digitalWrite(D0, value);
  return 0;
}
byte riot_arduino_uno_write_to_D1(byte value) {
  pinMode(D1, OUTPUT);
  digitalWrite(D1, value);
  return 0;
}
byte riot_arduino_uno_write_to_D2(byte value) {
  pinMode(D2, OUTPUT);
  digitalWrite(D2, value);
  return 0;
}
byte riot_arduino_uno_write_to_D3(byte value) {
  pinMode(D3, OUTPUT);
  digitalWrite(D3, value);
  return 0;
}
byte riot_arduino_uno_write_to_D4(byte value) {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, value);
  return 0;
}
byte riot_arduino_uno_write_to_D5(byte value) {
  pinMode(D5, OUTPUT);
  digitalWrite(D5, value);
  return 0;
}
byte riot_arduino_uno_write_to_D6(byte value) {
  pinMode(D6, OUTPUT);
  digitalWrite(D6, value);
  return 0;
}
byte riot_arduino_uno_write_to_D7(byte value) {
  pinMode(D7, OUTPUT);
  digitalWrite(D7, value);
  return 0;
}
byte riot_arduino_uno_write_to_D8(byte value) {
  pinMode(D8, OUTPUT);
  digitalWrite(D8, value);
  return 0;
}
byte riot_arduino_uno_write_to_D9(byte value) {
  pinMode(D9, OUTPUT);
  digitalWrite(D9, value);
  return 0;
}
byte riot_arduino_uno_write_to_D10(byte value) {
  pinMode(D10, OUTPUT);
  digitalWrite(D10, value);
  return 0;
}
byte riot_arduino_uno_write_to_D11(byte value) {
  pinMode(D11, OUTPUT);
  digitalWrite(D11, value);
  return 0;
}
byte riot_arduino_uno_write_to_D12(byte value) {
  pinMode(D12, OUTPUT);
  digitalWrite(D12, value);
  return 0;
}
byte riot_arduino_uno_write_to_D13(byte value) {
  pinMode(D13, OUTPUT);
  digitalWrite(D13, value);
  return 0;
}
byte riot_arduino_uno_write_to_LED(byte value) {
  pinMode(D13, OUTPUT);
  digitalWrite(D13, value);
  return 0;
}
byte riot_arduino_uno_write_to_A0(byte value) {
  pinMode(A0, OUTPUT);
  digitalWrite(A0, value);
  return 0;
}
byte riot_arduino_uno_write_to_A1(byte value) {
  pinMode(A1, OUTPUT);
  digitalWrite(A1, value);
  return 0;
}
byte riot_arduino_uno_write_to_A2(byte value) {
  pinMode(A2, OUTPUT);
  digitalWrite(A2, value);
  return 0;
}
byte riot_arduino_uno_write_to_A3(byte value) {
  pinMode(A3, OUTPUT);
  digitalWrite(A3, value);
  return 0;
}
byte riot_arduino_uno_write_to_A4(byte value) {
  pinMode(A4, OUTPUT);
  digitalWrite(A4, value);
  return 0;
}
byte riot_arduino_uno_write_to_A5(byte value) {
  pinMode(A5, OUTPUT);
  digitalWrite(A5, value);
  return 0;
}

/**
  We map the output streams in the sinks struct to the board's
  outputs here. For simplicity, we write all outputs as bytes for
  now, later we can use bool for digital and 0-255 for analog/pwm.
*/
void riot_arduino_uno_map_sinks_to_write_outputs(riot_arduino_uno_sinks *sinks) {
  if(sinks->D0 != NULL) {
    stream_of_byte_map(sinks->D0, riot_arduino_uno_write_to_D0);
  }
  if(sinks->D1 != NULL) {
    stream_of_byte_map(sinks->D1, riot_arduino_uno_write_to_D1);
  }
  if(sinks->D2 != NULL) {
    stream_of_byte_map(sinks->D2, riot_arduino_uno_write_to_D2);
  }
  if(sinks->D3 != NULL) {
    stream_of_byte_map(sinks->D3, riot_arduino_uno_write_to_D3);
  }
  if(sinks->D4 != NULL) {
    stream_of_byte_map(sinks->D4, riot_arduino_uno_write_to_D4);
  }
  if(sinks->D5 != NULL) {
    stream_of_byte_map(sinks->D5, riot_arduino_uno_write_to_D5);
  }
  if(sinks->D6 != NULL) {
    stream_of_byte_map(sinks->D6, riot_arduino_uno_write_to_D6);
  }
  if(sinks->D7 != NULL) {
    stream_of_byte_map(sinks->D7, riot_arduino_uno_write_to_D7);
  }
  if(sinks->D8 != NULL) {
    stream_of_byte_map(sinks->D8, riot_arduino_uno_write_to_D8);
  }
  if(sinks->D9 != NULL) {
    stream_of_byte_map(sinks->D9, riot_arduino_uno_write_to_D9);
  }
  if(sinks->D10 != NULL) {
    stream_of_byte_map(sinks->D10, riot_arduino_uno_write_to_D10);
  }
  if(sinks->D11 != NULL) {
    stream_of_byte_map(sinks->D11, riot_arduino_uno_write_to_D11);
  }
  if(sinks->D12 != NULL) {
    stream_of_byte_map(sinks->D12, riot_arduino_uno_write_to_D12);
  }
  if(sinks->D13 != NULL) {
    stream_of_byte_map(sinks->D13, riot_arduino_uno_write_to_D13);
  }
  if(sinks->LED != NULL) {
    stream_of_byte_map(sinks->LED, riot_arduino_uno_write_to_LED);
  }
  if(sinks->A0 != NULL) {
    stream_of_byte_map(sinks->A0, riot_arduino_uno_write_to_A0);
  }
  if(sinks->A1 != NULL) {
    stream_of_byte_map(sinks->A1, riot_arduino_uno_write_to_A1);
  }
  if(sinks->A2 != NULL) {
    stream_of_byte_map(sinks->A2, riot_arduino_uno_write_to_A2);
  }
  if(sinks->A3 != NULL) {
    stream_of_byte_map(sinks->A3, riot_arduino_uno_write_to_A3);
  }
  if(sinks->A4 != NULL) {
    stream_of_byte_map(sinks->A4, riot_arduino_uno_write_to_A4);
  }
  if(sinks->A5 != NULL) {
    stream_of_byte_map(sinks->A5, riot_arduino_uno_write_to_A5);
  }
}

/**
  We read the pins and manually push a next value to the individual
  streams in the sources struct.
*/
void riot_arduino_uno_read_inputs(riot_arduino_uno_sources *sources) {
  pinMode(D0, INPUT);
  sources->D0->next(sources->D0, digitalRead(D0));
  pinMode(D1, INPUT);
  sources->D1->next(sources->D1, digitalRead(D1));
  pinMode(D2, INPUT);
  sources->D2->next(sources->D2, digitalRead(D2));
  pinMode(D3, INPUT);
  sources->D3->next(sources->D3, digitalRead(D3));
  pinMode(D4, INPUT);
  sources->D4->next(sources->D4, digitalRead(D4));
  pinMode(D5, INPUT);
  sources->D5->next(sources->D5, digitalRead(D5));
  pinMode(D6, INPUT);
  sources->D6->next(sources->D6, digitalRead(D6));
  pinMode(D7, INPUT);
  sources->D7->next(sources->D7, digitalRead(D7));
  pinMode(D8, INPUT);
  sources->D8->next(sources->D8, digitalRead(D8));
  pinMode(D9, INPUT);
  sources->D9->next(sources->D9, digitalRead(D9));
  pinMode(D10, INPUT);
  sources->D10->next(sources->D10, digitalRead(D10));
  pinMode(D11, INPUT);
  sources->D11->next(sources->D11, digitalRead(D11));
  pinMode(D12, INPUT);
  sources->D12->next(sources->D12, digitalRead(D12));
  pinMode(D13, INPUT);
  sources->D13->next(sources->D13, digitalRead(D13));
  /**
    The following are diabled, because stream_of_unit16_t is not
    available in the base stream library yet. Hence we are not able
    to use the 10-bit resolution analog inputs as of now.
  */
  // pinMode(A0, INPUT);
  // sources->A0->next(sources->A0, analogRead(A0));
  // pinMode(A1, INPUT);
  // sources->A1->next(sources->A1, analogRead(A1));
  // pinMode(A2, INPUT);
  // sources->A2->next(sources->A2, analogRead(A2));
  // pinMode(A3, INPUT);
  // sources->A3->next(sources->A3, analogRead(A3));
  // pinMode(A4, INPUT);
  // sources->A4->next(sources->A4, analogRead(A4));
  // pinMode(A5, INPUT);
  // sources->A5->next(sources->A5, analogRead(A5));
}

/**
  Returns true if the sinks is empty, i.e., all the streams in the
  sinks struct point to null. 
*/
bool riot_arduino_uno_is_sinks_empty(riot_arduino_uno_sinks *sinks) {
  if(sinks->D0 != NULL)
    return false;
  if(sinks->D1 != NULL)
    return false;
  if(sinks->D2 != NULL)
    return false;
  if(sinks->D3 != NULL)
    return false;
  if(sinks->D4 != NULL)
    return false;
  if(sinks->D5 != NULL)
    return false;
  if(sinks->D6 != NULL)
    return false;
  if(sinks->D7 != NULL)
    return false;
  if(sinks->D8 != NULL)
    return false;
  if(sinks->D9 != NULL)
    return false;
  if(sinks->D10 != NULL)
    return false;
  if(sinks->D11 != NULL)
    return false;
  if(sinks->D12 != NULL)
    return false;
  if(sinks->D13 != NULL)
    return false;
  if(sinks->LED != NULL)
    return false;
  if(sinks->A0 != NULL)
    return false;
  if(sinks->A1 != NULL)
    return false;
  if(sinks->A2 != NULL)
    return false;
  if(sinks->A3 != NULL)
    return false;
  if(sinks->A4 != NULL)
    return false;
  if(sinks->A5 != NULL)
    return false;
  return true;
}

int riot_arduino_uno_run(riot_arduino_uno_main main) {
  if(main == NULL) {
    return -1;
  }
  riot_arduino_uno_sources *sources = riot_arduino_uno_sources_create();
  if(sources == NULL) {
    return -2;
  }
  riot_arduino_uno_sinks *sinks = main(sources);
  if(sinks == NULL) {
    return -3;
  }
  riot_arduino_uno_map_sinks_to_write_outputs(sinks);
  while (true) {
    riot_arduino_uno_read_inputs(sources);
    if(riot_arduino_uno_is_sinks_empty(sinks))
      break;
  }
  return 0;
}
