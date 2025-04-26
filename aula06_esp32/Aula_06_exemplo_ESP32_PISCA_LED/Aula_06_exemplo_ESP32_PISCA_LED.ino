#define LED_ONBOARD 2 // LED azul já ligado na placa

void setup() {
 // Habilita monitor serial 
 Serial.begin(115200);

 // Configura pino do LED como OUTPUT
 pinMode(LED_ONBOARD, OUTPUT);

}

void loop() {
  Serial.println("Funcionou!");
  digitalWrite(LED_ONBOARD, HIGH); // LED recebe 3,3V 
  delay(100);
  digitalWrite(LED_ONBOARD, LOW); // LED com 0V  
  delay(1000);
}