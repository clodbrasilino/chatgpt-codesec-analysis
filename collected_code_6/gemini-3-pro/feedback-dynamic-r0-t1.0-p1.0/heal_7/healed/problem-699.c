#include <stdio.h>
#include <string.h>

char str1[1000005];
char str2[1000005];

int min_swaps(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    if (len1 != len2) {
        return -1;
    }

    int count_zero_to_one = 0;
    int count_one_to_zero = 0;

    for (size_t i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }

        if (s1[i] == '0' && s2[i] == '1') {
            count_zero_to_one++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            count_one_to_zero++;
        }
    }

    if (count_zero_to_one != count_one_to_zero) {
        return -1;
    }

    return count_zero_to_one;
}

int main(void) {
    if (scanf("%1000000s", str1) != 1) {
        printf("Not Possible\n");
        return 0;
    }
    if (scanf("%1000000s", str2) != 1) {
        printf("Not Possible\n");
        return 0;
    }

    int result = min_swaps(str1, str2);

    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Not Possible\n");
    }

    return 0;
}