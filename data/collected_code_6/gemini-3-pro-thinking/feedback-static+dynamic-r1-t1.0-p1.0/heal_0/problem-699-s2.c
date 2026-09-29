#include <stdio.h>

long min_swaps_binary_strings(const char *str1, const char *str2);

long min_swaps_binary_strings(const char *str1, const char *str2) {
    long diff01 = 0;
    long diff10 = 0;
    size_t i = 0;

    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    while (str1[i] != '\0' && str2[i] != '\0') {
        if ((str1[i] != '0' && str1[i] != '1') || (str2[i] != '0' && str2[i] != '1')) {
            return -1;
        }

        if (str1[i] != str2[i]) {
            if (str1[i] == '0') {
                diff01++;
            } else {
                diff10++;
            }
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return -1;
    }

    if (diff01 != diff10) {
        return -1;
    }

    return diff01;
}

int main(void) {
    const char *str1 = "11001100";
    const char *str2 = "10101010";
    
    long swaps = min_swaps_binary_strings(str1, str2);
    
    if (swaps >= 0) {
        printf("%ld\n", swaps);
    } else {
        printf("-1\n");
    }
    
    return 0;
}