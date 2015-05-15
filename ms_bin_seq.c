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

void ms_bin_seq_read_open(const char *filename, ms_bin_seq_read_flag_t flag, ms_bin_seq_read_t *mbp, ms_state_t *st)
{
	struct stat stat_buf;
	int err;

	if (flag & MS_BIN_SEQ_READ_FLAG_HOST_WIDTH) {
		mbp->elem_size = sizeof(int);
		flag ^= MS_BIN_SEQ_READ_FLAG_HOST_WIDTH;
	} else
		mbp->elem_size = st->bin_elem_size;

	if (flag) {
		error("unknown bit is specified to flag\n");
		exit(EXIT_FAILURE);
	}

	if ((mbp->fd = open(filename, O_RDONLY)) == -1) {
		error("open: %s: %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}

	switch (mbp->elem_size) {
		case 1:
			mbp->bin_conv_b2h = ms_conv_bin8_to_host;
			break;
		case 2:
			mbp->bin_conv_b2h = ms_conv_bin16_to_host;
			break;
		case 4:
			mbp->bin_conv_b2h = ms_conv_bin32_to_host;
			break;
		case 8:
			mbp->bin_conv_b2h = ms_conv_bin64_to_host;
			break;
		default:
			error("unsupported or invalid elem_size: %d\n", mbp->elem_size);
			exit(EXIT_FAILURE);
	}

	mbp->buf.addr = NULL;
	ms_bin_seq_read_set_buffer(1, mbp, st);

	if ((err = fstat(mbp->fd, &stat_buf)) == -1) {
		error("fstat: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ((stat_buf.st_size % mbp->buf.size) != 0) {
		error("incorrect file size\n");
		exit(EXIT_FAILURE);
	}

	mbp->total = stat_buf.st_size / mbp->buf.size;
	mbp->count = 0;
}

void ms_bin_seq_read_close(ms_bin_seq_read_t *mbp, ms_state_t *st)
{
	int err;

	free(mbp->buf.addr);

	if ((err = close(mbp->fd)) == -1) {
		error("close: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void ms_bin_seq_read_set_buffer(size_t nmemb, ms_bin_seq_read_t *mbp, ms_state_t *st)
{
	if (nmemb <= 0) {
		error("nmemb must be greater than 0\n");
		exit(EXIT_FAILURE);
	}

	if (mbp->buf.addr != NULL)
		free(mbp->buf.addr);

	mbp->buf.nmemb = nmemb;
	mbp->buf.size = st->Ceilings * mbp->elem_size;
	mbp->buf.bufsize = mbp->buf.nmemb * mbp->buf.size;
	if ((mbp->buf.addr = malloc(mbp->buf.bufsize)) == NULL) {
		error("failed to alloc bin buffer\n");
		exit(EXIT_FAILURE);
	}
	mbp->buf.read = mbp->buf.nmemb;
}

ms_bin_ret_t ms_bin_seq_read_next(int *ms, ms_bin_seq_read_t *mbp, ms_state_t *st)
{
	int err;

	if (mbp->count == mbp->total) {
		error("full read\n");
		exit(EXIT_FAILURE);
	}

	if (mbp->buf.read == mbp->buf.nmemb) {
		if ((err = read(mbp->fd, mbp->buf.addr, mbp->buf.bufsize)) == -1) {
			error("read: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		mbp->buf.read = 0;
	}

	mbp->bin_conv_b2h(ms, ((uint8_t*) mbp->buf.addr) + mbp->buf.read * mbp->buf.size, st);

	mbp->count++;
	mbp->buf.read++;

	return mbp->count == mbp->total ? MS_BIN_RET_EOF : MS_BIN_RET_NONE;
}

void ms_bin_seq_read_seek(off_t count, int whence, ms_bin_seq_read_t *mbp, ms_state_t *st)
{
	int err;

	switch (whence) {
		case SEEK_SET:
			if (count >= mbp->total) {
				error("too big offset count\n");
				exit(EXIT_FAILURE);
			}
			mbp->count = count;
			break;
		case SEEK_CUR:
			if ((mbp->count += count) >= mbp->total) {
				error("too big offset count\n");
				exit(EXIT_FAILURE);
			}
			break;
		case SEEK_END:
			if ((mbp->count = mbp->total - 1 + count) >= mbp->total) {
				error("too big offset count\n");
				exit(EXIT_FAILURE);
			}
			break;
		default:
			error("unknown value for whence: %d\n", whence);
			exit(EXIT_FAILURE);
	}

	if ((err = lseek(mbp->fd, count * mbp->buf.size, whence)) == -1) {
		error("lseek: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	mbp->buf.read = mbp->buf.nmemb;
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
	if (flag & MS_BIN_SEQ_WRITE_FLAG_HOST_WIDTH) {
		mbp->elem_size = sizeof(int);
		flag ^= MS_BIN_SEQ_WRITE_FLAG_HOST_WIDTH;
	} else
		mbp->elem_size = st->bin_elem_size;

	if (flag) {
		error("unknown bit is specified to flag\n");
		exit(EXIT_FAILURE);
	}

	if ((mbp->fd = open(filename, O_WRONLY | open_flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1) {
		error("open: %s: %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}

	switch (mbp->elem_size) {
		case 1:
			mbp->bin_conv_h2b = ms_conv_host_to_bin8;
			break;
		case 2:
			mbp->bin_conv_h2b = ms_conv_host_to_bin16;
			break;
		case 4:
			mbp->bin_conv_h2b = ms_conv_host_to_bin32;
			break;
		case 8:
			mbp->bin_conv_h2b = ms_conv_host_to_bin64;
			break;
		default:
			error("unsupported or invalid elem_size: %d\n", mbp->elem_size);
			exit(EXIT_FAILURE);
	}

	mbp->buf.size = st->Ceilings * mbp->elem_size;
	if ((mbp->buf.addr = malloc(mbp->buf.size)) == NULL) {
		error("failed to alloc bin buffer\n");
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

	free(mbp->buf.addr);
}

void ms_bin_seq_write_next(int *ms, ms_bin_seq_write_t *mbp, ms_state_t *st)
{
	int err;

	mbp->bin_conv_h2b(mbp->buf.addr, ms, st);

	if ((err = write(mbp->fd, mbp->buf.addr, mbp->buf.size)) == -1) {
		error("write: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
