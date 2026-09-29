#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps_binary_strings(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    
    if (len1 != len2) {
        return -1;
    }
    
    size_t count1_0 = 0;
    size_t count1_1 = 0;
    size_t count2_0 = 0;
    size_t count2_1 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (s1[i] == '0') {
            count1_0++;
        } else if (s1[i] == '1') {
            count1_1++;
        } else {
            return -1;
        }
        
        if (s2[i] == '0') {
            count2_0++;
        } else if (s2[i] == '1') {
            count2_1++;
        } else {
            return -1;
        }
    }

    if (count1_0 != count2_0 || count1_1 != count2_1) {
        return -1;
    }

    size_t mismatch_1_0 = 0;
    size_t mismatch_0_1 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (s1[i] == '1' && s2[i] == '0') {
            mismatch_1_0++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            mismatch_0_1++;
        }
    }

    return (int)(mismatch_1_0 / 2 + mismatch_0_1 / 2 + (mismatch_1_0 % 2) * 2);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <binary_string1> <binary_string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = min_swaps_binary_strings(argv[1], argv[2]);
    
    if (result < 0) {
        fprintf(stderr, "Invalid input or unequal strings.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}