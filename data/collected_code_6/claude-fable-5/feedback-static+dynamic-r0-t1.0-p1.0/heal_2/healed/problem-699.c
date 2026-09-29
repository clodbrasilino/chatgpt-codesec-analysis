#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

int min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    int count10 = 0;
    int count01 = 0;

    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    len1 = strnlen(s1, MAX_INPUT_LEN);
    len2 = strnlen(s2, MAX_INPUT_LEN);

    if (len1 >= MAX_INPUT_LEN || len2 >= MAX_INPUT_LEN) {
        return -1;
    }

    if (len1 != len2) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
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
        return -1;
    }

    return count10;
}

static void strip_newline(char *s)
{
    size_t len;

    if (s == NULL) {
        return;
    }

    len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

int main(void)
{
    char s1[MAX_INPUT_LEN];
    char s2[MAX_INPUT_LEN];
    int result;

    if (fgets(s1, sizeof(s1), stdin) == NULL) {
        return 1;
    }
    if (fgets(s2, sizeof(s2), stdin) == NULL) {
        return 1;
    }

    strip_newline(s1);
    strip_newline(s2);

    result = min_swaps(s1, s2);

    if (result < 0) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
    } else {
        if (printf("%d\n", result) < 0) {
            return 1;
        }
    }

    return 0;
}