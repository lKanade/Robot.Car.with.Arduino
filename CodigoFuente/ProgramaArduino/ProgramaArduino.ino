#include <SoftwareSerial.h>

// CONTROL DEL MOTOR DERECHO
int Contor_In1 = 7;
int Contor_In2 = 6;

// CONTROL DEL MOTOR IZQUIERDO
int Contor_In3 = 5;
int Contor_In4 = 4;

// VARIABLES PARA CONTROLAR EL SENSOR ULTRASONICO O DE PROXIMIDAD
long dist;
long time;
char e = 'S';

//BT
SoftwareSerial BT(10, 11); // RX | TX

void setup() {
  // PIN DE LOS MOTORES
  pinMode(Contor_In1, OUTPUT);
  pinMode(Contor_In2, OUTPUT);
  pinMode(Contor_In3, OUTPUT);
  pinMode(Contor_In4, OUTPUT);

  // PIN PARA EL SENSOR DE PROXIMIDAD
  Serial.begin(9600);
  pinMode(9,INPUT); //9 ENTRADA DE DATOS ECCO
  pinMode(8, OUTPUT); //8 SALIDA DE DATOS TRIGGER

  // FUNCIONES BT

  BT.begin(9600); // inicia el puerto serial para comunicacion con el Bluetooth
  Serial.println("Esperando comandos AT:");
  Serial.println("Activando el modulo HC-04");

  // LEDS
  pinMode (3, OUTPUT); // Luz de freno
  pinMode (2, OUTPUT); // Luz blanca
  pinMode (12, OUTPUT); // Intermitente Izquierda
  pinMode (13, OUTPUT); // Intermitente Derecha
} //FIN DEL METODO SETUP

void loop() {
  Bt();
}//FIN DEL METODO LOOP

// FUNCIONALIDAD DEL SENSOR
void Sensor(){
  Run();
  digitalWrite(8,LOW);
  delayMicroseconds(5);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  time = pulseIn(9, HIGH);
  dist = (0.017*time);
  delay(10);
  Serial.print("Distancia: ");
  Serial.print(dist);
  Serial.println(" cm/hr");
  if(dist < 40){
    Stop();
    delay(1000);
    Reverse();
    delay(500);
    Stop();
    delay(1000);
    int d = random(0, 3);
    if(d == 2){ 
      Serial.println("Girar a la izquierda");
      Serial.println(d);
      Left();
      delay(1000);
      Stop();
      delay(700);
    } else if (d == 1){ // FIN DEL IF
      Serial.println("Girar a la derecha");
      Serial.println(d);
      Right();
      delay(1000);
      Stop();
      delay(700);
    } else if ((d == 0) or (d == 3) ){ // FIN DEL IF
      Serial.println("Numero seleccionado:  ");
      Serial.println(d);
      Stop();
      delay(700);
      Reverse();
      delay(800);
      Stop();
      delay(700);
    } // FIN DEL IF
  } // FIN DEL IF PRINCIPAL
} // FIN DEL METODO SENSOR

// FUNCIONALIDAD DE LOS MOTORES

void Run(){
  digitalWrite (2, HIGH);
  digitalWrite (3, LOW);
  digitalWrite(Contor_In1, HIGH);
  digitalWrite(Contor_In2, LOW);
  digitalWrite(Contor_In3, LOW);
  digitalWrite(Contor_In4, HIGH); 
}//FIN DEL METODO RUN

void Reverse(){
  digitalWrite (3, LOW);
  digitalWrite(Contor_In1, LOW);
  digitalWrite(Contor_In2, HIGH);
  digitalWrite(Contor_In3, HIGH);
  digitalWrite(Contor_In4, LOW);
}//FIN DEL METODO REVERSE

void Stop(){
  digitalWrite (3, HIGH);
  digitalWrite (12, LOW);
  digitalWrite (13, LOW);
  digitalWrite(Contor_In1, LOW);
  digitalWrite(Contor_In2, LOW);
  digitalWrite(Contor_In3, LOW);
  digitalWrite(Contor_In4, LOW);
}//FIN DEL METODO STOP

void Right(){
  digitalWrite (13, HIGH);
  delay(200);
  digitalWrite (13, LOW);
  delay(200);
  digitalWrite (13, HIGH);
  delay(200);
  digitalWrite (13, LOW);
  delay(200);
  digitalWrite (13, HIGH);
  delay(200);
  digitalWrite (13, LOW);
  delay(200);
  digitalWrite (3, LOW);
  digitalWrite(Contor_In1, HIGH);
  digitalWrite(Contor_In2, LOW);
  digitalWrite(Contor_In3, LOW);
  digitalWrite(Contor_In4, LOW);
}//FIN DEL METODO RIGHT

void Left(){
  digitalWrite (12, HIGH);
  delay(200);
  digitalWrite (12, LOW);
  delay(200);
  digitalWrite (12, HIGH);
  delay(200);
  digitalWrite (12, LOW);
  delay(200);
  digitalWrite (12, HIGH);
  delay(200);
  digitalWrite (12, LOW);
  delay(200);
  digitalWrite (3, LOW);
  digitalWrite(Contor_In1, LOW);
  digitalWrite(Contor_In2, LOW);
  digitalWrite(Contor_In3, LOW);
  digitalWrite(Contor_In4, HIGH);
}//FIN DEL METODO LEFT

// CONDEXION BT

void Bt(){

if(BT.available() > 0){
    e = BT.read();
  }

    if(e == 'A'){
      e = '*';
      Run();
    }

    
    if(e == 'I'){
      e = '*';
      Left();
    }

    
    if(e == 'D'){
      e = '*';
      Right();
    }
    
    if(e == 'R'){
      e = '*';
      Reverse();
    }

    if(e == 'S'){
      e = '*';
      Stop();
    }
    
    if(e == '1'){
      Sensor();  
    }
}//FIN DEL METODO BT

