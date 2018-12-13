/**************************************
 * 
 * @author Mr Dk.
 * @version 2018.12.13
 * 
 **************************************/

#ifndef SOCKET_H_
#define SOCKET_H_

#define CONNECTED 1
#define UNCONNECTED 0

#define ENDIAN_LITTLE 1
#define ENDIAN_BIG 0

#define MAX_BUFFER_SIZE 2048

typedef struct Socket
{
    int _fd;
    int _bind;
    char _ipAddr[32];
    int _port;
    int _endian;
} Socket;

int connected(Socket *sock);

int connectAndBind(Socket *sock, char ipAddr[], int port, long timeout_sec);

void disconnect(Socket *sock);

void setEndian(Socket *sock, int endian);

int readLine(Socket *socket, char str[]);
int readString(Socket *socket, char str[]);
int readInt(Socket *socket, int *val);
int readFloat(Socket *socket, float *val);

int writeLine(Socket *socket, char str[]);
int writeString(Socket *socket, char str[]);
int writeInt(Socket *socket, int val);
int writeFloat(Socket *socket, float val);

#endif