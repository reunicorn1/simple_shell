#ifndef MAIN_H
#define MAIN_H

int execute(char **arg, char *cmd);
void loop(void);
char *recieve_input(void);
char **toker(char *str);
char *checkpoint(char **arg);
char *_which(char *arg);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);

#endif
