#include <stdio.h>
#include <stdbool.h>

bool arePermutations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    int counts[256] = {0};
    size_t i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        counts[(unsigned char)str1[i]]++;
        counts[(unsigned char)str2[i]]--;
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return false;
    }

    for (int j = 0; j < 256; j++) {
        if (counts[j] != 0) {
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