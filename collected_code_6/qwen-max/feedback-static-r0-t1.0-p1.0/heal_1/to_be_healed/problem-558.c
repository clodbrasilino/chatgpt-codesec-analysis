#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abs_diff(int a, int b) {
    return a > b ? a - b : b - a;
}

int digit_distance(int num1, int num2) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char s1[12], s2[12];
    /* Possible weaknesses found:
     * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
     */
    sprintf(s1, "%d", num1);
    /* Possible weaknesses found:
     * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
     */
    sprintf(s2, "%d", num2);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(s1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len2 = strlen(s2);
    size_t max_len = (len1 > len2) ? len1 : len2;

    int distance = 0;
    for (size_t i = 0; i < max_len; ++i) {
        int d1 = (i < len1) ? s1[i] - '0' : 0;
        int d2 = (i < len2) ? s2[i] - '0' : 0;
        distance += abs_diff(d1, d2);
    }
    return distance;
}

int main() {
    int num1 = 234;
    int num2 = 489;
    printf("The digit distance between %d and %d is: %d\n", num1, num2, digit_distance(num1, num2));
    return 0;
}