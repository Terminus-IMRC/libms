#ifndef __COMMON_H_INCLUDED__
#define __COMMON_H_INCLUDED__

#include "libms.h"
#include "error.h"

	void is_ms_init(ms_state_t *st);
	void is_ms_finalize(ms_state_t *st);
	void str_to_ms_init(ms_state_t *st);
	void str_to_ms_finalize(ms_state_t *st);
	void ms_state_print_info_init(ms_state_t *st);
	void ms_state_print_info_finalize(ms_state_t *st);
	void output_ms_init(ms_state_t *st);
	void output_ms_finalize(ms_state_t *st);
	void ms_mem_basics_init(ms_state_t *st);
	void ms_mem_basics_finalize(ms_state_t *st);

#endif /* __COMMON_H_INCLUDED__ */
