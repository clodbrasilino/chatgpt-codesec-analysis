#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countSubstrings(const char* s) {
    if (s == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(s);
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return 0; 
        }
    }

    for (int i = 0; i < n; i++) {
        int current_sum = 0;
        for (int j = i; j < n; j++) {
            current_sum += (s[j] - '0');
            int current_length = j - i + 1;
            if (current_sum == current_length) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char* str = "1101112";
    int result = countSubstrings(str);
    printf("%d\n", result);
    return 0;
}