#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ms_utils_init(ms_state_t *stp)
{
	stp->init_and_finalize_counts.utils ++;
	if (stp->init_and_finalize_counts.utils != 1)
		return;

	/* is_ms */
	ms_sums(stp) = malloc(ms_Xm2p2(stp) * sizeof(int));
	if (ms_sums(stp) == NULL) {
		error("failed to malloc sums\n");
		exit(EXIT_FAILURE);
	}

	return;
}

void ms_utils_finalize(ms_state_t *stp)
{
	stp->init_and_finalize_counts.utils --;
	if (stp->init_and_finalize_counts.utils != 0)
		return;

	/* is_ms */
	free(ms_sums(stp));

	return;
}

ms_bool_t is_ms(int *ms, ms_state_t *st)
{
	int i, j;

	memset(ms_sums(st), 0, ms_Xm2p2(st) * sizeof(int));
	for (i = 0; i < ms_X(st); i ++) {
		for (j = 0; j < ms_X(st); j ++){
			ms_sums(st)[j] += ms[j * ms_X(st) + i];
			ms_sums(st)[ms_X(st) + j] += ms[j + i * ms_X(st)];
		}
		ms_sums(st)[ms_Xm2(st) + 0] += ms[i + i * ms_X(st)];
		ms_sums(st)[ms_Xm2(st) + 1] += ms[(ms_X(st) - 1 - i) + i * ms_X(st)];
	}

	for (i = 0; i < ms_Xm2p2(st); i ++)
		if (ms_sums(st)[i] != ms_OneLine(st))
			return MS_FALSE;
	return MS_TRUE;
}

void str_to_ms(int *ms, char *s, ms_state_t *st)
{
	int i;

	for (i = 0; i < ms_Ceilings(st); i ++)
		ms[i] = (int) strtol(s, &s, 10);
	
	return;
}

void ms_to_str(char *s, const int *ms, ms_state_t *st)
{
	int i;
	char buf[0x100];

	s[0] = '\0';

	for (i = 0; i < ms_Ceilings(st); i ++) {
		sprintf(buf, "%d", ms[i]);
		strcat(s, buf);
		if (i != ms_Ceilings(st) - 1)
			strcat(s, " ");
	}
}

void ms_state_print_info(ms_state_t *st)
{
	printf("X: %d\n", ms_X(st));
	printf("Ceilings: %d\n", ms_Ceilings(st));
	printf("OneLine: %d\n", ms_OneLine(st));
	printf("sums: %p\n", ms_sums(st));

	return;
}

void output_ms(int *ms, FILE *fp, ms_state_t *st)
{
	int i;

	for (i = 0; i < ms_Ceilings(st); i ++)
		fprintf(fp, "%d%c", ms[i], i != ms_Ceilings(st) - 1 ? ' ' : '\n');

	return;
}

int ms_compare(const int *ms1, const int *ms2, ms_state_t *stp)
{
	int i;

	for (i = 0; i < ms_Ceilings(stp); i++) {
		int d = ms1[i] - ms2[i];
		if (d != 0)
			return d;
	}
	return 0;
}
