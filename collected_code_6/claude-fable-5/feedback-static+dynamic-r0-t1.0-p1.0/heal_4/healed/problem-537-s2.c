#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define MAX_INPUT_LEN 65536

static size_t bounded_strlen(const char *src, size_t maxlen)
{
    const char *end;

    end = memchr(src, '\0', maxlen);
    if (end == NULL) {
        return maxlen;
    }
    return (size_t)(end - src);
}

static char *duplicate_string(const char *src)
{
    size_t len;
    char *dup;

    if (src == NULL) {
        return NULL;
    }

    len = bounded_strlen(src, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    dup = malloc(len + 1);
    if (dup == NULL) {
        return NULL;
    }

    memcpy(dup, src, len);
    dup[len] = '\0';
    return dup;
}

static int is_delim(char c)
{
    static const char *delims = " \t\r\n.,;:!?\"'()";
    return strchr(delims, c) != NULL && c != '\0';
}

char *find_first_repeated_word(const char *input)
{
    char *copy;
    char *result;
    char **seen;
    char *p;
    char *token;
    size_t count;
    size_t i;

    if (input == NULL) {
        return duplicate_string("None");
    }

    copy = duplicate_string(input);
    if (copy == NULL) {
        return NULL;
    }

    seen = calloc(MAX_WORDS, sizeof(char *));
    if (seen == NULL) {
        free(copy);
        return NULL;
    }

    result = NULL;
    count = 0;
    p = copy;

    while (*p != '\0' && count < MAX_WORDS) {
        while (*p != '\0' && is_delim(*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        token = p;
        while (*p != '\0' && !is_delim(*p)) {
            p++;
        }
        if (*p != '\0') {
            *p = '\0';
            p++;
        }
        for (i = 0; i < count; i++) {
            if (seen[i] != NULL && strcmp(seen[i], token) == 0) {
                result = duplicate_string(token);
                goto cleanup;
            }
        }
        seen[count] = duplicate_string(token);
        if (seen[count] == NULL) {
            goto cleanup;
        }
        count++;
    }

    result = duplicate_string("None");

cleanup:
    for (i = 0; i < count; i++) {
        free(seen[i]);
    }
    free(seen);
    free(copy);
    return result;
}

int main(void)
{
    char *input;
    char *repeated;
    size_t total;
    size_t nread;

    input = malloc(MAX_INPUT_LEN);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    total = 0;
    while (total < MAX_INPUT_LEN - 1) {
        nread = fread(input + total, 1, MAX_INPUT_LEN - 1 - total, stdin);
        if (nread == 0) {
            break;
        }
        total += nread;
    }

    if (total == 0 && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[total] = '\0';

    repeated = find_first_repeated_word(input);
    free(input);

    if (repeated == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", repeated) < 0) {
        free(repeated);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        free(repeated);
        return EXIT_FAILURE;
    }

    free(repeated);
    return EXIT_SUCCESS;
}