#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define BUFSIZE 30

void error_handling(char **message);
int checkplace(char **board,int x,int y);
int checkwin(char **board, int size, int x, int y);
void printboard(char **board,int size);

int main()
{

	int serv_sock;
    	char message[BUFSIZE];
	int str_len;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;
	
	int size,x,y,count=0,win=0;
	char **board;

	// 시간 tm 구조체
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	if(argc!=2)
		{
			printf("Usage : %s <port>\n", argv[0]);
			exit(1);
		}
	serv_sock=socket(PF_INET,SOCK_DGRAM, 0);
	if(serv_sock==-1)
		error_handling("소켓 생성 오류");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if (bind(serv_sock,(struct sockaddr*) &serv_addr, sizeof(serv_addr))==1)
		error_handling("bind() error");
	
	//size 받기 
	clnt_addr_size=sizeof(clnt_addr);
	recvfrom(serv_sock, &size,4, 0,(struct sockaddr*) &clnt_addr, &clnt_addr_size);
		    

	//보드 동적 배열 할당
	board = (char **)malloc (sizeof(char *)* size);

	for(int i=0;i<size;i++)
		board[i] = (char *)malloc(sizeof(char) *size);

	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			board[i][j] ='';
	//ip 출력
	printf("client ip: %s \n", inet_ntoa(clnt_addr.sin_addr));
	// 시간 출력
	printf("client 접속 시간: %d-%d-%d %d:%d:%d\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
			tm.tm_hour, tm.tm_min, tm.tm_sec); 

	    server_addr.sin_family = AF_INET;
            server_addr.sin_addr.s_addr = htons(INADDR_ANY);
            server_addr.sin_port = htons(portNum);      

    while (1) 
    {
	//win을 받아서 상대가 이겼을때 1이오고 아니면 0으로    
        recvfrom(serv_sock,&win,4,0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	//니가 이겼을때 ㅋ
	if (win == 1)
       	{
		for(int i=0;i<size;i++)
			recvfrom(serv_sock, board[i], strlen(board[i]), 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		printf("클라이언트로 부터 받은 보드판:\n");
		printboard(board,size);
		printf("패배하셨습니다!\n");
		break;
        }
        
	//게임 진행 될떄 win =0
	for(int i=0;i<size;i++)
		recvfrom(serv_sock, board[i], strlen(board[i]), 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	printf("클라이언트로 부터 받은 보드판: \n");
	printboard(board,size);
	
	count+=2;
	if(count>=size*size)
	{
		printboard(board,size);
		printf("비겼습니다!\n");
		return 0;
	}

	while(1)
	
	{
		printf("좌표 위치 찍기");
		scanf("%d %d", &x,&y);
		if(checkplace(board,x,y)==0)
			break;
	}
	board[x][y] = 'O';
	printboard(board,size);
	
	//이겼을때
	if(checkwin(board,size,x,y)==1)
	{
		printf("경기에서 이겼습니다!!!!!!!!!!\n");
		printf("놓인 횟수: %d \n",count);
		win =1;
		sendto(serv_sock, &win, 4 ,0, (struct sockaddr*)&clnt_addr, sizeof(clnt_addr));
		for(int i=0;i<size;i++)
			sendto(serv_sock, board[i], strlen(board[i]),0, (struct sockaddr*)&clnt_addr, sizeof(clnt_addr));
		break;
	}
	sendto(serv_sock, &win, 4 ,0, (struct sockaddr*)&clnt_addr, sizeof(clnt_addr));
	for(int i=0;i<size;i++)
		sendto(serv_sock, board[i], strlen(board[i]),0, (struct sockaddr*)&clnt_addr, sizeof(clnt_addr));
    }

    close(serv_sock);
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
			printf("%c |",board[i][j]);
		printf("\n");
	}
	for(int j=0;j<size;j++)
		printf("---|");
	printf("\n\n");
}

int checkwin(char **board, int size, int x, int y)
{
	int count=0;
	//세로줄 완성 확인
	for(int i=0;i<size;i++)
	{
		if(board[i][y]!='O')
			break;
		else count++;
	}
	if(count==size)
		return 1;
	else count=0;

	//가로줄 완성 확인
	for(int i=0;i<size;i++)
	{
		if(board[x][i]!='O')
			break;
		else count++;
	}
	if(count==size)
		return 1;
	else count=0;

	//대각선 확인
	if(x+y==size-1)
	{
		for(int i=0;i<size;i++)
		{
			if(board[i][size-1-i]!='O')
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
			if(board[i][i]!='O')
				break;
			else count++;
		}
		if(count==size)
			return 1;
		else count=0;
	}
	return 0;
}

int checkplace(char **board,int x ,int y)
{
	if(board[x][y]!=' ')
	{
		printf("다시 놓아주세요 !\n\n");
		return 1;
	}
	else return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

