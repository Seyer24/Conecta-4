#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
    Aqui definimos la matriz ya que al ser el juego clasico,
    el tamano del tablero seria este siempre.
*/
#define FILAS 7
#define COLUMNAS 6

/*
    Prototipos de funciones
    Cada prototipo tiene su nombre especificando que es para que no fuera confuso.
    Y pues obviamente al trabajar todas las funciones sobre la matriz,
    practicamente todas apuntan a ella, menos la de limpiar pantalla,
    ya que no importa que hubiese en esta, se limpiase la pantalla siempre.
*/
void InicializarTablero(char (*tablero)[COLUMNAS]);
void ImprimirTablero(char (*tablero)[COLUMNAS]);
int  InsertarFicha(char (*tablero)[COLUMNAS], int columna, char ficha);
int  VerificarGanador(char (*tablero)[COLUMNAS], char ficha);
void AnimarCaida(char (*tablero)[COLUMNAS], int columna, char ficha);
void LimpiarPantalla();
int  MovimientoValido(char (*tablero)[COLUMNAS], int columna);
int  EvaluarEstado(char (*tablero)[COLUMNAS], char ficha);

/*
    Aqui abrimos el bloque principal donde declaramos las variables globales
    ya que estas se reutilizan constantemente.
*/
int main(){
	char tablero[FILAS][COLUMNAS];
	char jugador1[30], jugador2[30];
	char ficha1 = 'X', ficha2 = 'O';
	int turnoActual;
	int columna, movimientos = 0, estado = 0;
	// 0: sigue, 1: gana X, 2: gana O, 3: empate

	srand(time(NULL));
	InicializarTablero(tablero);

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

	// ==== Bucle principal ====
	while(estado == 0 && movimientos < FILAS * COLUMNAS){
		LimpiarPantalla();
		ImprimirTablero(tablero);

		if(turnoActual == 0)
			printf("\nTurno de %s (X)\n", jugador1);
		else
			printf("\nTurno de %s (O)\n", jugador2);

		printf("Seleccione una columna (1-%d): ", COLUMNAS);
		scanf("%d", &columna);

		// Validar movimiento antes de insertar
		if(!MovimientoValido(tablero, columna-1)){
			printf("Movimiento invalido. Intente de nuevo.\n");
			system("pause");
			continue;
		}

		// Inserta ficha y anima caída
		if(turnoActual == 0){
			InsertarFicha(tablero, columna-1, ficha1);
			AnimarCaida(tablero, columna-1, ficha1);
			estado = EvaluarEstado(tablero, ficha1);
			turnoActual = 1;
		} else {
			InsertarFicha(tablero, columna-1, ficha2);
			AnimarCaida(tablero, columna-1, ficha2);
			estado = EvaluarEstado(tablero, ficha2);
			turnoActual = 0;
		}
		movimientos++;
	}

	LimpiarPantalla();
	ImprimirTablero(tablero);

	// ==== Resultado final ====
	if(estado == 1)
		printf("\n¡%s (X) ha ganado!\n", jugador1);
	else if(estado == 2)
		printf("\n¡%s (O) ha ganado!\n", jugador2);
	else
		printf("\n¡Empate! El tablero está lleno.\n");

	return 0;
}

// ==== FUNCIONES ====

// Inicializa el tablero con espacios vacíos
void InicializarTablero(char (*tablero)[COLUMNAS]){
	for(int i=0; i<FILAS; i++)
		for(int j=0; j<COLUMNAS; j++)
			*(*(tablero + i) + j) = ' ';
}

// Imprime el tablero actual
void ImprimirTablero(char (*tablero)[COLUMNAS]){
	printf("\n  ");
	for(int i=1; i<=COLUMNAS; i++)
		printf(" %2d ", i);
	printf("\n");

	for(int i=0; i<FILAS; i++){
		printf(" |");
		for(int j=0; j<COLUMNAS; j++){
			printf(" %c |", *(*(tablero + i) + j));
		}
		printf("\n");
	}

	printf(" ");
	for(int i=0; i<COLUMNAS; i++)
		printf("----");
	printf("\n");
}

// Valida si el movimiento es posible (columna válida y no llena)
int MovimientoValido(char (*tablero)[COLUMNAS], int columna){
	if(columna < 0 || columna >= COLUMNAS)
		return 0;
	if(*(*(tablero + 0) + columna) != ' ') // si la parte superior ya está llena
		return 0;
	return 1;
}

// Inserta ficha en la columna elegida (último espacio disponible)
int InsertarFicha(char (*tablero)[COLUMNAS], int columna, char ficha){
	for(int i=FILAS-1; i>=0; i--){
		if(*(*(tablero + i) + columna) == ' '){
			*(*(tablero + i) + columna) = ficha;
			return 1;
		}
	}
	return 0;
}

// Verifica si hay cuatro en línea
int VerificarGanador(char (*tablero)[COLUMNAS], char ficha){
	// Horizontal
	for(int i=0; i<FILAS; i++)
		for(int j=0; j<COLUMNAS-3; j++)
			if(*(*(tablero+i)+j)==ficha && *(*(tablero+i)+(j+1))==ficha &&
			   *(*(tablero+i)+(j+2))==ficha && *(*(tablero+i)+(j+3))==ficha)
				return 1;

	// Vertical
	for(int i=0; i<FILAS-3; i++)
		for(int j=0; j<COLUMNAS; j++)
			if(*(*(tablero+i)+j)==ficha && *(*(tablero+i+1)+j)==ficha &&
			   *(*(tablero+i+2)+j)==ficha && *(*(tablero+i+3)+j)==ficha)
				return 1;

	// Diagonal hacia abajo
	for(int i=0; i<FILAS-3; i++)
		for(int j=0; j<COLUMNAS-3; j++)
			if(*(*(tablero+i)+j)==ficha && *(*(tablero+i+1)+(j+1))==ficha &&
			   *(*(tablero+i+2)+(j+2))==ficha && *(*(tablero+i+3)+(j+3))==ficha)
				return 1;

	// Diagonal hacia arriba
	for(int i=3; i<FILAS; i++)
		for(int j=0; j<COLUMNAS-3; j++)
			if(*(*(tablero+i)+j)==ficha && *(*(tablero+i-1)+(j+1))==ficha &&
			   *(*(tablero+i-2)+(j+2))==ficha && *(*(tablero+i-3)+(j+3))==ficha)
				return 1;

	return 0;
}

// Evalúa si el juego continúa, hay ganador o empate
int EvaluarEstado(char (*tablero)[COLUMNAS], char ficha){
	if(VerificarGanador(tablero, ficha)){
		if(ficha == 'X') return 1;
		else return 2;
	}

	// Si no hay espacios vacíos, es empate
	int lleno = 1;
	for(int j=0; j<COLUMNAS; j++){
		if(*(*(tablero + 0) + j) == ' ')
			lleno = 0;
	}
	if(lleno) return 3;

	return 0; // el juego sigue
}

// Animacion simple de caída (mantiene la estructura original)
void AnimarCaida(char (*tablero)[COLUMNAS], int columna, char ficha){
	for(int i=0; i<FILAS; i++){
		if(*(*(tablero+i)+columna) != ' '){
			int destino = i; // posición final
			*(*(tablero+i)+columna) = ' ';

			for(int k=0; k<=destino; k++){
				LimpiarPantalla();
				char temp[FILAS][COLUMNAS];
				memcpy(temp, tablero, sizeof(temp));
				temp[k][columna] = ficha;
				ImprimirTablero(temp);
				struct timespec ts = {0, 100000000}; // 0.1s
				nanosleep(&ts, NULL);
			}
			*(*(tablero+destino)+columna) = ficha;
			break;
		}
	}
}

// Limpia la pantalla según el sistema operativo
void LimpiarPantalla(){
	system("cls");
}
