#include <stdio.h>
#include <string.h>

#define MAX_LEN 4096

long min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count10 = 0;
    long count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1L;
    }

    len1 = strnlen(s1, MAX_LEN);
    len2 = strnlen(s2, MAX_LEN);

    if (len1 >= MAX_LEN || len2 >= MAX_LEN) {
        return -1L;
    }

    if (len1 != len2) {
        return -1L;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return -1L;
        }
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                count10++;
            } else {
                count01++;
            }
        }
    }

    if (count10 != count01) {
        return -1L;
    }

    return count10;
}

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strnlen(s, MAX_LEN);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

int main(void)
{
    char a[MAX_LEN];
    char b[MAX_LEN];
    long result;

    if (fgets(a, sizeof(a), stdin) == NULL) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
        return 0;
    }

    if (fgets(b, sizeof(b), stdin) == NULL) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
        return 0;
    }

    strip_newline(a);
    strip_newline(b);

    result = min_swaps(a, b);

    if (result < 0) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
        return 0;
    }

    if (printf("%ld\n", result) < 0) {
        return 1;
    }

    return 0;
}