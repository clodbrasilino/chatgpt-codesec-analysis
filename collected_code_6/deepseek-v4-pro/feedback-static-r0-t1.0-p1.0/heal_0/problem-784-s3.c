#include <stdio.h>
#include <stdlib.h>

int product_of_first_even_and_odd(int *arr, int size) {
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    if (arr == NULL || size <= 0) {
        return 0;
    }

    for (int i = 0; i < size; i++) {
        if (!even_found && arr[i] % 2 == 0) {
            first_even = arr[i];
            even_found = 1;
        }
        if (!odd_found && arr[i] % 2 != 0) {
            first_odd = arr[i];
            odd_found = 1;
        }
        if (even_found && odd_found) {
            break;
        }
    }

    if (!even_found || !odd_found) {
        return 0;
    }

    return first_even * first_odd;
}

int main(void) {
    int list1[] = {3, 5, 2, 7, 8};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = product_of_first_even_and_odd(list1, size1);
    printf("Product: %d\n", result1);

    int list2[] = {2, 4, 6, 8};
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = product_of_first_even_and_odd(list2, size2);
    printf("Product: %d\n", result2);

    int list3[] = {1, 3, 5, 7};
    int size3 = sizeof(list3) / sizeof(list3[0]);
    int result3 = product_of_first_even_and_odd(list3, size3);
    printf("Product: %d\n", result3);

    int *list4 = NULL;
    int size4 = 5;
    int result4 = product_of_first_even_and_odd(list4, size4);
    printf("Product: %d\n", result4);

    int list5[] = {10, 3, 4, 5};
    int size5 = sizeof(list5) / sizeof(list5[0]);
    int result5 = product_of_first_even_and_odd(list5, size5);
    printf("Product: %d\n", result5);

    return 0;
}