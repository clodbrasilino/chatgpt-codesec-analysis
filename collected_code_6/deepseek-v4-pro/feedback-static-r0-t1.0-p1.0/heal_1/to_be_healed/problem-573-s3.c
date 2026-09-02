#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int contains(int *arr, int size, int value) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
long long product_of_unique(int *list, int size) {
    if (list == NULL || size <= 0) {
        return 0;
    }
    
    int *unique = (int *)malloc(size * sizeof(int));
    if (unique == NULL) {
        return 0;
    }
    
    int unique_count = 0;
    
    for (int i = 0; i < size; i++) {
        if (!contains(unique, unique_count, list[i])) {
            unique[unique_count] = list[i];
            unique_count++;
        }
    }
    
    long long product = 1;
    for (int i = 0; i < unique_count; i++) {
        product *= unique[i];
    }
    
    free(unique);
    return product;
}

int main(void) {
    int list1[] = {1, 2, 3, 2, 4, 3, 5};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    
    int list2[] = {2, 2, 2, 2};
    int size2 = sizeof(list2) / sizeof(list2[0]);
    
    int list3[] = {-1, -2, -3, -2, -1};
    int size3 = sizeof(list3) / sizeof(list3[0]);
    
    int list4[] = {5};
    int size4 = sizeof(list4) / sizeof(list4[0]);
    
    printf("Product of unique numbers in list1: %lld\n", product_of_unique(list1, size1));
    printf("Product of unique numbers in list2: %lld\n", product_of_unique(list2, size2));
    printf("Product of unique numbers in list3: %lld\n", product_of_unique(list3, size3));
    printf("Product of unique numbers in list4: %lld\n", product_of_unique(list4, size4));
    
    return 0;
}