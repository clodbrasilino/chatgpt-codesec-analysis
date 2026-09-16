#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return *(const char *)b - *(const char *)a;
}

void find_largest_number(const int *digits, int count, char *result) {
    if (digits == NULL || result == NULL || count <= 0) {
        if (result != NULL) {
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
    int count = sizeof(digits) / sizeof(digits[0]);
    
    char *result = (char *)malloc(count + 1);
    if (result == NULL) {
        return EXIT_FAILURE;
    }
    
    find_largest_number(digits, count, result);
    
    printf("%s\n", result);
    
    free(result);
    
    return EXIT_SUCCESS;
}