#include <stdio.h>
#include <stdlib.h>

long long calculate_product(const int *tuple, size_t size) {
    if (tuple == NULL || size == 0) {
        return 0;
    }

    long long product = 1;
    for (size_t i = 0; i < size; ++i) {
        product *= tuple[i];
    }

    return product;
}

int main(void) {
    int my_tuple[] = {2, 3, 4, 5};
    size_t tuple_size = sizeof(my_tuple) / sizeof(my_tuple[0]);

    long long result = calculate_product(my_tuple, tuple_size);

    printf("%lld\n", result);

    return 0;
}