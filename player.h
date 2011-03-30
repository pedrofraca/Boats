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

#include<string.h>
#include<board.h>
#define port 4576
class thePlayer
{
	char name[10];
	char ip[14];
	int descriptor;
	int throwStatus;
		public:
			board board1;
			board board2;
	void setThrowStatus(int vStatus)
	{
		//si el estado de la tirada es 0, todavia no ha concluido
		//si el estado de la tirada es 1, ha concluido.
		throwStatus=vStatus;
	};
	int returnThrowStatus(void)
	{
		return(throwStatus);
	};

	void getName(char vName[10])
	{
		strcpy(name,vName);
	};
	void getIP(char v_ip[14])
	{
		strcpy(ip,v_ip);
	};
	void setDescriptor(int v_des)
	{
		descriptor=v_des;
	};
	int getDescriptor(void)
	{
		return(descriptor);
	};
	void sendData(int sock,char *buf,int long_buf)
	{
		int bytesToSend=long_buf;
		int bytesSent;
		while (bytesToSend>0)
		{
			bytesSent=send(sock,buf,bytesToSend,0);
			if (bytesSent==-1)
			{
				printf("Error sending data");
				exit(-1);
			};
			bytesToSend = bytesToSend - bytesSent;
			buf = buf + bytesSent;
		};
	};
//Misma descripción que la anterior pero a la inversa.
	void receive (int sock,char *buf,int long_buf)
	{
		int bytesToReceive=long_buf;
		int bytesReceived;
		while (bytesToReceive>0)
		{
			bytesReceived=recv(sock,buf,bytesToReceive,0);
			if (bytesReceived==-1)
			{
				printf("Error receiving data");
				exit(-1);
			};
			bytesToReceive = bytesToReceive - bytesReceived;
			buf =buf +  bytesReceived;
		};
	};

	void startMatch(int num)
	{
	//Si num=1 se inicia una partida simple y si es 2 una partida en red
		switch (num)
		{
			case 1:
			{
				board1.putBoatsOverTheBoard();
				break;
			};
			case 2:
			{
					int desAcp;
					socklen_t cliLong;
				// Este caso el jugador hace de servidor de la partida.
					struct sockaddr_in dirServer,dirCliente;//Direccion del servidor.
					if ((descriptor=socket(AF_INET,SOCK_STREAM,0))==-1)
					{
						printf("Error creating the socket\n");
						exit (-1);
					};
					dirServer.sin_family=AF_INET;
					dirServer.sin_addr.s_addr=inet_addr("0.0.0.0");
					dirServer.sin_port=htons(port);
					if ((bind(descriptor,(struct sockaddr *) &dirServer,sizeof(dirServer)))<0)
					{
						printf("Error publishing ip address. \n");
						exit(-1);
					};
					if (listen(descriptor,5)==-1)
					{
						printf("Error creating the clients queu. \n");
						exit(-1);
					};
					cliLong=sizeof(dirCliente);
					//Bucle para acpetar las conexiones entrantes.
					int clienteConectado;
					clienteConectado=0;
					while (clienteConectado==0)
					{
						printf("\t YOU DECIDE TO PLAY AS A SERVER, WAITING CONNECTION FOR A CLIENT......");
						if ((desAcp=accept(descriptor,(struct sockaddr *) &dirCliente, &cliLong))==-1)
						{
							printf("Error accepting connections \n");
							exit(-1);
						}
						else
						{
							clienteConectado=1;
						};
					};
					close(descriptor);
					printf("\n Client connected.\n");
					sleep(1);
					setDescriptor(desAcp);
					board1.putBoatsOverTheBoard();
				break;
			};
			case 3:
			{
				struct sockaddr_in dirServer1;	
				if((descriptor=socket(AF_INET,SOCK_STREAM,0))==-1)
				{
					printf("\n Error creating connector with client.\n");
					exit(-1);
				}
				dirServer1.sin_family=AF_INET;
				dirServer1.sin_addr.s_addr=inet_addr(ip);
				dirServer1.sin_port=htons(port);
				if (connect(descriptor,(struct sockaddr *)&dirServer1,sizeof(dirServer1))==-1)
					{
						printf("Error connecting with server.");
						exit(-1);
					} 
				else
					{ 
						printf("Connection established\n");
						setDescriptor(descriptor);
						board1.putBoatsOverTheBoard();
					};
				break;
			};
		};
	};
	
	
};

