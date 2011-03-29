/*
 *  partida.h
 *  barquitos
 *
 *  Created by Pedro on 18/03/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */



#include <player.h>
#define retries 50
#define buffer 256
//Para identificar a los barcos unicamente en el tablero los numeraremos por orden de 
//introduccion: Es decir el barco de mayor longitud recibira el valor 1 asi hasta 10, decrementando 
//las longitudes de los barcos. Quedando los valores as:
//4->1
//3->2
//3->3
//2->4
//2->5
//2->6
//1->7
//1->8
//1->9
//1->10

class match
{
	int matchStatus;
	public:
	thePlayer player;
	void changeMatchStatus(int vStatus)
	{
		//If match status is 0, match is ongoing
		//If 1 the match is finished
		matchStatus=vStatus;
	};
	int returnMatchStatus(void)
	{
		return(matchStatus);
	};
	void startSimpleMatch(void)
	{
		player.startMatch(1);
	};
	void startServerMatch(void)
	{
		player.startMatch(2);
	};
	void startClientMatch(void)
	{
		player.startMatch(3);
	};
	
	int doThrow(int row,int column)
	{
		int status;
		status=player.board1.casillas[row][column].returnStatus();
		if(((status>= 11) && (status<= 20 )) || (status==99) ) printf("Capitan!!!!, ya ha disparado sobre esa casilla.\n\n");
		else{
			if (status==0) player.board1.casillas[row][column].changeStatus(99);
			if ((status >= 1) && (status <= 10))player.board1.casillas[row][column].changeStatus(status + 10);
		};
		if ((player.board1.casillas[row][column].returnStatus()>10)&&(player.board1.casillas[row][column].returnStatus()<=20)) player.board1.introduceNumeroHundidos( player.board1.devuelveNumeroHundidos() + 1);
		if ( player.board1.devuelveNumeroHundidos()==20) changeMatchStatus(1);
		else changeMatchStatus(0);
		return(player.board1.casillas[row][column].returnStatus());
	};
	int doNetworkThrow(char row[2],char column[2])
	{
		
		int des;
		char envio[buffer];
		char recibir[buffer];
		int v_fila,v_columna;
		v_fila=v_columna=0;
		strcpy(envio,"TIRADA");
		des=player.getDescriptor();
		player.sendData(des,envio,sizeof(envio));
		player.receive(des,recibir,sizeof(recibir));
		strcpy(envio,row);
		if (strcmp(recibir,"OK")==0) player.sendData(des,envio,sizeof(envio));
		strcpy(envio,column);
		player.receive(des,recibir,sizeof(recibir));
		if (strcmp(recibir,"OK")==0) player.sendData(des,envio,sizeof(envio));
		strcpy(envio,"FTIRADA");
		if (strcmp(recibir,"OK")==0) player.sendData(des,envio,sizeof(envio));
		strcpy(envio,"OK");
		player.sendData(des,envio,sizeof(envio));
		player.receive(des,recibir,sizeof(recibir));
		v_fila=((int)row[0])-48;
		v_columna=((int)column[0])-48;
		player.board2.casillas[v_fila][v_columna].changeStatus(atoi(recibir));
		
		if ( player.board1.devuelveNumeroHundidos()==20) changeMatchStatus(1);
		else changeMatchStatus(0);

		return(player.board1.casillas[v_fila][v_columna].returnStatus());
	
	};
	
	
	int receiveNetworkThrow(void)
	{
		int des;
		int fila,columna;
		char envio[buffer];
		char recibir[buffer];
		char tira2[2];
		int tira;
	
		des=player.getDescriptor();
		do
		{
			player.receive(des,recibir,sizeof(recibir));
			if (strcmp(recibir,"TIRADA")==0)
			{
				strcpy(envio,"OK");
				player.sendData(des,envio,sizeof(envio));
				player.receive(des,recibir,sizeof(recibir));
				fila=((int)recibir[0])-48;
				strcpy(envio,"OK");
				player.sendData(des,envio,sizeof(envio));
				player.receive(des,recibir,sizeof(recibir));
				columna=((int)recibir[0])-48;
			//	strcpy(envio,"OK");
			//	player.enviar(des,envio,sizeof(envio));
			};
			
		}while(strcmp(recibir,"FTIRADA")!=0);
		tira=doThrow(fila,columna);
		switch(tira)
		{
			case 99: 
			{
				strcpy(envio,"99");break;
			};
			case 10:
			{
				strcpy(envio,"10");break;
			};
			case 11:
			{
				strcpy(envio,"11");break;
			};
			case 12:
			{
				strcpy(envio,"12");break;
			};
			case 13:
			{
				strcpy(envio,"13");break;
			};
			case 14:
			{
				strcpy(envio,"14");break;
			};
			case 15:
			{
				strcpy(envio,"15");break;
			};
			case 16:
			{
				strcpy(envio,"16");break;
			};
			case 17:
			{
				strcpy(envio,"17");break;
			};
			case 18:
			{
				strcpy(envio,"18");break;
			};
			case 19:
			{
				strcpy(envio,"19");break;
			};
			case 20:
			{
				strcpy(envio,"20");break;
			};
		};
		do
		{
			player.receive(des,recibir,sizeof(recibir));
		}while (strcmp(recibir,"OK")!=0);
		player.sendData(des,envio,sizeof(envio));
	return(tira);
	};
	
	int verifyBoxes(int valor)
	{
			int fila,columna,estado,cont;
				fila=0;columna=0;estado=0;cont=0;
				while (fila<9)
				{
					while (columna<9)
					{
						estado=player.board1.casillas[fila][columna].returnStatus();
						if (estado==valor) cont=cont+1;
						columna=columna+1;
					};
					printf("\n");
					fila=fila+1;
					columna=0;
				};
				return(cont);
	};
	
		int verifyBoxes2(int valor)
	{
			int fila,columna,estado,cont;
				fila=0;columna=0;estado=0;cont=0;
				while (fila<9)
				{
					while (columna<9)
					{
						estado=player.board2.casillas[fila][columna].returnStatus();
						if (estado==valor) cont=cont+1;
						columna=columna+1;
					};
					printf("\n");
					fila=fila+1;
					columna=0;
				};
				return(cont);
	};
	
};


		