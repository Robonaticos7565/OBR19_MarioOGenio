/**
 *  Program: Mario O Gênio Robot Program
 *  Author: Josias Calebe e Matheus Santos
 *  Team Robonáticos
 *  Support: SESI and SENAI
*/

#include "Gyro.h"
#include "ViewController.h"
  int a;
  bool aserViado = false;

void setup() {
  Serial.begin(9600);

  LigarGyro();
  
  pinMode (sensor[0], INPUT);
  pinMode (sensor[1], INPUT);
  pinMode (sensor[2], INPUT);
  pinMode (sensor[3], INPUT);
  pinMode (sensor[4], INPUT);
  pinMode (sensor[5], INPUT);
  pinMode (sensor[6], INPUT);
  pinMode (sensor[7], INPUT);
  pinMode (sensor[8], INPUT);
  pinMode (sensor[9], INPUT);
  pinMode (sensor[10], INPUT);
  pinMode (sensor[11], INPUT_PULLUP);
  pinMode (sensor[12], INPUT_PULLUP);
  pinMode (sensor[11], INPUT);
  pinMode (sensor[12], INPUT);
  pinMode (sensor[13], INPUT);
  pinMode (sensor[14], INPUT);
  pinMode (sensor[15], INPUT);

  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (A3, INPUT);
  pinMode (A4, INPUT);
  pinMode (A5, INPUT);
  pinMode (A6, INPUT);
  pinMode (A7, INPUT);

  pinMode (51,INPUT_PULLUP); //button reductor

  pinMode (motor[0], OUTPUT);
  pinMode (motor[1], OUTPUT);
  pinMode (motor[2], OUTPUT);
  pinMode (motor[3], OUTPUT);
  AlertaDeInicio();
}


void loop() {
//TesteSensores();
//return;
//Mover(P(3,310,1000,65.5,0),P(2,210,950,61.05,40),0);
clearLeds();
//SimNao();
//return;
if(digitalRead(sensor[14]) == 1 && (digitalRead(sensor[4]) == 1 || digitalRead(sensor[5]) == 1)){
  Mover(-100,-100,1);
    while(digitalRead(sensor[0]) == 0 && digitalRead(sensor[1]) == 0){
      Mover(80,120,0);
    }
    if(digitalRead(sensor[0]) == 1 || digitalRead(sensor[1]) == 1){
    Mover(-100,-100,50);
          if(digitalRead(sensor[0]) == 0 && digitalRead(sensor[1]) == 1 && digitalRead(sensor[14]) == 0 && digitalRead(sensor[13]) == 0 && (analogRead(sensor[10]) < 770)){
              Noventa(0);
          }
          if(digitalRead(sensor[0]) == 1 && digitalRead(sensor[1]) == 0 && digitalRead(sensor[14]) == 0 && digitalRead(sensor[13]) == 0 && (analogRead(sensor[8]) < 700)){
              Noventa(1);
          }
          if(digitalRead(sensor[0]) == 1 && (analogRead(sensor[8]) > 700 && analogRead(sensor[8]) < 800) && (analogRead(sensor[10]) < 770)){
              Verde(0);
          }
          if(digitalRead(sensor[1]) == 1 && (analogRead(sensor[8]) < 700) && (analogRead(sensor[10]) > 770 && analogRead(sensor[10]) < 880)){
              Verde(1);
          }
          if(digitalRead(sensor[0]) == 1 && digitalRead(sensor[1]) == 1 && (analogRead(sensor[8]) > 700 && analogRead(sensor[8]) < 800) && (analogRead(sensor[10]) > 770 && analogRead(sensor[10]) < 880)){
              Cento();
          }
          
          //Mover(0,0,10000);
    }
  }
Mover(P(3,310,1000,65.5,0),P(2,210,950,61.05,40),0);
  //SimNao();

}
