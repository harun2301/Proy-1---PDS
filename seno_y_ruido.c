/*
*	Procesamiento Digital de Señales
*			1° Proyecto
*
*	Autores:	Oscar Harún Baños Mancilla, Rafael Araujo Lague
*	Fecha:		Abril 16, 2024
*/

/*
*	Comando para compilar en la terminal de linux
*	gcc [nombre].c -lm -o [nombre].out
*
*	Comando para correr programa en la terminal
*	./[nombre].out
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// --------------------------- M A C R O S   Y   V A R I A B L E S   G L O B A L E S ---------------------------

#define	M	1000		// número de puntos de la senoidal
#define f0	2 			// frecuencia natural de la senoidal
#define A 	2			// amplitud de la senoidal
#define pi 	3.141592	// constante para pi

float xs[M];			// arreglo de datos para el seno
float rand_n[M];		// arreglo para el ruido aleatorio
float signal[M];		// arreglo para la señal con ruido
float xs_sub[M/3];		// arreglo para la señal submuestrada a razón de 3
float E_x;				// energía de la senoidal
float E_s;				// energía de la senoidal con ruido
float min = -0.05;		// cota inferior de ruido aleatorio
float max = 0.05;		// cota superior para ruido aleatorio
float SNR;

int n, i;					// índices



// --------------------------- F I R M A   D E   F U N C I O N E S ---------------------------

void ej_1(FILE *escrib);	// resuelve el primer punto del proyecto
void ej_2(FILE *escrib);	// resuelve el segundo punto del proyecto
float r_xx(float x[]);		// calcula la autocorrelación de una señal especificada


// --------------------------- P R O G R A M A   P R I N C I P A L ---------------------------

int main(void){
	FILE *escrib;								// apuntador a archivo 
	
	ej_1(escrib);
	ej_2(escrib);

	return 0;
}


// --------------------------- D E F I N I C I O N   D E   F U N C I O N E S ---------------------------

/*
* Crea una senoidal y una señal de ruido aleatorio. 
* Las suma y grafica esta nueva señal con ruido.
*/
void ej_1(FILE *escrib){

	srand(time(NULL));								

	// CREACIÓN DE LA SENOIDAL
	escrib = fopen("puntos_sin.dat","w");
	for(n=0; n<M-1; n++){
		xs[n] = A*sin(2*pi*f0*n/M);				// calculamos punto a punto
		fprintf(escrib, "%6.4f\n", xs[n]);		// va escribiendo uno a uno los puntos
	}
	fclose(escrib);



	// CREACIÓN DE LA SEÑAL DE RUIDO ALEATORIO CON SNR < 3dB
	escrib = fopen("rand_noise.dat","w");
	for(n=0; n<M-1; n++){
		rand_n[n] = min + ((float)rand() / RAND_MAX) * (max - min);				// calculamos punto a punto
		fprintf(escrib, "%1.8f\n", rand_n[n]);		// va escribiendo uno a uno los puntos
	}
	fclose(escrib);



	// SUMA DE LA SENOIDAL + RUIDO
	escrib = fopen("noise_sin.dat","w");
	for(n=0; n<M-1; n++){
		signal[n] = xs[n] + rand_n[n];				// calculamos punto a punto
		fprintf(escrib, "%2.8f\n", signal[n]);		// va escribiendo uno a uno los puntos
	}
	fclose(escrib);



	E_x = r_xx(xs);
	E_s = r_xx(signal);
	SNR = 10*log10(E_x/E_s);

	printf("La energia total de la senoidal es: %f\n", E_x);
	printf("La energia total de la senoidal + ruido es: %f\n", E_s);
	printf("El SNR de la senoidal + ruido es: %f\n", SNR);

	system("gnuplot -p 'graf_seno_y_ruido.gp'");
}


/*
* Submuestre la senoidal con ruido a razón de 3.
* Es decir, de 3 en 3
*/
void ej_2(FILE *escrib){
	// SENOIDAL SUBMUESTRADA A RAZÓN DE 3
	xs_sub[0] = xs[0];
	escrib = fopen("sub_3.dat","w");
	for(n=0; n<M/3; n++){
		xs_sub[n] = signal[3*n];
		fprintf(escrib, "%2.8f\n", xs_sub[n]); 
	}
	fclose(escrib);
	system("gnuplot -p 'graf_sub3.gp'");
}



/*
* Calcula la autocorrelación de una señal.
* Es decir, su energía.
*/
float r_xx(float signal[]){
	float E;						// energía de la señal
	for(n=0; n<M-1; n++){
		E += signal[n] * signal[n];
	}
	return E;
}