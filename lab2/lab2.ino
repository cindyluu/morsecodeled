#include <assert.h>

// on off definition
#define COL_OFF HIGH
#define COL_ON  LOW
#define ON      true
#define OFF     false

//strobe, clock, data, output enable pins
int BUTTON_PIN = 2;
int STROBE_PIN = 3;
int DATA_PIN = 4;
int CLOCK_PIN = 5;

int test_digit = 0;

//column pins
int COLUMN_1_PIN = 9;
int COLUMN_2_PIN = 10;
int COLUMN_3_PIN = 11;
int COLUMN_4_PIN = 12;
int COLUMN_5_PIN = 13;
int COLUMN_PINS[5] = {
    COLUMN_1_PIN,
    COLUMN_2_PIN,
    COLUMN_3_PIN,
    COLUMN_4_PIN,
    COLUMN_5_PIN
};

// Digit map contains an array item for each digit
// Each digit in the outer array contains a value
// representing the rows, stored as an 8-bit value.
int DIGIT_MAP[10][5] = {
    {0x00, 0x7F, 0x41, 0x41, 0x7F}, // 0
    {0x00, 0x00, 0x21, 0xFF, 0x01}, // 1
    {0x00, 0xCF, 0xC9, 0xC9, 0xF9}, // 2
    {0x00, 0xC1, 0xC9, 0xC9, 0xFF}, // 3
    {0x00, 0xF8, 0x08, 0x08, 0xFF}, // 4
    {0x00, 0xF9, 0xC9, 0xC9, 0xCF}, // 5
    {0x00, 0xFF, 0xC9, 0xC9, 0xCF}, // 6
    {0x00, 0xE0, 0xC0, 0xC0, 0xFF}, // 7
    {0x00, 0xFF, 0xC9, 0xC9, 0xFF}, // 8
    {0x00, 0xF9, 0xC9, 0xC9, 0xFF}  // 9
};

void setup() {
    pinMode(BUTTON_PIN,INPUT);
    pinMode(DATA_PIN,OUTPUT);
    pinMode(STROBE_PIN,OUTPUT);
    pinMode(CLOCK_PIN,OUTPUT);

    pinMode(COLUMN_1_PIN,OUTPUT);
    pinMode(COLUMN_2_PIN,OUTPUT);
    pinMode(COLUMN_3_PIN,OUTPUT);
    pinMode(COLUMN_4_PIN,OUTPUT);
    pinMode(COLUMN_5_PIN,OUTPUT);
}

void toggle_columns(bool on) {
    //turn off all columns
    int col;
    for(col=0; col<5; col++) {
        if (on) {
            digitalWrite(COLUMN_PINS[col], COL_ON);
        } else {
            digitalWrite(COLUMN_PINS[col], COL_OFF);
        }
    }
}

void switch_rows(int row_map) {
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(STROBE_PIN, LOW);

    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, row_map);

    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(STROBE_PIN, HIGH);
    delay(1);
}

void display_digit(int digit) {
    assert(digit < 10 && digit > -1);

    int col;
    for (col=0; col<=5; col++) {
        switch_rows(DIGIT_MAP[digit][col]);
        digitalWrite(COLUMN_PINS[col], COL_ON);
        delay(10);
        digitalWrite(COLUMN_PINS[col], COL_OFF);
    }
}

void loop() {
    display_digit(4);
    // delay(100);
}
