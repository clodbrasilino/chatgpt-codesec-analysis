#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void reverse_range(char *begin, char *end)
{
    while (begin < end) {
        char tmp = *begin;
        *begin = *end;
        *end = tmp;
        ++begin;
        --end;
    }
}

char *reverse_words(char *str, size_t len)
{
    if (str == NULL || len == 0) {
        return str;
    }
    reverse_range(str, str + len - 1);
    char *p = str;
    char *end = str + len;
    while (p < end) {
        if (isspace((unsigned char)*p)) {
            ++p;
        } else {
            char *start = p;
            while (p < end && !isspace((unsigned char)*p)) {
                ++p;
            }
            reverse_range(start, p - 1);
        }
    }
    return str;
}

static char *read_line(FILE *stream, size_t *out_len)
{
    size_t size = 128;
    size_t total = 0;
    char *buffer = malloc(size);
    if (buffer == NULL) {
        if (out_len) *out_len = 0;
        return NULL;
    }
    for (;;) {
        if (size - total <= 1) {
            if (size > SIZE_MAX / 2) {
                free(buffer);
                if (out_len) *out_len = 0;
                return NULL;
            }
            size *= 2;
            char *tmp = realloc(buffer, size);
            if (tmp == NULL) {
                free(buffer);
                if (out_len) *out_len = 0;
                return NULL;
            }
            buffer = tmp;
        }
        if (fgets(buffer + total, (int)(size - total), stream) == NULL) {
            if (total == 0) {
                free(buffer);
                if (out_len) *out_len = 0;
                return NULL;
            }
            break;
        }
        size_t n = strlen(buffer + total);
        total += n;
        if (total > 0 && buffer[total - 1] == '\n') {
            buffer[total - 1] = '\0';
            --total;
            break;
        }
    }
    if (out_len) *out_len = total;
    return buffer;
}

int main(void)
{
    char *line;
    size_t len;
    while ((line = read_line(stdin, &len)) != NULL) {
        if (len > 0) {
            reverse_words(line, len);
            puts(line);
        }
        free(line);
    }
    return 0;
}