#define M1 5
#define M2 3
#define M3 11
#define M4 10
#define PIR A0

#define M1E1 6
#define M1E2 7

#define M2E1 4
#define M2E2 2

#define M3E1 13
#define M3E2 12

#define M4E1 9
#define M4E2 8

//ME = MotoresEntradas
int ME[] = {M1E1 , M1E2 , M2E1 , M2E2 , M3E1 , M3E2 , M4E1 , M4E2};
int Motores[] = {M1 , M2 , M3 , M4};

int W[] = {1 , 0 , 1 , 0 , 1 , 0 , 1 , 0};
int A[] = {0 , 0 , 1 , 0 , 0 , 0 , 1 , 0};
int S[] = {0 , 1 , 0 , 1 , 0 , 1 , 0 , 1};
int D[] = {1 , 0 , 0 , 0 , 1 , 0 , 0 , 0};
int F[] = {1 , 1 , 1 , 1 , 1 , 1 , 1 , 1};
int R[] = {0 , 0 , 0 , 0 , 0 , 0 , 0 , 0};
int Q[] = {0 , 1 , 1 , 0 , 0 , 1 , 1 , 0};
int E[] = {1 , 0 , 0 , 1 , 1 , 0 , 0 , 1};

char Dato;


void setup()
{
  pinConfig();
  configBT();
  Serial.begin(9800);
  Serial.setTimeout(50);
}

void loop()
{ 
  comunicacion();
  switch (Dato)
  {
    case 'w':
      evento(W); //avanzar
      break;
    case 'a':
      evento(A); //izquierda
      break;
    case 's':
      evento(S); //retroceder
      break;
    case 'd':
      evento(D); //derecha
      break;
    case 'f':
      evento(F); //frenar de golpe
      break;
    case 'r':
      evento(R); //frenar despacio
      break;
    case 'q':
      evento(Q); //izquierda sobre su eje
      break;
    case 'e':
      evento(E); //derecha sobre su eje
      break;
  }
}

void pinConfig()
{
  for( int PIN = 2 ; PIN < 14; PIN++)
  {
    pinMode(PIN , OUTPUT);
  }
  pinMode(PIR , INPUT);
}

void evento(int E[])
{
  for(int x = 0; x < sizeof(Motores) / 2; x++)
  {
    analogWrite(Motores[x] , 255);
  }

  for(int i = 0; i < sizeof(ME) / 2; i++)
  {
    digitalWrite(ME[i] , E[i]);
  }
}

void configBT()
{
  if(Serial.available())
  {
    Serial.print(Serial.read());
  } 
}

bool movRead()
{
  bool valor = analogRead(PIR);
  return valor;
}

void serialEvent()
{
  while (Serial.available())
  {
    Dato = Serial.read();
  }
  Serial.flush();
}

void comunicacion()
{
  if(movRead() == true)
  {
    if(!Serial.available())
    {
      Serial.write("Objeto detectado mas adelante!\n");
      delay(100);
    }
  }
}