// Incluimos librería
#include <DHT.h>

//Libreria LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 8, 9, 10, 11 , 12);
 
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  // Inicializamos comunicación serie
  Serial.begin(9600);
 
  // Comenzamos el sensor DHT
  dht.begin();
  
  
  // Comenzamos el LCD
  //lcd.begin(16, 2);
  //lcd.setCursor(0,1);
  //lcd.write(" ");
  


}
 
void loop() {
    // Esperamos 4 segundos entre medidas
  delay(4000);
 
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  //// Leemos la temperatura en grados Fahreheit
  //float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t))
  {
    // || isnan(f)) 
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  // Calcular el índice de calor en Fahreheit
  //float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C\n");
  
  //Serial.print(f);
  //Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C \n");
  //Serial.print(hif);
  //Serial.println(" *F");

  //Prueba de LCD
   delay(4000);
   lcd.setCursor(0,0);
  lcd.write("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(t);
 
}
