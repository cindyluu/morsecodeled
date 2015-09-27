// on off definition
#define COL_OFF HIGH
#define COL_ON LOW

//strobe, clock, data, output enable pins
int BUTTON_PIN = 2;
int STROBE_PIN = 3;
int DATA_PIN = 4;
int CLOCK_PIN = 5;
int OUTPUT_ENABLE_PIN = 6;

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
// representing the rows, stored as an 8-bit value 
// (1 bit per row),
// array of rows that should be illuminated for each
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
    pinMode(OUTPUT_ENABLE_PIN,OUTPUT);

    pinMode(COLUMN_1_PIN,OUTPUT);
    pinMode(COLUMN_2_PIN,OUTPUT);
    pinMode(COLUMN_3_PIN,OUTPUT);
    pinMode(COLUMN_4_PIN,OUTPUT);
    pinMode(COLUMN_5_PIN,OUTPUT);
}

void columnsOFF() {
    //turn off all columns
    for(int x = 0; x<5;x++) {
        digitalWrite(COLUMN_PINS[x],COL_OFF);
    }
}

void display_one() {
    columnsOFF();

    digitalWrite(OUTPUT_ENABLE_PIN, LOW);

    digitalWrite(STROBE_PIN, LOW);

    // Send data to the shift register
    digitalWrite(COLUMN_2_PIN, COL_ON);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0x0F);

    digitalWrite(STROBE_PIN, LOW);
    digitalWrite(STROBE_PIN, HIGH);
    digitalWrite(OUTPUT_ENABLE_PIN,HIGH);
}

void loop() {
    display_one();
    delay(1000);
    columnsOFF();
    delay(1000);
}


// digitalWrite(OUTPUT_ENABLE_PIN,LOW);

    // // shift out the bits, take the latch pin high so the LEDs will light up, pause before next value:
    // //1
    // digitalWrite(OUTPUT_ENABLE_PIN,HIGH);
    // digitalWrite(COLUMN_PINS[3],COL_ON);
    // digitalWrite(STROBE_PIN, LOW);
    // shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0x4F);
    // digitalWrite(STROBE_PIN, HIGH);
    // delay(1000);
//2
//    columnsOFF();
//    digitalWrite(COLUMN_PINS[0],COL_ON);
//    digitalWrite(COLUMN_PINS[1],COL_ON);
//    digitalWrite(COLUMN_PINS[2],COL_ON);
//    digitalWrite(COLUMN_PINS[3],COL_ON);
//    digitalWrite(COLUMN_PINS[4],COL_ON);
//    digitalWrite(STROBE_PIN, LOW);
//    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0x4F);
//    digitalWrite(STROBE_PIN, HIGH);
//    delay(500);


//4
//    columnsOFF();
//    for (int x = 0; x < 5; x++){
//        for(int y = 0; y <5; y++ ){
//        digitalWrite(COLUMN_PINS[x],COL_ON);
//        if (x!=y) {
//        digitalWrite(COLUMN_PINS[y],COL_OFF);
//    , }
//        digitalWrite(STROBE_PIN, LOW);
//        shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 154);
//        delay(1);
//        digitalWrite(STROBE_PIN, HIGH);
//        delay(50);
//  , }
//, }
