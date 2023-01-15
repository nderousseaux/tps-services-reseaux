#include "includes/tcp.h"

/* Crée un socket client de type TCP, tente de se connecter */
SOCKET init_tcp_client(char * hostname, int port) {
	SOCKET sock;
	
	// On crée la socket
	CHKNEG(sock = socket(AF_INET, SOCK_STREAM, 0));

	// On définit l'adresse du serveur
	SOCKADDR_IN sin = { 0 };
    sin.sin_addr = *(IN_ADDR *) gethostbyname(hostname)->h_addr;
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;

	// On se connecte au serveur
    CHKNEG(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)));
	return sock;
}

/* Crée un socket serveur de type TCP */
SOCKET init_tcp_server(int port, int max_clients) {
	SOCKET sock;

	// On crée la socket
	CHKNEG(sock = socket(AF_INET, SOCK_STREAM, 0));

	// On définit l'adresse du serveur
	SOCKADDR_IN sin = { 0 };
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;

	// On lie la socket à l'adresse
	CHKNEG(bind(sock, (SOCKADDR *) &sin, sizeof(SOCKADDR)));

	// On met la socket en écoute
	CHKNEG(listen(sock, max_clients));

	return sock;
}

/* Attend une connection TCP, bloquant jusqu'à la connection */
SOCKET wait_tcp_connection(SOCKET sock) {
	SOCKET csock;
	SOCKADDR_IN csin = { 0 };

	// On attend une connexion
	unsigned int sinsize = sizeof csin;
	CHKNEG(csock = accept(sock, (SOCKADDR *)&csin, &sinsize));

	return csock;
}

/* Envoie un message à travers le socket */
void send_tcp(SOCKET sock, char * message) {
	CHKNEG(send(sock, message, strlen(message), 0));
}

/* Attend la réception d'un message, bloquant jusqu'à la réception */
char * recv_tcp(SOCKET sock) {
	char * buffer = malloc(1024);
	int n = 0;
	// On reçoit un message du client
	CHKNEG(n = recv(sock, buffer, 1024, 0));

	// On ajoute le caractère de fin de chaîne
	buffer[n] = '\0';

	return buffer;
}