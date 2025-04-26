#include <WiFi.h>
#include <ThingSpeak.h>

 
int keyIndex = 0;          
WiFiClient  client;

#define SSID "Wokwi-GUEST"		
#define PASS ""	

#define CH_ID 2899923			
#define WRITE_APIKEY "ZLML8ERPOG74SYCH"   

unsigned long myChannelNumber = CH_ID;
const char * myWriteAPIKey = WRITE_APIKEY;

int number1 = 0;
int number2 = random(0,100);
int number3 = random(0,100);
int number4 = random(0,100);
String myStatus = "";

void setup() {
  Serial.begin(115200);  
  while (!Serial) {
    ; 
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  
}

void loop() {

  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(SSID, PASS);  
      Serial.print(".");
      delay(2000);     
    } 
    Serial.println("\nConnected.");
  }

  // set the fields with the values
  ThingSpeak.setField(1, number1);
  ThingSpeak.setField(2, number2);
  ThingSpeak.setField(3, number3);
  ThingSpeak.setField(4, number4);

  // figure out the status message
  if(number1 > number2){
    myStatus = String("field1 is greater than field2"); 
  }
  else if(number1 < number2){
    myStatus = String("field1 is less than field2");
  }
  else{
    myStatus = String("field1 equals field2");
  }
  
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  // change the values
  number1++;
  if(number1 > 99){
    number1 = 0;
  }
  number2 = random(0,100);
  number3 = random(0,100);
  number4 = random(0,100);
  
  delay(20000); // Wait 20 seconds to update the channel again
}
