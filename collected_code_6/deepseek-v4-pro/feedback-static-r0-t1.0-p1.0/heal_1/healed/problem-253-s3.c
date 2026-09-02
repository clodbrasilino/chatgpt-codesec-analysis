#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

int count_integers(const int *list, size_t size) {
    if (list == NULL && size > 0) {
        return -1;
    }
    if (size > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    return (int)size;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {10, 20, 30};
    int *empty_list = NULL;
    
    printf("Count of list1: %d\n", count_integers(list1, sizeof(list1) / sizeof(list1[0])));
    printf("Count of list2: %d\n", count_integers(list2, sizeof(list2) / sizeof(list2[0])));
    printf("Count of empty_list: %d\n", count_integers(empty_list, 0));
    printf("Count of NULL with size: %d\n", count_integers(NULL, 5));
    
    return 0;
}