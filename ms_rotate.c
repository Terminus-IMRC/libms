#include "common.h"
#include <stdlib.h>

void ms_rotate_init(ms_state_t *st)
{
	if(st->is_ms_rotate_init_called)
		return;
	st->is_ms_rotate_init_called=!0;

	ms_mem_basics_init(st);

	return;
}

void ms_rotate_finalize(ms_state_t *st)
{
	if(st->is_ms_rotate_finalize_called)
		return;
	st->is_ms_rotate_finalize_called=!0;

	ms_mem_basics_finalize(st);

	return;
}

void ms_rotate(int *ms, ms_rotate_t rcond, ms_state_t *st)
{
	int i, j;

	switch(rcond){
		case MS_ROTATE_NOP:
			break;

		case MS_ROTATE_R:
		case MS_ROTATE_3L:
			for(i=0; i<st->X; i++)
				for(j=0; j<st->X; j++)
					st->ms_tmp[j*st->X+(st->X-i-1)]=ms[i*st->X+j];
			ms_cp(ms, st->ms_tmp, st);
			break;

		case MS_ROTATE_2R:
		case MS_ROTATE_2L:
			for(i=0; i<st->X; i++)
				for(j=0; j<st->X; j++)
					st->ms_tmp[(st->X-i-1)*st->X+(st->X-j-1)]=ms[i*st->X+j];
			ms_cp(ms, st->ms_tmp, st);
			break;

		case MS_ROTATE_L:
		case MS_ROTATE_3R:
			for(i=0; i<st->X; i++)
				for(j=0; j<st->X; j++)
					st->ms_tmp[(st->X-j-1)*st->X+i]=ms[i*st->X+j];
			ms_cp(ms, st->ms_tmp, st);
			break;

		case MS_ROTATE_REV:
			for(i=0; i<st->X; i++)
				for(j=0; j<st->X; j++)
					st->ms_tmp[i*st->X+(st->X-j-1)]=ms[i*st->X+j];
			ms_cp(ms, st->ms_tmp, st);
			break;

		default:
			error("invalid rotate condition: %d\n", rcond);
			exit(EXIT_FAILURE);
	}

	return;
}
