#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int binary_tuple_to_int(const int *tuple, size_t length) {
    int result = 0;
    for (size_t i = 0; i < length; i++) {
        if (tuple[i] != 0 && tuple[i] != 1) {
            return -1;
        }
        result = (result << 1) | tuple[i];
    }
    return result;
}

int main(void) {
    int tuple1[] = {1, 0, 1, 1};
    int tuple2[] = {1, 1, 1, 1, 1, 1, 1, 1};
    int tuple3[] = {2, 0, 1};
    int tuple4[] = {0};
    
    int result1 = binary_tuple_to_int(tuple1, sizeof(tuple1) / sizeof(tuple1[0]));
    int result2 = binary_tuple_to_int(tuple2, sizeof(tuple2) / sizeof(tuple2[0]));
    int result3 = binary_tuple_to_int(tuple3, sizeof(tuple3) / sizeof(tuple3[0]));
    int result4 = binary_tuple_to_int(tuple4, sizeof(tuple4) / sizeof(tuple4[0]));
    
    printf("Tuple1: %d\n", result1);
    printf("Tuple2: %d\n", result2);
    printf("Tuple3: %d\n", result3);
    printf("Tuple4: %d\n", result4);
    
    return 0;
}