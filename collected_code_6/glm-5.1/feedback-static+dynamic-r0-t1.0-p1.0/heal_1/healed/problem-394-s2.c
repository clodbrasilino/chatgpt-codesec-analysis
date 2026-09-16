#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_distinct(const int *tuple, size_t size) {
    if (tuple == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            if (tuple[i] == tuple[j]) {
                return false;
            }
        }
    }
    
    return true;
}

int main(void) {
    int t1[] = {1, 2, 3, 4, 5};
    size_t s1 = sizeof(t1) / sizeof(t1[0]);
    
    int t2[] = {1, 2, 3, 2, 5};
    size_t s2 = sizeof(t2) / sizeof(t2[0]);
    
    int t3[] = {7};
    size_t s3 = sizeof(t3) / sizeof(t3[0]);
    
    int *t4 = NULL;
    size_t s4 = 0;
    
    printf("%d\n", is_distinct(t1, s1));
    printf("%d\n", is_distinct(t2, s2));
    printf("%d\n", is_distinct(t3, s3));
    printf("%d\n", is_distinct(t4, s4));
    
    return 0;
}