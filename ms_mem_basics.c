#include "common.h"
#include <stdlib.h>
#include <stdarg.h>

void ms_mem_basics_init(ms_state_t *st)
{
	if(st->is_ms_mem_basics_init_called)
		return;
	st->is_ms_mem_basics_init_called=!0;

	st->ms_tmp=ms_alloc(st);

	return;
}

void ms_mem_basics_finalize(ms_state_t *st)
{
	if(st->is_ms_mem_basics_finalize_called)
		return;
	st->is_ms_mem_basics_finalize_called=!0;

	ms_free(st->ms_tmp, st);

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

void ms_move(int *ms_dst, int *ms_src, ms_state_t *st)
{
	ms_cp(st->ms_tmp, ms_src, st);
	ms_cp(ms_dst, st->ms_tmp, st);

	return;
}

/* Actually this argument order is irregular, but it cannot be helped since C89 does not have va_copy nor __va_copy */
void ms_subst(int *ms, ms_state_t *st, ...)
{
	int i;
	va_list ap;

	va_start(ap, st);
	for(i=0; i<st->Ceilings; i++)
		ms[i]=va_arg(ap, int);
	va_end(ap);

	return;
}
