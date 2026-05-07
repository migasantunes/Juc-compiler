#ifndef IO_H
#define IO_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} StrBuf;

void sb_init(StrBuf *sb);
void sb_free(StrBuf *sb);
void sb_append(StrBuf *sb, const char *s);
void sb_appendf(StrBuf *sb, const char *fmt, ...);

#endif

