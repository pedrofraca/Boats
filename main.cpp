
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <match.h>
#include <terminal.h>

void conversion(int valor,char cadena[2])
{
	if (valor==0) strcpy(cadena,"0");
	if (valor==1) strcpy(cadena,"1");
	if (valor==2) strcpy(cadena,"2");
	if (valor==3) strcpy(cadena,"3");
	if (valor==4) strcpy(cadena,"4");
	if (valor==5) strcpy(cadena,"5");
	if (valor==6) strcpy(cadena,"6");
	if (valor==7) strcpy(cadena,"7");
	if (valor==8) strcpy(cadena,"8");
};
int main (int argc, char * const argv[]) 
{
	match juego;
	terminal consola;
	char ip[14];
	int tira,longitud,hundido,tira2,tira3;
	int r_tira2,r_tira3;
	consola.pintaMenu();
	switch(consola.getTerminalStatus())
	{
		case 1:
			{
				juego.player.board1.introduceNumeroHundidos(0);
				consola.setThrows(0);
				consola.setMaxThrows(10);
				juego.startSimpleMatch();
				consola.getStatus(juego.player.board1);
				consola.pideFilaColumna();
				tira=juego.doThrow(consola.getRow(),consola.getColumn());
				do
				{
					consola.getStatus(juego.player.board1);
					hundido=juego.verifyBoxes(tira);
					longitud=juego.player.board1.verificaHundido(consola.getRow(),consola.getColumn());
						if (tira==99) consola.pintaMensaje("¡¡¡¡AGUA!!!!");
						if ((longitud>0)&&(longitud==hundido)) consola.mensajeHundido(longitud);
						consola.pideFilaColumna();
					tira=juego.doThrow(consola.getRow(),consola.getColumn());
				}while(consola.getThrow() < (consola.getMaxThrow() + 1) && (juego.returnMatchStatus()==0));
				consola.pintaMensaje("\n FIN DEL JUEGO");
				if(juego.returnMatchStatus()==1) 	consola.pintaMensaje("\n Has hundido todos los barcos.");
				break;
			};
		case 2:
			{
				char fila[2];
				char columna[2];
				juego.startServerMatch();
				consola.setThrows(1);
				consola.setMaxThrows(50);
				consola.devuelveEstadoDescubierto(juego.player.board1);
				consola.getStatus(juego.player.board2);
				do
				{	
					r_tira2=juego.receiveNetworkThrow();
					consola.devuelveEstadoDescubierto(juego.player.board1);
					consola.getStatus(juego.player.board2);
					consola.pideFilaColumna();
					conversion(consola.getRow(),fila);
					conversion(consola.getColumn(),columna);
					tira2=juego.doNetworkThrow(fila,columna);
					consola.devuelveEstadoDescubierto(juego.player.board1);
					consola.getStatus(juego.player.board2);
					hundido=juego.verifyBoxes(tira2);
					longitud=juego.player.board1.verificaHundido(consola.getRow(),consola.getColumn());
						if (tira2==99) consola.pintaMensaje("¡¡¡¡Tú disparo ha sido AGUA!!!!");
						if ((longitud>0)&&(longitud==hundido)) consola.mensajeHundido(longitud);
				}while(consola.getThrow() < (consola.getMaxThrow() + 1) || (juego.returnMatchStatus()==0));
			};
		
		case 3:
			{
				char fila[2];
				char columna[2];
				consola.recibeIP();
				scanf("%s",&ip);
				juego.player.getIP(ip);
				juego.player.board1.introduceNumeroHundidos(0);
				consola.setThrows(1);
				consola.setMaxThrows(50);
				consola.devuelveEstadoDescubierto(juego.player.board1);
				consola.getStatus(juego.player.board2);
				juego.startClientMatch();
				consola.pideFilaColumna();
				conversion(consola.getRow(),fila);
				conversion(consola.getColumn(),columna);
				tira2=juego.doNetworkThrow(fila,columna);
				hundido=juego.verifyBoxes(tira3);
				longitud=juego.player.board1.verificaHundido(consola.getRow(),consola.getColumn());
						if (tira3==99) consola.pintaMensaje("¡¡¡¡Tú disparo ha sido AGUA!!!!");
						if ((longitud>0)&&(longitud==hundido)) consola.mensajeHundido(longitud);
				do
				{
					consola.devuelveEstadoDescubierto(juego.player.board1);
					consola.getStatus(juego.player.board2);
					r_tira3=juego.receiveNetworkThrow();
					consola.devuelveEstadoDescubierto(juego.player.board1);
					consola.getStatus(juego.player.board2);
					consola.pideFilaColumna();
					conversion(consola.getRow(),fila);
					conversion(consola.getColumn(),columna);
					tira3=juego.doNetworkThrow(fila,columna);
					consola.devuelveEstadoDescubierto(juego.player.board1);
					consola.getStatus(juego.player.board2);
					hundido=juego.verifyBoxes(tira3);
					longitud=juego.player.board1.verificaHundido(consola.getRow(),consola.getColumn());
						if (tira3==99) consola.pintaMensaje("¡¡¡¡Tú disparo ha sido AGUA!!!!");
						if ((longitud>0)&&(longitud==hundido)) consola.mensajeHundido(longitud);
				}while(consola.getThrow() < (consola.getMaxThrow() + 1) || (juego.returnMatchStatus()==0));
				break;
			};
	};
	
	
};
