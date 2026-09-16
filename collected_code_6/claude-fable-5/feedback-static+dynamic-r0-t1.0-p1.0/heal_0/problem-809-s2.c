#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool check_smaller(const int *tup1, const int *tup2, size_t len)
{
    size_t i;

    if (tup1 == NULL || tup2 == NULL || len == 0U) {
        return false;
    }

    for (i = 0U; i < len; i++) {
        if (tup2[i] >= tup1[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int first[] = {10, 4, 5};
    int second[] = {13, 5, 18};
    int third[] = {1, 2, 3};
    size_t len1 = sizeof(first) / sizeof(first[0]);

    if (check_smaller(first, second, len1)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    if (check_smaller(first, third, len1)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}