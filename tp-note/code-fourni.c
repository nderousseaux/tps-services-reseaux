#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int argc_cmd = 0;
char argv_cmd[1024][1024];


#define CHECK(x)                                            \
    do                                                      \
    {                                                       \
        if (!(x))                                           \
        {                                                   \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x);                                     \
            exit(EXIT_FAILURE);                             \
        }                                                   \
    } while (0)




char* prompt_shell(void)
{
    static char buf[512];

    snprintf(buf, sizeof(buf), "%s@ftp > ", getenv("USER"));
    fflush(stdout);

    return buf;
}


int takeInput(char* str)
{
    char *buf;
    HIST_ENTRY *last;
    buf = readline(prompt_shell());
    last = previous_history();
    if (strlen(buf) != '\0' && (!last || strcmp(last->line, buf))) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        strcpy(str, buf);
        return 1;
    }
}


void parse_command(char command[1024])
{
    if (!strlen(command)) {
        return;
    }

    int idx = 0;
    for (int i = 0 ; i < strlen(command) ; i++)
    {
        if (command[i] == ' ') {
            argc_cmd += 1;
            idx = 0;
        } else {
            argv_cmd[argc_cmd][idx] = command[i];
            idx += 1;
        }
    }
    argc_cmd++;
}

// If you want some debug
void print_args()
{
    printf("Here are the arguments:\n");
    for (int i = 0 ; i < argc_cmd ; i++) {
        printf("%s\n", argv_cmd[i]);
    }
}


void reset_args()
{
    memset(argv_cmd, 0, 1024 * 1024);
    argc_cmd = 0;
}



int process_input(...)
{
    
}


int main(int argc, char** argv)
{
    char command[1024];
    int cnt = 1;

    while (cnt) {
        reset_args();
        memset(command, 0, 1024);

        takeInput(command);

        if (strcmp("quit", command) == 0) {
            cnt = 0;
            continue;
        }
        parse_command(command);
        process_input(...);
    }

    return 0;
}