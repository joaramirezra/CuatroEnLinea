#include "miniwin.h" // libreria utilizada para los graficas,tamaño de venta, color, movilidad del juego
#include "iostream" // libreria de entrada y salida de datos 
#include "windows.h"
#include "math.h"
#include "sstream"

using namespace miniwin;

//variable globales

const int numeroFilas = 6;
const int numeroColumnas = 7;
int size = 70;
int Tablero [numeroFilas][numeroColumnas];
int x,y,turno;
bool enJuego ;

void Configurarpartida();

void LLenarTablero(){
	for(int i = 0 ; i < numeroFilas ; i++){
		for(int j = 0 ; j<numeroColumnas ; j++){
			Tablero[i][j]= -1 ; // -1 es vacio , 0 es jugador 1 , 1 es jugador 2
		}
	}
}

bool VerificarGanador(){
	int contador;
	// verifica si hay 4 fichas en linea en direccion horizontal
	for(int i = 0 ; i < numeroFilas ; i++){
		contador = 0;
		for(int j = 0 ; j < numeroColumnas ; j++){
			if(Tablero[i][j] == turno%2 ) contador++;
			else contador =0;
			if (contador == 4)return true;
		}
	}
	// verifica si hay 4 fichas en linea en direccion vertical
	
	for(int j = 0 ; j < numeroColumnas  ; j++){
		contador = 0;
		for(int i = 0 ; i < numeroFilas   ; i++){
			if(Tablero[i][j] == turno%2 ) contador++;
			else contador = 0;
			if (contador == 4)return true;
		}
	}	
	
	//ojo, la notacion hay que tenerla en razon a la matriz tablero, ya que en la parte grafica
	// el eje y esta invertido
	// verifica si hay 4 fichas en linea en direccion diagonal ascendente (\)superior
	for(int j = 0 ; j < numeroColumnas ; j++){
		contador = 0;
		for(int i = 0 ; i < numeroFilas ; i++){
			if(i+j<numeroColumnas){
				if(Tablero[i][j+i] == turno%2 ) contador++;
				else contador = 0;
				if (contador == 4)return true;
			}
		}
	}
	
	// verifica si hay 4 fichas en linea en direccion diagonal ascendente (\)superior
	for(int i = 1 ; i < numeroFilas  ; i++){
		contador = 0;
		for(int j = 0 ; j <numeroColumnas  ; j++){
			if(i+j < numeroFilas){
				if(Tablero[j+i][j] == turno%2 ) contador++;
				else contador = 0;
				if (contador == 4)return true;
			}
		}
	}
	
	// verifica si hay 4 fichas en linea en direccion diagonal ascendente (/)superior
	for(int i = numeroColumnas-1 ; i >= 0; i--){
		contador = 0;
		for(int j = 0 ; j < numeroFilas ; j++){
			if(i-j >= 0){
				if(Tablero[j][i-j] == turno%2 ) contador++;
				else contador = 0;
				if (contador == 4)return true;
			}
		}
	}
	//verifica si hay 4 fichas en linea en direccion diagonal ascendente (/)inferior
	for(int i = numeroFilas-2 ; i >= 0 ; i--){
		contador = 0;
		for(int j = 0 ; j < numeroColumnas ; j++){
			if( i - j >= 0){
				if(Tablero[i-j][i] == turno%2 ) contador++;
				else contador = 0;
				if (contador == 4)return true;	
			}
		}
	}
	return false;
}

int VerificarCasilla(int x ){
	int counter = 0; // se inicializa un contador en cero, este se encarga de contar las fichas de manera vertical
	while(Tablero[counter][x] !=-1 && counter < 6)counter++; //mientras la casilla este ocupada y sea menor que 6 (7 fichas) , aumente uno al contador
	if(counter < 6) return counter; // una vez sale del contador, si el contador esta en el rango , es decir esta vqcia, devulve la poscion vertical donde se coloca
	return -1; // en caso contrario se retorna -1 indicando que no hay espacio en esa columna 
}

void Dibujarcasilla(float x1 , float y1 ,float medida){
	rectangulo(x1, y1, (x1+medida) , (y1+medida));
 	circulo((x1+medida/2), (y1+medida/2), medida/2);
}

void DibujarTablero(){
 	for (int j = 1 ; j <= numeroFilas  ; j++){
		for (int i = 0; i< numeroColumnas;i++){
	    	if(j%2==0)color(ROJO); // si la columna es %2 = 0 se pinta de rojo
	    	else color(AZUL);// si la columna es %2 = 1 se pinta de azul
			Dibujarcasilla(i*size,j*size,size); 	
		}
	}
 	refresca();
}

void colocarFicha(int x, int y,bool jugador){
	if(jugador ==  true) color(AZUL); // jugador 1
	else color(ROJO); // jugador 2
	circulo_lleno(x*size+size/2,size/2 + y*size,size/2);
}

void BorrarFicha(int x, int y){
	color(NEGRO);
	circulo_lleno(x*size+size/2,size/2 + y*size,size/2);
}


void Configurarpartida(){
	vredimensiona(500, 500); // se crea la ventana de 500 px x 500px
	LLenarTablero(); // con -1
	DibujarTablero(); // se dibuja el tablero inicial
	x = 0;
	y = 0;
	enJuego = true;
	turno =0;
	colocarFicha(0,0,(turno%2==0));
	refresca();		
}

void dibujarTableroMensaje(){
	std::ostringstream ss;
    
    for(int i = numeroFilas-1 ; i>-1 ;i--){
		for(int j = 0 ; j<numeroColumnas ; j++){
			if(Tablero[i][j] == -1 ) ss<<" - ";
			else if(Tablero[i][j] == 0 ) ss<<" 0 ";
			if(Tablero[i][j] == 1 ) ss<<" X ";	
		}
		ss<<"\n";
	}
	mensaje(ss.str());
}
			


int main (){
	int entradaTeclado;	
	Configurarpartida(); // se borran todos los valores de la matriz de juegos, ademas de reiniciar todos los valores
	do{
		entradaTeclado= tecla(); // se lee los valores del teclado 
		if(entradaTeclado == IZQUIERDA && x > 0){
			BorrarFicha(x--,y);
			colocarFicha(x,0,(turno%2==0));
			refresca();
		}
		else if(entradaTeclado == DERECHA && x < 6){
			BorrarFicha(x++,y);
			colocarFicha(x,0,(turno%2==0));
			refresca();		
		}
		else if(entradaTeclado == ABAJO){
			int validacion  = VerificarCasilla(x);
			 
			if(validacion != -1){
				colocarFicha(x,6-validacion,(turno%2==0));
				Tablero[validacion][x] = turno%2;
				
				if(VerificarGanador()){
					BorrarFicha(x,0);
					refresca();
					if(turno%2==0)mensaje("Gano el jugador azul");
					else mensaje("Gano el jugador rojo");
					Configurarpartida();
				}

				else {
					turno++;
					BorrarFicha(x,y);
					//x=0;
					colocarFicha(x,0,(turno%2==0));
					//DibujarTablero2();
				}
				refresca();
			}
				
		}
		if(turno>41){
			mensaje("Partida Empatada");
			Configurarpartida();
		}
		
	}while(enJuego);
	
	return 0;
}

/*
metodos para debugear


void DibujarTableroConsola(){
	for(int i = 0 ; i < numeroFilas ; i++){
		for(int j = 0 ; j < numeroColumnas ; j++){
			cout<<Tablero[i][j]<<" ";
		}
		cout<<endl;
	}	
}

void colocarFichaDEBUG(int , int ,int );

void DibujarTablero2(){
	for(int i = 0 ; i < numeroFilas ; i++){
		for(int j = 0 ; j < numeroColumnas ; j++){
			colocarFichaDEBUG(j,6-i,Tablero[i][j]);
		}
	}
}

void colocarFichaDEBUG(int x, int y,int jugador){
	if(jugador ==  0) color(VERDE); // jugador 1
	else if(jugador ==  1) color(BLANCO); // jugador 2
	else color(CYAN); 
	circulo_lleno(x*size+size/2,size/2 + y*size,size/4);
}


*/
