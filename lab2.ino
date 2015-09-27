
//strobe, clock, data, output enable pins

int button = 2;
int strobepin = 3;
int datapin = 4;
int clockpin = 5;
int oepin = 6;

//column pins
int col1 = 9;
int col2 = 10;
int col3 = 11;
int col4 = 12;
int col5 = 13;
int columns[5] = {col1, col2, col3, col4, col5};

//char zero[5] = {'0x00',  '0xFF',  '0x81',  '0x81',  '0xFF'};

// on off definition
#define col_off HIGH
#define col_on LOW
 
void setup() {
pinMode(button,INPUT);
pinMode(datapin,OUTPUT);
pinMode(strobepin,OUTPUT);
pinMode(clockpin,OUTPUT);
pinMode(oepin,OUTPUT);

pinMode(col1,OUTPUT);
pinMode(col2,OUTPUT);
pinMode(col3,OUTPUT);
pinMode(col4,OUTPUT);
pinMode(col5,OUTPUT);
  Serial.begin(9600);
  Serial.println("reset");
}

void columnsOFF() {
//turn off all columns
    for (int x = 0; x<5;x++){
    digitalWrite(columns[x],col_off);
    }
    delay(1000);
}


void loop() {
    digitalWrite(oepin,LOW);
    columnsOFF();
// shift out the bits, take the latch pin high so the LEDs will light up, pause before next value:
//1
    digitalWrite(oepin,HIGH);
    digitalWrite(columns[3],col_on);
    digitalWrite(strobepin, LOW);
    shiftOut(datapin, clockpin, MSBFIRST, 0x4F);  
    digitalWrite(strobepin, HIGH);
    delay(1000);

//2
//    columnsOFF();
//    digitalWrite(columns[0],col_on);
//    digitalWrite(columns[1],col_on);
//    digitalWrite(columns[2],col_on);
//    digitalWrite(columns[3],col_on);
//    digitalWrite(columns[4],col_on);
//    digitalWrite(strobepin, LOW);
//    shiftOut(datapin, clockpin, MSBFIRST, 0x4F);  
//    digitalWrite(strobepin, HIGH);
//    delay(500);


//4
//    columnsOFF();
//    for (int x = 0; x < 5; x++){
//        for(int y = 0; y <5; y++ ){
//        digitalWrite(columns[x],col_on);
//        if (x!=y) {
//        digitalWrite(columns[y],col_off);          
//        }    
//        digitalWrite(strobepin, LOW);
//        shiftOut(datapin, clockpin, MSBFIRST, 154);  
//        delay(1); 
//        digitalWrite(strobepin, HIGH);
//        delay(50);  
//      }    
//    }
}
