
#include <DHT.h>
#include <WiFi.h>
#include <ThingSpeak.h>

#define DHTPIN 32
#define DHTTYPE DHT22

DHT sensorDHT(DHTPIN, DHTTYPE);

const char* UniversityID = "12324291";
const char* WiFi_Name="Wokwi-GUEST";
const char* WiFi_Pass="";

const int IdChannel= 3551964;
const char* ApiKeyWrite= "WRITE_API_KEY";
WiFiClient clientObject;
void setup() {
  Serial.begin(115200);
  Serial.print("University ID: ");
  Serial.println(UniversityID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFi_Name,WiFi_Pass);
  while(WiFi.status()!=WL_CONNECTED){
      Serial.print("NOT_CONNECTED");
      delay(1000);

  }
  sensorDHT.begin();
  ThingSpeak.begin(clientObject);
}
void loop() {
  float temperature = sensorDHT.readTemperature();
  float humidity = sensorDHT.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT22");
    delay(20000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  ThingSpeak.setField(1,temperature);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  ThingSpeak.setField(2,humidity);


  int stat=ThingSpeak.writeFields(IdChannel,ApiKeyWrite);
  if(stat==200){
    Serial.print("Data it sent ");

  }else {
    Serial.print("Sending failed. Error code: ");
    Serial.println(stat);
}

 
  delay(20000); 
}
