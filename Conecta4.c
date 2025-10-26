/*

-------------Proyecto Conecta 4------------------
Equipo: Nadia y Arath Reyes Gonzalez
Universidad Autonoma de Baja California
Lenguaje C

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void IniciarJuego();
void AcabarJuego();

//Defininos el tamano del tablero 
#define COLUMNAS 6
#define filas 7

int main(){

  int opc=0;
  
  do{
    
    printf("\nBienvenido al proyecto Conecta 4\n");
    printf("\nIniciar el juego? 1=si ");
    printf("\nSalir del juego?  2=nO ");
    scanf("%d", &opc);

  } while (opc = 1 || opc > = 2)
      printf("\nDesea volver al menu? Si=1 Y terminar el juego=2  ");
        scanf("%d", &opc);
  
return 0;
}


