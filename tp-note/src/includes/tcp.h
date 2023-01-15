#ifndef H_GL_TCP
#define H_GL_TCP

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>

#include "utils.h"

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

/* Crée un socket client de type TCP, tente de se connecter */
SOCKET init_tcp_client(char * hostname, int port);

/* Crée un socket serveur de type TCP */
SOCKET init_tcp_server(int port, int max_clients);

/* Attend une connection TCP, bloquant jusqu'à la connection */
SOCKET wait_tcp_connection(SOCKET sock);

/* Envoie un message à travers le socket */
void send_tcp(SOCKET sock, char * message);

/* Attend la réception d'un message, bloquant jusqu'à la réception */
char * recv_tcp(SOCKET sock);

#define close_socket(s) close(s)

#endif  // H_GL_TCP