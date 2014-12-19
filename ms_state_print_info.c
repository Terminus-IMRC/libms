#include "common.h"
#include <stdio.h>

void ms_state_print_info_init(ms_state_t *st)
{
	return;
}

void ms_state_print_info_finalize(ms_state_t *st)
{
	return;
}

void ms_state_print_info(ms_state_t *st)
{
	printf("X: %d\n", st->X);
	printf("Ceilings: %d\n", st->Ceilings);
	printf("OneLine: %d\n", st->OneLine);
	printf("sums: %p\n", st->sums);
	printf("ms: %p\n", st->ms);

	return;
}
