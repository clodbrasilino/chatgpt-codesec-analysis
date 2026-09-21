#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 7, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 6, got <no output>
  */

int digit_distance(int num1, int num2) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[32];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[32];
    
    int len1 = snprintf(str1, sizeof(str1), "%d", num1);
    int len2 = snprintf(str2, sizeof(str2), "%d", num2);
    
    if (len1 < 0 || len1 >= (int)sizeof(str1) || len2 < 0 || len2 >= (int)sizeof(str2)) {
        return -1;
    }
    
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