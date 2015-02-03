#include "common.h"
#include <stdlib.h>

void ms_mem_basics_init(ms_state_t *st)
{
	return;
}

void ms_mem_basics_finalize(ms_state_t *st)
{
	return;
}

int* ms_alloc(ms_state_t *st)
{
	int *p;

	p=malloc(st->Ceilings*sizeof(int));
	if(p==NULL){
		error("failed to malloc p\n");
		exit(EXIT_FAILURE);
	}

	return p;
}

void ms_free(int *ms, ms_state_t *st)
{
	free(ms);

	return;
}
