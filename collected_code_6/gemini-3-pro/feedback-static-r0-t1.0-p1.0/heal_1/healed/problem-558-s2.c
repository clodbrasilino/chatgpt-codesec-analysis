#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int digit_distance(int num1, int num2) {
    int len1 = snprintf(NULL, 0, "%d", num1);
    int len2 = snprintf(NULL, 0, "%d", num2);
    
    if (len1 < 0 || len2 < 0 || len1 != len2) {
        return -1;
    }
    
    char *str1 = malloc((size_t)len1 + 1);
    char *str2 = malloc((size_t)len2 + 1);
    
    if (!str1 || !str2) {
        free(str1);
        free(str2);
        return -1;
    }
    
    snprintf(str1, (size_t)len1 + 1, "%d", num1);
    snprintf(str2, (size_t)len2 + 1, "%d", num2);
    
    int distance = 0;
    
    for (int i = 0; i < len1; i++) {
        distance += abs(str1[i] - str2[i]);
    }
    
    free(str1);
    free(str2);
    
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