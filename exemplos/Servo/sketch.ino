/* 

  Feito por Koepel

*/

#include <Servo.h>

#define NUM_SERVOS 32
Servo myServo[NUM_SERVOS];

void setup() 
{
  // Conectar pinos do Arduino Mega para os Servo-motores.
  // Começando no pino 22, deve haver exatamente 32 espaços.
  for( int i=0; i<NUM_SERVOS; i++)
  {
    myServo[i].attach( i + 22);     
  }
}


void loop() 
{
  // Primeira sequência.
  // Servo-motores setados em ângulos aleatórios
  for( int a=0; a<15; a++)
  {
    for( int i=0; i<NUM_SERVOS; i++)
    {
      myServo[i].write( random( 0, 181));
      delay( 2);
    }
    delay( 150);
  }

  // Segunda sequência.
  // Servo-motres movimentam no mesmo ângulo.
  for( int i=0; i<NUM_SERVOS; i++)
  {
    myServo[i].write( 0);            
  }
  delay( 1000);                     
  
  for( int a=0; a<3; a++)
  {
    for( int r=0; r<=180; r++)       // mover para a direita
    {
      for( int i=0; i<NUM_SERVOS; i++)
      {
        myServo[i].write( r);
      }
      delay( 6);
    }
    for( int r=180; r>=0; r--)
    {
      for( int i=0; i<NUM_SERVOS; i++)  // mover para a esquerda
      {
        myServo[i].write( r);
      }
      delay( 6);
    }
  }


  // Terceria sequência.
  // Efeito onda em rotação.
  for( int a=0; a<6; a++)
  {
    for( int i=0; i<NUM_SERVOS; i++)
    {
      for( int j=0; j<NUM_SERVOS; j++)
      {
        // Calculate distance to active servo
        int d = j - i;
        if( d < 0)
          d = -d;
        if( d > (NUM_SERVOS / 2))
          d = NUM_SERVOS - d;

        int angle = 90 - (10 * d);
        if( angle < 0)
          angle = 0;
        myServo[j].write( angle);
      }
      delay(40);
    }
  }


  // Quarta sequência.
  // "Compasso"
  
  int pointer = NUM_SERVOS * 3 / 4;
  showPointer( pointer);
  delay( 1000);                       

  for( int i=0; i<5; i++)
  {
    showPointer( --pointer);
    delay( 150);
  }
  delay( 200);
  for( int i=0; i<9; i++)
  {
    showPointer( ++pointer);
    delay( 150);
  }
  delay( 200);
  for( int i=0; i<5; i++)
  {
    showPointer( --pointer);
    delay( 150);
  }
  delay( 200);
  for( int i=0; i<4; i++)
  {
    showPointer( ++pointer);
    delay( 150);
  }
  delay( 160);
  for( int i=0; i<2; i++)
  {
    showPointer( --pointer);
    delay( 150);
  }
  delay( 80);
  for( int i=0; i<1; i++)
  {
    showPointer( ++pointer);
    delay( 150);
  }

  delay( 2000);
}



// Funções extras



// Criar e mostrar determinados ponteiros 
void showPointer( int s)
{
  int pointerA = s % NUM_SERVOS;        
  int pointerB = (s + 1) % NUM_SERVOS;  
  int tailA = (s + 16) % NUM_SERVOS;
  int tailB = (s + 17) % NUM_SERVOS;

 
  myServo[pointerA].write(180-56);
  myServo[pointerB].write(56);


  myServo[tailA].write(95);
  myServo[tailB].write(85);

  
  int n = (NUM_SERVOS / 2) - 2;
  int start = pointerB + 1;
  for( int i=0; i<n; i++)
  {
    int j = (start + i) % NUM_SERVOS;
    myServo[j].write( 2);
  }

 
  start = tailB + 1;
  for( int i=0; i<n; i++)
  {
    int j = (start + i) % NUM_SERVOS;
    myServo[j].write( 178);
  }
}



// Criar o arquivo "diagram.json". Configurações do projeto.
void GenerateDiagram()
{
  Serial.begin(115200);

  Serial.print( "{\n");
  Serial.print( "  \"versão\": 1,\n");
  Serial.print( "  \"autor\": \"Generated\",\n");
  Serial.print( "  \"editor\": \"wokwi\",\n");
  Serial.print( "  \"partes\": [\n");

  Serial.print( "    {\n");
  Serial.print( "      \"tipos\": \"wokwi-arduino-mega\",\n");
  Serial.print( "      \"id\": \"mega\",\n");
  Serial.print( "      \"top\": 270,\n");
  Serial.print( "      \"left\": 185,\n");
  Serial.print( "      \"attrs\": {}\n");
  Serial.print( "    },\n");

  // Put the servo motor in reverse order in the diagram.json
  // I think that is visually better.
  // The horn now overlaps the next servo when the horn moves to the right.
  for( int i=NUM_SERVOS-1; i>=0; i--)
  {
    float rotate = float( i) * (360.0 / float( NUM_SERVOS));
    float rad = rotate / 360.0 * 2.0 * M_PI;
    float top = (300.0 * sin( rad)) + 300.0;
    float left = (300.0 * cos( rad)) + 300.0;
    Serial.print( "    {\n");
    Serial.print( "      \"tipos\": \"wokwi-servo\",\n");
    Serial.print( "      \"id\": \"servo");
    Serial.print( i);
    Serial.print( "\",\n");
    Serial.print( "      \"em cima\": ");
    Serial.print( top);
    Serial.print( ",\n");
    Serial.print( "      \"esquerda\": ");
    Serial.print( left);
    Serial.print( ",\n");
    Serial.print( "      \"girar\": ");
    Serial.print( rotate);
    Serial.print( ",\n");
    Serial.print( "      \"attrs\": { \"hornColor\": \"Vermelho\" }\n");
    Serial.print( "    }");
    if( i != 0)
      Serial.print( ",");
    Serial.print( "\n");
  } 

  Serial.print( "  ],\n");
  Serial.print( "  \"conexões\": [\n");

  for( int i=0; i<NUM_SERVOS; i++)
  {
    int j = i + 1;
    if( j == NUM_SERVOS)
      j = 0;
    Serial.print( "    [ \"servo");
    Serial.print( i);
    Serial.print( ":V+\", \"servo");
    Serial.print( j);
    Serial.print( ":V+\", \"Vermelho\", [] ],\n");
    Serial.print( "    [ \"servo");
    Serial.print( i);
    Serial.print( ":GND\", \"servo");
    Serial.print( j);
    Serial.print( ":GND\", \"Preto\", [] ],\n");

    Serial.print( "    [ \"mega:");
    Serial.print( i + 22);
    Serial.print( "\", \"servo");
    Serial.print( i);
    Serial.print( ":PWM\", \"Verde\", [ ] ],\n");
  }
  Serial.print( "    [ \"mega:GND.2\", \"servo9:GND\", \"Preto\", [ ] ],\n");
  Serial.print( "    [ \"mega:5V\", \"servo9:V+\", \"Vermelho\", [ ] ]\n");

  Serial.print( "  ]\n");
  Serial.print( "}\n");
}







