#include <stdio.h>
#include <string.h>

int count_odd_rotations(const char *binary_string, int length) {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        int value = 0;
        for (int j = 0; j < length; ++j) {
            if (binary_string[(i + j) % length] == '1') {
                value = (value * 2 + 1) % 2;
            } else {
                value = (value * 2) % 2;
            }
        }
        if (value % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main() {
    char binary_string[] = "1010";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(binary_string);
    int rotations_with_odd_value = count_odd_rotations(binary_string, length);
    printf("Count of rotations with odd value: %d\n", rotations_with_odd_value);
    return 0;
}