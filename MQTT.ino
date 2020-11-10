#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

//********* MQTT CONFIG *********//
const char* mqtt_server ="ioticos.org";
const int* mqtt_port = 1883;//puede modificarse
const char* mqtt_use ="kiVzIgbjLKkpcuy";//puede modificarse
const char* mqtt_pass ="LUBew37TNDmRlbA";//puede modificarse
const char* root_topic_subscribe ="hwSd5AthTfleEd9/input";//puede modificarse
const char* root_topic_publish ="hwSd5AthTfleEd9/output";//puede modificarse

//******* WIFI CONFIG ********//
const char* ssid="BTS";
const char* password="ddaeng_93J-HOPE"; 

//*********** GLOBALES ***********//
WiFiClient espClient;
PubSubClient client(espClient);
char msg[25];
long count=0;

//********* FUNCIONES *********//
void calback(char* topic, byte* payload, usingned int length);
void reconnected();
void setup_wifi();

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallcack(callback);
}

void loop() {
  if(!client.connected()){
    reconnected();
    }
   if(client.connected()){
    String str="La cuenta es-> " + String(count);
    str.toCharArray(msg,25);
    count++;
    delay(300);
    }
    client.loop();
}
//********* CONEXION WIFI *********//
void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("conectando a ssid: ");
  Serial.println(ssdi);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
  Serial.print("");
  Serial.println("Conectando a red WiFi");
  Serial,print("Direccion IP: ");
  Serial.println(WiFi.localIP());  
  }
//******** CONEXION MQTT ********//
void reconnect(){
  while(!client.connected(){
      Serial.print("Intentando conexion Mqtt...");
      String clientId="IOTICOS_H_W");
      clientId += String(random(0xffff), HEX);
      if(client.connect(clientID.c_str(), mqtt_user,mqtt_pass)){
        Serial.println("Conectado!");
        if(client.suscribe(root_topic_suscribe)){
          Serial.println("Suscripcion ok");
         }
         else{
            Serial.println("Fallo la Suscripcion");
          }
        }
        else{
            Serial.print("fallo :( con error ->");
            Serial.print(client.state());
            SErial.println(" Intentamos de nuevo en 5 segundos");
            delay(5000);
       }
    }
  }
  //******** CALLBACK *********//
  void calback(char* topic, byte* payload, usigned int length){
    String incoming="";
    Serial.print("Mensaje recibido desde -> ");
    Serial.print(topic);
    Serial.println("");
    for(int i=0; i<length; i++){
      incoming+=(char)payload[i];
      }
      incoming.trim();
      Serial.println("Mensaje ->"+ incoming);
    }
  
