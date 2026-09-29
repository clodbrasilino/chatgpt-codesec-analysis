#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'binary_string' can be declared as pointer to const [constParameterPointer]
 */
int count_odd_rotations(char *binary_string, int length) {
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
        if (value == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    char binary_string[] = "1101";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(binary_string);
    int result = count_odd_rotations(binary_string, length);
    printf("Count of rotations with odd value: %d\n", result);
    return 0;
}