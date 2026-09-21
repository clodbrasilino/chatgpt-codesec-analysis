#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_odd_rotations(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    int odd_rotations = 0;

    for (int i = 0; i < n; i++) {
        if (str[i] == '1') {
            odd_rotations++;
        }
    }

    return odd_rotations;
}

int main() {
    const char *binary_string = "10110";
    
    int result = count_odd_rotations(binary_string);
    
    printf("%d\n", result);
    
    return 0;
}