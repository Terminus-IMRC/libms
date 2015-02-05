#include "common.h"
#include <stdlib.h>
#include <string.h>

void is_ms_init(ms_state_t *st)
{
	if(st->is_is_ms_init_called)
		return;
	st->is_is_ms_init_called=!0;

	ms_sums(st)=malloc(ms_Xm2p2(st)*sizeof(int));
	if(ms_sums(st)==NULL){
		error("failed to malloc sums\n");
		exit(EXIT_FAILURE);
	}

	return;
}

void is_ms_finalize(ms_state_t *st)
{
	if(st->is_is_ms_finalize_called)
		return;
	st->is_is_ms_finalize_called=!0;

	free(ms_sums(st));

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
