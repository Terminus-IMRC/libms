#ifndef _LIBMS_COMMON_H_
#define _LIBMS_COMMON_H_

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
	void ms_rotate_init(ms_state_t *st);
	void ms_rotate_finalize(ms_state_t *st);

#define ms_sums(stp) ((((stp))->sums))
#define ms_ms_tmp(stp) ((((stp))->ms_tmp))

#endif /* _LIBMS_COMMON_H_ */
