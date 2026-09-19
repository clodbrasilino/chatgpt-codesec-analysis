#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int min_swaps(const char *s1, const char *s2)
{
    size_t i;
    size_t len1;
    size_t len2;
    int count10 = 0;
    int count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        }
    }

    if (count10 != count01) {
        return -1;
    }

    return count10;
}

static void run_case(const char *s1, const char *s2)
{
    int result = min_swaps(s1, s2);

    if (result < 0) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
}

int main(int argc, char **argv)
{
    char *buffer;
    char **tokens;
    size_t capacity;
    size_t length;
    size_t token_capacity;
    size_t token_count;
    size_t n;
    size_t idx;
    char *p;

    if (argc >= 3) {
        run_case(argv[1], argv[2]);
        return 0;
    }

    capacity = 1u << 20;
    length = 0;
    buffer = (char *)malloc(capacity);
    if (buffer == NULL) {
        return 1;
    }

    while ((n = fread(buffer + length, 1, capacity - length - 1, stdin)) > 0) {
        length += n;
        if (capacity - length - 1 == 0) {
            char *new_buffer;
            capacity *= 2;
            new_buffer = (char *)realloc(buffer, capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
        }
    }
    buffer[length] = '\0';

    token_capacity = 16;
    token_count = 0;
    tokens = (char **)malloc(token_capacity * sizeof(*tokens));
    if (tokens == NULL) {
        free(buffer);
        return 1;
    }

    p = buffer;
    while (*p != '\0') {
        while (*p != '\0' && isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }
        if (token_count == token_capacity) {
            char **new_tokens;
            token_capacity *= 2;
            new_tokens = (char **)realloc(tokens, token_capacity * sizeof(*tokens));
            if (new_tokens == NULL) {
                free(tokens);
                free(buffer);
                return 1;
            }
            tokens = new_tokens;
        }
        tokens[token_count++] = p;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
        }
        if (*p != '\0') {
            *p = '\0';
            p++;
        }
    }

    idx = 0;
    if (token_count % 2 == 1) {
        char *end = NULL;
        long t = strtol(tokens[0], &end, 10);
        if (end != tokens[0] && *end == '\0' &&
            t == (long)((token_count - 1) / 2)) {
            idx = 1;
        }
    }

    for (; idx + 1 < token_count; idx += 2) {
        run_case(tokens[idx], tokens[idx + 1]);
    }

    free(tokens);
    free(buffer);

    return 0;
}