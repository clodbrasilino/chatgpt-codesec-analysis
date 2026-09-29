#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long tuple_to_int(const unsigned int *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return 0;
    }

    unsigned long long result = 0;
    for (size_t i = 0; i < size; i++) {
        unsigned int current = tuple[i];
        unsigned int temp = current;
        unsigned long long multiplier = 1;
        
        if (current == 0) {
            multiplier = 10;
        } else {
            while (temp > 0) {
                multiplier *= 10;
                temp /= 10;
            }
        }
        
        if (result > (ULLONG_MAX - current) / multiplier) {
            return 0; 
        }
        
        result = result * multiplier + current;
    }
    
    return result;
}

int main(void) {
    unsigned int tuple1[] = {1, 2, 3};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    unsigned long long res1 = tuple_to_int(tuple1, size1);
    printf("%llu\n", res1);

    unsigned int tuple2[] = {15, 20, 3};
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    unsigned long long res2 = tuple_to_int(tuple2, size2);
    printf("%llu\n", res2);

    return 0;
}