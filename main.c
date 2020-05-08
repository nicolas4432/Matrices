#include <stdio.h>

typedef struct {
	char* SOPA;		//La Sopa
	int tam;		//Tamaño de Matriz NxN
} SopaDeLetras;

typedef struct {
	char* palabras;//Las Palabras
	int num;		//Numero de Palabras
} Palabras;

char* generarMatriz(int M, int N)
{
	char* Matriz = malloc(M * N * sizeof(char));					//Reservamos M*N porque es un array de 1 dim

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Matriz[i * N + j] = (char)(i + (j + 1) * (i + 1) + '0');//Se suma '0' para el casting de int to char
																	//Se itera con i*N porque ese sera el movimiento entre las columnas
		}
	}
}

void ImprimirMatriz(char* Matriz, int M, int N, int ImprimirPosiciones)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (ImprimirPosiciones == 1)
				printf("[%d][%d] = %c\t", i, j, Matriz[i * N + j]);
			else
				printf("%c ", Matriz[i * N + j]);

			if (j + 1 == N)
				printf("\n");
		}
	}
}

char* transponer(char* MatrizOriginal, int Fila, int Columna)
{
	char* MatrizTranspuesta = malloc(Fila * Columna * sizeof(char));

	for (int i = 0; i < Fila; i++)
	{
		for (int j = 0; j < Columna; j++)
		{
			MatrizTranspuesta[j * Fila + i] = MatrizOriginal[i * Columna + j];
		}
	}

	return MatrizTranspuesta;
}

char* voltear(char* MatrizOriginal, int Fila, int Columna)
{
	char* MatrizVolteada = malloc(Fila * Columna * sizeof(char));
	int posicion;
	for (int i = 0; i < Fila; i++)
	{
		for (int j = 0; j < Columna; j++)
		{
			posicion = j * Fila + (Fila - i - 1);
			MatrizVolteada[j * Fila + i] = MatrizOriginal[posicion];
		}
	}

	return MatrizVolteada;
}

SopaDeLetras leerSopaDeArchivo()
{
	//Variables a usar
	char	tamanio_char[10],										//Lee la primera linea con el tamaño de matriz
			caracter;												//Iterador de caracter leido
	int		posCaracter = 0;										//Iterador para la posición de la matriz a guardar
	SopaDeLetras sopa;												//Estructura donde se guardara la Sopa
	FILE* sopaPtr = fopen("sopa.in", "r");							//Abrimos el archivo sopa.in con un Puntero FILE*

	if (sopaPtr == NULL) {											//El archivo se pudo leer?
		printf("Problema al leer archivo.");
		sopa.SOPA = NULL;
		sopa.tam = 0;
		return sopa;
	}

	//Obtenemos el tamaño de la sopa leyendo la primera fila
	fgets(tamanio_char, 10, sopaPtr);								//Se lee el tamaño de matriz primera linea archivo
	sopa.tam = atoi(tamanio_char);									//Convierte la primera linea de chars en un entero

	//Creamos la matriz
	sopa.SOPA = malloc(sopa.tam * sopa.tam * sizeof(char));			//Reservamos el espacio

	while (1) {
		caracter = fgetc(sopaPtr);
		if (caracter == EOF) break;									//Hasta que se pueda leer

		else
		{
			if (caracter == ' ' || caracter == '\n') continue;		//Los saltos de linea y espacios no los debe leer

			sopa.SOPA[posCaracter] = caracter;
			posCaracter++;
		}
	}

	fclose(sopaPtr);												//Cierre de archivo

	return sopa;
}

Palabras leerPalabrasDeArchivo()
{
	//Variables a usar
	char	tamanio_char[10],										//Lee la primera linea con el tamaño de matriz
		caracter;												//Iterador de caracter leido
	int		posCaracter = 0;										//Iterador para la posición de la matriz a guardar
	Palabras palabras;												//Estructura donde se guardara la Sopa
	FILE* palabrasPtr = fopen("palabras.in", "r");							//Abrimos el archivo sopa.in con un Puntero FILE*

	if (palabrasPtr == NULL) {											//El archivo se pudo leer?
		printf("Problema al leer archivo.");
		palabras.palabras = NULL;
		palabras.num = 0;
		return palabras;
	}

	//Obtenemos el tamaño de la sopa leyendo la primera fila
	fgets(tamanio_char, 10, palabrasPtr);								//Se lee el tamaño de matriz primera linea archivo
	palabras.num = atoi(tamanio_char);									//Convierte la primera linea de chars en un entero

	//Creamos la matriz
	palabras.palabras = malloc(palabras.num * 25 * sizeof(char*));		//Reservamos el espacio

			
	int i = 1;
	while (1) {
		caracter = fgetc(palabrasPtr);
		if (caracter == EOF) break;									//Hasta que se pueda leer

		else
		{
			if (caracter == '\n') {
				while (posCaracter < 25 * i)
				{
					posCaracter++;
				}
				i++;
			}
			else {

				palabras.palabras[posCaracter] = caracter;
				posCaracter++;
			}

		}
	}

	fclose(palabrasPtr);												//Cierre de archivo

	return palabras;
}

void busquedaPalabras(SopaDeLetras sopa, Palabras palabras) {
	int tamanioMatriz = sopa.tam;
	int numeroPalabras = palabras.num;
	int letra = 0;
	int largo = 0;
	char* palabraEncontrada = malloc(palabras.num * 25 * sizeof(char*));
	int pos = 0;
	int ultimoLargoEncon = 0;
	int posEncontrada;
	int tamanioPalabra = 5; // funcion tamaño palabra
	int pasada = 0;
	//strcpy(var, "")

	for (int k = 0; k < numeroPalabras; k++) {
		//while (palabras.palabras[letra] != '\0') {
			for (int i = 0; i < tamanioMatriz; i++) {
				for (int j = 0; j < tamanioMatriz; j++) {
					if (palabras.palabras[letra] == sopa.SOPA[i * tamanioMatriz + j]) {
 						pos = 0;
						while (palabras.palabras[letra] == sopa.SOPA[i * tamanioMatriz + j]) {
							palabraEncontrada[pos] = palabras.palabras[letra];
							largo++;
							letra++;
							
							if (pos == 0)
							{
								posEncontrada = i * tamanioMatriz + j;
							}
							pos++;
							j++;
						
						}
						j--;
						if (largo == tamanioPalabra) { // si el largo de la ultima palabra es igual la largo de la palabra se pasa a la siguiente palabra
							// funcion agregar palabra y pasar a la siguiente
							largo = 0;
							j = 10;
							i = 11;
						}
						else if (largo > ultimoLargoEncon) {
							// funcion agregar palabra
							ultimoLargoEncon = largo;
							largo = 0;
						}

						letra = k * 25 + pasada;
					}

				}
				if (tamanioPalabra > ultimoLargoEncon && tamanioPalabra > pasada && ultimoLargoEncon != 0 && i == 9)
				{
					i = -1;
					pasada++;
					letra = k * 25 + pasada;
					ultimoLargoEncon = 0;
				}
			}

		//}
		letra = (k + 1) * 25;  //paso a la siguiente palabra
		pasada = 0;
		ultimoLargoEncon = 0;
		//tamanioPalabra = tamaño siguiente palabra
	}
}


void main()
{
	/*------------------Se lee la matriz----------------------*/
	printf("Leyendo sopa.in...\n\n");
	SopaDeLetras sopa = leerSopaDeArchivo();
	if (sopa.SOPA == NULL) {
		printf("Error al leer archivo o no se encontro.");
		return;
	}
	else
		printf("Archivo leido con exito.\n\n");
	/*------------------Se imprime la matriz------------------*/
	printf("Matriz (%dx%d): \n\n", sopa.tam, sopa.tam);
	ImprimirMatriz(sopa.SOPA, sopa.tam, sopa.tam, 0);


	/*------------------Se leen las palabras----------------------*/
	printf("Leyendo palabras.in...\n\n");
	Palabras palabras = leerPalabrasDeArchivo();
	if (sopa.SOPA == NULL) {
		printf("Error al leer archivo o no se encontro.");
		return;
	}
	else
		printf("Archivo leido con exito.\n\n");








	busquedaPalabras(sopa, palabras);







	/*------------------Se imprime la matriz------------------*/
	printf("\n\nMatriz Transpuesta: \n\n");
	ImprimirMatriz(transponer(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas

	printf("\n\nMatriz Volteada: \n\n");
	ImprimirMatriz(voltear(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas

	printf("\n\nMatriz Transpuesta Volteada: \n\n");
	ImprimirMatriz(voltear(transponer(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas








}