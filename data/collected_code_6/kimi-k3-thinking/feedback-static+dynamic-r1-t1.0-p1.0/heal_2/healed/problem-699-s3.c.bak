#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_token(FILE *stream)
{
    size_t capacity = 4096;
    size_t length = 0;
    int c;
    char *buffer = (char *)malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        c = fgetc(stream);
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
            char *resized = (char *)realloc(buffer, new_capacity);
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

long min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count10 = 0;
    long count01 = 0;

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

int main(void)
{
    char *s1;
    char *s2;

    while ((s1 = read_token(stdin)) != NULL) {
        long result;

        s2 = read_token(stdin);
        if (s2 == NULL) {
            free(s1);
            break;
        }

        result = min_swaps(s1, s2);
        if (result < 0) {
            printf("Not Possible\n");
        } else {
            printf("%ld\n", result);
        }

        free(s1);
        free(s2);
    }

    return 0;
}