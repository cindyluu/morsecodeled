#include <assert.h>

// Utility constants
const bool ON = true;
const bool OFF = false;
const int CLICKED = HIGH;
const int RELEASED = LOW;
const int DOT = 1;
const int DASH = 0;

// Pin constants
const int BUTTON_PIN = 2;
const int STROBE_PIN = 3;
const int DATA_PIN = 4;
const int CLOCK_PIN = 5;
const int COLUMN_1_PIN = 9;
const int COLUMN_2_PIN = 10;
const int COLUMN_3_PIN = 11;
const int COLUMN_4_PIN = 12;
const int COLUMN_5_PIN = 13;
const int COLUMN_PINS[5] = {
    COLUMN_1_PIN,
    COLUMN_2_PIN,
    COLUMN_3_PIN,
    COLUMN_4_PIN,
    COLUMN_5_PIN
};

// Digit map contains an array for each digit, 0-9. Each digit map value is
// an array itself. Each of these digit arrays include 5 values, 1 for each
// column of the LED dot matrix display (i.e., columns 1-5). The values for each
// columns of a digit represent the rows on that column that should be lit.
//
// For example, the digit 0 is stored as follows:
//
//  80 FF C1 C1 FF
//  1  1  1  1  1 (ignored/unconnected)
//  0  1  1  1  1
//  0  1  0  0  1
//  0  1  0  0  1
//  0  1  0  0  1
//  0  1  0  0  1
//  0  1  1  1  1
//
// Note: the most significant bit is ignored on the dot matrix display
//
const int DIGIT_MAP[10][5] = {
    {0x80, 0xFF, 0xC1, 0xC1, 0xFF}, // 0
    {0x80, 0x80, 0xA1, 0xFF, 0x81}, // 1
    {0x80, 0xCF, 0xC9, 0xC9, 0xF9}, // 2
    {0x80, 0xC1, 0xC9, 0xC9, 0xFF}, // 3
    {0x80, 0xF8, 0x88, 0x88, 0xFF}, // 4
    {0x80, 0xF9, 0xC9, 0xC9, 0xCF}, // 5
    {0x80, 0xFF, 0xC9, 0xC9, 0xCF}, // 6
    {0x80, 0xE0, 0xC0, 0xC0, 0xFF}, // 7
    {0x80, 0xFF, 0xC9, 0xC9, 0xFF}, // 8
    {0x80, 0xF9, 0xC9, 0xC9, 0xFF}  // 9
};

// Runtime globals
int click_state;
int last_click_state = RELEASED;
unsigned long last_debounce_time = 0;   // the last time the output pin was toggled
const unsigned long debounce_delay = 5; // the debounce time; increase if the output flickers
const unsigned long dot_duration = 150; // the length of a dot
int digit = -1;
int morse_code[5];
int morse_code_index = 0;


void toggle_columns(bool on) {
    int state;
    state = on ? LOW : HIGH;
    digitalWrite(COLUMN_PINS[0], state);
    digitalWrite(COLUMN_PINS[1], state);
    digitalWrite(COLUMN_PINS[2], state);
    digitalWrite(COLUMN_PINS[3], state);
    digitalWrite(COLUMN_PINS[4], state);
}

void toggle_rows(int row_map) {
    digitalWrite(STROBE_PIN, LOW);

    delay(3);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, row_map);

    digitalWrite(STROBE_PIN, HIGH);
}

void display_digit(int digit) {
    if (digit > -1) {
        // if (digit > 9 || digit < 0) {
        //     Serial.print("Digit: ");
        //     Serial.println(digit);
        // }
        assert(digit < 10 && digit > -1);

        int col;
        for (col=0; col<5; col++) {
            toggle_rows(DIGIT_MAP[digit][col]);
            toggle_columns(OFF);
            digitalWrite(COLUMN_PINS[col], LOW);
        }
    }
}

void print_code_status() {
    Serial.print("Button state changed to ");
    Serial.println(click_state == CLICKED ? "CLICKED " : "RELEASED");

    Serial.print("[");
    Serial.print(morse_code[0]);
    Serial.print(", ");
    Serial.print(morse_code[1]);
    Serial.print(", ");
    Serial.print(morse_code[2]);
    Serial.print(", ");
    Serial.print(morse_code[3]);
    Serial.print(", ");
    Serial.print(morse_code[4]);
    Serial.println("]");
}

int parse_morse_code(int code[5]) {
    int dot_sum = code[0] + code[1] + code[2] + code[3] + code[4];
    int result = code[0] == DOT ? dot_sum : (10 - dot_sum);
    return result % 10;
}

int update_code_sequence(int digit, int new_state, unsigned long click_duration) {
    if (click_duration <= dot_duration) {
        morse_code[morse_code_index] = DOT;
        Serial.println("DOT");
    } else {
        morse_code[morse_code_index] = DASH;
        Serial.println("DASH");
    }

    if (++morse_code_index > 4) {
        morse_code_index = 0;
        return parse_morse_code(morse_code);
    }
    return digit;
}

void setup() {
    Serial.begin(9600);

    pinMode(BUTTON_PIN, INPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STROBE_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(COLUMN_1_PIN, OUTPUT);
    pinMode(COLUMN_2_PIN, OUTPUT);
    pinMode(COLUMN_3_PIN, OUTPUT);
    pinMode(COLUMN_4_PIN, OUTPUT);
    pinMode(COLUMN_5_PIN, OUTPUT);

    digitalWrite(CLOCK_PIN, HIGH);
    toggle_columns(OFF);
    delay(100);
}

int reading;
unsigned long current_time;
unsigned long click_start;

void loop() {
    // https://www.arduino.cc/en/Tutorial/Debounce
    reading = digitalRead(BUTTON_PIN);
    current_time = millis();

    if (reading != last_click_state) {
        last_debounce_time = millis();
    }

    if ((current_time - last_debounce_time) > debounce_delay) {
        // State is really changing here

        if (reading != click_state) {
            click_state = reading;

            if (click_state == RELEASED) {
                digit = update_code_sequence(digit, click_state, current_time - click_start);
            } else {
                click_start = last_debounce_time;
            }
            // print_code_status();
        }
    }

    last_click_state = reading;

    display_digit(digit);
}
