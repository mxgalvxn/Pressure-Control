#include<TimerOne.h>
int IN3 = 5; // Input3 conectada al pin 5 -> bomba
int IN4 = 4; // Input4 conectada al pin 4 -> bomba
int ENB = 3; // ENB conectada al pin 3 de Arduino -> Enable de bomba
int VALV = 8;
int SENS = A0;
int POTEN = A1;
bool bandera = 1;
int sensor;
int medicion;
int potenciometro;
int margen = 10;
int margenSuperior;
int margenInferior;
const int interruptPin = 2;
long unsigned int counter = 0;
double presion = 0.0;
float tiempo = 0.0;
float T = 0.02;
//Parámetros del PID
float referencia = POTEN;
float Kp = 3;
float Ti = 7;
float Td = 0.0;
float Kp1 = -.002;
float Ti1 = .002;
float Td1 = 0.0;
//Parámetros del control PID Discreto
float K0 = Kp+(Kp*T/Ti)+(Kp*Td/T);
float K1 = -Kp-2*Kp*Td/T;
float K2 = Kp*Td/T;
//Inicializar el error y el control
28
float e = 0, e1 = 0, e2 = 0;
float u = 0, u1 = 0;
void setup()
{
pinMode(ENB, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(VALV, OUTPUT);
digitalWrite (IN3, HIGH);
digitalWrite (IN4, LOW);
attachInterrupt(digitalPinToInterrupt(interruptPin), counting,
RISING);
Timer1.initialize(20000);
Serial.begin(9600);
}
void loop()
{
sensor = analogRead(SENS);
potenciometro = analogRead(POTEN);
potenciometro = map(potenciometro,70,950,60,320);
margenSuperior = potenciometro + margen;
margenInferior = potenciometro - margen;
if(bandera){
if(sensor > potenciometro){
Timer1.attachInterrupt(llenar);
analogWrite(VALV, 255);
}
else if(sensor < potenciometro){
analogWrite(ENB, 255);
analogWrite(VALV, 0);
}
else bandera = 0;
}
29
else{
if(sensor < margenSuperior && sensor > margenInferior){
analogWrite(ENB, 0);
analogWrite(VALV, 0);
}
else if(sensor > margenSuperior){
analogWrite(ENB, 0);
analogWrite(VALV, 255);
bandera = 1;
}
else if(sensor < margenInferior){
analogWrite(ENB, 255);
analogWrite(VALV, 0);
bandera = 1;
}
}
Serial.print(potenciometro);
Serial.print("\t");
Serial.println(sensor);
delay(100);
}
void counting(){
counter++;
}
void llenar(){
//Calculo de las RPM
presion = sensor*(1450)/500;
tiempo = tiempo + T;
referencia = 3500;
e = referencia-sensor;
u = u1 + K0*e + K1*e1 + K2*e2;
if(u>255){
u = 255;
}
else if (u<0){
u = 0;
}
analogWrite(ENB, u);
u1 = u;
e2 = e1;
30
e1 = e;
counter = 0;
}
