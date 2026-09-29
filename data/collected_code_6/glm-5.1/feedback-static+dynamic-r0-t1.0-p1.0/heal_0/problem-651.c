#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_subset(int *tuple1, size_t size1, int *tuple2, size_t size2) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return false;
    }

    for (size_t i = 0; i < size1; i++) {
        bool found = false;
        for (size_t j = 0; j < size2; j++) {
            if (tuple1[i] == tuple2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int t1[] = {1, 2, 3};
    int t2[] = {4, 5, 1, 2, 3, 6};
    
    bool result = is_subset(t1, sizeof(t1) / sizeof(t1[0]), t2, sizeof(t2) / sizeof(t2[0]));
    
    printf("%d\n", result);

    int t3[] = {1, 2, 7};
    int t4[] = {4, 5, 1, 2, 3, 6};
    
    result = is_subset(t3, sizeof(t3) / sizeof(t3[0]), t4, sizeof(t4) / sizeof(t4[0]));
    
    printf("%d\n", result);

    return 0;
}