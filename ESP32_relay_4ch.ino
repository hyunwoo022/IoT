#define ESP32

#include <secret.h>
#include <Arduino.h>
#if defined (ESP32)
  #include <Wifi.h>
#elif defined (ESP8266)
  #include <ESP8266Wifi.h>
#endif
#include <Firebase_ESP_Client.h> //Mobizt

FirebaseData fbData;
FirebaseAuth auth;
FireaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

int LED_1 = 26;
int LED_2 = 27;
int LED_3 = 32;
int LED_4 = 33;

void setup() {
  Serial.begin(115200);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  wifi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.print();
  Serial.print("Connected with IP: ")
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api.key = API_KEY;
  config.database_url = DATABASE_URL;

  if(Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
} else {
  Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  FIrebase.reconectWiFi(true);
}

void loop(){
  if(Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 5000 || sendDataPrenMilis == 0)){
    sendDataPrevMillis = millis();
    if(Firebase.RTDB.getString(&fbData, "/AutoHome/S1")){
      String state1 = fbData.stringData();
      Serial.print("event: ");
      Serial.println(state1);
      if(state1 == "1"){
        digitalWrite(LED_1, HIGH); // On
      } else if(state1 == "0"){
        digitalWrite(LED_1, LOW); //Off
      }
    }

    sendDataPrevMillis = millis();
    if(Firebase.RTDB.getString(&fbData, "/AutoHome/S2")){
      String state1 = fbData.stringData();
      Serial.print("event: ");
      Serial.println(state1);
      if(state1 == "1"){
        digitalWrite(LED_2, HIGH); // On
      } else if(state1 == "0"){
        digitalWrite(LED_2, LOW); //Off
      }
    }

    sendDataPrevMillis = millis();
    if(Firebase.RTDB.getString(&fbData, "/AutoHome/S3")){
      String state1 = fbData.stringData();
      Serial.print("event: ");
      Serial.println(state1);
      if(state1 == "1"){
        digitalWrite(LED_3, HIGH); // On
      } else if(state1 == "0"){
        digitalWrite(LED_3, LOW); //Off
      }
    }

    sendDataPrevMillis = millis();
    if(Firebase.RTDB.getString(&fbData, "/AutoHome/S4")){
      String state1 = fbData.stringData();
      Serial.print("event: ");
      Serial.println(state1);
      if(state1 == "1"){
        digitalWrite(LED_4, HIGH); // On
      } else if(state1 == "0"){
        digitalWrite(LED_4, LOW); //Off
      }
    }
  }
}
