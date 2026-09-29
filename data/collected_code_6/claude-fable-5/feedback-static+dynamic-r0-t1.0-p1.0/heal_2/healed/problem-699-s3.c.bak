#include <stdio.h>
#include <string.h>

static const char *min_swaps(const char *s1, const char *s2)
{
    static char buffer[32];
    size_t len1;
    size_t len2;
    size_t i;
    int count01 = 0;
    int count10 = 0;

    if (s1 == NULL || s2 == NULL) {
        return "Not Possible";
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        return "Not Possible";
    }

    for (i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            return "Not Possible";
        }
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') {
                count01++;
            } else {
                count10++;
            }
        }
    }

    if (count01 != count10) {
        return "Not Possible";
    }

    if (snprintf(buffer, sizeof(buffer), "%d", count01) < 0) {
        return "Not Possible";
    }

    return buffer;
}

int main(void)
{
    const char *a = "1101";
    const char *b = "1011";
    const char *result;

    result = min_swaps(a, b);

    if (strcmp(result, "Not Possible") == 0) {
        if (printf("Not Possible\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Minimum swaps required: %s\n", result) < 0) {
            return 1;
        }
    }

    return 0;
}