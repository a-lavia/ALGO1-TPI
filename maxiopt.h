#ifndef MAXIOPT_H
#define MAXIOPT_H

typedef struct {
	char shortname;
	const char *name;
	int args;
} maxiopt_t;

void maxiopt(maxiopt_t *opts, char *arg, maxiopt_t **opt, int *extra);

#endif // MAXIOPT_H
