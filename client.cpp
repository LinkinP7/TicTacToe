#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"
#define BUFSIZE 30

int checkwin(char **board, int size,int x,int y);
int checkplace(char **board,int x,int y);
void printboard(char **board,int size);
void error_handling(char *message);
int main(int argc, char **argv)
{
	int sock;
	char message[BUFSIZE];
	int str_len;
	int size,x,y,count=0,win=0;
	char **board;
	socklen_t addr_size;

       	struct sockaddr_in serv_addr;
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

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	printf("게임의 사이즈를 입력하세요 : "); scanf("%d",&size);

	//이차원 배열 동적 할당
	board = (char **)malloc (sizeof(char *) * size);
	for(int i=0;i<size;i++)
		board[i] = (char *)malloc(sizeof(char) *size);

	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			board[i][j] = ' ';

	sendto(sock, &size, 4, 0, (struct sockaddr*)&serv_addr , sizeof(serv_addr));
	addr_size=sizeof(from_addr);
	printboard(board,size);

	while(1)
	{
		while(1)
		{
			printf("위치를 입력하세요 : "); scanf("%d %d",&x,&y);
			if(checkplace(board,x,y)==0)
				break;
		}
		board[x][y] = 'X';

		count+=2;

		if(count>=size*size)
		{
			sendto(sock, &win, 4, 0, (struct sockaddr*)&serv_addr , sizeof(serv_addr));
			printboard(board,size);
			for(int i=0;i<size;i++)
				sendto(sock, board[i], strlen(board[i]), 0, (struct sockaddr*)&serv_addr , sizeof(serv_addr));
			printf("비겼습니다 !\n");
			break;
		}
		else
			printboard(board,size);

		if(checkwin(board,size,x,y)==1)
		{
			printf("경기에서 이겼습니다 !!!!!!!!!\n");
			printf("놓인 횟수 : %d \n",count-1);
			win=1;
			sendto(sock, &win, 4, 0, (struct sockaddr*)&serv_addr , sizeof(serv_addr));

			for(int i=0;i<size;i++)
				sendto(sock, board[i], strlen(board[i]), 0, (struct sockaddr*)&serv_addr , sizeof(serv_addr));
			break;
		}

		sendto(sock, &win, 4, 0, (struct sockaddr*)&serv_addr , sizeof(serv_addr));
		for(int i=0;i<size;i++)
			sendto(sock, board[i], strlen(board[i]), 0, (struct sockaddr*)&serv_addr , sizeof(serv_addr));
		recvfrom(sock, &win, 4, 0, (struct sockaddr*)&from_addr, &addr_size);
		if(win==1)
		{
			for(int i=0;i<size;i++)
				recvfrom(sock, board[i], strlen(board[i]), 0, (struct sockaddr*)&from_addr, &addr_size);
			printf("서버로 부터 받은 보드판 : \n");
			printboard(board,size);
			printf("패배하셨습니다 !\n");
			break;
		}

		for(int i=0;i<size;i++)
			recvfrom(sock, board[i], strlen(board[i]), 0, (struct sockaddr*)&from_addr, &addr_size);
		printf("서버로 부터 받은 보드판 : \n");
		printboard(board,size);
	}

	close(sock);
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


