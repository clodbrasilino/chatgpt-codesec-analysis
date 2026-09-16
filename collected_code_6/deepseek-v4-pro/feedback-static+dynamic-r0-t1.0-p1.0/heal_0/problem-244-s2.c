#include <stdio.h>
#include <math.h>
#include <stdint.h>

int64_t next_perfect_square(int64_t num) {
    if (num < 0) {
        return 0;
    }
    
    int64_t root = (int64_t)sqrt((double)num);
    
    if (root * root <= num) {
        root++;
    }
    
    if (root > 3037000499LL) {
        return -1;
    }
    
    return root * root;
}

int main(void) {
    int64_t test_values[] = {
        -5, 0, 1, 2, 3, 4, 15, 16, 17, 100, 1000, 9223372030926249000LL
    };
    
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        int64_t result = next_perfect_square(test_values[i]);
        if (result != -1) {
            printf("next_perfect_square(%lld) = %lld\n", 
                   (long long)test_values[i], (long long)result);
        } else {
            printf("next_perfect_square(%lld) = overflow\n", 
                   (long long)test_values[i]);
        }
    }
    
    return 0;
}