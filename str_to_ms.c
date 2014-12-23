#include "common.h"
#include <stdlib.h>

static _Bool init_done=0;

void str_to_ms_init(ms_state_t *st)
{
	if(!init_done){
		st->ms=malloc(st->Ceilings*sizeof(int));
		if(st->ms==NULL){
			error("failed to malloc ms\n");
			exit(EXIT_FAILURE);
		}

		init_done=!0;
	}

	return;
}

void str_to_ms_finalize(ms_state_t *st)
{
	free(st->ms);

	return;
}

int* str_to_ms(char *s, ms_state_t *st)
{
	int i;

	for(i=0; i<st->Ceilings; i++)
		st->ms[i]=(int)strtol(s, &s, 10);
	
	return st->ms;
}
