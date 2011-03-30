 /* Is a game to play boat battleship using network
    Copyright (C) 2004  <pedro.fraca@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <err.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <stdlib.h>
#include <iostream>

#include <random>
#include <time.h>

#include <boat.h>
#include <box.h>

#define columnas 9

#define filas 9
#define longEst 1

class board
{
	int numeroHundidos;
	public:
	box casillas [filas][columnas];
	boat barco1[10];
	void introduceNumeroHundidos(int v_numeroHundidos)
		{
			numeroHundidos=v_numeroHundidos;
		};
	int devuelveNumeroHundidos(void)
	{
		return(numeroHundidos);
	};
		int insertaBarco(boat barco)
		{
			int contador,libre;
			int col,fil,dir;
			int error=0;
			time_t t;
			contador=0;
			srand((unsigned) time(&t));
			
			int estado=0;
			estado=0;
			while (estado!=1)
			{
				col=rand()%9;
				fil=rand()%9;
			if (casillas[fil][col].returnStatus()==0)
			{
				//srand((unsigned) time(&t));
				//si la direccion del barco es 1 hacia la derecha, si es 0 hacia abajo.
				dir=rand() % 2;
				if (dir==1) //en el caso de que la direccion sea hacia la derecha.
				{
					if ((barco.devuelveLongitud()+col)-1<=8)
					{
						libre=0;
						error=0;
						contador=col;
						while ((libre< barco.devuelveLongitud() ) && (error==0) && (contador<9))
						//for (contador=col;contador=col+barco.devuelveLongitud();contador++) if(casillas[contador][fil].devuelveEstado()==0) libre=libre+1;
						{
								if(casillas[fil][contador].returnStatus()==0)
								{
									libre=libre+1;
									contador=contador+1;
								}
								else
								{
										error=1;
								};
							
						};
							if (libre >= barco.devuelveLongitud())
							{
								contador=col;
								libre=barco.devuelveLongitud();
	//							for (contador=col;contador=col+barco.devuelveLongitud();contador++) casillas[contador][fil].introEstado(barco.devuelveLongitud()); 
								while (libre>0)
									{	
										casillas[fil][contador].changeStatus(barco.devuelveValor());
										contador=contador + 1;
										libre=libre-1;
									};
								estado=1;
							};
					};
				}
				else//en el caso de que la direccion sea 0 hacia abajo.
				{
					if ((barco.devuelveLongitud()+fil)-1<=8)
						{
							libre=0;
							error=0;
							contador=fil;
							while ((libre< barco.devuelveLongitud()) && (error==0) && (contador<9))
							{
//							for (contador=col;contador=col+barco.devuelveLongitud();contador++)
								if(casillas[contador][col].returnStatus()==0)
								{
									libre=libre+1;
									contador=contador+1;
								}
								else
								{
									error=1;
								};
							};
							if (libre>=barco.devuelveLongitud())
							{
								//for (contador=col;contador=col+barco.devuelveLongitud();contador++)
								contador=fil;
								libre=barco.devuelveLongitud();
								while (libre>0)
								{
									casillas[contador][col].changeStatus(barco.devuelveValor());
									contador=contador + 1;
									libre=libre-1;
								};
								estado=1;
							};
						};
				};
			};
				
	};
};

		void putBoatsOverTheBoard(void)
		{
			time_t t;
			srand((unsigned) time(&t));
			barco1[0].introLongitud(4);
			barco1[1].introLongitud(3);
			barco1[2].introLongitud(3);
			barco1[3].introLongitud(2);
			barco1[4].introLongitud(2);
			barco1[5].introLongitud(2);
			barco1[6].introLongitud(1);
			barco1[7].introLongitud(1);
			barco1[8].introLongitud(1);
			barco1[9].introLongitud(1);
			barco1[0].introValor(1);
			barco1[1].introValor(2);
			barco1[2].introValor(3);
			barco1[3].introValor(4);
			barco1[4].introValor(5);
			barco1[5].introValor(6);
			barco1[6].introValor(7);
			barco1[7].introValor(8);
			barco1[8].introValor(9);
			barco1[9].introValor(10);
			insertaBarco(barco1[0]);
			insertaBarco(barco1[1]);
			insertaBarco(barco1[2]);
			insertaBarco(barco1[3]);
			insertaBarco(barco1[4]);
			insertaBarco(barco1[5]);
			insertaBarco(barco1[6]);
			insertaBarco(barco1[7]);
			insertaBarco(barco1[8]);
			insertaBarco(barco1[9]);
		
		};
	int verificaHundido(int fila, int columna)
	{
		int contador=0;
		int longi=0;
		while ((contador<11))
		{
				if ((casillas[fila][columna].returnStatus()-10)==(barco1[contador].devuelveValor()))
				{
					longi=barco1[contador].devuelveLongitud();
				};
				contador=contador+1;
		};
		return(longi);
	};
	
};

