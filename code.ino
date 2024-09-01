#include <HCSR04.h>                 //Library HCSR04
#include <LiquidCrystal_I2C.h>      //Library LCD I2C
#include <Servo.h>                  //Library Servo

Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);   //Alamat I2C
HCSR04 hc(5,6);                     //initialisation class HCSR04 (trig pin , echo pin)

float TinggiSensor = 10.21;         //Tinggi pemasangan sensor
float TinggiAir;                    //Tinggi air
int bendungan;                      //Posisi bendungan

void setup() {
  lcd.init ();            //Mulai LCD
  lcd.setBacklight(HIGH);
  myservo.attach(9);      //Servo pada pin D9
}

void loop() {
  TinggiAir = TinggiSensor - hc.dist();       //Rumus mencari tinggi air
  bendungan = map(TinggiAir, 0, 12, 0, 100);  //konversi ke persen

  if (TinggiAir > 12){      //Jika melebihi tinggi maksimal
    TinggiAir = 12;
    bendungan = 100;
  }
  else if (TinggiAir < 0){  //Jika error nilai < 0
    TinggiAir = 0;
    bendungan = 0;
  }
  
  lcd.setCursor(0,0);
  lcd.print("T Air : ");
  lcd.print(TinggiAir);                   //Tampilkan tinggi air
  lcd.print("cm");

  lcd.setCursor(0,1);
  lcd.print("Bendungan : ");
  lcd.print(bendungan);                   //Tampilkan posisi bendungan
  lcd.print("%");

  bendungan = map(bendungan, 0, 100, 0, 90);  //Konversi ke sudut 0* - 90*
  myservo.write(bendungan);
  
  delay(1000);
  lcd.clear();
}
