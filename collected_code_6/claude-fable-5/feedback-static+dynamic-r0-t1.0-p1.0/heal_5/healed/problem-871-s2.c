#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

bool are_rotations(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t temp_size;
    char *temp;
    bool result;

    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    len1 = strnlen(s1, MAX_INPUT_LEN);
    len2 = strnlen(s2, MAX_INPUT_LEN);

    if (len1 >= MAX_INPUT_LEN || len2 >= MAX_INPUT_LEN) {
        return false;
    }

    if (len1 != len2) {
        return false;
    }

    if (len1 == 0) {
        return true;
    }

    if (len1 > (SIZE_MAX - 1) / 2) {
        return false;
    }

    temp_size = (2 * len1) + 1;

    temp = malloc(temp_size);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    if (len1 > temp_size - 1 || len1 > temp_size - 1 - len1) {
        free(temp);
        return false;
    }

    memcpy(temp, s1, len1);
    memcpy(temp + len1, s1, len1);
    temp[temp_size - 1] = '\0';

    result = (strstr(temp, s2) != NULL);

    free(temp);
    return result;
}

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strnlen(s, MAX_INPUT_LEN);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

int main(void)
{
    char buf1[MAX_INPUT_LEN];
    char buf2[MAX_INPUT_LEN];

    while (fgets(buf1, sizeof(buf1), stdin) != NULL &&
           fgets(buf2, sizeof(buf2), stdin) != NULL) {
        strip_newline(buf1);
        strip_newline(buf2);

        if (are_rotations(buf1, buf2)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}