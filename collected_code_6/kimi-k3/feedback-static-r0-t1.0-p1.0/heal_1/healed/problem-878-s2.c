#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool check_tuple_size(const int *tuple, int size, int k) {
    if (tuple == NULL || size < 0) {
        return false;
    }
    return size == k;
}

int main(void) {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int k = 5;
    
    if (check_tuple_size(tuple, size, k)) {
        printf("Tuple contains only %d elements\n", k);
    } else {
        printf("Tuple does not contain only %d elements\n", k);
    }
    
    return 0;
}