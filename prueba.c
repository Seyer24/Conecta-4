#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FILAS 7
#define COLUMNAS 6

// Prototipos
void InicializarTablero(char tablero[FILAS][COLUMNAS]);
void ImprimirTablero(char tablero[FILAS][COLUMNAS]);
int InsertarFicha(char tablero[FILAS][COLUMNAS], int columna, char ficha);
int VerificarGanador(char tablero[FILAS][COLUMNAS], char ficha);
void AnimarCaida(char tablero[FILAS][COLUMNAS], int columna, char ficha);
void LimpiarPantalla();

int main(){
	char tablero[FILAS][COLUMNAS];
	char jugador1[30], jugador2[30];
	char ficha1 = 'X', ficha2 = 'O';
	int turnoActual;
	int columna, lleno = 0;
	int movimientos = 0;
	int ganador = 0;

	srand(time(NULL));
	InicializarTablero(tablero);

	// Menú inicial
	printf("=====================================\n");
	printf("      Bienvenido a Conecta 4\n");
	printf("=====================================\n");
	printf("Ingrese el nombre del Jugador 1: ");
	scanf("%29s", jugador1);
	printf("Ingrese el nombre del Jugador 2: ");
	scanf("%29s", jugador2);

	// Turno aleatorio
	turnoActual = rand() % 2;
	printf("\nTurnos al azar...\n");
	if(turnoActual == 0)
		printf("Empieza %s (X)\n", jugador1);
	else
		printf("Empieza %s (O)\n", jugador2);
	printf("=====================================\n");
	system("pause");

	// Bucle principal del juego
	while(!ganador && movimientos < FILAS * COLUMNAS){
		LimpiarPantalla();
		ImprimirTablero(tablero);

		if(turnoActual == 0)
			printf("\nTurno de %s (X)\n", jugador1);
		else
			printf("\nTurno de %s (O)\n", jugador2);

      
		printf("Seleccione una columna (1-%d): ", COLUMNAS);
		scanf("%d", &columna);

		if(columna < 1 || columna > COLUMNAS){
			printf("Valor invalido! Ingresa valor entre 1-6 solamente.\n");
        printf("Presione enter para continuar...");
			while (getchar () != '\n'); //Para limpiar el buffer
			continue;
		}

		if(turnoActual == 0){
			if(InsertarFicha(tablero, columna-1, ficha1)){
				AnimarCaida(tablero, columna-1, ficha1);
				ganador = VerificarGanador(tablero, ficha1);
				turnoActual = 1;
				movimientos++;
			} else {
				printf("Columna llena. Intente otra.\n");
				system("pause");
			}
		} else {
			if(InsertarFicha(tablero, columna-1, ficha2)){
				AnimarCaida(tablero, columna-1, ficha2);
				ganador = VerificarGanador(tablero, ficha2);
				turnoActual = 0;
				movimientos++;
			} else {
				printf("Columna llena. Intente otra.\n");
				system("pause");
			}
		}
	}

	LimpiarPantalla();
	ImprimirTablero(tablero);
	if(ganador){
		if(turnoActual == 1)
			printf("\n¡%s (X) ha ganado!\n", jugador1);
		else
			printf("\n¡%s (O) ha ganado!\n", jugador2);
	} else {
		printf("\n¡Empate! El tablero está lleno.\n");
	}

	return 0;
}

// ======== FUNCIONES ========

void InicializarTablero(char tablero[FILAS][COLUMNAS]){
	for(int i=0; i<FILAS; i++)
		for(int j=0; j<COLUMNAS; j++)
			tablero[i][j] = ' ';
}

void ImprimirTablero(char tablero[FILAS][COLUMNAS]){
	printf("\n  ");
	for(int i=1; i<=COLUMNAS; i++)
		printf(" %d ", i);
	printf("\n");

	  for(int i=0; i<FILAS; i++){
		  printf(" |");
		    for(int j=0; j<COLUMNAS; j++){
			    printf(" %c |", tablero[i][j]);
		}
		printf("\n");
	}
	printf(" ");
	        for(int i=0; i<COLUMNAS; i++)
		        printf("----");
	printf("\n");
}

int InsertarFicha(char tablero[FILAS][COLUMNAS], int columna, char ficha){
	for(int i=FILAS-1; i>=0; i--){
		if(tablero[i][columna] == ' '){
			tablero[i][columna] = ficha;
			return 1;
		}
	}
	return 0;
}

// Animación de caída de la ficha
void AnimarCaida(char tablero[FILAS][COLUMNAS], int columna, char ficha){
	
  for(int i=0; i<FILAS; i++){
		if(tablero[i][columna] != ' '){
      int destino = 1; //Posicion final de la fecha
			
      for(int k=0; k<destino; k++){
				LimpiarPantalla();
				  char temp[FILAS][COLUMNAS];
				    memcpy(temp, tablero, sizeof(temp));

				for(int t=0; t<=k; t++)
					temp[t][columna] = ' ';
				    temp[k][columna] = ficha;
				    ImprimirTablero(temp);

				struct timespec ts = {0, 300000000}; // 0.1 seg
				nanosleep(&ts, NULL);
			}
			break;
		}
	}
}

// Verifica si hay 4 en línea
int VerificarGanador(char tablero[FILAS][COLUMNAS], char ficha){
	// Horizontal
	for(int i=0; i<FILAS; i++)
		for(int j=0; j<COLUMNAS-3; j++)
			if(tablero[i][j]==ficha && tablero[i][j+1]==ficha && tablero[i][j+2]==ficha && tablero[i][j+3]==ficha)
				return 1;
	// Vertical
	for(int i=0; i<FILAS-3; i++)
		for(int j=0; j<COLUMNAS; j++)
			if(tablero[i][j]==ficha && tablero[i+1][j]==ficha && tablero[i+2][j]==ficha && tablero[i+3][j]==ficha)
				return 1;
	// Diagonal 
	for(int i=0; i<FILAS-3; i++)
		for(int j=0; j<COLUMNAS-3; j++)
			if(tablero[i][j]==ficha && tablero[i+1][j+1]==ficha && tablero[i+2][j+2]==ficha && tablero[i+3][j+3]==ficha)
				return 1;
	// Diagonal /
	for(int i=3; i<FILAS; i++)
		for(int j=0; j<COLUMNAS-3; j++)
			if(tablero[i][j]==ficha && tablero[i-1][j+1]==ficha && tablero[i-2][j+2]==ficha && tablero[i-3][j+3]==ficha)
				return 1;
	return 0;
}

void LimpiarPantalla(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}