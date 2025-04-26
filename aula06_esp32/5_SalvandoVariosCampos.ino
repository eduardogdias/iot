#include <WiFi.h>
#include "ThingSpeak.h" 

#define SECRET_SSID "Wokwi-GUEST" // nome rede
#define SECRET_PASS "" // senha rede

#define SECRET_CH_ID 2936690 //	Preencha o número do seu canal do ThingSpeak	
#define SECRET_WRITE_APIKEY "C5MATKH5Z76QKCKV"   // Preencha a API Key do seu canal

char ssid[] = SECRET_SSID;   
char pass[] = SECRET_PASS;   
int keyIndex = 0;            
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int number = 0;
int numero2 = 50;

void setup() {
  Serial.begin(115200);  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  
}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Tentando conectar ao SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); 
      Serial.print(".");
      delay(1000);     
    } 
    Serial.println("\nConectado.");
  }

  ThingSpeak.setField(1, number);
  ThingSpeak.setField(2, numero2);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if(x == 200){
    Serial.println("Os dois campos do Canal foram atualizados com sucesso!");
  }
  else{
    Serial.println("Erro ao atualizar o canal 1. HTTP error code: " + String(x));
  }
  
  
  // Exemplo: gerando um número aleatório de 0 a 99
  numero2--;
  number++;
  if(number > 99){
    number = 0;
  }
  
  delay(20000); // Aguarda 20 segundos para atualizar o canal.
}
