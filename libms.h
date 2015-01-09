#ifndef __LIBMS_H_INCLUDED__
#define __LIBMS_H_INCLUDED__

#include <stdio.h>

	typedef struct{
		int X, Ceilings, OneLine;
		int Xm2, Xm2p2;
		int *sums;
		int *ms;
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

#endif /* __LIBMS_H_INCLUDED__ */
