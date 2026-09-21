#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 4096

long min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count01;
    long count10;

    if (s1 == NULL || s2 == NULL) {
        return -1L;
    }

    len1 = strnlen(s1, MAX_LEN);
    len2 = strnlen(s2, MAX_LEN);

    if (len1 != len2 || len1 == 0U) {
        return -1L;
    }

    count01 = 0L;
    count10 = 0L;

    for (i = 0U; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1L;
        }
        if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        }
    }

    if (count01 != count10) {
        return -1L;
    }

    return count01;
}

static int read_line(char *buf, size_t size)
{
    size_t len;

    if (buf == NULL || size == 0U) {
        return -1;
    }

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    len = strnlen(buf, size);
    while (len > 0U && (buf[len - 1U] == '\n' || buf[len - 1U] == '\r')) {
        buf[len - 1U] = '\0';
        len--;
    }

    return 0;
}

int main(void)
{
    char a[MAX_LEN + 2];
    char b[MAX_LEN + 2];
    long result;

    if (read_line(a, sizeof(a)) != 0) {
        if (printf("Not Possible\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (read_line(b, sizeof(b)) != 0) {
        if (printf("Not Possible\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    result = min_swaps(a, b);

    if (result < 0L) {
        if (printf("Not Possible\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("%ld\n", result) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}