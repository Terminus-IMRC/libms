#include "common.h"
#include <stdlib.h>

void ms_counters_init(ms_state_t *stp)
{
	stp->init_and_finalize_counts.counters ++;
	if (stp->init_and_finalize_counts.counters != 1)
		return;
}

void ms_counters_finalize(ms_state_t *stp)
{
	stp->init_and_finalize_counts.counters --;
	if (stp->init_and_finalize_counts.counters != 0)
		return;
}

void ms_counters(ms_counters_t *counters, const int lc, ms_state_t *stp)
{
	if ((lc < 0) || (lc >= ms_Xm2(stp) + 2)) {
		error("lc out-of-range: %d\n", lc);
		exit(EXIT_FAILURE);
	}

	if (lc < ms_X(stp)) {
		/* vert */
		counters->start = lc;
		counters->step = ms_X(stp);
		counters->end = ms_Ceilings(stp);
	} else if (lc < ms_Xm2(stp)) {
		/* horiz */
		counters->start = ms_X(stp) * (lc - ms_X(stp));
		counters->step = 1;
		counters->end = ms_X(stp) * (lc - ms_X(stp) + 1);
	} else if (lc == ms_Xm2(stp)) {
		/* diag 1 */
		counters->start = 0;
		counters->step = ms_X(stp) + 1;
		counters->end = ms_Ceilings(stp);
	} else {
		/* diag 2 */
		counters->start = ms_X(stp) - 1;
		counters->step = ms_X(stp) - 1;
		counters->end = ms_Ceilings(stp) - ms_X(stp) + 1;
	}
}

int MS_LINE_VERT(const int l, ms_state_t *stp)
{
	if ((l < 0) || (l >= ms_X(stp))) {
		error("l out-of-range: %d\n", l);
		exit(EXIT_FAILURE);
	}

	return l;
}

int MS_LINE_HORIZ(const int l, ms_state_t *stp)
{
	if ((l < 0) || (l >= ms_X(stp))) {
		error("l out-of-range: %d\n", l);
		exit(EXIT_FAILURE);
	}

	return l + ms_X(stp);
}

int MS_LINE_DIAG(const int l, ms_state_t *stp)
{
	if ((l < 0) || (l >= 2)) {
		error("l out-of-range: %d\n", l);
		exit(EXIT_FAILURE);
	}

	return l + ms_Xm2(stp);
}
