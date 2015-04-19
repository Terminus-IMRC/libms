#ifndef _LIBMS_H_
#define _LIBMS_H_

#include <stdio.h>
#include <string.h>
#include <stdint.h>

	typedef enum{
		MS_ORIGIN_ZERO, MS_ORIGIN_ONE
	} ms_origin_t;

	typedef struct ms_state{
		int X, Ceilings, OneLine;
		int Xm2, Xm2p2, Xs1;
		ms_origin_t org;
		int bin_elem_size;
		int *sums;
		int *ms_tmp;

		_Bool is_is_ms_init_called, is_is_ms_finalize_called;
		_Bool is_str_to_ms_init_called, is_str_to_ms_finalize_called;
		_Bool is_ms_state_print_info_init_called, is_ms_state_print_info_finalize_called;
		_Bool is_output_ms_init_called, is_output_ms_finalize_called;
		_Bool is_ms_mem_basics_init_called, is_ms_mem_basics_finalize_called;
		_Bool is_ms_rotate_init_called, is_ms_rotate_finalize_called;
		_Bool is_ms_bin_init_called, is_ms_bin_finalize_called;
		_Bool is_ms_conv_init_called, is_ms_conv_finalize_called;
	} ms_state_t;

	typedef enum{
		MS_FALSE, MS_TRUE
	} ms_bool_t;

	typedef enum{
		MS_ROTATE_NOP,
		MS_ROTATE_R, MS_ROTATE_3L,
		MS_ROTATE_2R, MS_ROTATE_2L,
		MS_ROTATE_L, MS_ROTATE_3R,
		MS_ROTATE_REV
	} ms_rotate_t;

	struct bin_buf {
		void *addr;
		int size;
	};

	typedef struct {
		int fd;
		int count, total;
		int elem_size;
		void (*bin_conv_b2h)(int*, void*, ms_state_t*);
		struct bin_buf buf;
	} ms_bin_seq_read_t;

	typedef enum {
		MS_BIN_SEQ_READ_FLAG_NONE = 0x0,
		MS_BIN_SEQ_READ_FLAG_HOST_WIDTH = 0x1,
	} ms_bin_seq_read_flag_t;

	typedef struct {
		int fd;
		int elem_size;
		void (*bin_conv_h2b)(void*, int*, ms_state_t*);
		struct bin_buf buf;
	} ms_bin_seq_write_t;

	typedef enum {
		MS_BIN_SEQ_WRITE_FLAG_NONE = 0x0,
		MS_BIN_SEQ_WRITE_FLAG_CREAT = 0x1,
		MS_BIN_SEQ_WRITE_FLAG_TRUNC = 0x2,
		MS_BIN_SEQ_WRITE_FLAG_HOST_WIDTH = 0x4,
	} ms_bin_seq_write_flag_t;

	typedef struct {
		void *addr;
		size_t size;
	} ms_bin_map_t;

	typedef enum {
		MS_BIN_MAP_FLAG_NONE = 0x0,
		MS_BIN_MAP_FLAG_READ = 0x1,
		MS_BIN_MAP_FLAG_WRITE = 0x2,
	} ms_bin_map_flag_t;

	typedef enum {
		MS_BIN_RET_NONE,
		MS_BIN_RET_EOF,
	} ms_bin_ret_t;

	void ms_init(int X, ms_origin_t org, ms_state_t *st);
	void ms_finalize(ms_state_t *st);
	ms_bool_t is_ms(int *ms, ms_state_t *st);
	void str_to_ms(int *ms, char *s, ms_state_t *st);
	void ms_state_print_info(ms_state_t *st);
	void output_ms(int *ms, FILE *fp, ms_state_t *st);
	int* ms_alloc(ms_state_t *st);
	void ms_free(int *ms, ms_state_t *st);
	void ms_move(int *ms_dst, int *ms_src, ms_state_t *st);
	void ms_subst(int *ms, ms_state_t *st, ...);
	void ms_rotate(int *ms, ms_rotate_t rcond, ms_state_t *st);
	void ms_bin_seq_read_open(const char *filename, ms_bin_seq_read_flag_t flag, ms_bin_seq_read_t *mbp, ms_state_t *st);
	void ms_bin_seq_read_close(ms_bin_seq_read_t *mbp, ms_state_t *st);
	ms_bin_ret_t ms_bin_seq_read_next(int *ms, ms_bin_seq_read_t *mbp, ms_state_t *st);
	void ms_bin_seq_read_seek(int count, int whence, ms_bin_seq_read_t *mbp, ms_state_t *st);
	void ms_bin_seq_write_open(const char *filename, ms_bin_seq_write_flag_t flag, ms_bin_seq_write_t *mbp, ms_state_t *st);
	void ms_bin_seq_write_close(ms_bin_seq_write_t *mbp, ms_state_t *st);
	void ms_bin_seq_write_next(int *ms, ms_bin_seq_write_t *mbp, ms_state_t *st);
	void ms_conv_host_to_bin8(void *dst, int *src, ms_state_t *st);
	void ms_conv_bin8_to_host(int *dst, void *src, ms_state_t *st);
	void ms_conv_host_to_bin16(void *dst, int *src, ms_state_t *st);
	void ms_conv_bin16_to_host(int *dst, void *src, ms_state_t *st);
	void ms_conv_host_to_bin32(void *dst, int *src, ms_state_t *st);
	void ms_conv_bin32_to_host(int *dst, void *src, ms_state_t *st);
	void ms_conv_host_to_bin64(void *dst, int *src, ms_state_t *st);
	void ms_conv_bin64_to_host(int *dst, void *src, ms_state_t *st);
	void* ms_bin_map(const char *filename, ms_bin_map_flag_t flag, ms_bin_map_t *mbp, ms_state_t *st);
	void ms_bin_unmap(ms_bin_map_t *mbp, ms_state_t *st);
	void ms_bin_map_sync(ms_bin_map_t *mbp, ms_state_t *st);

#define ms_X(stp) ((((stp))->X))
#define ms_Ceilings(stp) ((((stp))->Ceilings))
#define ms_OneLine(stp) ((((stp))->OneLine))
#define ms_Xm2(stp) ((((stp))->Xm2))
#define ms_Xm2p2(stp) ((((stp))->Xm2p2))
#define ms_Xs1(stp) ((((stp))->Xs1))

#define ms_cp(ms_dst, ms_src, stp) (((void)memcpy(((ms_dst)), ((ms_src)), ms_Ceilings((stp))*sizeof(int))))

#endif /* _LIBMS_H_ */
