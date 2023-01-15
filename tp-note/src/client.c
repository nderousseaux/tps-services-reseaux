#include "includes/client.h"

int client_udp(char * message) {

    // On se connecte au serveur
    SOCKADDR_IN to = { 0 };
    SOCKET sock = init_udp_client("localhost", 8080, &to);

    // On envoie un message au serveur
    send_udp(sock, &to, message);

    // On ferme la socket
    close_socket(sock);

    return EXIT_SUCCESS;
}

int client_tcp(char * message) {
    // On se connecte au serveur
    SOCKET sock = init_tcp_client("localhost", 8080);

    // On envoie un message au serveur
    send_tcp(sock, message);

    // On ferme la socket
    close_socket(sock);

    return EXIT_SUCCESS;
}