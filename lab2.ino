
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

void columnsOFF() {
//turn off all columns
    for (int x = 0; x<5;x++){
    digitalWrite(columns[x],col_off);
    }
    delay(1000);
}


void loop() {
    columnsOFF();
// shift out the bits, take the latch pin high so the LEDs will light up, pause before next value:
//1
    digitalWrite(columns[3],col_on);
    digitalWrite(strobepin, LOW);
    shiftOut(datapin, clockpin, MSBFIRST, 0xFF);  
    digitalWrite(strobepin, HIGH);
    delay(1000);
    columnsOFF();
//4
    for (int x = 0; x < 5; x++){
        for(int y = 0; y <5; y++ ){

        digitalWrite(columns[x],col_on);
        if (x!=y) {
        digitalWrite(columns[y],col_on);          
        }    
        digitalWrite(strobepin, LOW);
        shiftOut(datapin, clockpin, MSBFIRST, 0x0F);  
        digitalWrite(strobepin, HIGH);
        delay(50);  
      }    
    }
}
