// Incluimos librería de sensor de temperatura y humedad
#include <DHT.h>

//libreria Ethernet
#include <SPI.h>
#include <Ethernet.h>

//Libreria LCDI2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//Se declara el tipo de LCD a usar
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

////////////////////////////////////////////////////////////////////////////
 
// Declaracion de mac address para shield ethernet:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

// DNS Server
IPAddress dnServer(192, 168, 15, 1);

// Gateway:
IPAddress gateway(192, 168, 15, 1);

// Subnet:
IPAddress subnet(255, 255, 255, 0);

//ip Direction 
IPAddress ip(192, 168, 15, 20);

//InicializarCrear la instancia del server
EthernetServer server(81);

//////////////////////statement of variables and ports///////////////////////////////////

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Ports
#define LISTEN_PORT 81

//Se declaran variables para lectura de sensor de movimiento
const int LEDPin = 8;        // pin para el LED
const int PIRPin = 3;         // pin de entrada (for PIR sensor)
int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin

////////////////////////////////////////////////////////////////////////////

void setup()
{

  // Inicializamos comunicación serie
  Serial.begin(9600);
     
 // Comenzamos el sensor DHT
  dht.begin();
  
  //Se inicializa LCD
  lcd.begin(16,2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.clear();

  // initialize the ethernet device
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);

  //inicializar servidor web
  server.begin();
  Serial.println("Server inicializado");

  //Se inicializan los pins de entrada y salida para el pir
   pinMode(LEDPin, OUTPUT); 
   pinMode(PIRPin, INPUT);
}

 ////////////////////////////////////////////////////////////////////////////

void loop() 
{
  //Time para programa general
  delay(200);
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();

  // Comprobamos si ha habido algún error en la lectura y de ser asi lo imrpimimos
  if (isnan(h) || isnan(t))
  {
    lcd.clear();
    Serial.println("Error obteniendo los datos del sensor DHT11");
    lcd.setCursor(0,0);
    lcd.print("Error obteniendo");
    lcd.setCursor(0,1);
    lcd.print("los datos del sensor DHT11");
    return;
  }

  //Introduccion del sensor de movimiento
  val = digitalRead(PIRPin);
    if (val == HIGH)   //si está activado
    { 
       digitalWrite(LEDPin, HIGH);  //LED ON
       if (pirState == LOW)  //si previamente estaba apagado
       {
        Serial.println("Sensor activado");
        lcd.clear();
        lcd.setCursor(11,0);
        lcd.write("HIGH");
        pirState = HIGH;
       }
    } 
    else   //si esta desactivado
    {
       digitalWrite(LEDPin, LOW); // LED OFF
       if (pirState == HIGH)  //si previamente estaba encendido
       {
         Serial.println("Sensor parado");
         lcd.clear();
         lcd.setCursor(11,1);
         lcd.write("LOW");
         pirState = LOW;
       }
    }

 ///////////////////////////////////////Servidor Web////////////////////////////////////////////////////////

  //Se establece el html del server
  EthernetClient client = server.available();  // Buscamos entrada de clientes
  if (client) 
  { 
    boolean currentLineIsBlank = true;  // Las peticiones HTTP finalizan con linea en blanco
    while (client.connected())
    {
    if (client.available())
    {  
      char c = client.read();
      // A partir de aquí mandamos nuestra respuesta
      if (c == '\n' && currentLineIsBlank) 
      {   
        //Enviar una respuesta tipica
        client.println("HTTP/1.1 200 OK");             
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println("Refresh: 15");            // Actualizar cada 15 segs
        client.println();
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
        float h = dht.readHumidity();           // Leer el sensor
        float t = dht.readTemperature();
        //Desde aqui creamos nuestra pagina con el codigo HTML que pongamos
        client.print("<head><title>Situacion del lugar</title></head>");
        client.print("<body><h1> Situacion Ambiente</h1><p>Temperatura -");
        client.print(t);     // Aqui va la temperatura
        client.print(" grados Celsius</p>");
        client.print("<p>Humedad:  ");
        client.print(h);    // Aqui va la humedad
        client.print(" porciento</p>");
        client.print("<p><em> La página se actualiza cada 15 segundos.</em></p></body></html>");
        break;
      }
      if (c == '\n')
      {
        currentLineIsBlank = true;          // nueva linea
      }
      else if (c != '\r')
      {
        currentLineIsBlank = false;
      }
    }
    }
    delay(5);         // Para asegurarnos de que los datos se envia
    client.stop();     // Cerramos la conexion
  }

  //////////////////////////////////////Impresion de informacion/////////////////////////////////////////////

  //Impresion de temp
  //lcd.scrollDisplayLeft(); 
  lcd.setCursor(0,0);
  lcd.write("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(t);
  //Impresion de  humedad 
  lcd.setCursor(0,1);
  lcd.write("Hum: ");
  lcd.setCursor(5,1);
  lcd.print(h);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
