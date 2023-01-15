#include "includes/server.h"

SOCKET sock;
SOCKET sock_client;

void end_server() {
    printf("Bye\n");
    close_socket(sock);
    close_socket(sock_client);
    exit(EXIT_SUCCESS);
}

int server_udp(void) {
    // On capture le CTRL+C
    signal(SIGINT, end_server);

    SOCKET sock = init_udp_server(8080);
    
    while(1==1) {
        // On reçoit un message du client
        SOCKADDR_IN from = { 0 };
        char * message = recv_udp(sock, &from);

        // On affiche le message
        printf("Message reçu: %s\n", message);
    
        // On libère la mémoire
        free(message);
    }

    close_socket(sock);
    return EXIT_FAILURE;
}

int server_tcp(void) {

    // On capture le CTRL+C
    signal(SIGINT, end_server);

    // On crée la socket
    sock = init_tcp_server(8080, 1);

    while(1==1) {
        // On attend une connexion
        sock_client = wait_tcp_connection(sock);

        // On reçoit un message du client
        char * message = recv_tcp(sock_client);

        // On affiche le message
        printf("Message reçu: %s\n", message);
    
        // On libère la mémoire
        free(message);
        close_socket(sock_client);
    }
    close_socket(sock);
    return EXIT_FAILURE;
}