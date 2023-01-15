#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/server.h"
#include "includes/client.h"

void usage(char * name) {
    fprintf(stderr, "Usage: %s [tcp|udp] [server|client] [message]\n", name);
    fprintf(stderr, "  server: Run the server\n");
    fprintf(stderr, "  client message: Run the client, send a message to the server\n");
}

int main(int argc, char *argv[]) {
    enum {TCP, UDP} proto;

    // Si l'arg 1 est égal à "tcp"
    if (
        argc > 1 &&
        strcmp(argv[1], "tcp") == 0
    )
        proto = TCP;
    else if (
        argc > 1 &&
        strcmp(argv[1], "udp") == 0
    )
        proto = UDP;
    else {
        usage(argv[0]);
        return EXIT_FAILURE;
    }
        
    // Si l'arg 1 est égal à "server" on lance le server
    if (
        argc > 2 &&
        strcmp(argv[2], "server") == 0
    )
        if (proto == TCP)
            return server_tcp();
        else
            return server_udp();
    
    // Sinon, on lance le client
    else if (
        argc > 3 &&
        strcmp(argv[2], "client") == 0
    ) {
        // On envoie la concaténation des arguments
        char * message;
        CHK(message = malloc(sizeof(char) * 1024));
        message = strcpy(message, argv[3]);
        for (int i = 4; i < argc; i++) {
            message = strcat(message, " ");
            message = strcat(message, argv[i]);
        }

        int res;
        if (proto == TCP)
            res = client_tcp(message);
        else
            res = client_udp(message);

        free(message);
        return res;
    }

    // Sinon on génère une erreur
    usage(argv[0]);
    return EXIT_FAILURE;
}