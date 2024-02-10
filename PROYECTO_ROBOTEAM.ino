//Librerias

// lcd
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


// ---DEFINICIONES---
// Entradas y Salidas

#define LEDAZUL 3

#define POTENCIOMETRO A0

#define led_verde_G 6
#define led_rojo_R  5

#define sensorT A1

#define tiempoLed 7

#define buzzer 4

#define buton_inicio 8
#define buton_pausa 9
#define buton_reset 10

// ---VARIABLES---
int valorPotenciometro;
int lecturaPotenciometro;
int lecturaSensor;
float voltaje;
float tempC;

int horas;     
int minutos;     
int segundos;    
int decimas;           
int milisegundos;

int a;
int b;






// ---FUNCION SETUP---

void setup() {
  
  pinMode(LEDAZUL, OUTPUT);
  pinMode(POTENCIOMETRO, INPUT);

  pinMode(led_verde_G, OUTPUT);  
  pinMode(led_rojo_R, OUTPUT);

  pinMode(sensorT, INPUT);

  pinMode(buzzer, OUTPUT);


  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(3,0);
  lcd.print("BIENVENIDO");
  delay (3000);
  lcd.clear();
  
  lcd.setCursor(3,0);
  lcd.print("SOY ZATTY");
  delay (3000);
  lcd.clear();

  lcd.setCursor(2,0);
  lcd.print("TU ASISTENTE");
  lcd.setCursor(4,1);
  lcd.print("PERSONAL");
  delay (3000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("CUIDEMOS EL AGUA");
  delay (3000);
  lcd.clear();

 

  

  

}

void loop() {


  //USO DEL POTENCIOMETRO Y EL LED AZUL 
  
  //lecturaPotenciometro = analogRead(POTENCIOMETRO) /4.0117647059; // = 1023 / 255 = 4.0117647059
  
  valorPotenciometro = analogRead(POTENCIOMETRO);
  lecturaPotenciometro = map(valorPotenciometro, 0, 1023, 0, 255);
  
 

  // CONDICIONES
  
  if (lecturaPotenciometro >= 0 and lecturaPotenciometro <= 10){
    
    analogWrite(LEDAZUL, LOW);
    digitalWrite(led_verde_G, LOW);
    digitalWrite(led_rojo_R, LOW);
    digitalWrite(buzzer, LOW);

   lcd.clear();
     
  }else if (lecturaPotenciometro >=11 and lecturaPotenciometro <= 127){
    
    analogWrite(LEDAZUL, lecturaPotenciometro);
    digitalWrite(led_verde_G, HIGH);
    digitalWrite(led_rojo_R, LOW);
    digitalWrite(buzzer, LOW);

/*
    lcd.setCursor(10,0);
    lcd.print(tempC, 1);
    lcd.setCursor(15,0); 
    lcd.print("C");
    lcd.display();
*/

  }else if (lecturaPotenciometro >= 128 and lecturaPotenciometro <= 255){
    
   analogWrite(LEDAZUL, lecturaPotenciometro);
   digitalWrite(led_verde_G, LOW);
   digitalWrite(led_rojo_R, HIGH);
   digitalWrite(buzzer, HIGH);
/*
   lcd.setCursor(10,0);
   lcd.print(tempC, 1);
   lcd.setCursor(15,0); 
   lcd.print("C");
   lcd.display();
*/
  }

  //SENSOR TEMPERATURA

/* 
  lecturaSensor = analogRead(sensorT);
*/  
 
  //Serial.print ("Lectura: ");
  //Serial.println (lecturaSensor);

/*
  Calculo:

  0.01V - 1°C
  0.23V - 23°C
  
*/


/*
  voltaje = (lecturaSensor * 3.3) / 1024.0;
  tempC = (voltaje * 1)/0.01;

  Serial.print ("Temperatura: ");
  Serial.println (tempC, 1);
  //Serial.print ("Voltaje: ");
  //Serial.println (voltaje);
*/

// FUNCIONAMIENTO DEL CRONOMETRO

   inicio:
  if (lecturaPotenciometro >= 11 ){
    a = 1;
    b = 0;
    while (a == 1){
      contador:
    milisegundos = millis();
    
    if (milisegundos % 100 == 0){
        decimas++;
        
        if (decimas == 10){
          decimas = 0;
          segundos++;
          }
        if (segundos == 60){
          segundos = 0;
          minutos++;           
          }
        if (minutos == 60){
          minutos = 0;
          horas++;             
          }
     lcd.setCursor(0, 1);
        if (horas < 10)        {
          lcd.print("0");      }
          lcd.print(horas);
          lcd.print(":");
          lcd.setCursor(3, 1);
        if (minutos < 10)      {
          lcd.print("0");      }
        lcd.print(minutos);
        lcd.print(":");
        lcd.setCursor(6, 1);
        if (segundos < 10)     {
        lcd.print("0");        }
        lcd.print(segundos);

        
        if (digitalRead(buton_pausa) == false)      {
        delay(200);
          a = 0;
          b = 1;
          while (b == 1)                       {
            if (digitalRead( buton_inicio) == false) {
            goto contador;

            }
            if (digitalRead(buton_reset) == false)   { 
              horas = 0;
              minutos = 0;
              segundos = 0;
              decimas = 0;
              lcd.clear();
              delay(200);
              goto inicio;    }
          }
        }
        if (digitalRead(buton_reset) == false) 
        { 
          a = 0;                          
          horas = 0;                        
          minutos = 0;
          segundos = 0;
          decimas = 0;
          lcd.clear();
          delay(200);   
          goto inicio;  
        }
      }
    }
  }
}
