#include <stdio.h>
#include <stdbool.h>

bool check_elements_greater_than_corresponding_first(const int *tuple1, const int *tuple2, size_t size) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (tuple2[i] <= tuple1[i]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const int tuple1[] = {1, 2, 3, 4, 5};
    const int tuple2[] = {2, 4, 6, 8, 10};
    size_t size = sizeof(tuple1) / sizeof(tuple1[0]);
    
    bool result = check_elements_greater_than_corresponding_first(tuple1, tuple2, size);
    
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    const int tuple3[] = {1, 5, 3};
    const int tuple4[] = {2, 4, 6};
    size_t size2 = sizeof(tuple3) / sizeof(tuple3[0]);
    
    result = check_elements_greater_than_corresponding_first(tuple3, tuple4, size2);
    
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}