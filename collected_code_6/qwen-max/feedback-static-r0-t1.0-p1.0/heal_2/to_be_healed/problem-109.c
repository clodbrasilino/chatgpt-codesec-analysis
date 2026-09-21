#include <stdio.h>
#include <string.h>

int count_odd_rotations(const char *str, size_t len) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        int sum = 0;
        for (int j = 0; j < len; j++) {
            sum += str[(i + j) % len] - '0';
        }
        if (sum % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main() {
    const char binary_string[] = "1001";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(binary_string);
    int result = count_odd_rotations(binary_string, len);
    printf("Count of rotations with odd value: %d\n", result);
    return 0;
}