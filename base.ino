int IN3 = 1;    // Input3 conectada al pin 5 -> bomba
int IN4 = 2;    // Input4 conectada al pin 4 -> bomba
int ENB = 3;    // ENB conectada al pin 3 de Arduino -> Enable de bomba
int VALV = 12;
int SENS = A3;
int POTEN = A1;
bool bandera = 1;

int sensor;
int medicion;
int potenciometro;
int margen = 10;
int margenSuperior;
int margenInferior;

void setup()
{
  pinMode(ENB, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(VALV, OUTPUT);

  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  
  Serial.begin(9600);
  

 
}


void loop()
{
  sensor = analogRead(SENS);
  potenciometro = 600;
  

  
  margenSuperior = potenciometro + margen;
  margenInferior = potenciometro - margen;

  if(bandera){
    if(sensor > potenciometro){
      analogWrite(ENB, 0);
      analogWrite(VALV, 255);
    }
    else if(sensor < potenciometro){
      analogWrite(ENB, 255);
      analogWrite(VALV, 0);
    }
    else bandera = 0;
  }
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

  Serial.println(sensor);
  delay(100);
}
