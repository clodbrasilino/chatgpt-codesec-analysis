#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_token(FILE *stream)
{
    size_t capacity = 4096;
    size_t length = 0;
    char *buffer = (char *)malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        int c = fgetc(stream);

        if (c == EOF) {
            break;
        }

        if (c == ' ' || c == '\t' || c == '\n' ||
            c == '\r' || c == '\v' || c == '\f') {
            if (length > 0) {
                break;
            }
            continue;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *resized;

            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }

            resized = (char *)realloc(buffer, new_capacity);

            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
    }

    if (length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

static int min_swaps(const char *s1, const char *s2, long *result)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count10 = 0;
    long count01 = 0;

    if (s1 == NULL || s2 == NULL || result == NULL) {
        return 0;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        return 0;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return 0;
        }

        if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        }
    }

    if (count10 != count01) {
        return 0;
    }

    *result = count10;
    return 1;
}

int main(void)
{
    char *s1;

    while ((s1 = read_token(stdin)) != NULL) {
        char *s2 = read_token(stdin);
        long result = 0;

        if (s2 == NULL) {
            printf("Not Possible\n");
            free(s1);
            break;
        }

        if (min_swaps(s1, s2, &result)) {
            printf("%ld\n", result);
        } else {
            printf("Not Possible\n");
        }

        free(s1);
        free(s2);
    }

    return 0;
}