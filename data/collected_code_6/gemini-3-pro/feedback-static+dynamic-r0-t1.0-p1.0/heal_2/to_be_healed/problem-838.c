#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 1000000
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  */

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    int mismatches_01 = 0;
    int mismatches_10 = 0;
    size_t i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        /* Possible weaknesses found:
         *  Assuming that condition 'i>=1000000' is not redundant
         */
        if (i >= MAX_LEN) {
            return -1;
        }

        /* Possible weaknesses found:
         *  Either the condition 'i>=1000000' is redundant or the array 's1[7]' is accessed at index 999999, which is out of bounds. [arrayIndexOutOfBoundsCond]
         *  Array index out of bounds
         */
        if (s1[i] != '0' && s1[i] != '1') return -1;
        if (s2[i] != '0' && s2[i] != '1') return -1;

        if (s1[i] == '0' && s2[i] == '1') {
            mismatches_01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            mismatches_10++;
        }
        
        i++;
    }

    if (s1[i] != '\0' || s2[i] != '\0' || i == 0) {
        return -1;
    }

    if ((mismatches_01 + mismatches_10) % 2 != 0) {
        return -1;
    }

    return (mismatches_01 / 2) + (mismatches_10 / 2) + (mismatches_01 % 2) * 2;
}

int main(void) {
    const char *s1 = "100110";
    const char *s2 = "011010";

    int result = min_swaps(s1, s2);
    
    if (result != -1) {
        printf("Minimum swaps: %d\n", result);
    } else {
        printf("Invalid input or impossible to make strings equal.\n");
    }

    return 0;
}