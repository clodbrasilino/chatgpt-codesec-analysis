#include <stdio.h>
#include <string.h>

int maxDifference(const char* str) {
    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    if (n == 0) {
        return -1;
    }

    int current_sum = 0;
    int max_sum = -1;

    for (int i = 0; i < n; i++) {
        int val = (str[i] == '0') ? 1 : -1;
        
        current_sum += val;
        
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
        
        if (current_sum < 0) {
            current_sum = 0;
        }
    }

    return max_sum;
}

int main(void) {
    const char* test1 = "11000010001";
    const char* test2 = "1111";
    const char* test3 = "0000";

    printf("%d\n", maxDifference(test1));
    printf("%d\n", maxDifference(test2));
    printf("%d\n", maxDifference(test3));

    return 0;
}