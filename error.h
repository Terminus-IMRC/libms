#ifndef __ERROR_H_INCLUDED__
#define __ERROR_H_INCLUDED__

#include <stdio.h>

#define error(str, ...) fprintf(stderr, "%s:%d: error: "str, __FILE__, __LINE__, ## __VA_ARGS__)

#endif /* __ERROR_H_INCLUDED__ */
