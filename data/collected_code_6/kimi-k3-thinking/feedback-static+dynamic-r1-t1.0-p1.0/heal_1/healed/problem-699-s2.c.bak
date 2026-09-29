#include <stdio.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2)
{
    size_t i;
    size_t len1;
    size_t len2;
    int count10 = 0;
    int count01 = 0;

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
    static char str1[1000005];
    static char str2[1000005];
    int result;

    if (scanf("%1000004s", str1) != 1) {
        return 1;
    }
    if (scanf("%1000004s", str2) != 1) {
        return 1;
    }

    result = min_swaps(str1, str2);

    if (result < 0) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}