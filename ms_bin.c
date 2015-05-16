#include "common.h"

void ms_bin_init(ms_state_t *st)
{
	int t;

	st->init_and_finalize_counts.bin ++;
	if (st->init_and_finalize_counts.bin != 1)
		return;

	t = st->Ceilings;
	st->bin_elem_size = 0;
	while (t > 0) {
		st->bin_elem_size ++;
		t -= (1 << 8);
	}
	if ((st->org == MS_ORIGIN_ONE) && (t == 0))
		st->bin_elem_size ++;
}

void ms_bin_finalize(ms_state_t *st)
{
	st->init_and_finalize_counts.bin --;
	if (st->init_and_finalize_counts.bin != 0)
		return;
}
