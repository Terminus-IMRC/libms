#include "common.h"
#include <stdlib.h>
#include <string.h>

void is_ms_init(ms_state_t *st)
{
	st->sums=malloc(st->Xm2p2*sizeof(int));
	if(st->sums==NULL){
		error("failed to malloc sums\n");
		exit(EXIT_FAILURE);
	}

	return;
}

void is_ms_finalize(ms_state_t *st)
{
	free(st->sums);

	return;
}

ms_bool_t is_ms(int *ms, ms_state_t *st)
{
	int i, j;

	memset(st->sums, 0, st->Xm2p2*sizeof(int));
	for(i=0; i<st->X; i++){
		for(j=0; j<st->X; j++){
			st->sums[j]+=ms[j*st->X+i];
			st->sums[1*st->X+j]+=ms[j+i*st->X];
		}
		st->sums[st->Xm2+0]+=ms[i+i*st->X];
		st->sums[st->Xm2+1]+=ms[(st->X-1-i)+i*st->X];
	}

	for(i=0; i<st->Xm2p2; i++)
		if(st->sums[i]!=st->OneLine)
			return MS_FALSE;
	return MS_TRUE;
}
