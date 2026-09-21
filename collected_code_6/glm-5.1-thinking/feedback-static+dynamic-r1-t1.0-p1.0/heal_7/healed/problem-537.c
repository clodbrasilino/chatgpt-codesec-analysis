#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

static char *my_strdup(const char *s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char *new_s = malloc(len);
    if (new_s == NULL) return NULL;
    memcpy(new_s, s, len);
    return new_s;
}

static int ci_strcmp(const char *a, const char *b) {
    while (*a && *b) {
        int diff = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (diff != 0) return diff;
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

char *find_first_repeated_word(const char *str) {
    if (str == NULL) return NULL;

    char *temp = my_strdup(str);
    if (temp == NULL) return NULL;

    size_t capacity = 16;
    size_t count = 0;
    char **seen = malloc(capacity * sizeof(char *));
    if (seen == NULL) {
        free(temp);
        return NULL;
    }

    const char *delim = " ,.!?;:\t\n\r";
    char *saveptr;
    char *token = strtok_r(temp, delim, &saveptr);
    char *result = NULL;

    while (token != NULL) {
        for (size_t i = 0; i < count; i++) {
            if (ci_strcmp(seen[i], token) == 0) {
                result = my_strdup(token);
                goto cleanup;
            }
        }

        if (count >= capacity) {
            if (capacity > SIZE_MAX / (2 * sizeof(char *))) {
                goto cleanup;
            }
            capacity *= 2;
            char **new_seen = realloc(seen, capacity * sizeof(char *));
            if (new_seen == NULL) {
                goto cleanup;
            }
            seen = new_seen;
        }

        seen[count] = my_strdup(token);
        if (seen[count] == NULL) {
            goto cleanup;
        }
        count++;

        token = strtok_r(NULL, delim, &saveptr);
    }

    result = my_strdup("None");

cleanup:
    free(temp);
    for (size_t j = 0; j < count; j++) free(seen[j]);
    free(seen);
    return result;
}

int main(void) {
    const char *text = "This is a test, this is only a test.";
    char *repeated = find_first_repeated_word(text);
    if (repeated != NULL) {
        printf("%s\n", repeated);
        free(repeated);
    }
    return 0;
}