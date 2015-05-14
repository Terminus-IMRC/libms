#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ms_utils_init(ms_state_t *stp)
{
	if (stp->is_ms_utils_init_called)
		return;
	stp->is_ms_utils_init_called = !0;

	/* is_ms */
	ms_sums(stp)=malloc(ms_Xm2p2(stp)*sizeof(int));
	if(ms_sums(stp)==NULL){
		error("failed to malloc sums\n");
		exit(EXIT_FAILURE);
	}

	return;
}

void ms_utils_finalize(ms_state_t *stp)
{
	if (stp->is_ms_utils_finalize_called)
		return;
	stp->is_ms_utils_finalize_called = !0;

	/* is_ms */
	free(ms_sums(stp));

	return;
}

ms_bool_t is_ms(int *ms, ms_state_t *st)
{
	int i, j;

	memset(ms_sums(st), 0, ms_Xm2p2(st)*sizeof(int));
	for(i=0; i<ms_X(st); i++){
		for(j=0; j<ms_X(st); j++){
			ms_sums(st)[j]+=ms[j*ms_X(st)+i];
			ms_sums(st)[1*ms_X(st)+j]+=ms[j+i*ms_X(st)];
		}
		ms_sums(st)[ms_Xm2(st)+0]+=ms[i+i*ms_X(st)];
		ms_sums(st)[ms_Xm2(st)+1]+=ms[(ms_X(st)-1-i)+i*ms_X(st)];
	}

	for(i=0; i<ms_Xm2p2(st); i++)
		if(ms_sums(st)[i]!=ms_OneLine(st))
			return MS_FALSE;
	return MS_TRUE;
}

void str_to_ms(int *ms, char *s, ms_state_t *st)
{
	int i;

	for(i=0; i<ms_Ceilings(st); i++)
		ms[i]=(int)strtol(s, &s, 10);
	
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

void output_ms(int *ms, FILE *fp, ms_state_t *st)
{
	int i;

	for(i=0; i<ms_Ceilings(st); i++)
		fprintf(fp, "%d%c", ms[i], i!=ms_Ceilings(st)-1?' ':'\n');

	return;
}
