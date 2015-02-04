#include "common.h"
#include <stdlib.h>

void str_to_ms_init(ms_state_t *st)
{
	if(st->is_str_to_ms_init_called)
		return;
	st->is_str_to_ms_init_called=!0;

	return;
}

void str_to_ms_finalize(ms_state_t *st)
{
	if(st->is_str_to_ms_finalize_called)
		return;
	st->is_str_to_ms_finalize_called=!0;

	return;
}

void str_to_ms(int *ms, char *s, ms_state_t *st)
{
	int i;

	for(i=0; i<st->Ceilings; i++)
		ms[i]=(int)strtol(s, &s, 10);
	
	return;
}
