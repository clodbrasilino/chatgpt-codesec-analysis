#include <stdio.h>
#include <stdlib.h>
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
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }

        if (s1[i] == '0' && s2[i] == '1') {
            mismatches_01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            mismatches_10++;
        }
        i++;
    }

    if (s1[i] != '\0' || s2[i] != '\0') {
        return -1;
    }

    if ((mismatches_01 + mismatches_10) % 2 != 0) {
        return -1;
    }

    int swaps = (mismatches_01 / 2) + (mismatches_10 / 2);
    
    if (mismatches_01 % 2 != 0) {
        swaps += 2;
    }

    return swaps;
}

int main(void) {
    const char *s1 = "0100101";
    const char *s2 = "0110001";

    int result = min_swaps(s1, s2);
    
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("Error: Invalid or incompatible strings.\n");
    }

    return 0;
}