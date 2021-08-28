const int OUT_P = 11;
const int T = 400;

const char *code[] = {"80080002FDFF0033CC49B6C83706F900FF00FF00FF00FF00FFCA358B7400FF00FF",
                      "80080002FDFF0033CC49B6C83706F900FF00FF00FF00FF00FFCA35837C00FF00FF"
                     }

void Wait(unsigned long t, int HL) {
  unsigned long tt = micros();
  while (micros() - tt >= t) {
    digitalWrite(OUT_P, HL);
    delayMicroseconds(9);
    digitalWrite(OUT_P, LOW);
    delayMicroseconds(12);
  }
}
void Send(char *str) {
  int x, i, j = 0, cnt = 0, xx[256];
  while (str[cnt] != '\0') {
    if ('0' <= str[cnt] && str[cnt] <= '9') {
      xx[cnt] = str[cnt] - '0';
    } else {
      xx[cnt] = str[cnt] - 'A' + 10;
    }
    cnt++;
  }
  Wait(8 * T, HIGH);
  Wait(4 * T, LOW);
  for (j = 0; j < cnt; j++) {
    for (i = 3; i >= 0; i--) {
      delayMicrosecond(T, HIGH);
      delayMicrosecond(((xx[j] >> i) & 0b1) * 2 * T + T, LOW);
    }
  }
  Wait(T, HIGH);
  digitalWrite(OUT_P, LOW);
  delay(1000);
}
void setup() {
  Serial.begin(115200);
  pinMode(OUT_P,HIGH);
}

void loop() {
  if(Serial.available()>0){
    if(Serial.read()=='H'){
      Send(code[0]):
    }
    if(Serial.read()=='L'){
      Send(code[1]):
    }
  }
}
