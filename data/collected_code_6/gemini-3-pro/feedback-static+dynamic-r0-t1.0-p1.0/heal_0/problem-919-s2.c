#include <stdio.h>
#include <stdlib.h>

long long multiply_list(const int *list, size_t size) {
    if (list == NULL || size == 0) {
        return 0;
    }

    long long result = 1;
    for (size_t i = 0; i < size; ++i) {
        result *= list[i];
    }

    return result;
}

int main(void) {
    int my_list[] = {2, 3, 4, 5};
    size_t size = sizeof(my_list) / sizeof(my_list[0]);

    long long result = multiply_list(my_list, size);

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}