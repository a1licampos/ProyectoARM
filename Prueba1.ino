int boton1 = 0; //BLANCO
int boton2 = 0; //ROJO
int boton3 = 0; //VERDE
int boton4 = 0; //AZUL

bool fin = false; //BTN 1
bool fin2 = false; //BTN 2
bool fin3 = false; //BTN 3
bool fin4 = false; //BTN 4


int votos = 0;

int jug1 = 0;
int jug2 = 0;
int jug3 = 0;
int jug4 = 0;

bool toques = false;

unsigned long tiempo1 = 0; //Verde
unsigned long tiempo2 = 0; //Amarillo
unsigned long tiempo3 = 0; //Rojo
unsigned long tiempoGeneral = 0; //Tiempo Padre

bool tiempoSinVotacion = true;

void setup() {
  Serial.begin(9600);
  
  //SEMÁFORO
  pinMode(2, OUTPUT);                   //LED VERDE
  pinMode(3, OUTPUT);                   //LED AMARILLO
  pinMode(4, OUTPUT);                   //LED ROJO
  
  pinMode(5, OUTPUT);                   //5 BLANCO
  pinMode(6, OUTPUT);                   //6 ROJO
  pinMode(7, OUTPUT);                   //7 VERDE
  pinMode(8, OUTPUT);                   //8 AZUL

  //BOTONES
  pinMode(9, INPUT);                    // 9 BOTÓN 1
  pinMode(10, INPUT);                   // 10 BOTÓN 2
  pinMode(11, INPUT);                   // 11 BOTÓN 3
  pinMode(12, INPUT);                   // 12 BOTÓN 4

  //Conexión toques
  pinMode(13, OUTPUT);
  
  tiempo1 = millis();
  tiempo2 = millis();
  tiempo3 = millis();
  
  Serial.println("Comenzamos...");
}
 
void loop(){

  //ACUTALIZAMOS EL TIEMPO QUE QUEREMOS
  tiempoGeneral = millis();


  //VERDE
  if (tiempoSinVotacion){
      if(tiempoGeneral > (tiempo1 + 5000) ){
          digitalWrite(2, HIGH); 
          digitalWrite(4, LOW);
      }
    
      //AMARILLO
      if (tiempoGeneral > (tiempo2 + 8000) ){
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
      }
    
      
      //ROJO
      if (tiempoGeneral > (tiempo3 + 10000) ){
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        digitalWrite(13, HIGH);
          tiempo1 = millis();
          tiempo2 = millis();
          tiempo3 = millis();
      }
  }

  //ASIGNAMOS A LA VARIABLE EL PIN A LEER
  boton1 = digitalRead(9);
  boton2 = digitalRead(10);
  boton3 = digitalRead(11);
  boton4 = digitalRead(12);

  
  //CONTADOR DE VOTOS
  if(boton1 == HIGH && !fin && votos < 4){ 
    digitalWrite(5, HIGH); 
      Serial.println("ENCENDIDO BOTÓN 1");
        fin = true;
          votos++;
            jug1++;
      Serial.println(votos);
  }

  if(boton2 == HIGH && !fin2 && votos < 4){ 
    digitalWrite(6, HIGH); 
      Serial.println("ENCENDIDO BOTÓN 2");
        fin2 = true;
          votos++;
            jug2++;
      Serial.println(votos);
  }


  if(boton3 == HIGH && !fin3 && votos < 4){ 
    digitalWrite(7, HIGH); 
      Serial.println("ENCENDIDO BOTÓN 3");
        fin3 = true;
          votos++;
            jug3++;
      Serial.println(votos);
  }

  if(boton4 == HIGH && !fin4 && votos < 4){ 
      digitalWrite(8, HIGH); 
      Serial.println("ENCENDIDO BOTÓN 4");
        fin4 = true;
          votos++;
            jug4++;
      Serial.println(votos);
  }


  //APAGAR LOS LED PARA VOLVER A VOTAR
  if(fin){
    delay(1000);
      digitalWrite(5, LOW);
        fin = false;
  }

  if(fin2){
    delay(1000);
      digitalWrite(6, LOW);
        fin2 = false;
  }

    if(fin3){
    delay(1000);
      digitalWrite(7, LOW);
        fin3 = false;
  }

    if(fin4){
    delay(1000);
      digitalWrite(8, LOW);
        fin4 = false;
  }


  //VERIFICAR VOTOS
  if(votos == 4){

      tiempoSinVotacion = false;
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      
      if(jug1 >= 3 && !toques){
        Serial.println("JUGADOR 1 RECIBE TOQUES");
          toques = true;
      }

      if(jug2 >= 3 && !toques){
        Serial.println("JUGADOR 2 RECIBE TOQUES");
          toques = true;
      }

      if(jug3 >= 3 && !toques){
        Serial.println("JUGADOR 3 RECIBE TOQUES");
          toques = true;
      }

      if(jug4 >= 3 && !toques){
        Serial.println("JUGADOR 4 RECIBE TOQUES");
          toques = true;
      }

      delay(5000);
      OtraVez();
  }

  
  
}

void OtraVez(){
  votos = 0;
  jug1 = 0;
  jug2 = 0;
  jug3 = 0;
  jug4 = 0;
  toques = false;
  tiempoSinVotacion = true;
  Serial.println("\nOtra Ronda!\n");
}
