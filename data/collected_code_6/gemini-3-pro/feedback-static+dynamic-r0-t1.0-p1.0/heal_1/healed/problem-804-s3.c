#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_product_even(const int *numbers, size_t size) {
    if (numbers == NULL || size == 0) {
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        if (numbers[i] % 2 == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int nums1[] = {1, 3, 5, 7, 9};
    size_t size1 = sizeof(nums1) / sizeof(nums1[0]);

    int nums2[] = {1, 3, 4, 7, 9};
    size_t size2 = sizeof(nums2) / sizeof(nums2[0]);

    const int *nums3 = NULL;
    size_t size3 = 0;

    const char *bool_str[] = {"false", "true"};

    printf("Product of nums1 even? %s\n", bool_str[is_product_even(nums1, size1)]);
    printf("Product of nums2 even? %s\n", bool_str[is_product_even(nums2, size2)]);
    printf("Product of nums3 even? %s\n", bool_str[is_product_even(nums3, size3)]);

    return EXIT_SUCCESS;
}