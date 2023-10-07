#ifndef MAIN_H
#define MAIN_H

int execute(char **arg, char *cmd);
void loop(void);
char *recieve_input(void);
char **toker(char *str);
char *checkpoint(char **arg);
char *_which(char *arg);

/*our own version of functions*/
ssize_t _getline(char **lineptr, size_t *restrict n, FILE *restrict stream);

/*string manipulation functons*/
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);

#endif
