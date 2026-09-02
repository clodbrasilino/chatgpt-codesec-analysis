#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int list_to_int(const int *list, size_t count, long *result) {
    long value = 0;
    size_t i;
    int num;
    
    if (list == NULL || result == NULL || count == 0) {
        errno = EINVAL;
        return -1;
    }
    
    for (i = 0; i < count; i++) {
        num = list[i];
        
        if (num < 0) {
            errno = EINVAL;
            return -1;
        }
        
        if (value > (LONG_MAX - num) / 10) {
            errno = ERANGE;
            return -1;
        }
        
        value = value * 10 + num;
    }
    
    if (value > INT_MAX) {
        errno = ERANGE;
        return -1;
    }
    
    *result = value;
    return 0;
}

int main(void) {
    int numbers[] = {6, 2, 1, 4, 5};
    long result;
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    if (list_to_int(numbers, count, &result) == 0) {
        printf("Result: %ld\n", result);
    } else {
        perror("Conversion failed");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}