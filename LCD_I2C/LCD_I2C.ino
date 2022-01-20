#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define COLUMNA       16
#define LINEA         2
#define I2C_DISP_ADR  0x27
#define DISCHARGE_PIN 8  //NPN + DIODE
#define PULSE_PIN     9  //VCC + PNP + 1000R
#define ESR_PIN       A0
#define SAMPLES       100


byte    esrSamples;
double  esr;
int     milliVolts;
//int     Rs = 1100.0;
int     ADCvRef = 0;

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(I2C_DISP_ADR, COLUMNA, LINEA);  //

int vRefADC(){
  long result;
  // Lee 2.56V de referencia interna respecto a Vdd
  //ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  // Lee 2.56V de referencia interna respecto a Vdd, selecciona ADC0
  ADMUX = _BV(REFS1) | _BV(REFS0);

  delay(2); //Espera a que Vdd se estabilice.
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  Serial.println(ADCvRef);
  result = 1125300L / result; //Recalcula la tension en mV
  return result;
}

void setup() {
  char linea[16];
  // Inicializar el LCD
  lcd.init();
  Serial.begin(9600);
  // Escribimos el Mensaje en el LCD.
  lcd.setCursor(0, 0);
  lcd.print("ESR Meter");
  delay(1000);  
  //Encender la luz de fondo.
  lcd.backlight();
  ADCvRef = vRefADC();
  Serial.print("ADCvRef:  ");
  Serial.println(ADCvRef);
  lcd.setCursor(0, 0);
  sprintf(linea, "%d", ADCvRef);
  lcd.print(linea);
  delay(2000);
}

void loop() {
   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
   // Escribimos el número de segundos trascurridos
  lcd.print(millis()/1000);
  lcd.print(" Segundos");
  delay(100);
}