#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps(const char *s1, const char *s2, int *swaps)
{
    size_t len1;
    size_t len2;
    size_t i;
    int diff10 = 0;
    int diff01 = 0;

    if (s1 == NULL || s2 == NULL || swaps == NULL) {
        return -1;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
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

    *swaps = diff10;
    return 0;
}

int print_result(int status, int swaps)
{
    if (status != 0) {
        if (printf("Not Possible\n") < 0) {
            return -1;
        }
    } else {
        if (printf("Minimum swaps required: %d\n", swaps) < 0) {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    const char *str1 = "1101";
    const char *str2 = "0011";
    int swaps = 0;
    int status;

    status = min_swaps(str1, str2, &swaps);

    if (print_result(status, swaps) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}