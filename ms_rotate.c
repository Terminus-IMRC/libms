#include "common.h"
#include <stdlib.h>

void ms_rotate_init(ms_state_t *st)
{
	st->init_and_finalize_counts.rotate ++;
	if (st->init_and_finalize_counts.rotate != 1)
		return;

	ms_mem_basics_init(st);

	return;
}

void ms_rotate_finalize(ms_state_t *st)
{
	st->init_and_finalize_counts.rotate --;
	if (st->init_and_finalize_counts.rotate != 0)
		return;

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
			for (i = 0; i < ms_X(st); i ++)
				for (j = 0; j < ms_X(st); j ++)
					ms_ms_tmp(st)[j * ms_X(st) + (ms_Xs1(st) - i)] = ms[i * ms_X(st) + j];
			ms_cp(ms, ms_ms_tmp(st), st);
			break;

		case MS_ROTATE_2R:
		case MS_ROTATE_2L:
			for (i = 0; i < ms_X(st); i ++)
				for (j = 0; j < ms_X(st); j ++)
					ms_ms_tmp(st)[(ms_Xs1(st) - i) * ms_X(st) + (ms_Xs1(st) - j)] = ms[i * ms_X(st) + j];
			ms_cp(ms, ms_ms_tmp(st), st);
			break;

		case MS_ROTATE_L:
		case MS_ROTATE_3R:
			for (i = 0; i < ms_X(st); i ++)
				for (j = 0; j < ms_X(st); j ++)
					ms_ms_tmp(st)[(ms_Xs1(st) - j) * ms_X(st) + i] = ms[i * ms_X(st) + j];
			ms_cp(ms, ms_ms_tmp(st), st);
			break;

		case MS_ROTATE_REV:
			for (i = 0; i < ms_X(st); i ++)
				for (j = 0; j < ms_X(st); j ++)
					ms_ms_tmp(st)[i * ms_X(st) + (ms_Xs1(st) - j)] = ms[i * ms_X(st) + j];
			ms_cp(ms, ms_ms_tmp(st), st);
			break;

		default:
			error("invalid rotate condition: %d\n", rcond);
			exit(EXIT_FAILURE);
	}

	return;
}
