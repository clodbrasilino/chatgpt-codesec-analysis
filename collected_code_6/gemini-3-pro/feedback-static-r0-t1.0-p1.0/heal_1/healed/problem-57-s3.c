#if defined(__linux__) || defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    
    size_t len1 = strnlen(str1, 12);
    size_t len2 = strnlen(str2, 12);
    size_t total_size = len1 + len2 + 1;
    
    char *concat1 = (char *)malloc(total_size);
    char *concat2 = (char *)malloc(total_size);
    
    if (!concat1 || !concat2) {
        free(concat1);
        free(concat2);
        exit(EXIT_FAILURE);
    }
    
    snprintf(concat1, total_size, "%s%s", str1, str2);
    snprintf(concat2, total_size, "%s%s", str2, str1);
    
    int result = strcmp(concat2, concat1);
    
    free(concat1);
    free(concat2);
    
    return result;
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