#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <stdint.h>

#define NMATCH 10
#define MAX_INPUT_LENGTH ((size_t)64 * 1024 * 1024)

static size_t bounded_strlen(const char *s, size_t maxlen)
{
    size_t n = 0;

    while (n < maxlen && s[n] != '\0') {
        n++;
    }
    return n;
}

static int checked_copy(char *dst, size_t dst_capacity, size_t *dst_offset,
                        const char *src, size_t src_len)
{
    size_t i;

    if (dst == NULL || dst_offset == NULL) {
        return -1;
    }
    if (src_len > 0 && src == NULL) {
        return -1;
    }
    if (*dst_offset > dst_capacity || src_len > dst_capacity - *dst_offset) {
        return -1;
    }
    for (i = 0; i < src_len; i++) {
        dst[*dst_offset + i] = src[i];
    }
    *dst_offset += src_len;
    return 0;
}

static int replacement_length(const char *replacement,
                              const regmatch_t m[], size_t nmatch,
                              size_t *result)
{
    size_t len = 0;
    size_t i;

    if (replacement == NULL || m == NULL || result == NULL) {
        return -1;
    }
    for (i = 0; replacement[i] != '\0'; i++) {
        if (replacement[i] == '\\' &&
            replacement[i + 1] >= '0' && replacement[i + 1] <= '9') {
            size_t g = (size_t)(replacement[i + 1] - '0');

            if (g < nmatch && m[g].rm_so >= 0 && m[g].rm_eo >= m[g].rm_so) {
                size_t glen = (size_t)(m[g].rm_eo - m[g].rm_so);

                if (glen > SIZE_MAX - len) {
                    return -1;
                }
                len += glen;
            }
            i++;
        } else {
            if (len == SIZE_MAX) {
                return -1;
            }
            len++;
        }
    }
    *result = len;
    return 0;
}

static int replacement_expand(char *out, size_t *oi, size_t capacity,
                              const char *replacement,
                              const char *str, const regmatch_t m[],
                              size_t nmatch)
{
    size_t i;

    if (out == NULL || oi == NULL || replacement == NULL ||
        str == NULL || m == NULL) {
        return -1;
    }
    for (i = 0; replacement[i] != '\0'; i++) {
        if (replacement[i] == '\\' &&
            replacement[i + 1] >= '0' && replacement[i + 1] <= '9') {
            size_t g = (size_t)(replacement[i + 1] - '0');

            if (g < nmatch && m[g].rm_so >= 0 && m[g].rm_eo >= m[g].rm_so) {
                size_t glen = (size_t)(m[g].rm_eo - m[g].rm_so);

                if (checked_copy(out, capacity, oi,
                                 str + m[g].rm_so, glen) != 0) {
                    return -1;
                }
            }
            i++;
        } else {
            if (*oi >= capacity) {
                return -1;
            }
            out[(*oi)++] = replacement[i];
        }
    }
    return 0;
}

static char *regex_replace_all(const char *input, const char *pattern,
                               const char *replacement)
{
    regex_t re;
    regmatch_t m[NMATCH];
    size_t len;
    size_t pos;
    size_t out_size;
    size_t capacity;
    size_t oi;
    char *out;

    if (input == NULL || pattern == NULL || replacement == NULL) {
        return NULL;
    }

    if (bounded_strlen(pattern, MAX_INPUT_LENGTH + 1) > MAX_INPUT_LENGTH ||
        bounded_strlen(replacement, MAX_INPUT_LENGTH + 1) > MAX_INPUT_LENGTH) {
        return NULL;
    }

    if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    len = bounded_strlen(input, MAX_INPUT_LENGTH + 1);
    if (len > MAX_INPUT_LENGTH) {
        regfree(&re);
        return NULL;
    }
    out_size = len + 1;

    pos = 0;
    while (pos < len && regexec(&re, input + pos, NMATCH, m, 0) == 0) {
        size_t rlen;
        size_t mlen;

        if (m[0].rm_so < 0 || m[0].rm_eo < m[0].rm_so ||
            (size_t)m[0].rm_eo > len - pos) {
            regfree(&re);
            return NULL;
        }
        if (m[0].rm_so == m[0].rm_eo) {
            if ((size_t)m[0].rm_eo >= len - pos) {
                break;
            }
            pos += (size_t)m[0].rm_eo + 1;
            continue;
        }
        if (replacement_length(replacement, m, NMATCH, &rlen) != 0) {
            regfree(&re);
            return NULL;
        }
        mlen = (size_t)(m[0].rm_eo - m[0].rm_so);
        if (rlen > SIZE_MAX - out_size) {
            regfree(&re);
            return NULL;
        }
        out_size += rlen;
        if (mlen >= out_size) {
            regfree(&re);
            return NULL;
        }
        out_size -= mlen;
        pos += (size_t)m[0].rm_eo;
    }

    out = malloc(out_size);
    if (out == NULL) {
        regfree(&re);
        return NULL;
    }
    capacity = out_size - 1;

    pos = 0;
    oi = 0;
    while (pos < len && regexec(&re, input + pos, NMATCH, m, 0) == 0) {
        if (m[0].rm_so < 0 || m[0].rm_eo < m[0].rm_so ||
            (size_t)m[0].rm_eo > len - pos) {
            free(out);
            regfree(&re);
            return NULL;
        }
        if (m[0].rm_so == m[0].rm_eo) {
            size_t adv;

            if ((size_t)m[0].rm_eo >= len - pos) {
                break;
            }
            adv = (size_t)m[0].rm_eo + 1;
            if (adv > len - pos ||
                checked_copy(out, capacity, &oi, input + pos, adv) != 0) {
                free(out);
                regfree(&re);
                return NULL;
            }
            pos += adv;
            continue;
        }
        if (checked_copy(out, capacity, &oi,
                         input + pos, (size_t)m[0].rm_so) != 0) {
            free(out);
            regfree(&re);
            return NULL;
        }
        if (replacement_expand(out, &oi, capacity, replacement,
                               input + pos, m, NMATCH) != 0) {
            free(out);
            regfree(&re);
            return NULL;
        }
        pos += (size_t)m[0].rm_eo;
    }
    if (checked_copy(out, capacity, &oi, input + pos, len - pos) != 0) {
        free(out);
        regfree(&re);
        return NULL;
    }
    out[oi] = '\0';

    regfree(&re);
    return out;
}

char *camel_to_snake(const char *input)
{
    char *step1;
    char *step2;
    size_t i;

    if (input == NULL) {
        return NULL;
    }

    step1 = regex_replace_all(input, "([A-Z]+)([A-Z][a-z])", "\\1_\\2");
    if (step1 == NULL) {
        return NULL;
    }

    step2 = regex_replace_all(step1, "([a-z0-9])([A-Z])", "\\1_\\2");
    free(step1);
    if (step2 == NULL) {
        return NULL;
    }

    for (i = 0; step2[i] != '\0'; i++) {
        step2[i] = (char)tolower((unsigned char)step2[i]);
    }

    return step2;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "HTTPSConnection",
        "XMLHttpRequest",
        "simpleTest",
        "already_snake_case",
        "A",
        "",
        NULL
    };
    size_t i;

    for (i = 0; tests[i] != NULL; i++) {
        char *snake = camel_to_snake(tests[i]);

        if (snake == NULL) {
            fprintf(stderr, "error: failed to convert \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", tests[i], snake);
        free(snake);
    }

    return EXIT_SUCCESS;
}