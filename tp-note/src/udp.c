#include "includes/udp.h"

/* Crée un socket client de type UDP, sauvegarde la destination */
SOCKET init_udp_client(char * hostname, int port, SOCKADDR_IN * sin) {
	SOCKET sock;
	
	// On crée la socket
	CHKNEG(sock = socket(AF_INET, SOCK_DGRAM, 0));

	// On définit l'adresse du serveur
    sin->sin_addr = *(IN_ADDR *) gethostbyname(hostname)->h_addr;
    sin->sin_port = htons(port);
    sin->sin_family = AF_INET;

	return sock;
}

/* Crée un socket serveur de type udp */
SOCKET init_udp_server(int port) {
	SOCKET sock;

	// On crée la socket
	CHKNEG(sock = socket(AF_INET, SOCK_DGRAM, 0));

	// On définit l'adresse du serveur
	SOCKADDR_IN sin = { 0 };
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	// On lie la socket à l'adresse
	CHKNEG(bind(sock, (SOCKADDR *) &sin, sizeof(SOCKADDR)));

	return sock;
}

/* Envoie un message à travers le socket */
void send_udp(SOCKET sock, SOCKADDR_IN * dest, char * message) {
	unsigned int tosize = sizeof(SOCKADDR_IN);
    sendto(sock, message, strlen(message), 0, (SOCKADDR *)dest, tosize);
}

/* Reçoit un message à travers le socket, stocke l'addresse de celui qui à envoyé */
char * recv_udp(SOCKET sock, SOCKADDR_IN * from) {
	unsigned int fromsize = sizeof(SOCKADDR_IN);
	char * buffer;
	CHK(buffer = malloc(sizeof(char) * 1024));

	int n;
    CHKNEG(n = recvfrom(sock, buffer, 1024, 0, (SOCKADDR *)from, &fromsize));
    buffer[n] = '\0';

	return buffer;
}