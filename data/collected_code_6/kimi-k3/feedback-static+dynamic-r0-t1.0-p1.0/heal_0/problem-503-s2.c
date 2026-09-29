#include <stdio.h>
#include <stdlib.h>

long long add_consecutive(const int *list, size_t size)
{
    long long sum = 0;
    size_t i;

    if (list == NULL || size == 0) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        sum += list[i];
    }

    return sum;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    long long result;

    result = add_consecutive(list, size);
    printf("Sum: %lld\n", result);

    return 0;
}