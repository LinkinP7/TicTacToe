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
		    

	//이게 아마 보드일듯?
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


   	 char buffer[bufsize];

    	struct sockaddr_in server_addr;
    	socklen_t size;

    	client = socket(AF_INET, SOCK_STREAM, 0);

    	if (client < 0) 
    	{
        	cout << "\nError establishing socket..." << endl;
       		 exit(1);
  	}

	 cout << "\n=> Socket server has been created..." << endl;

    

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

  
    if ((bind(client, (struct sockaddr*)&server_addr,sizeof(server_addr))) < 0) 
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }

    size = sizeof(server_addr);
    cout << "=> Looking for clients..." << endl;
    listen(client, 1);
    server = accept(client,(struct sockaddr *)&server_addr,&size);

    if (server < 0) 
        cout << "=> Error on accepting..." << endl;

    while (1) // 이런식으로?? 맞는거 같기도 하고
    {
        recvfrom(serv_sock,&win,4,0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if (win == 1)
       	{
		for(int i=0;i<size;i++)
			recvfrom(serv_sock, board[i], strlen(board[i]), 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		printf("클라이언트로 부터 받은 보드판:\n");
		printboard(board,size);
		printf("졋을때?");
		break;
        }
        }  while (*buffer != '*');

        do {
            cout << "\nServer: ";
            do {
                cin >> buffer;
                send(server, buffer, bufsize, 0);
                if (*buffer == '#') {
                    send(server, buffer, bufsize, 0);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');

            cout << "Client: ";
            do {
                recv(server, buffer, bufsize, 0);
                cout << buffer << " ";
                if (*buffer == '#') {
                    *buffer == '*';
                    isExit = true;
                }
            } while (*buffer != '*');
        } while (!isExit);


        cout << "\n\n=> Connection terminated with IP " << inet_ntoa(server_addr.sin_addr);
        close(server);
        cout << "\nGoodbye..." << endl;
        isExit = false;
        exit(1);
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
