#ifndef H_GL_SERVER
#define H_GL_SERVER

#include <signal.h>

#include "tcp.h"
#include "udp.h"

int server_udp(void);

int server_tcp(void);

#endif