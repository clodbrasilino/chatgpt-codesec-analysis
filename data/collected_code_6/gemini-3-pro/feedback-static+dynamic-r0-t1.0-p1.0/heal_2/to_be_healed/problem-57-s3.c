#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const char *str1 = *(const char * const *)a;
    const char *str2 = *(const char * const *)b;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char concat1[32];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char concat2[32];
    
    snprintf(concat1, sizeof(concat1), "%s%s", str1, str2);
    snprintf(concat2, sizeof(concat2), "%s%s", str2, str1);
    
    return strcmp(concat2, concat1);
}

void printLargestNumber(const int *arr, size_t n) {
    if (!arr || n == 0) {
        return;
    }
    
    char **strArr = (char **)malloc(n * sizeof(char *));
    if (!strArr) {
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; i < n; i++) {
        strArr[i] = (char *)malloc(12 * sizeof(char));
        if (!strArr[i]) {
            for (size_t j = 0; j < i; j++) {
                free(strArr[j]);
            }
            free(strArr);
            exit(EXIT_FAILURE);
        }
        snprintf(strArr[i], 12, "%d", arr[i]);
    }
    
    qsort(strArr, n, sizeof(char *), compare);
    
    if (strcmp(strArr[0], "0") == 0) {
        printf("0\n");
    } else {
        for (size_t i = 0; i < n; i++) {
            printf("%s", strArr[i]);
        }
        printf("\n");
    }
    
    for (size_t i = 0; i < n; i++) {
        free(strArr[i]);
    }
    free(strArr);
}

int main(void) {
    int arr[] = {3, 30, 34, 5, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    
    printLargestNumber(arr, n);
    
    return EXIT_SUCCESS;
}