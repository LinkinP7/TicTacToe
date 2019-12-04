#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#define BUFSIZE 30

void printboard(char **board,int size);
void error_handling(char *message);
int main()
{
	char message[BUFSIZE];
	int size,count=0;
	char **board;


    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

   
    recv(client, buffer, bufsize, 0);
   

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

int checkwin()
{
}

void printboard()
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

int checkplace()
{
}

void error_handling()
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


