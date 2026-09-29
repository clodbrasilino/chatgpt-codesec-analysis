#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'outer' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'inner' can be declared as pointer to const [constParameterPointer]
 */
bool is_subarray(int *outer, size_t outer_size, int *inner, size_t inner_size) {
    if (inner_size > outer_size) return false;
    if (inner_size == 0) return true;
    
    for (size_t i = 0; i <= outer_size - inner_size; i++) {
        size_t j = 0;
        while (j < inner_size && outer[i + j] == inner[j]) {
            j++;
        }
        if (j == inner_size) return true;
    }
    return false;
}

int main(void) {
    int outer[] = {1, 2, 3, 4, 5, 6, 7};
    int inner1[] = {3, 4, 5};
    int inner2[] = {4, 5, 8};
    int inner3[] = {1, 2};
    int inner4[] = {6, 7};
    int inner5[] = {1, 3};
    
    printf("inner1 is subarray: %s\n", is_subarray(outer, sizeof(outer)/sizeof(outer[0]), inner1, sizeof(inner1)/sizeof(inner1[0])) ? "true" : "false");
    printf("inner2 is subarray: %s\n", is_subarray(outer, sizeof(outer)/sizeof(outer[0]), inner2, sizeof(inner2)/sizeof(inner2[0])) ? "true" : "false");
    printf("inner3 is subarray: %s\n", is_subarray(outer, sizeof(outer)/sizeof(outer[0]), inner3, sizeof(inner3)/sizeof(inner3[0])) ? "true" : "false");
    printf("inner4 is subarray: %s\n", is_subarray(outer, sizeof(outer)/sizeof(outer[0]), inner4, sizeof(inner4)/sizeof(inner4[0])) ? "true" : "false");
    printf("inner5 is subarray: %s\n", is_subarray(outer, sizeof(outer)/sizeof(outer[0]), inner5, sizeof(inner5)/sizeof(inner5[0])) ? "true" : "false");
    
    return 0;
}