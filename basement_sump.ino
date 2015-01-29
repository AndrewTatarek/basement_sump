// user moddable variables
int led = 13;
int Sensor = A0;
int PumpOffLevel = 10;
int PumpOnLevel = 150;
float CriticalFillSpeed = 5; // mm per 64 seconds
int OffDelayTime = 10000; // milliseconds that the pump runs for after water drops below low point

// programmer modable
#define WaterLevel ((180.0/431)*(431-analogRead(Sensor))) // this is in mm
float History[256]; // this covers a 64 second period

void setup() {                
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}

void loop() {
    for(int i = 0;i<256;i++){
        History[i]=-9999;
    }
    for(unsigned char i = 0;WaterLevel<PumpOnLevel;i++){ // notice that i deliberately overflows
        Serial.println(WaterLevel); // for diagnostics 
        if(WaterLevel>30&&WaterLevel-CriticalFillSpeed<History[i]){
            break;
        }
        History[i]=WaterLevel;
        delay(250);
    }
    digitalWrite(led, HIGH); 
    Serial.println("ON");
    
    while(WaterLevel>PumpOffLevel){
        Serial.println(WaterLevel); // for diagnostics 
    }
    delay(OffDelayTime); // the pump should remain on for a bit after the 
    digitalWrite(led, LOW);
    Serial.println("OFF");
}

