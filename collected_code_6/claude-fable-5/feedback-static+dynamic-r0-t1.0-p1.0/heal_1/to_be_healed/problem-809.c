#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_smaller(const int *tup1, const int *tup2, size_t len)
{
    size_t i;

    if (tup1 == NULL || tup2 == NULL) {
        return false;
    }

    for (i = 0; i < len; i++) {
        if (tup2[i] >= tup1[i]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int first[] = {10, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'second' can be declared as const array [constVariable]
     */
    int second[] = {2, 3, 4};
    /* Possible weaknesses found:
     *  Variable 'third' can be declared as const array [constVariable]
     */
    int third[] = {12, 3, 4};
    size_t len = sizeof(first) / sizeof(first[0]);
    bool result;

    result = check_smaller(first, second, len);
    if (printf("%s\n", result ? "true" : "false") < 0) {
        return 1;
    }

    result = check_smaller(first, third, len);
    if (printf("%s\n", result ? "true" : "false") < 0) {
        return 1;
    }

    return 0;
}