#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'src' can be declared as pointer to const [constParameterPointer]
 */
int filter_odd(int *src, size_t src_len, int **dst, size_t *dst_len) {
    if (src == NULL || dst == NULL || dst_len == NULL) {
        return -1;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] % 2 != 0) {
            count++;
        }
    }
    
    if (count == 0) {
        *dst = NULL;
        *dst_len = 0;
        return 0;
    }
    
    int *out = malloc(count * sizeof(int));
    if (out == NULL) {
        return -1;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < src_len; i++) {
        if (src[i] % 2 != 0) {
            out[j++] = src[i];
        }
    }
    
    *dst = out;
    *dst_len = count;
    return 0;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    int *odd_arr = NULL;
    size_t odd_len = 0;
    
    int ret = filter_odd(arr, arr_len, &odd_arr, &odd_len);
    
    if (ret == 0) {
        for (size_t i = 0; i < odd_len; i++) {
            printf("%d ", odd_arr[i]);
        }
        printf("\n");
        free(odd_arr);
    }
    
    return 0;
}