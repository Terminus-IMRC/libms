#include "common.h"
#include <stdio.h>

void output_ms_init(ms_state_t *st)
{
	if(st->is_output_ms_init_called)
		return;
	st->is_output_ms_init_called=!0;

	return;
}

void output_ms_finalize(ms_state_t *st)
{
	if(st->is_output_ms_finalize_called)
		return;
	st->is_output_ms_finalize_called=!0;

	return;
}

void output_ms(int *ms, FILE *fp, ms_state_t *st)
{
	int i;

	for(i=0; i<ms_Ceilings(st); i++)
		fprintf(fp, "%d%c", ms[i], i!=ms_Ceilings(st)-1?' ':'\n');

	return;
}
