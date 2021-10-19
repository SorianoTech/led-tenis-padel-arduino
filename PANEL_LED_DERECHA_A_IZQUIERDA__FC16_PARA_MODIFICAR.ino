#include <MD_MAX72xx.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define NUM_OF_MATRIX 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10
 
MD_MAX72XX cartel = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, NUM_OF_MATRIX);
 
String mensaje = "6";
 
String proximo_mensaje;
 
void setup() {
  // inicializar el objeto mx
  cartel.begin();
 
  // Establecer intencidad a un valor de 10
  cartel.control(MD_MAX72XX::INTENSITY, 1);
 
  // Desactivar auto-actualizacion
  cartel.control( MD_MAX72XX::UPDATE, false );
 
  // inicializar puerto Serie a 9600 baudios
  Serial.begin(9600);
}
void loop() {
  //tiempo que tarda en mover la letra
  slide_text( 1000 );
  //actualizar_mensaje();
}
//Funcion eliminada por que solo tenemos un mensaje
/*void actualizar_mensaje(){
 
  while( Serial.available() ){
 
    char c = Serial.read();
 
    if( c == '\n' ){
      mensaje = proximo_mensaje;
      proximo_mensaje = "";
      break;
    }
    else
      proximo_mensaje += c;
    
  }
}*/

//funcion para imprimir el carrusel
void slide_text(int ms_delay){
  int col = 0;
  int fila = 0;
  int last_pos;
  bool completo = false;
  
  cartel.clear();
 //bucle de comprobación de si ha terminado el mensaje
  printText(30,mensaje);
  
  //bucle para recorrer el carrusel
  /*while( completo == false ){
    last_pos = printText(col, mensaje);
    delay(ms_delay);
    col++;
    if( last_pos > (int)cartel.getColumnCount() )
      completo = true;
  }*/
}

//Función para imprimir 
int printText(int col, const String text){
  int w;
  //int f;
  
  for( int i = 0; i < text.length();i++ ){
    // imprimir letra
    w = cartel.setChar( col, text[i] );
    //f=cartel.setChar(fil,text[i]); 
    // la proxima letra empieza donde termina esta
    col = col - w; 
    // Se deja una columna entre letras.
    
    cartel.setColumn(col, B00000000);
    //cartel.setRow(fil,B00000000);
    
    
    col = col - 1;
    
    if( col < 0 )
      break;
      
  }
  cartel.update();
  return col;
}
