#include <WiFi.h>
#include <Espalexa.h>

boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);

// Change this!!
const char* ssid = "your ssid";
const char* password = "your passwd";

const int OUT_P = 23;
const int T = 400;

char *code[] = {"80080002FDFF0033CC49B6C83706F900FF00FF00FF00FF00FFCA358B7400FF00FF",
                "80080002FDFF0033CC49B6C83706F900FF00FF00FF00FF00FFCA35837C00FF00FF"
               };

void Wait(unsigned long t, int HL) {
  unsigned long tt = micros(),wt;
  while (micros() - tt <= t) {
    digitalWrite(OUT_P, HL);
    wt=micros();
    while(micros()-wt<=8);
    digitalWrite(OUT_P, LOW);
    delayMicroseconds(12);
    wt=micros();
    while(micros()-wt<=8);
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
      Wait(T, HIGH);
      Wait(((xx[j] >> i) & 0b1) * 2 * T + T, LOW);
    }
  }
  Wait(T, HIGH);
  digitalWrite(OUT_P, LOW);
  delay(1000);
}

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);
  pinMode(OUT_P,OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  espalexa.addDevice("denki", firstLightChanged);
  espalexa.begin();
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness) {
  Serial.print("Device 1 changed to ");

  if (brightness) {
    Serial.print("ON, brightness ");
    Serial.print(brightness);
    Send(code[0]);
  }
  else  {
    Serial.println("OFF");
    Send(code[1]);
  }
}
