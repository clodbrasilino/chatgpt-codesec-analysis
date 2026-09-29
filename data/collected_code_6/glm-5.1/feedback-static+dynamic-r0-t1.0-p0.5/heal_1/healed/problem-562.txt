#include <stdio.h>
#include <stdlib.h>

int max_length(int * const *lists, const int *sizes, int count) {
    int max_len = 0;
    if (lists == NULL || sizes == NULL || count <= 0) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        if (lists[i] != NULL && sizes[i] > max_len) {
            max_len = sizes[i];
        }
    }
    return max_len;
}

int main(void) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6, 7, 8};
    int c[] = {9, 10};
    
    int *lists[] = {a, b, c};
    int sizes[] = {sizeof(a) / sizeof(a[0]), sizeof(b) / sizeof(b[0]), sizeof(c) / sizeof(c[0])};
    int count = 3;
    
    int result = max_length(lists, sizes, count);
    printf("%d\n", result);
    
    return 0;
}