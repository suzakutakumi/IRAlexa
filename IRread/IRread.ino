const int IN_P=23;
void setup() {
  Serial.begin(9600);
  pinMode(IN_P, INPUT_PULLUP);
}
unsigned long t;
unsigned short tt[2][320];
int cnt = 0;
void loop() {
  if (!digitalRead(IN_P)) {
    t = micros();
    while ((!digitalRead(IN_P)));
    tt[0][cnt] = micros() - t;
    t = micros();
    while (digitalRead(IN_P)) {
      //delayMicroseconds(100);
      if (micros() - t >= 8000) {
        tt[1][cnt] = micros() - t;
        //Serial.println("OK");
        int c = 0, sum = 0, x = 1;
        for (int i = 0; i <= cnt; i++) {
          //Serial.print(String(tt[0][i]) + "," + String(tt[1][i]) + ",");
          if (i >= 1) {
            c++;
            sum = (sum<<1)+(tt[1][i] >= 1000 ? 1 : 0);
            if (c >= 4) {
              x = 1;
              c = 0;
              Serial.print(sum, HEX);
              sum = 0;
            }
          }
          //Serial.println("");
        }
        Serial.println("");
        cnt = 0;
        return;
      }
    }
    tt[1][cnt] = micros() - t;
    //Serial.println(String(tt[cnt])+",");
    cnt++;
    if (cnt >= 320) {
      cnt = 0;
      Serial.println("Over");
    }
  }
}
