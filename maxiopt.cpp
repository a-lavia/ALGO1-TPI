/******************************************************************************
 *                Juego de la vida toroidal - ALGO1-TT 2018c2                 *
 *                                                                            *
 *****************************************************************************/

#include "maxiopt.h"

void maxiopt(maxiopt_t *opts, char *arg, maxiopt_t **opt, int *extra)
{
	bool found = false;
	const char *curopt;
	char *argptr = arg;

	while (!found && opts->shortname) {
		curopt = opts->name;
		argptr = arg;
		*extra = 0;
		while (*argptr && *curopt && *argptr++ == *curopt++) (*extra)++;
		// found -> no hay mas argptr y no hay mas curopt, o no hay mas curopt pero args > 0
		if ((!*argptr && !*curopt) || (!*curopt && *argptr == '=' && opts->args > 0)) {
			if (*argptr) // salteo '='
				(*extra)++;
			found = true;
		} else {
			opts++;
		}
	}

	*opt = opts;
}
