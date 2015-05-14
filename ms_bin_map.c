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

void* ms_bin_map(const char *filename, ms_bin_map_flag_t flag, ms_bin_map_t *mbp, ms_state_t *st)
{
	int fd;
	int map_prot = PROT_NONE;
	struct stat stat_buf;
	int err;

	if (flag & MS_BIN_MAP_FLAG_READ) {
		map_prot |= PROT_READ;
		flag ^= MS_BIN_MAP_FLAG_READ;
	}
	if (flag & MS_BIN_MAP_FLAG_WRITE) {
		map_prot |= PROT_WRITE;
		flag ^= MS_BIN_MAP_FLAG_WRITE;
	}

	if (flag) {
		error("unknown bit is specified to flag\n");
		exit(EXIT_FAILURE);
	}

	if ((fd = open(filename, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1) {
		error("open: %s: %s\n", filename, strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ((err = fstat(fd, &stat_buf)) == -1) {
		error("fstat: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	mbp->size = stat_buf.st_size;

	if ((mbp->addr = mmap(NULL, mbp->size, map_prot, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		error("mmap: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if ((err = close(fd)) == -1) {
		error("close: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return mbp->addr;
}

void ms_bin_unmap(ms_bin_map_t *mbp, ms_state_t *st)
{
	int err;

	if ((err = munmap(mbp->addr, mbp->size)) == -1) {
		error("munmap: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void ms_bin_map_sync(ms_bin_map_t *mbp, ms_state_t *st)
{
	int err;

	if ((err = msync(mbp->addr, mbp->size, MS_SYNC | MS_INVALIDATE)) == -1) {
		error("msync: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
