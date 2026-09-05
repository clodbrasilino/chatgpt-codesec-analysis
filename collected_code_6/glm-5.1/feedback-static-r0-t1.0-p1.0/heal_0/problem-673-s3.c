#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long list_to_single_int(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }
    
    long long result = 0;
    
    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            return 0;
        }
        
        if (result > (LLONG_MAX - list[i]) / 10) {
            return 0;
        }
        
        result = result * 10 + list[i];
    }
    
    return result;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    long long res1 = list_to_single_int(list1, size1);
    printf("%lld\n", res1);

    int list2[] = {9, 8, 7};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    long long res2 = list_to_single_int(list2, size2);
    printf("%lld\n", res2);

    int list3[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    size_t size3 = sizeof(list3) / sizeof(list3[0]);
    long long res3 = list_to_single_int(list3, size3);
    printf("%lld\n", res3);

    long long res4 = list_to_single_int(NULL, 0);
    printf("%lld\n", res4);

    return 0;
}