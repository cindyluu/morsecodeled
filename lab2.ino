
//strobe, clock, data, output enable pins

int datapin = 10;
int strobepin = 11;
int clockpin = 12;
int outputen = 13;

//column pins
int col1 = 5;
int col2 = 6;
int col3 = 7;
int col4 = 8;
int col5 = 9;
int columns[5] = {col1, col2, col3, col4, col5};
// on off definition
#define col_off HIGH
#define col_on LOW
 
void setup() {
pinMode(datapin,OUTPUT);
pinMode(strobepin,OUTPUT);
pinMode(clockpin,OUTPUT);
pinMode(outputen,OUTPUT);
pinMode(col1,OUTPUT);
pinMode(col2,OUTPUT);
pinMode(col3,OUTPUT);
pinMode(col4,OUTPUT);
pinMode(col5,OUTPUT);
}

void number1() {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(col1,col_off);
    digitalWrite(col2,col_off);
    digitalWrite(col3,col_off);
    digitalWrite(col4,col_on);
    digitalWrite(col5,col_off);
    digitalWrite(outputen, HIGH);
    digitalWrite(strobepin, LOW);
    // shift out the bits:
    shiftOut(datapin, clockpin, MSBFIRST, 255);  
    //take the latch pin high so the LEDs will light up:
    digitalWrite(strobepin, HIGH);
    // pause before next value:
}


void loop() {

number1();
}
