// Incluimos librería de sensor de temperatura y humedad
#include <DHT.h>

//libreria APIRest
#include <aREST.h>

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

//REST
aREST rest = aREST();

//////////////////////statement of variables and ports///////////////////////////////////

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Ports
#define LISTEN_PORT 81

////////////////////////////////////////////////////////////////////////////

void setup()
{
  //Inicializamos aREST
  aREST rest = aREST();

  // Inicializamos comunicación serie
  Serial.begin(9600);
     
 // Comenzamos el sensor DHT
  dht.begin();
  
  //Se inicializa LCD
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.clear();

  // initialize the ethernet device
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);

  //inicializar servidor web
  server.begin();
  Serial.println("Server inicializado");


}

////////////////////////////////////////////////////////////////////////////

void loop() 
{
    /////////////Se establece el html del server
  EthernetClient client = server.available();  // Buscamos entrada de clientes
  if (client) 
  { 
    Serial.println("new client");
    boolean currentLineIsBlank = true;  // Las peticiones HTTP finalizan con linea en blanco
    while (client.connected())
    {
      if (client.available())
      {  
        char c = client.read();
        Serial.write(c);   // Esto no es necesario, pero copiamos todo a la consola
        // A partir de aquí mandamos nuestra respuesta
        if (c == '\n' && currentLineIsBlank) 
        {   
          // Enviar una respuesta tipica
          client.println("HTTP/1.1 200 OK");             
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 15");            // Actualizar cada 15 segs
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          float h = dht.readHumidity();           // Leer el sensor
          float t = dht.readTemperature();
          Serial.println(t);
          Serial.println(h);
          // Desde aqui creamos nuestra pagina con el codigo HTML que pongamos
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
    delay(10);         // Para asegurarnos de que los datos se envia
    client.stop();     // Cerramos la conexion
    Serial.println("client disonnected");
  }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Esperamos 4 segundos entre medidas
  delay(500);

 // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
   
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t))
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
    // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);

  //Se deja la impresion en buffer por si se ocupa
  //Impresion Serial
  //Serial.print("Humedad: ");
  //Serial.print(h);
  //Serial.print(" % ");
  //Serial.print("Temperatura: ");
  //Serial.print(t);
  //Serial.print(" *C\n ");


  /////////////////////////////////////////////////
  //desplazamos una posición a la izquierda
  lcd.scrollDisplayLeft(); 
  delay(500);
  
  // Actualizar la pantalla completa cada segundo
  //lcd.clear();
  
  //Impresion de temp
  lcd.setCursor(0,0);
  lcd.write("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(t);
  
  //Impresion de  humedad 
  lcd.setCursor(0,1);
  lcd.print("Humedad: ");
  lcd.setCursor(8,1);
  lcd.print(h);

  //Impresion de ip
  lcd.setCursor(14,0);
  lcd.print("IP: ");
  lcd.setCursor(17,0);
  lcd.print("192.168.15.20"); 
}
