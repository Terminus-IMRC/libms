#ifndef _LIBMS_COMMON_H_
#define _LIBMS_COMMON_H_

#include "libms.h"
#include "error.h"

	void ms_mem_basics_init(ms_state_t *st);
	void ms_mem_basics_finalize(ms_state_t *st);
	void ms_rotate_init(ms_state_t *st);
	void ms_rotate_finalize(ms_state_t *st);
	void ms_bin_init(ms_state_t *st);
	void ms_bin_finalize(ms_state_t *st);
	void ms_conv_init(ms_state_t *st);
	void ms_conv_finalize(ms_state_t *st);
	void ms_utils_init(ms_state_t *st);
	void ms_utils_finalize(ms_state_t *st);
	void ms_counters_init(ms_state_t *stp);
	void ms_counters_finalize(ms_state_t *stp);

#define ms_sums(stp) ((((stp))->sums))
#define ms_ms_tmp(stp) ((((stp))->ms_tmp))

#endif /* _LIBMS_COMMON_H_ */
