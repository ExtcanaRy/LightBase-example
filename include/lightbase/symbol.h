#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int lb_load_symbols(const char *in_filename);
void *lb_sym_find(const char *in_sym);
void lb_sym_free();

#ifdef __cplusplus
}
#endif

#define SCALL(sym, func_proto, ...) \
	((func_proto)lb_sym_find(sym))(__VA_ARGS__)

#define ACALL(addr, func_proto, ...) \
	((func_proto)addr)(__VA_ARGS__)
