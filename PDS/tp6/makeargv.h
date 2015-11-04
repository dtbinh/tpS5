#ifndef H_MAKEARGV
#define H_MAKEARGV

int makeargv(const char *s, const char *delimiters, char ***argvp);
void freeargv(char **argv);

#endif
