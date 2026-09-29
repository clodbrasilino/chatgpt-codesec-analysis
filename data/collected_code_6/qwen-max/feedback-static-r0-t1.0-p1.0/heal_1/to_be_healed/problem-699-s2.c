#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 's1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 's2' can be declared as pointer to const [constParameterPointer]
 */
int minSwaps(char *s1, char *s2, int n) {
    int count[2] = {0};
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }
    return (count[0] == count[1]) ? count[0] : -1;
}

int main() {
    char s1[] = "1100";
    char s2[] = "1001";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(s1);
    int result = minSwaps(s1, s2, n);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    return 0;
}