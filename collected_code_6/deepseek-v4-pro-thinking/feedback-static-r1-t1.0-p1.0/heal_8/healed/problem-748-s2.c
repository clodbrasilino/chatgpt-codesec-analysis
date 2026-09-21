#include <ctype.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1048576

static char *read_line(void)
{
    size_t cap = 128;
    size_t len = 0;
    char *buf = malloc(cap);
    if (!buf)
        return NULL;
    buf[0] = '\0';
    while (1) {
        if (fgets(buf + len, cap - len, stdin) == NULL) {
            if (len == 0) {
                free(buf);
                return NULL;
            }
            break;
        }
        size_t chunk_len = strnlen(buf + len, cap - len);
        len += chunk_len;
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
            len--;
            break;
        }
        if (cap > SIZE_MAX / 2) {
            free(buf);
            return NULL;
        }
        cap *= 2;
        char *tmp = realloc(buf, cap);
        if (!tmp) {
            free(buf);
            return NULL;
        }
        buf = tmp;
    }
    char *tmp = realloc(buf, len + 1);
    if (tmp)
        buf = tmp;
    return buf;
}

static int safe_copy(char *dst, size_t dst_size, size_t *pos,
                     const char *src, size_t n)
{
    if (*pos + n >= dst_size)
        return 0;
    for (size_t i = 0; i < n; i++)
        dst[(*pos)++] = src[i];
    return 1;
}

char *insert_spaces(const char *str)
{
    regex_t regex;
    char *output = NULL;
    size_t max_len, pos = 0, offset = 0;
    size_t total_len;
    int ret;

    if (!str)
        return NULL;

    total_len = strnlen(str, MAX_INPUT_LENGTH);
    if (total_len >= MAX_INPUT_LENGTH)
        return NULL;
    if (total_len > (SIZE_MAX - 1) / 2) {
        return NULL;
    }
    max_len = total_len * 2 + 1;

    ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0)
        return NULL;

    output = malloc(max_len);
    if (!output) {
        regfree(&regex);
        return NULL;
    }

    while (1) {
        regmatch_t match;
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH)
            break;
        if (ret != 0) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        size_t match_start = offset + match.rm_so;
        size_t match_end   = offset + match.rm_eo;
        size_t seg_len     = match_start - offset;

        if (!safe_copy(output, max_len, &pos, str + offset, seg_len)) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (match_start > 0 && !isspace((unsigned char)str[match_start - 1])) {
            if (pos >= max_len - 1) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            output[pos++] = ' ';
        }

        if (!safe_copy(output, max_len, &pos, str + match_start,
                       match_end - match_start)) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        offset = match_end;
    }

    {
        size_t rem = total_len - offset;
        if (!safe_copy(output, max_len, &pos, str + offset, rem)) {
            free(output);
            regfree(&regex);
            return NULL;
        }
    }

    output[pos] = '\0';
    regfree(&regex);
    return output;
}

int main(void)
{
    char *input = read_line();
    if (!input)
        return 1;

    char *result = insert_spaces(input);
    free(input);

    if (!result) {
        fputs("Error processing string\n", stderr);
        return 1;
    }

    puts(result);
    free(result);
    return 0;
}