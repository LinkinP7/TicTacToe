#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#define BUFSIZE 30

int checkplace(char **board,int x,int y);
void printboard(char **board,int size);
void error_handling(char *message);
int main(int argc, char **argv)
{
	int sock;
	char message[BUFSIZE];
	int str_len;
	int size,count=0;
	char **board;

       	struct sockaddr_in server_addr;
	struct sockaddr_in from_addr;

	if(argc!=3)
	{
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
		exit(1);
	}

	sock=socket(PF_INET, SOCK_DGRAM,0);
	if(sock==-1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));

	server_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	printf("게임의 사이즈를 입력하세요 : "); scanf("%d",&size);

	//이차원 배열 동적 할당
	board = (char **)malloc (sizeof(char *) * size);
	for(int i=0;i<size;i++)
		board[i] = (char *)malloc(sizeof(char) *size);

	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			board[i][j] = ' ';







/*    do {
        cout << "Client: ";
        do {
            cin >> buffer;
            send(client, buffer, bufsize, 0);
            if (*buffer == '#') {
                send(client, buffer, bufsize, 0);
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != 42);

        cout << "Server: ";
        do {
            recv(client, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }

        } while (*buffer != 42);
        cout << endl;

    } while (!isExit);


    cout << "\n=> Connection terminated.\nGoodbye...\n";

    close(client);*/
    return 0;
}

int checkwin(char **board, int size, int x, int y)
{
	int count=0;
	for(int i=0;i<size;i++)
	{
		if(board[i][y]!='X')
			break;
		else count++;
	}
	if(count==size)
		return 1;
	else count=0;

	for(int i=0;i<size;i++)
	{
		if(board[x][i]!='X')
			break;
		else count++;
	}
	if(count==size)
		return 1;
	else count=0;

	if(x+y==size-1)
	{
		for(int i=0;i<size;i++)
		{
			if(board[i][size-1-i]!='X')
				break;
			else count++;
		}
		if(count==size)
			return 1;
		else count=0;
	}

	if(x==y)
	{
		for(int i=0;i<size;i++)
		{
			if(board[i][i]!='X')
				break;
			else count++;
		}
		if(count==size)
			return 1;
		else count=0;
	}
	return 0;
}

void printboard(char **board,int size)
{
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
			printf("---|");
		printf("\n");

		for(int j=0;j<size;j++)
			printf("%c  |",board[i][j]);
		printf("\n");
	}
	for(int j=0;j<size;j++)
		printf("---|");
	printf("\n\n");
}

int checkplace(char **board, int x, int y)
{
	if(board[x][y]!=' ')
	{
		printf("다시 놓아주세요 !\n\n");	return 1;
	}
	else return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


