/*
 *  terminal.h
 *  barquitos
 *
 *  Created by Pedro on 06/04/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */


#define longEst 1
#include <stdio.h>
#include <string.h>
#include <iostream>

#include <string>

class terminal
{
	int terminalStatus;
	int throws;
	int maxThrows;
	int rColumn;
	int rRow;
	public: 
	void setRow(int vRow)
	{
		rRow=vRow;
	};
	int getRow(void)
	{
		return(rRow);
	};
	void setColumn(int vColumn)
	{
		rColumn=vColumn;
	};
	int getColumn(void)
	{
		return(rColumn);
	};
	void setThrows(int vThrows)
	{
		throws=vThrows;
	};
	void setMaxThrows(int vThrow)
	{
		maxThrows=vThrow;
	};
	int getMaxThrow(void)
	{
		return(maxThrows);
	};
	int getThrow(void)
	{
		return(throws);
	};
	void setTerminalStatus(int vStatus)
	{
		terminalStatus=vStatus;
	};
	int getTerminalStatus(void)
	{
		return(terminalStatus);
	};
//	int insertaEstadoTerminal(void)
//	{
//		return(terminalStatus);
//	};
	void getStatus(board tableroPlayer)
		{
				int x,y,t;
				int estado=0;
				x=0;y=0;t=1;
				printf("\n\n++++ENEMY'S BATTLEFIELD+++++\n");
				printf(" ");
				while (t<10)
				{
					printf("  %i ",t);
					t=t+1;
				};
				printf("\n");
				while (x<9)
				{
					printf("______________________________________");
					printf("\n");
					t=x + 65;
					std::cout << char(t);
					while (y<9)
					{
						printf("| ");
						estado=tableroPlayer.casillas[x][y].returnStatus();
						if ((estado>=0) && (estado<=10)) printf(" ?");
						else
						{
							if (estado==99) printf(" ~");
							else
							{
								if ((estado>10) && (estado<21))
								{
									printf(" X");
								};
							};
						};
						y=y+1;
					};
					printf("|");
					printf("\n");
					x=x+1;
					y=0;
				};
				printf("______________________________________");
				printf("\n");
		};
		void devuelveEstadoDescubierto(board tableroPlayer)
		{
				int x,y,t;
				int estado=0;
				x=0;y=0;t=1;
				printf("\n\n+++++++++YOURS BATTLEFIELD+++++++++\n");
				printf(" ");
				while (t<10)
				{
					printf("  %i ",t);
					t=t+1;
				};
				printf("\n");
				while (x<9)
				{
					printf("______________________________________");
					printf("\n");
					t=x + 65;
					std::cout << char(t);
					while (y<9)
					{
						printf("| ");
						estado=tableroPlayer.casillas[x][y].returnStatus();
						if ((estado>0) && (estado<=10)) printf("%s X");
						else
						{
							if (estado==0) printf("%s ~");
							else
							{
								if ((estado==99))
								{
									printf("%s A");
								}
								else
								{
									printf("%s *");
								
								};
							};
						};
						y=y+1;
					};
					printf("|");
					printf("\n");
					x=x+1;
					y=0;
				};
				printf("______________________________________");
				printf("\n");
 		};
	
int pintaMenu (void)
{
	int opcion;
	int hundido;
	int opcion3;
	do 
	{
		system("clear");
		printf("\t\t ******** Welcome to the navy battle ********\n");
		printf("\n\n");
		printf("\t 1.Start Simple Match vs your computer.\n");
		printf("\t 2.Start Network Match vs a client over the network.\n");
		printf("\t 3.EXIT NAVY BATTLE (No one choose this option).\n");
		scanf("%i",&opcion);
		switch (opcion)
		{
			case 1:
			{	
				setTerminalStatus(1);
				break;
				
			};
			case 2:
			{
				do
				{
				printf("\n\n");
				printf("\t ******** Battle navy over the Internet ********\n");
				printf("\n\n");
				printf("\t 1.Start match as a server.\n");
				printf("\t 2.Connect to a started match.\n");
				printf("\t 3.RETURN TO MAIN MENU.\n");
				printf("\n Select an option: ");
				scanf("%i",&opcion3);
					switch (opcion3)
					{
						case 1:
						{	
							setTerminalStatus(2);
							break;
						};
			
						case 2:
						{	
							setTerminalStatus(3);
							break;
						};
					};
				}while((opcion3>3) && (opcion3<1));
			};

		};
	}while((opcion>3) && (opcion<1));

};
void pintaMensaje (char mensaje[100])
{
	printf("%s\n",mensaje);
};
void recibeIP(void)
{

	printf("\tINSERT IP ADDRESS TO CONNECT.\n");
	printf("\tIP:");
	
};
void mensajeHundido(int longitud)
{
	printf("The boat with length % i has been destroyed \n",longitud);
};
void pideFilaColumna(void)
{
	int columna;
	char sino[1];
	char a_fila[1];
//	do
//	{
			printf("Throw %i of %i.\n",throws,maxThrows);
			do
			{
				printf("Insert a row: ");
				scanf("%s",&a_fila);
			}while((strcmp(a_fila,"A")!=0) && (strcmp(a_fila,"B")!=0) && (strcmp(a_fila,"C")!=0)&&(strcmp(a_fila,"D")!=0)&&(strcmp(a_fila,"E")!=0)&&(strcmp(a_fila,"F")!=0)&&(strcmp(a_fila,"G")!=0)&&(strcmp(a_fila,"H")!=0)&&(strcmp(a_fila,"I")!=0));
			do
			{
				printf("Insert a column: ");
				scanf("%i",&columna);
			}while((columna<1)&&(columna>10));
			setThrows(getThrow() + 1);
			printf("\n");
			system("clear");
		/*	if (tiradas<maxTiradas)
			{
				printf("¿Desea seguir tirando?(s): ");
				scanf("%s",&sino);
			};
		}while((strcmp(sino,"S")==0) || (strcmp(sino,"s")==0));*/
		setColumn(columna - 1 );
		if (strcmp(a_fila,"A")==0) setRow(0);
		if (strcmp(a_fila,"B")==0) setRow(1);
		if (strcmp(a_fila,"C")==0) setRow(2);
		if (strcmp(a_fila,"D")==0) setRow(3);
		if (strcmp(a_fila,"E")==0) setRow(4);
		if (strcmp(a_fila,"F")==0) setRow(5);
		if (strcmp(a_fila,"G")==0) setRow(6);
		if (strcmp(a_fila,"H")==0) setRow(7);
		if (strcmp(a_fila,"I")==0) setRow(8);

};
};





