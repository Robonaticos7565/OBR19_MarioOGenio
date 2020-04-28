// ------ LEDs Brancos 
#define ledDireita 22         // LED Branco Direito
#define ledEsquerda 30        // LED Branco Esqerdo


// ------ LEDs RGB 
#define ledVermelho 24        // LED RGB pin Vermelho
#define ledVerde 26           // LED RGB pin Verde
#define ledAzul 28            // LED RGB pin Azul


int sensor[] = {52, 46, A10, A11, 40, 38, A9, A8, A12, 44, A13, A14, A15, 50, 34, 48};
int sensorLinha[] = {digitalRead(sensor[3]), digitalRead(sensor[5]), digitalRead(sensor[0]), digitalRead(sensor[6]), digitalRead(sensor[2])};
int sensorF;
int motor[] = {6, 7, 5, 4}; // D1, D2, E1, E2
int poderMotor;
int btnRedutor = 48;

void clearLeds(){
  analogWrite(ledDireita, 0);
  analogWrite(ledEsquerda, 0);
  analogWrite(ledAzul, 0);
  analogWrite(ledVermelho, 0);
  analogWrite(ledVerde, 0);
}

int leitura = 0;
double kP = 8;
double tp = 95;
double turn;
double error;
//double media = 15; ((b+w)/2)/(b/100);
int leituraDoSensor;
int minPower = -95;
int maxPower = 95;



void Mover(int e, int d, int dlay) {
  if (e >= 0) {
    analogWrite(motor[2], e);
    analogWrite(motor[3], 0);
  } else {
    analogWrite(motor[2], 0);
    analogWrite(motor[3], abs(e));
  }
  if (d >= 0) {
    analogWrite(motor[0], d);
    analogWrite(motor[1], 0);
  } else {
    analogWrite(motor[0], 0);
    analogWrite(motor[1], abs(d));
  }
    delay(dlay);
}

int P(int s, int w, int b, float media, int plus){
    leituraDoSensor = analogRead (sensor[s]);
    leitura = map(leituraDoSensor,w,b,0,100);//450,1005
    error = leitura - media;//72,388 (b+w)/2)/(b/100)
    turn = kP * error;
    poderMotor = tp - turn;
    if (poderMotor < minPower){
      poderMotor = minPower;
    }
    if (poderMotor > maxPower){
      poderMotor = maxPower;
    }
    poderMotor += plus;
  return poderMotor;
}

void SimNao(){
  if(digitalRead(sensor[3]) == 0 && digitalRead(sensor[2]) == 1)
{
  Mover(120,-80,0);
}

if(digitalRead(sensor[2]) == 0 && digitalRead(sensor[3]) == 1)
{
  Mover(-80,130,0);
}
if(digitalRead(sensor[2]) == 0 && digitalRead(sensor[3]) == 0 && digitalRead(sensor[13]) == 1)
{
  Mover(100,140,0);
}
if(digitalRead(sensor[2]) == 1 && digitalRead(sensor[3]) == 1 && digitalRead(sensor[13]) == 1)
{
  Mover(100,140,0);
}
if(digitalRead(sensor[2]) == 0 && digitalRead(sensor[3]) == 0 && digitalRead(sensor[13]) == 0)
{
  Mover(100,140,0);
}

}

void Correcao(){
  if (P(3,310,1000,65.5,0) > P(2,210,950,61.05,40)){ //2Direita, 3Esq
    Mover(P(3,310,1000,65.5,0),P(3,310,1000,65.5,0)*-1,0);
  }
  if (P(3,310,1000,65.5,0) < P(2,210,950,61.05,40)){ //2Direita, 3Esq
    Mover(P(2,210,950,61.05,0)*-1,P(2,210,950,61.05,40),0);
  }
}

void VirarComGyro(int e, int d, float grau){
    LerGyro();
    angleZVar = angleZ + grau;
    if (grau > 0){
      do{
      LerGyro();
      Mover(e, d, 0);
    }while(angleZVar >= angleZ);
    }else{
      do{
      LerGyro();
      Mover(e, d, 0);
    }while(angleZVar <= angleZ);
    }
}

//if (analogRead(A0) > 230){
//      clearLeds();
//      digitalWrite(ledVermelho, HIGH);
//      digitalWrite(ledEsquerda, HIGH);
//      digitalWrite(ledDireita, HIGH);
//      Mover(0,0,500);
//      
//      if(analogRead(A0) < 230){
//        return;
//      }
//    VirarComGyro(120, -150, -55);
//    Mover(0,0,300);
//    
//    do{
//      Mover(90,120,0);
//    }while(analogRead(A4) < 350);
//    
//    while (analogRead(A4) > 350){
//      Mover(90,120,0);      
//    };
//    
//    Mover(90,120,500);
//    Mover(0,0,300);
//    VirarComGyro(-120, 150, 55);
//    Mover(0,0,300);
//    
//    do{
//      Mover(90,120,0);
//    }while(analogRead(A4) < 350);
//    
//    do{
//      Mover(90,120,0);
//    }while(analogRead(A4) > 350);
//    Mover(90,120,500);
//    Mover(0,0,300);
//    VirarComGyro(-120, 150, 55);
//    Mover(0,0,300);
//    do{
//      Mover(90,120,0);
//    }while(analogRead(A4) < 350);
//    do{
//      Mover(90,120,0);
//    }while(digitalRead(sensor[7]) == 0);
//    Mover(0,0,300);
//    VirarComGyro(120, -150, -55);
//    if(LS[5] == P){
//      return;
//    }
//    Mover(-90,-90,600);
//    
//    if(LS[5] == P){
//      return;
//    }
//    Mover(90,120,0);
//  }

void Noventa(byte aserGay){
  if(aserGay==0){
    if(digitalRead(sensor[13]) == 1){
        Mover(100,140,0);
      return;
    }
    Mover(100,140,350);
    clearLeds();
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledDireita, HIGH);
    Mover(0,0, 300);
    VirarComGyro(-150, 130, 25);
    do{
      Mover(-150, 130, 0);
    }while(digitalRead(sensor[13]) == 0);
    Mover(0,0, 300);
    Mover(-110, -110, 250);
  }
  if(aserGay==1){
    Mover(0,0, 300);
    if(digitalRead(sensor[13]) == 1){
      Mover(100,140,0);
      return;
    }
    Mover(100,140,350);
    clearLeds();
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledEsquerda, HIGH);
    Mover(0,0, 300);
    VirarComGyro(150, -150, -25);
    do{
      Mover(150, -150, 0);
    }while(digitalRead(sensor[13]) == 0);
    Mover(0,0, 300);
    Mover(-110, -110, 250);
  }
}

void Verde(byte AserViado){
  if(AserViado==0){
    Mover(100,140,200);
    clearLeds();
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledEsquerda, HIGH);
    VirarComGyro(150,-150,-30);
    do{Mover(150,-150,0);}while(digitalRead(sensor[13])==0);
    Mover(0,0,300);
    Mover(-110,-120,250);
  }
  if(AserViado==1){
    Mover(100,140,200);
    clearLeds();
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledDireita, HIGH);
    VirarComGyro(-150,130,30);
    do{Mover(-150,130,0);}while(digitalRead(sensor[13])==0);
    Mover(0,0,300);
    Mover(-110,-120,250);
  }
}

void Cento(){
  clearLeds();
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledDireita, HIGH);
    digitalWrite(ledEsquerda, HIGH);
  VirarComGyro(-150,150,110);
  Mover(-110,-120,250);
}



void TesteSensores(){
     int S0 = digitalRead(sensor[0]);   // dir meio
     int S1 = digitalRead(sensor[1]);    // esq meio
     int S2 = digitalRead(sensor[2]);    // segue line dir A10
     int S3 = digitalRead(sensor[3]);    // segue line esq A11
     int S4 = digitalRead(sensor[4]);   // extreme dir 40
     int S5 = digitalRead(sensor[5]);    // extreme esq 38
     int S6 = analogRead(sensor[6]);   // verde dir A9
     int S7 = analogRead(sensor[7]);   // verde esq A8
     int S8 = analogRead(sensor[8]);    // verde dir baixo
     int S9 = digitalRead(sensor[9]);    // meio baixo
     int S10 = analogRead(sensor[10]);  // verde esq baixo
     int S11 = analogRead(sensor[11]);  // p dir baixo
     int S12 = analogRead(sensor[12]);  // p esq baixo
     int S13 = digitalRead(sensor[13]);  // avancado 50
     int S14 = digitalRead(sensor[14]);  // meio cima 34
     int S15 = digitalRead(sensor[15]);  // recuado 48

     int Sh0 = analogRead(A0); //frente esq
     int Sh1 = analogRead(A1); //frente dir
     int Sh2 = analogRead(A2); //dir cima
     int Sh3 = analogRead(A3); //baixo dir
     int Sh4 = analogRead(A4); //baixo esq
     int Sh5 = analogRead(A5); //dentro
     int Sh6 = analogRead(A6); //cima esq
     int Sh7 = analogRead(A7); //cima esq
     
     Serial.print ("LFS: L  0 1 2 3 4 5 6 7  R ==> "); 
     Serial.print (S8); 
//     Serial.print (" ");
//     Serial.print (S3); 
     Serial.print (" ");
     Serial.print (S10); 
//     Serial.print (" ");
//     Serial.print (S7); 
//     Serial.print (" ");
//     Serial.print (S1);
//     Serial.print (" ");
//     Serial.print (S10); 
//     Serial.print (" ");
//     Serial.print (S12); 
     Serial.println ("  ");
//     Serial.print (S7); 
//     Serial.print ("  ");
//     Serial.print (S8); 
//     Serial.print ("  ");
//     Serial.print (S9); 
//     Serial.print ("  ");
//     Serial.print (S10); 
//     Serial.print ("  ");
//     Serial.print (S11); 
//     Serial.print ("  ");
//     Serial.print (S12); 
//     Serial.print ("  ");
//     Serial.print (S13); 
//     Serial.print ("  ");
//     Serial.print (S14); 
//     Serial.print ("  ");
//     Serial.print (S15); 
//     Serial.print ("  ");
//     Serial.println (" "); 
//     Serial.print (turn);
//     Serial.print ("   ");
//     Serial.print (leitura);
//     Serial.print (" ");
//     Serial.print (poderMotor);
//     Serial.print (" ");
//     Serial.println (error);
}

void AlertaDeInicio() {
  analogWrite(ledDireita, 255);
  analogWrite(ledEsquerda, 255);
  analogWrite(ledAzul, 255);
  delay(25);
  analogWrite(ledDireita, 0);
  analogWrite(ledEsquerda, 0);
  analogWrite(ledAzul, 0);
  delay(50);
  analogWrite(ledDireita, 255);
  analogWrite(ledEsquerda, 255);
  analogWrite(ledVermelho, 255);
  delay(25);
  analogWrite(ledDireita, 0);
  analogWrite(ledEsquerda, 0);
  analogWrite(ledVermelho, 0);
  delay(50);
  analogWrite(ledDireita, 255);
  analogWrite(ledEsquerda, 255);
  analogWrite(ledVerde, 255);
  delay(25);
  analogWrite(ledDireita, 0);
  analogWrite(ledEsquerda, 0);
  analogWrite(ledVerde, 0);
}

