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

char* palabrasBuscar(Palabras palabras, int PalabraNumero) {
	int tamanio = 0;
	int tamanioChar = 0;
	char* combinaciones = malloc(4000 * sizeof(char*));
	char* palabraI = malloc(25 * sizeof(char*));
	char* palabraF = malloc(25 * sizeof(char*));
	char* palabraFF = malloc(25 * sizeof(char*));
	int largo = 0;
	int letrasMenos = 1;
	while (palabras.palabras[25 * PalabraNumero + tamanio] != 'Í') {
		palabraI[tamanio] = palabras.palabras[25 * PalabraNumero + tamanio];
		palabraF[tamanio] = palabras.palabras[25 * PalabraNumero + tamanio];
		palabraFF[tamanio] = palabras.palabras[25 * PalabraNumero + tamanio];
		tamanio++;
		largo = tamanio;
	}
	for (int i = 0; i < largo; i++)
	{
		combinaciones[i] = palabraI[i];
		if (i == largo - 1) {
			combinaciones[i + 1] = '\0';
		}
	}
	if (tamanio%2 == 1){
		tamanio++;
	}
	for (int i = 0; i < tamanio/2 ; i++) {
		for (int k = 0; k < letrasMenos + 1; k++) {
			strcpy(palabraF, "                          ");
			strcat(combinaciones, "-");

			for (int j = 0; j < largo - letrasMenos; j++) {
				palabraF[j] = palabraI[j + k];

				if (j == largo - letrasMenos - 1) {
					palabraF[j + 1] = '\0';
				}
			}
			strcat(combinaciones, palabraF);
		}
		letrasMenos++;
	}
	return combinaciones;
}

void busquedaPalabras(SopaDeLetras sopa, Palabras palabras) {
	int numeroPalabras = palabras.num;

	//strcpy(var, "")




	for (int k = 0; k < numeroPalabras; k++) {

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







	char * combina = palabrasBuscar(palabras, 1);
	printf("%s", combina);

	//char* ret;

	//ret = strstr(sopa.SOPA, "hoja");

	//printf("%s", ret);





	/*------------------Se imprime la matriz------------------*/
	printf("\n\nMatriz Transpuesta: \n\n");
	ImprimirMatriz(transponer(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas

	printf("\n\nMatriz Volteada: \n\n");
	ImprimirMatriz(voltear(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas

	printf("\n\nMatriz Transpuesta Volteada: \n\n");
	ImprimirMatriz(voltear(transponer(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas








}