/**************************************
 * 
 * @author Mr Dk.
 * @version 2018.12.13
 * 
 **************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "dksocket.h"

int connected(Socket *sock)
{
    if (sock->_fd <= 0 || sock->_bind <= 0)
    {
        return UNCONNECTED;
    }
    else
    {
        return CONNECTED;
    }
}

int connectAndBind(Socket *sock, char ipAddr[], int port, long timeout_sec)
{
    strcpy(sock->_ipAddr, ipAddr);
    sock->_port = port;
    sock->_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (sock->_fd < 0)
    {
        return sock->_fd;
    }

    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(struct sockaddr_in));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    dest.sin_addr.s_addr = htonl(INADDR_ANY);

    // Set fd into non-block mode
    fcntl(sock->_fd, F_SETFL, O_NONBLOCK);
    inet_aton(ipAddr, &(dest.sin_addr));

    sock->_bind = connect(sock->_fd, (struct sockaddr *)&dest, sizeof(struct sockaddr));
    if (sock->_bind == -1)
    {
        if (errno != EINPROGRESS)
        {
            close(sock->_fd);
            return sock->_bind;
        }

        fd_set writeSet;
        FD_ZERO(&writeSet);
        FD_SET(sock->_fd, &writeSet);
        struct timeval timeout = {timeout_sec, 0};

        if (select(sock->_fd + 1, NULL, &writeSet, NULL, &timeout))
        {
            sock->_bind = CONNECTED;
        }
    }

    int flags = fcntl(sock->_fd, F_GETFL);
    flags &= ~O_NONBLOCK;
    fcntl(sock->_fd, F_SETFL, flags);
    return sock->_bind;
}

void setEndian(Socket *sock, int endian)
{
    if (endian == ENDIAN_BIG)
    {
        sock->_endian = ENDIAN_BIG;
    }
    else
    {
        sock->_endian = ENDIAN_LITTLE;
    }
}

void disconnect(Socket *sock)
{
    if (connected(sock))
    {
        close(sock->_bind);
        sock->_bind = -1;
    }
}

int readLine(Socket *sock, char str[])
{
    int count = 0;
    char temp = 0;
    while (read(sock->_fd, &temp, 1))
    {
        if (temp == '\n')
        {
            break;
        }
        str[count] = temp;
        count++;
    }
    return count;
}

int readString(Socket *sock, char str[])
{
    int count = 0;
    char temp = 0;
    while (read(sock->_fd, &temp, 1))
    {
        if (temp == '\0')
        {
            break;
        }
        str[count] = temp;
        count++;
    }
    str[count] = '\0';
    return count;
}

int readInt(Socket *sock, int *val)
{
    int count = 0;
    char temp = 0;
    char buf[sizeof(int)];
    while (read(sock->_fd, &temp, 1))
    {
        if (sock->_endian == ENDIAN_BIG)
        {
            buf[sizeof(int) - 1 - count] = temp;
        }
        else
        {
            buf[count] = temp;
        }

        count++;
        if (count == sizeof(int))
        {
            break;
        }
    }
    memcpy(val, buf, sizeof(int));
    return count;
}

int readFloat(Socket *sock, float *val)
{
    int count = 0;
    char temp = 0;
    char buf[sizeof(float)];
    while (read(sock->_fd, &temp, 1))
    {
        if (sock->_endian == ENDIAN_BIG)
        {
            buf[sizeof(float) - 1 - count] = temp;
        }
        else
        {
            buf[count] = temp;
        }

        count++;
        if (count == sizeof(float))
        {
            break;
        }
    }
    memcpy(val, buf, sizeof(float));
    return count;
}

int writeInt(Socket *sock, int val)
{
    int count = 0;
    char buf[sizeof(int)];
    memcpy(buf, &val, sizeof(int));
    if (sock->_endian == ENDIAN_BIG)
    {
        for (unsigned int i = 0; i < sizeof(int); i++)
        {
            count += write(sock->_fd, &buf[sizeof(int)-1-i], 1);
        }
    }
    else 
    {
        for (unsigned int i = 0; i < sizeof(int); i++)
        {
            count += write(sock->_fd, &buf[i], 1);
        }
    }
    return count;
}

int writeFloat(Socket *sock, float val)
{
    int count = 0;
    char buf[sizeof(float)];
    memcpy(buf, &val, sizeof(float));
    if (sock->_endian == ENDIAN_BIG)
    {
        for (unsigned int i = 0; i < sizeof(float); i++)
        {
            count += write(sock->_fd, &buf[sizeof(float)-1-i], 1);
        }
    }
    else 
    {
        for (unsigned int i = 0; i < sizeof(float); i++)
        {
            count += write(sock->_fd, &buf[i], 1);
        }
    }
    return count;
}

int writeString(Socket *sock, char str[])
{
    return write(sock->_fd, str, strlen(str) + 1);
}

int writeLine(Socket *sock, char str[])
{
    int count = 0;
    count += write(sock->_fd, str, strlen(str) + 1);
    count += write(sock->_fd, "\n", 1);
    return count;
}