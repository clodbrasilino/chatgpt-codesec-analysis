#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool arePermutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2) {
        return false;
    }

    int counts[256] = {0};

    for (size_t i = 0; i < len1; i++) {
        counts[(unsigned char)str1[i]]++;
        counts[(unsigned char)str2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (counts[i] != 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *str1 = "listen";
    const char *str2 = "silent";

    if (arePermutations(str1, str2)) {
        printf("Strings are permutations.\n");
    } else {
        printf("Strings are not permutations.\n");
    }

    return 0;
}