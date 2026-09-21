#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int digit_distance(int num1, int num2) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[20];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[20];
    
    snprintf(str1, sizeof(str1), "%d", num1);
    snprintf(str2, sizeof(str2), "%d", num2);
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len1 = strlen(str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len2 = strlen(str2);
    
    if (len1 != len2) {
        return -1;
    }
    
    int distance = 0;
    
    for (int i = 0; i < len1; i++) {
        distance += abs(str1[i] - str2[i]);
    }
    
    return distance;
}

int main(void) {
    int num1_test1 = 123;
    int num2_test1 = 256;
    int result1 = digit_distance(num1_test1, num2_test1);
    if (result1 != -1) {
        printf("Digit distance between %d and %d is %d\n", num1_test1, num2_test1, result1);
    } else {
        printf("Numbers %d and %d have different lengths.\n", num1_test1, num2_test1);
    }

    int num1_test2 = 1234;
    int num2_test2 = 123;
    int result2 = digit_distance(num1_test2, num2_test2);
    if (result2 != -1) {
        printf("Digit distance between %d and %d is %d\n", num1_test2, num2_test2, result2);
    } else {
        printf("Numbers %d and %d have different lengths.\n", num1_test2, num2_test2);
    }

    return EXIT_SUCCESS;
}