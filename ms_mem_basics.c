#include "common.h"
#include <stdlib.h>
#include <stdarg.h>

void ms_mem_basics_init(ms_state_t *st)
{
	st->init_and_finalize_counts.mem_basics++;
	if(st->init_and_finalize_counts.mem_basics!=1)
		return;

	ms_ms_tmp(st)=ms_alloc(st);

	return;
}

void ms_mem_basics_finalize(ms_state_t *st)
{
	st->init_and_finalize_counts.mem_basics--;
	if(st->init_and_finalize_counts.mem_basics!=0)
		return;

	ms_free(ms_ms_tmp(st), st);

	return;
}

int* ms_alloc(ms_state_t *st)
{
	int *p;

	p=malloc(ms_Ceilings(st)*sizeof(int));
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

void ms_move(int *ms_dst, int *ms_src, ms_state_t *st)
{
	ms_cp(ms_ms_tmp(st), ms_src, st);
	ms_cp(ms_dst, ms_ms_tmp(st), st);

	return;
}

/* Actually this argument order is irregular, but it cannot be helped since C89 does not have va_copy nor __va_copy */
void ms_subst(int *ms, ms_state_t *st, ...)
{
	int i;
	va_list ap;

	va_start(ap, st);
	for(i=0; i<ms_Ceilings(st); i++)
		ms[i]=va_arg(ap, int);
	va_end(ap);

	return;
}
