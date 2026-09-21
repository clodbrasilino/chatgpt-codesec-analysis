#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(const char *a, const char *b, size_t len) {
    int count[2] = {0, 0};
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            count[a[i] - '0']++;
            if (a[i] - '0' < 0 || a[i] - '0' > 1 || b[i] - '0' < 0 || b[i] - '0' > 1) return -1;
        }
    }
    return count[1] % 2 == 0 ? count[1] / 2 : -1;
}

int main() {
    const char a[] = "1100";
    const char b[] = "1001";
    /* Possible weaknesses found:
     *  Assignment 'len_a=sizeof(a)-1', assigned value is 4
     */
    size_t len_a = sizeof(a) - 1;
    size_t len_b = sizeof(b) - 1;
    /* Possible weaknesses found:
     *  Condition 'len_a!=len_b' is always false [knownConditionTrueFalse]
     *  Condition 'len_a!=len_b' is always false
     */
    if (len_a != len_b) {
        printf("Strings are of different lengths\n");
        return 1;
    }
    int result = minSwaps(a, b, len_a);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    return 0;
}