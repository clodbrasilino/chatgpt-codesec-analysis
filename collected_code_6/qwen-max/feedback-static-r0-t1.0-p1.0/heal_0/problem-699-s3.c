#include <stdio.h>
#include <string.h>

int min_swaps(const char *str1, const char *str2, int len) {
    int count01 = 0, count10 = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] == '0' && str2[i] == '1') {
            count01++;
        } else if (str1[i] == '1' && str2[i] == '0') {
            count10++;
        }
    }
    return (count01 + 1) / 2 + (count10 + 1) / 2;
}

int main() {
    const char *str1 = "1100";
    const char *str2 = "0011";
    int len = strlen(str1);
    if (len != strlen(str2)) {
        printf("Strings must be of equal length\n");
        return 1;
    }
    int swaps = min_swaps(str1, str2, len);
    printf("Minimum number of swaps: %d\n", swaps);
    return 0;
}