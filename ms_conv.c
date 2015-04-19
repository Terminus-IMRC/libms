#include "libms.h"
#include <stdint.h>

void ms_conv_init(ms_state_t *st)
{
	if (st->is_ms_conv_init_called)
		return;
	st->is_ms_conv_init_called = !0;
}

void ms_conv_finalize(ms_state_t *st)
{
	if (st->is_ms_conv_finalize_called)
		return;
	st->is_ms_conv_finalize_called = !0;
}

void ms_conv_host_to_bin8(void *dst, int *src, ms_state_t *st)
{
	int i;
	uint8_t *p = dst;

	for (i = 0; i < st->Ceilings; i++)
		p[i] = src[i];
}

void ms_conv_bin8_to_host(int *dst, void *src, ms_state_t *st)
{
	int i;
	uint8_t *p = src;

	for (i = 0; i < st->Ceilings; i++)
		dst[i] = p[i];
}

void ms_conv_host_to_bin16(void *dst, int *src, ms_state_t *st)
{
	int i;
	uint16_t *p = dst;

	for (i = 0; i < st->Ceilings; i++)
		p[i] = src[i];
}

void ms_conv_bin16_to_host(int *dst, void *src, ms_state_t *st)
{
	int i;
	uint16_t *p = src;

	for (i = 0; i < st->Ceilings; i++)
		dst[i] = p[i];
}

void ms_conv_host_to_bin32(void *dst, int *src, ms_state_t *st)
{
	int i;
	uint32_t *p = dst;

	for (i = 0; i < st->Ceilings; i++)
		p[i] = src[i];
}

void ms_conv_bin32_to_host(int *dst, void *src, ms_state_t *st)
{
	int i;
	uint32_t *p = src;

	for (i = 0; i < st->Ceilings; i++)
		dst[i] = p[i];
}

void ms_conv_host_to_bin64(void *dst, int *src, ms_state_t *st)
{
	int i;
	uint64_t *p = dst;

	for (i = 0; i < st->Ceilings; i++)
		p[i] = src[i];
}

void ms_conv_bin64_to_host(int *dst, void *src, ms_state_t *st)
{
	int i;
	uint64_t *p = src;

	for (i = 0; i < st->Ceilings; i++)
		dst[i] = p[i];
}

void ms_conv_host_to_host(int *dst, int *src, ms_state_t *st)
{
	ms_cp(dst, src, st);
}
