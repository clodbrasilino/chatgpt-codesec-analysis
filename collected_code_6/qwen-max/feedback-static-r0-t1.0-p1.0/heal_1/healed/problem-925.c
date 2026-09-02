#include <stdio.h>
#include <stdlib.h>

long long product_of_tuple(const int *nums, int length) {
    long long product = 1;
    for (int i = 0; i < length; ++i) {
        product *= nums[i];
    }
    return product;
}

int main() {
    int nums[] = {1, 2, 3, 4, 5};
    int length = sizeof(nums) / sizeof(nums[0]);
    long long result = product_of_tuple(nums, length);
    printf("Product: %lld\n", result);
    return 0;
}