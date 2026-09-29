#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isTerminated(const char *str) {
    if (str == NULL) {
        return false;
    }
    while (*str) {
        if (!*str++)
            return true;
    }
    return false;
}

int minSwaps(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL || !isTerminated(str1) || !isTerminated(str2))
        return -1;
    int len1 = strnlen(str1, INT_MAX);
    int len2 = strnlen(str2, INT_MAX);
    if (len1 != len2)
        return -1;

    int count = 0;
    for (int i = 0; i < len1; i++) {
        if (str1[i] != str2[i])
            count++;
    }

    return count / 2;
}

int main() {
    char str1[] = "010101";
    char str2[] = "101010";
    int swaps = minSwaps(str1, str2);
    printf("Minimum number of swaps required: %d\n", swaps);
    return 0;
}