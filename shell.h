#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER 1024


/******** shell.c ********/

int main(int acrg, char **avrg, char **env);
void prompt(void);
void doornob(int signal_song);
void _EOF(char *buffer);
void shell_ex(char **cmd);


/******** cd.c ********/

void create_door(char **cmd, char *nm, char **env, int cc);
int change_direct(const char *trail);

/******** env-main.c ********/

void execute(char **cmd, char *nm, char **env, int cc);
void print_env(char **env);
char **_getTRAIL(char **env);
void error_msg(char *nm, int cc, char **cmd);


/******** token.c ********/

char **token(char *buffer, const char *tmi);

/******** memory_check.c ********/

void free_donut(char **cmd);
void free_ex(char **cmd);


/******** functions-etc.c ********/

int _atoi(char *str);
char *_strcat(char *dest, char *str);



/******** functions.c ********/

int _strcmp(char *str1, char *str2);
unsigned int _strlen(char *str);
char *_strcpy(char *dest, char *str);


#endif
