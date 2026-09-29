#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return *(const char *)b - *(const char *)a;
}

void find_largest_number(const int *digits, int count, char *result, size_t result_size) {
    if (digits == NULL || result == NULL || count <= 0) {
        if (result != NULL && result_size > 0) {
            result[0] = '\0';
        }
        return;
    }
    
    if ((size_t)count + 1 > result_size) {
        if (result_size > 0) {
            result[0] = '\0';
        }
        return;
    }
    
    char *temp = (char *)malloc(count + 1);
    if (temp == NULL) {
        result[0] = '\0';
        return;
    }
    
    for (int i = 0; i < count; i++) {
        temp[i] = digits[i] + '0';
    }
    temp[count] = '\0';
    
    qsort(temp, count, sizeof(char), compare);
    
    memcpy(result, temp, count + 1);
    
    free(temp);
}

int main() {
    int digits[] = {8, 6, 0, 1, 4};
    size_t count = sizeof(digits) / sizeof(digits[0]);
    
    char *result = (char *)malloc(count + 1);
    if (result == NULL) {
        return EXIT_FAILURE;
    }
    
    find_largest_number(digits, count, result, count + 1);
    
    printf("%s\n", result);
    
    free(result);
    
    return EXIT_SUCCESS;
}