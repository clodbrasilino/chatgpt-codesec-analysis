#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 4096

static size_t bounded_len(const char *s, size_t max)
{
    size_t i = 0;

    while (i < max && s[i] != '\0') {
        i++;
    }
    return i;
}

int min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    int diff10 = 0;
    int diff01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = bounded_len(s1, MAX_LEN);
    len2 = bounded_len(s2, MAX_LEN);

    if (len1 >= MAX_LEN || len2 >= MAX_LEN) {
        return -1;
    }

    if (len1 != len2) {
        return -1;
    }

    if (len1 == 0) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            diff10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            diff01++;
        }
    }

    if (diff10 != diff01) {
        return -1;
    }

    return diff10;
}

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = bounded_len(s, MAX_LEN);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

int main(void)
{
    char str1[MAX_LEN];
    char str2[MAX_LEN];
    int result;

    memset(str1, 0, sizeof(str1));
    memset(str2, 0, sizeof(str2));

    if (fgets(str1, (int)sizeof(str1), stdin) == NULL) {
        if (printf("Not Possible\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (fgets(str2, (int)sizeof(str2), stdin) == NULL) {
        if (printf("Not Possible\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    str1[sizeof(str1) - 1] = '\0';
    str2[sizeof(str2) - 1] = '\0';

    strip_newline(str1);
    strip_newline(str2);

    result = min_swaps(str1, str2);

    if (result < 0) {
        if (printf("Not Possible\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("%d\n", result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}