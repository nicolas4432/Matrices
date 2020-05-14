#include <stdio.h>
#include <string.h>
#include <malloc.h>

char palabrasE[100][100];
int cordenadas[500];

typedef struct {
	char* SOPA;		//La Sopa
	int tam;		//Tama�o de Matriz NxN
} SopaDeLetras;

typedef struct {
	char* palabras;//Las Palabras
	int num;		//Numero de Palabras
} Palabras;

//char* generarMatriz(int M, int N)
//{
//	char* Matriz = malloc(M * N * sizeof(char));					//Reservamos M*N porque es un array de 1 dim
//
//	for (int i = 0; i < M; i++)
//	{
//		for (int j = 0; j < N; j++)
//		{
//			Matriz[i * N + j] = (char)(i + (j + 1) * (i + 1) + '0');//Se suma '0' para el casting de int to char
//																	//Se itera con i*N porque ese sera el movimiento entre las columnas
//		}
//	}
//}

//void ImprimirMatriz(char* Matriz, int M, int N, int ImprimirPosiciones)
//{
//	for (int i = 0; i < M; i++)
//	{
//		for (int j = 0; j < N; j++)
//		{
//			if (ImprimirPosiciones == 1)
//				printf("[%d][%d] = %c\t", i, j, Matriz[i * N + j]);
//			else
//				printf("%c ", Matriz[i * N + j]);
//
//			if (j + 1 == N)
//				printf("\n");
//		}
//	}
//}

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
	char	tamanio_char[10],										//Lee la primera linea con el tama�o de matriz
			caracter;												//Iterador de caracter leido
	int		posCaracter = 0;										//Iterador para la posici�n de la matriz a guardar
	SopaDeLetras sopa;												//Estructura donde se guardara la Sopa
	FILE* sopaPtr = fopen("sopa2.in", "r");							//Abrimos el archivo sopa.in con un Puntero FILE*

	if (sopaPtr == NULL) {											//El archivo se pudo leer?
		printf("Problema al leer archivo.");
		sopa.SOPA = NULL;
		sopa.tam = 0;
		return sopa;
	}

	//Obtenemos el tama�o de la sopa leyendo la primera fila
	fgets(tamanio_char, 10, sopaPtr);								//Se lee el tama�o de matriz primera linea archivo
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
	sopa.SOPA[posCaracter] = '\0';

	fclose(sopaPtr);												//Cierre de archivo

	return sopa;
}

Palabras leerPalabrasDeArchivo()
{
	//Variables a usar
	char	tamanio_char[10],										//Lee la primera linea con el tama�o de matriz
		caracter;												//Iterador de caracter leido
	int		posCaracter = 0;										//Iterador para la posici�n de la matriz a guardar
	Palabras palabras;												//Estructura donde se guardara la Sopa
	FILE* palabrasPtr = fopen("palabras2.in", "r");							//Abrimos el archivo sopa.in con un Puntero FILE*

	if (palabrasPtr == NULL) {											//El archivo se pudo leer?
		printf("Problema al leer archivo.");
		palabras.palabras = NULL;
		palabras.num = 0;
		return palabras;
	}

	//Obtenemos el tama�o de la sopa leyendo la primera fila
	fgets(tamanio_char, 10, palabrasPtr);								//Se lee el tama�o de matriz primera linea archivo
	palabras.num = atoi(tamanio_char);									//Convierte la primera linea de chars en un entero

	//Creamos la matriz
	palabras.palabras = malloc(palabras.num * 25 * sizeof(char));		//Reservamos el espacio

			
	int i = 1;
	while (1) {
		caracter = fgetc(palabrasPtr);
		if (caracter == EOF) break;									//Hasta que se pueda leer

		else
		{
			if (caracter == '\n') {
				while (posCaracter < 25 * i)
				{
					
					palabras.palabras[posCaracter] = ' ';
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
	palabras.palabras[posCaracter] = ' ';
	palabras.palabras[posCaracter + 1] = '\0';

	fclose(palabrasPtr);												//Cierre de archivo

	return palabras;
}

char* palabrasBuscar(Palabras palabras, int PalabraNumero) {
	printf("pene \n");
	int tamanio = 0;
	int tamanioChar = 0;
	//char* combinaciones = malloc(2529 * sizeof(char*));
	//printf("pene1 %s\n", combinaciones);
	char* palabraI = malloc(25 * sizeof(char));
	printf("pene2 %s\n", palabraI);
	char* palabraF = malloc(25 * sizeof(char));
	printf("pene3 %s\n", palabraF);
	int largo = 0;
	int letrasMenos = 1;
	printf("pene4 \n");
	while (palabras.palabras[25 * PalabraNumero + tamanio] != ' ') { // \0 �
		palabraI[tamanio] = palabras.palabras[25 * PalabraNumero + tamanio];
		palabraF[tamanio] = palabras.palabras[25 * PalabraNumero + tamanio];
		tamanio++;
		largo = tamanio;
	}
	printf("pene5 \n");
	
	int suma = 0;
	for (int i = 0; i < tamanio; i++)
	{
		suma = suma + (i + 1) * (largo - i);
		suma = suma + (i - 1);
	}
	printf("\n\n%d\n\n", suma);
	
	char* combinaciones = malloc(suma * sizeof(char));
	
	
	for (int i = 0; i < largo; i++)
	{
		combinaciones[i] = palabraI[i];
		if (i == largo - 1) {
			combinaciones[i + 1] = '\0';
		}
	}
	printf("pene6 \n");

	printf("pene7 \n");
	for (int i = 0; i < tamanio - 2 ; i++) {
		for (int k = 0; k < letrasMenos + 1; k++) {
			strcpy(palabraF, "                        ");
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
	printf("pene8 %s\n", combinaciones);

	//char* combinacionesF = malloc(strlen(combinaciones) * sizeof(char*));
	//
	//printf("pene88 %d\n", strlen(combinaciones));

	//for (int i = 0; i < strlen(combinaciones); i++)
	//{
	//	combinacionesF[i] = combinaciones[i];
	//	printf("%d\n", i);
	//	if (i == strlen(combinaciones) - 1) {
	//		combinacionesF[i + 1] = '\0';
	//	}
	//}
	//printf("pene8 %s\n", combinacionesF);
	//printf("pene9 \n");
	//free(combinaciones);
	//combinaciones = NULL;
	free(palabraF);
	palabraF = NULL;
	free(palabraI);
	palabraI = NULL;
	printf("penee \n");
	return combinaciones;
}

int numeroCombinaciones(char* Combinaciones) {
	int cantidad = 0;
	int i = 0;
	while (Combinaciones[i] != '\0') {
		if (Combinaciones[i] == '-')
		{
			cantidad++;
		}
		i++;
	}
	return cantidad;
}

char* palabra(char* Combinaciones, int NumeroBuscada) {
	char* palabraI = malloc(25 * sizeof(char));
	char* palabraF = malloc(25 * sizeof(char));
	int contador = 0;
	int i = 0;
	if (NumeroBuscada == 0){
		while(Combinaciones[contador] != '-') {
			palabraI[contador] = Combinaciones[contador];
			contador++;
		}
		palabraI[contador] = '\0';
		contador = 0;
	}
	else {
		while (contador != NumeroBuscada) {
			if (Combinaciones[i] == '-') {
				contador++;
			}
			i++;
		}
		contador = 0;
		while (Combinaciones[i] != '-') {
			palabraI[contador] = Combinaciones[i];
			contador++;
			i++;
		}
		palabraI[contador] = '\0';
	}

	return palabraI;
}

void guardarDato(int fila, int columna, char* palabra, int numeroPalabra) {
	int contador = 0;
	while (palabra[contador] != '\0')
	{
		palabrasE[numeroPalabra][contador] = palabra[contador];
		contador++;
	}
	cordenadas[2 * numeroPalabra] = fila;
	cordenadas[2 * numeroPalabra + 1] = columna;
}

void busquedaPalabras(char* matrizNormal, char * matrizTranspuesta, char* matrizVolteadaNormal, char* matrizVolteadaTranspuesta, int TamanioMatriz ,Palabras palabras) {
	int numeroPalabras = palabras.num;
	char* combinaciones;
	int cantidadCombinaciones;
	char* palabraBuscada;

	char* encontrada;
	int posicion;
	char* encontrada2;
	int posicion2;
	char* encontrada3;
	int posicion3;
	char* encontrada4;
	int posicion4;

	int columna;
	int fila;

	for (int k = 0; k < numeroPalabras; k++) {
		printf("hola1  %d\n", numeroPalabras);
		combinaciones = palabrasBuscar(palabras, k);
		printf("hola2");
		cantidadCombinaciones = numeroCombinaciones(combinaciones);
		printf("hola3\n");
		for (int i = 0; i < cantidadCombinaciones; i++)
		{
			printf("hola4\n");
			palabraBuscada = palabra(combinaciones, i);
			if (strstr(matrizNormal, palabraBuscada) != NULL) {
				encontrada = strstr(matrizNormal, palabraBuscada);
				posicion = strlen(matrizNormal) - strlen(encontrada);

				fila = posicion / TamanioMatriz;
				columna = (posicion % TamanioMatriz) / 1;
				printf("poscicion:%d fila:%d columna:%d palabra:%s\n", posicion, fila, columna, palabraBuscada);
				guardarDato(fila, columna, palabraBuscada, k);
				break;
			}
			else if (strstr(matrizTranspuesta, palabraBuscada) != NULL) {
				encontrada2 = strstr(matrizTranspuesta, palabraBuscada);
				posicion2 = strlen(matrizTranspuesta) - strlen(encontrada2);

				columna = posicion2 / TamanioMatriz;
				fila = (posicion2 % TamanioMatriz) / 1;
				printf("poscicion:%d fila:%d columna:%d palabra:%s\n", posicion2, fila, columna, palabraBuscada);
				guardarDato(fila, columna, palabraBuscada, k);
				break;
			}
			else if (strstr(matrizVolteadaNormal, palabraBuscada) != NULL) {
				encontrada3 = strstr(matrizVolteadaNormal, palabraBuscada);
				posicion3 = strlen(matrizVolteadaNormal) - strlen(encontrada3);

				fila = posicion3 / TamanioMatriz;
				columna = (posicion3 % TamanioMatriz) / 1;
				columna = TamanioMatriz - columna - 1;
				printf("poscicion:%d fila:%d columna:%d palabra:%s\n", posicion3, fila, columna, palabraBuscada);
				guardarDato(fila, columna, palabraBuscada, k);
				break;

			}
			else if (strstr(matrizVolteadaTranspuesta, palabraBuscada) != NULL) {
				encontrada4 = strstr(matrizVolteadaTranspuesta, palabraBuscada);
				posicion4 = strlen(matrizVolteadaTranspuesta) - strlen(encontrada4);

				columna = posicion4 / TamanioMatriz;
				fila = (posicion4 % TamanioMatriz) / 1;
				columna = TamanioMatriz - columna - 1;
				printf("poscicion:%d fila:%d columna:%d palabra:%s\n", posicion4, fila, columna, palabraBuscada);
				guardarDato(fila, columna, palabraBuscada, k);
				break;
			}
		}
	}
}

void main()
{
	/*------------------Se lee la matriz Normal----------------------*/
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
	//ImprimirMatriz(sopa.SOPA, sopa.tam, sopa.tam, 0);


	/*------------------Se leen las palabras----------------------*/
	printf("Leyendo palabras.in...\n\n");
	Palabras palabras = leerPalabrasDeArchivo();
	if (sopa.SOPA == NULL) {
		printf("Error al leer archivo o no se encontro.");
		return;
	}
	else
		printf("Archivo leido con exito.\n\n");


/*------------------Se imprime la matriz Transpuesta------------------*/
	printf("\n\nMatriz Transpuesta: \n\n");
	//ImprimirMatriz(transponer(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas


/*------------------Se imprime la matriz Volteada------------------*/
	printf("\n\nMatriz Volteada: \n\n");
	//ImprimirMatriz(voltear(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas


/*------------------Se imprime la matriz Volteada Transpuesta------------------*/
	printf("\n\nMatriz Transpuesta Volteada: \n\n");
	//ImprimirMatriz(voltear(transponer(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam), sopa.tam, sopa.tam, 0);					//Se invierte el numero de filas y columnas


/*------------------Se buscan las palabras----------------------*/
	busquedaPalabras(sopa.SOPA, (transponer(sopa.SOPA, sopa.tam, sopa.tam)), voltear(sopa.SOPA, sopa.tam, sopa.tam),voltear(transponer(sopa.SOPA, sopa.tam, sopa.tam), sopa.tam, sopa.tam), sopa.tam, palabras);


/*------------------Se guardan las palabras----------------------*/
	//escribirDatos(palabras, );



}