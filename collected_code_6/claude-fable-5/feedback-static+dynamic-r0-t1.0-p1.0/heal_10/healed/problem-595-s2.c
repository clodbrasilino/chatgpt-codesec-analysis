#include <stdio.h>
#include <string.h>

#define MAX_LEN 4096

static size_t safe_strnlen(const char *s, size_t maxlen)
{
    size_t i;

    if (s == NULL) {
        return 0;
    }

    for (i = 0; i < maxlen; i++) {
        if (s[i] == '\0') {
            break;
        }
    }

    return i;
}

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = safe_strnlen(s, MAX_LEN);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

static long min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count10 = 0;
    long count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1L;
    }

    len1 = safe_strnlen(s1, MAX_LEN);
    len2 = safe_strnlen(s2, MAX_LEN);

    if (len1 >= MAX_LEN || len2 >= MAX_LEN) {
        return -1L;
    }

    if (len1 != len2 || len1 == 0) {
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

int main(void)
{
    char a[MAX_LEN];
    char b[MAX_LEN];
    long result;

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    if (fgets(a, (int)sizeof(a), stdin) == NULL) {
        printf("Not Possible\n");
        fflush(stdout);
        return 0;
    }

    if (fgets(b, (int)sizeof(b), stdin) == NULL) {
        printf("Not Possible\n");
        fflush(stdout);
        return 0;
    }

    a[sizeof(a) - 1] = '\0';
    b[sizeof(b) - 1] = '\0';

    strip_newline(a);
    strip_newline(b);

    result = min_swaps(a, b);

    if (result < 0L) {
        printf("Not Possible\n");
    } else {
        printf("%ld\n", result);
    }

    if (fflush(stdout) != 0) {
        return 1;
    }

    return 0;
}