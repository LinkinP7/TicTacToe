#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 30

void error_handling(char *message);
int main()
{
	char message[BUFSIZE];
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

   
    recv(client, buffer, bufsize, 0);
   

    do {
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

    close(client);
    return 0;
}

int checkwin()
{
}

void printboard()
{
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


