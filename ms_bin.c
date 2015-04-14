#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#define _ISOC99_SOURCE

#include "common.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <errno.h>

void ms_bin_init(ms_state_t *st)
{
	int t;

	if (st->is_ms_bin_init_called)
		return;
	st->is_ms_bin_init_called = !0;

	t = st->Ceilings;
	st->bin_elem_size = 0;
	while (t > 0) {
		st->bin_elem_size++;
		t -= (1 << 8);
	}
	if ((st->org == MS_ORIGIN_ONE) && (t == 0))
		st->bin_elem_size++;

	if (st->bin_elem_size != 1) {
		error("non-1-byte element size is not supported yet\n");
		exit(EXIT_FAILURE);
	}

	st->bin_buf_size = st->Ceilings * st->bin_elem_size;
	if ((st->bin_buf = malloc(st->bin_buf_size)) == NULL) {
		error("failed to alloc bin_buf\n");
		exit(EXIT_FAILURE);
	}
}

void ms_bin_finalize(ms_state_t *st)
{
	if (st->is_ms_bin_finalize_called)
		return;
	st->is_ms_bin_finalize_called = !0;

	free(st->bin_buf);
}

void ms_bin_seq_read_open(const char *filename, ms_bin_seq_read_flag_t flag, ms_bin_seq_read_t *mbp, ms_state_t *st)
{
	struct stat stat_buf;
	int err;

	if (flag) {
		error("unknown bit is specified to flag\n");
		exit(EXIT_FAILURE);
	}

	if ((mbp->fd = open(filename, O_RDONLY | O_LARGEFILE)) == -1) {
		error("open: %s: %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ((err = fstat(mbp->fd, &stat_buf)) == -1) {
		error("fstat: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ((stat_buf.st_size % st->bin_buf_size) != 0) {
		error("incorrect file size\n");
		exit(EXIT_FAILURE);
	}

	mbp->total = stat_buf.st_size / st->bin_buf_size;
	mbp->count = 0;
}

void ms_bin_seq_read_close(ms_bin_seq_read_t *mbp, ms_state_t *st)
{
	int err;

	if ((err = close(mbp->fd)) == -1) {
		error("close: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

ms_bin_ret_t ms_bin_seq_read_next(int *ms, ms_bin_seq_read_t *mbp, ms_state_t *st)
{
	int i;
	int err;

	if (mbp->count == mbp->total) {
		error("full read\n");
		exit(EXIT_FAILURE);
	}

	if ((err = read(mbp->fd, st->bin_buf, st->bin_buf_size)) == -1) {
		error("read: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < st->Ceilings; i++)
		ms[i] = st->bin_buf[i];

	mbp->count++;

	return mbp->count == mbp->total ? MS_BIN_RET_EOF : MS_BIN_RET_NONE;
}

void ms_bin_seq_write_open(const char *filename, ms_bin_seq_write_flag_t flag, ms_bin_seq_write_t *mbp, ms_state_t *st)
{
	int open_flag = 0;

	if (flag & MS_BIN_SEQ_WRITE_FLAG_CREAT) {
		open_flag |= O_CREAT;
		flag ^= MS_BIN_SEQ_WRITE_FLAG_CREAT;
	}
	if (flag & MS_BIN_SEQ_WRITE_FLAG_TRUNC) {
		open_flag |= O_TRUNC;
		flag ^= MS_BIN_SEQ_WRITE_FLAG_TRUNC;
	}

	if (flag) {
		error("unknown bit is specified to flag\n");
		exit(EXIT_FAILURE);
	}

	if ((mbp->fd = open(filename, O_WRONLY | open_flag | O_LARGEFILE, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1) {
		error("open: %s: %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void ms_bin_seq_write_close(ms_bin_seq_write_t *mbp, ms_state_t *st)
{
	int err;

	if ((err = close(mbp->fd)) == -1) {
		error("close: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void ms_bin_seq_write_next(int *ms, ms_bin_seq_write_t *mbp, ms_state_t *st)
{
	int i;
	int err;

	for (i = 0; i < st->Ceilings; i++)
		st->bin_buf[i] = ms[i];

	if ((err = write(mbp->fd, st->bin_buf, st->bin_buf_size)) == -1) {
		error("write: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
