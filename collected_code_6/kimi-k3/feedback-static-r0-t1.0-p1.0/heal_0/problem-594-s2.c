#include <stdio.h>
#include <stdlib.h>

int find_difference(int *list, int size)
{
    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;
    int i;

    if (list == NULL || size <= 0) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (list[i] % 2 == 0 && !even_found) {
            first_even = list[i];
            even_found = 1;
        } else if (list[i] % 2 != 0 && !odd_found) {
            first_odd = list[i];
            odd_found = 1;
        }

        if (even_found && odd_found) {
            break;
        }
    }

    if (!even_found || !odd_found) {
        return 0;
    }

    return first_even - first_odd;
}

int main(void)
{
    int list[] = {1, 3, 5, 2, 4, 6};
    int size = sizeof(list) / sizeof(list[0]);
    int result;

    result = find_difference(list, size);
    printf("Difference: %d\n", result);

    return 0;
}