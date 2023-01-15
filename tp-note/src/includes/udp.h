#ifndef H_GL_UDP
#define H_GL_UDP

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

/* Crée un socket client de type UDP, sauvegarde la destination */
SOCKET init_udp_client(char * hostname, int port, SOCKADDR_IN * sin);

/* Crée un socket serveur de type UDP */
SOCKET init_udp_server(int port);

/* Envoie un message à travers le socket */
void send_udp(SOCKET sock, SOCKADDR_IN * dest, char * message);

/* Reçoit un message à travers le socket, stocke l'addresse de celui qui à envoyé */
char * recv_udp(SOCKET sock, SOCKADDR_IN * from);

#define close_socket(s) close(s)

#endif  // H_GL_UDP