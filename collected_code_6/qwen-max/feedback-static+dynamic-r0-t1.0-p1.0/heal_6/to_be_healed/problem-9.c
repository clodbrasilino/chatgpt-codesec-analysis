#include <stdio.h>
#include <string.h>

int findMinRotations(const char *str, size_t len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[2 * len + 1];
    if (len > 0 && len < sizeof(temp)/2) {
        snprintf(temp, sizeof(temp), "%s%s", str, str);
        for (size_t i = 1; i <= len; i++) {
            if (strncmp(temp + i, str, len) == 0) {
                return i;
            }
        }
    }
    return len;
}

int main() {
    const char str[] = "abcde";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  Assignment 'len=strlen(str)', assigned value is 5
     */
    size_t len = strlen(str);
    /* Possible weaknesses found:
     *  Condition 'len>0' is always true
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     */
    if (len > 0) {
        printf("Minimum rotations: %zu\n", (size_t)findMinRotations(str, len));
    } else {
        printf("Invalid input string.\n");
    }
    return 0;
}