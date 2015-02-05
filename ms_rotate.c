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
			for(i=0; i<ms_X(st); i++)
				for(j=0; j<ms_X(st); j++)
					ms_ms_tmp(st)[j*ms_X(st)+(ms_X(st)-i-1)]=ms[i*ms_X(st)+j];
			ms_cp(ms, ms_ms_tmp(st), st);
			break;

		case MS_ROTATE_2R:
		case MS_ROTATE_2L:
			for(i=0; i<ms_X(st); i++)
				for(j=0; j<ms_X(st); j++)
					ms_ms_tmp(st)[(ms_X(st)-i-1)*ms_X(st)+(ms_X(st)-j-1)]=ms[i*ms_X(st)+j];
			ms_cp(ms, ms_ms_tmp(st), st);
			break;

		case MS_ROTATE_L:
		case MS_ROTATE_3R:
			for(i=0; i<ms_X(st); i++)
				for(j=0; j<ms_X(st); j++)
					ms_ms_tmp(st)[(ms_X(st)-j-1)*ms_X(st)+i]=ms[i*ms_X(st)+j];
			ms_cp(ms, ms_ms_tmp(st), st);
			break;

		case MS_ROTATE_REV:
			for(i=0; i<ms_X(st); i++)
				for(j=0; j<ms_X(st); j++)
					ms_ms_tmp(st)[i*ms_X(st)+(ms_X(st)-j-1)]=ms[i*ms_X(st)+j];
			ms_cp(ms, ms_ms_tmp(st), st);
			break;

		default:
			error("invalid rotate condition: %d\n", rcond);
			exit(EXIT_FAILURE);
	}

	return;
}
