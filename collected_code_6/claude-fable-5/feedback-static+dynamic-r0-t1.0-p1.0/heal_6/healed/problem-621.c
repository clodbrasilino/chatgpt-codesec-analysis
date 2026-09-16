#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static int is_numeric(const char *s)
{
    size_t i = 0;

    if (s == NULL || s[0] == '\0') {
        return 0;
    }
    if (s[0] == '+' || s[0] == '-') {
        i = 1;
        if (s[1] == '\0') {
            return 0;
        }
    }
    for (; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }
    return 1;
}

static char *duplicate_string(const char *s)
{
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    len = strlen(s) + 1;
    copy = malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    return copy;
}

static char *duplicate_range(const char *s, size_t len)
{
    char *copy;

    if (s == NULL) {
        return NULL;
    }
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

static void free_string_array(char **arr, size_t n)
{
    size_t i;

    if (