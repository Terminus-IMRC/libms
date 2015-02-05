#include "common.h"
#include <stdio.h>

void ms_state_print_info_init(ms_state_t *st)
{
	if(st->is_ms_state_print_info_init_called)
		return;
	st->is_ms_state_print_info_init_called=!0;

	return;
}

void ms_state_print_info_finalize(ms_state_t *st)
{
	if(st->is_ms_state_print_info_finalize_called)
		return;
	st->is_ms_state_print_info_finalize_called=!0;

	return;
}

void ms_state_print_info(ms_state_t *st)
{
	printf("X: %d\n", ms_X(st));
	printf("Ceilings: %d\n", ms_Ceilings(st));
	printf("OneLine: %d\n", ms_OneLine(st));
	printf("sums: %p\n", ms_sums(st));

	return;
}
