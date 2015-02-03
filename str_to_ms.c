#include "common.h"
#include <stdlib.h>

void str_to_ms_init(ms_state_t *st)
{
	return;
}

void str_to_ms_finalize(ms_state_t *st)
{
	return;
}

void str_to_ms(int *ms, char *s, ms_state_t *st)
{
	int i;

	for(i=0; i<st->Ceilings; i++)
		ms[i]=(int)strtol(s, &s, 10);
	
	return;
}
