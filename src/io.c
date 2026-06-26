#include "io.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

static void sb_ensure(StrBuf *sb, size_t extra) {
    if (sb->cap == 0) {
        sb->cap = 128;
        sb->data = (char *)malloc(sb->cap);
        sb->len = 0;
        sb->data[0] = '\0';
    }
    while (sb->len + extra + 1 > sb->cap) {
        sb->cap *= 2;
        sb->data = (char *)realloc(sb->data, sb->cap);
    }
}

void sb_init(StrBuf *sb) {
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}

void sb_free(StrBuf *sb) {
    if (sb->data) free(sb->data);
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}

void sb_append(StrBuf *sb, const char *s) {
    if (s == NULL) return;
    size_t n = strlen(s);
    sb_ensure(sb, n);
    memcpy(sb->data + sb->len, s, n);
    sb->len += n;
    sb->data[sb->len] = '\0';
}

void sb_appendf(StrBuf *sb, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char tmp[1024];
    int n = vsnprintf(tmp, sizeof(tmp), fmt, ap);
    va_end(ap);

    if (n < 0) return;
    if ((size_t)n < sizeof(tmp)) {
        sb_append(sb, tmp);
        return;
    }

    char *buf = (char *)malloc((size_t)n + 1);
    va_start(ap, fmt);
    vsnprintf(buf, (size_t)n + 1, fmt, ap);
    va_end(ap);
    sb_append(sb, buf);
    free(buf);
}

