#include "common.h"

void ms_init(int X, ms_origin_t org, ms_state_t *st)
{
	st->X=X;
	st->Xm2=st->X*2;
	st->Xm2p2=st->Xm2+2;
	st->Ceilings=st->X*st->X;

	if(org==MS_ORIGIN_ZERO){
		/* \sum_{i=0}^{X^2-1}i=\frac{1}{2}X(X^2-1) */
		st->OneLine=st->X*(st->Ceilings-1)/2;
	}else if(org==MS_ORIGIN_ONE){
		/* \sum_{i=1}^{X^2}i=\frac{1}{2}X(X^2+1) */
		st->OneLine=st->X*(st->Ceilings+1)/2;
	}

	st->is_is_ms_init_called=0;
	st->is_is_ms_finalize_called=0;
	st->is_str_to_ms_init_called=0;
	st->is_str_to_ms_finalize_called=0;
	st->is_ms_state_print_info_init_called=0;
	st->is_ms_state_print_info_finalize_called=0;
	st->is_output_ms_init_called=0;
	st->is_output_ms_finalize_called=0;

	is_ms_init(st);
	str_to_ms_init(st);
	ms_state_print_info_init(st);
	output_ms_init(st);
	ms_mem_basics_init(st);

	return;
}

void ms_finalize(ms_state_t *st)
{
	is_ms_finalize(st);
	str_to_ms_finalize(st);
	ms_state_print_info_finalize(st);
	output_ms_finalize(st);
	ms_mem_basics_finalize(st);

	return;
}
