#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    int count01 = 0;
    int count10 = 0;

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
        if (s1[i] != s2[i]) {
            if (s1[i] == '0') {
                count01++;
            } else {
                count10++;
            }
        }
    }

    if (count01 != count10) {
        return -1;
    }

    return count01;
}

void print_result(const char *s1, const char *s2)
{
    int result;

    result = min_swaps(s1, s2);

    if (result < 0) {
        printf("Not Possible\n");
        return;
    }

    printf("Minimum swaps required: %d\n", result);
}

int main(void)
{
    const char *a = "1101";
    const char *b = "1011";
    const char *c = "1100";
    const char *d = "0011";
    const char *e = "110";
    const char *f = "1011";
    const char *g = "111";
    const char *h = "000";

    print_result(a, b);
    print_result(c, d);
    print_result(e, f);
    print_result(g, h);
    print_result(NULL, b);

    return 0;
}