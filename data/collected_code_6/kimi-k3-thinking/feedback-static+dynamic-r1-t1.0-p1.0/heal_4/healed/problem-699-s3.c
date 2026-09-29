#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 1000000
#define STRINGIFY_INNER(x) #x
#define STRINGIFY(x) STRINGIFY_INNER(x)

static size_t bounded_length(const char *s, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

static int min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count10 = 0;
    long count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = bounded_length(s1, (size_t)MAX_INPUT_LEN + 1);
    len2 = bounded_length(s2, (size_t)MAX_INPUT_LEN + 1);

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        char c1 = s1[i];
        char c2 = s2[i];

        if ((c1 != '0' && c1 != '1') || (c2 != '0' && c2 != '1')) {
            return -1;
        }

        if (c1 == '1' && c2 == '0') {
            count10++;
        } else if (c1 == '0' && c2 == '1') {
            count01++;
        }
    }

    if (count10 != count01) {
        return -1;
    }

    return (int)count10;
}

int main(void)
{
    char *s1 = malloc((size_t)MAX_INPUT_LEN + 1);
    char *s2 = malloc((size_t)MAX_INPUT_LEN + 1);

    if (s1 == NULL || s2 == NULL) {
        free(s1);
        free(s2);
        return EXIT_FAILURE;
    }

    s1[0] = '\0';
    s2[0] = '\0';

    while (scanf("%" STRINGIFY(MAX_INPUT_LEN) "s%" STRINGIFY(MAX_INPUT_LEN) "s", s1, s2) == 2) {
        int result = min_swaps(s1, s2);

        if (result < 0) {
            printf("Not Possible\n");
        } else {
            printf("%d\n", result);
        }
    }

    free(s1);
    free(s2);

    return EXIT_SUCCESS;
}