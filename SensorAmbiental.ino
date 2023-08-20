/* Librerias para la pantalla LCD con modulo I2C */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/* Libreria para el sensor de temperatura y humedad*/
#include <DHT.h>

/* Conexiones en el Arduino */
//SCL -> A5
//SDA -> A4
//Sensor de humedad de suelo -> A0

//Pantalla LED
LiquidCrystal_I2C lcd(0x27,20,4);

//Sensor de humedad del suelo
const int dry = 538;
const int wet = 199;
int percentageHumidity;
int suelo;

//Valores del sensor DHT22
float t;
float h;

//Sensor DHT22 -> (DHTPin, DHTType)
DHT dht(10, DHT22);

void setup(){
  //Pantalla LCD
  lcd.init();
  lcd.backlight();

  //Sensor DHT22
  dht.begin();
}

void loop() {
  recogerDatos();
  mostrarDatos();
  delay(2000);
}

void recogerDatos(){
  t = dht.readTemperature();
  h = dht.readHumidity();
  suelo = analogRead(A0);
  percentageHumidity = map(suelo, wet, dry, 99, 0);
}

void mostrarDatos(){
  lcd.clear();
  mostrarTitulo();
  mostrarTemperatura();
  mostrarHumedad();
  mostrarHumedadSuelo();
}

void mostrarTitulo(){
  lcd.setCursor(0, 0);
  lcd.print("==Sensor Ambiental==");
}

void mostrarTemperatura(){
  lcd.setCursor(2, 1);
  lcd.print("Temperatura: ");
  lcd.print(round(t - 2));
  lcd.print((char)223);
}

void mostrarHumedad(){
  lcd.setCursor(2, 2);
  lcd.print("Humedad:     ");
  lcd.print(round(h));
  lcd.print("%");
}

void mostrarHumedadSuelo(){
  lcd.setCursor(2, 3);
  lcd.print("Suelo:       ");
  lcd.print(percentageHumidity);
  lcd.print("%");
}
