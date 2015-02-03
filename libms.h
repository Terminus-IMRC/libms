#ifndef __LIBMS_H_INCLUDED__
#define __LIBMS_H_INCLUDED__

#include <stdio.h>
#include <string.h>

	typedef struct{
		int X, Ceilings, OneLine;
		int Xm2, Xm2p2;
		int *sums;
		int *ms;
		int *move_ms;
	} ms_state_t;

	typedef enum{
		MS_ORIGIN_ZERO, MS_ORIGIN_ONE
	} ms_origin_t;

	typedef enum{
		MS_FALSE, MS_TRUE
	} ms_bool_t;

	void ms_init(int X, ms_origin_t org, ms_state_t *st);
	void ms_finalize(ms_state_t *st);
	ms_bool_t is_ms(int *ms, ms_state_t *st);
	int* str_to_ms(char *s, ms_state_t *st);
	void ms_state_print_info(ms_state_t *st);
	void output_ms(int *ms, FILE *fp, ms_state_t *st);
	int* ms_alloc(ms_state_t *st);
	void ms_free(int *ms, ms_state_t *st);
	void ms_move(int *ms_dst, int *ms_src, ms_state_t *st);

#define ms_X(stp) ((((stp))->X))
#define ms_Ceilings(stp) ((((stp))->Ceilings))
#define ms_OneLine(stp) ((((stp))->OneLine))
#define ms_Xm2(stp) ((((stp))->Xm2))
#define ms_Xm2p2(stp) ((((stp))->Xm2p2))

#define ms_cp(ms_dst, ms_src, stp) (((void)memcpy(((ms_dst)), ((ms_src)), ((stp))->Ceilings*sizeof(int))))

#endif /* __LIBMS_H_INCLUDED__ */
