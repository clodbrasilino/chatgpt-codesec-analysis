#include <stdio.h>
#include <stdlib.h>

int check_tuple_greater(const int *t1, const int *t2, size_t size) {
    if (t1 == NULL || t2 == NULL) {
        return 0;
    }
    if (size == 0) {
        return 1;
    }
    for (size_t i = 0; i < size; i++) {
        if (t2[i] <= t1[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int pass = 1;

    const int t1_0[] = {1, 2, 3};
    const int t2_0[] = {2, 3, 4};
    if (check_tuple_greater(t1_0, t2_0, sizeof(t1_0) / sizeof(t1_0[0])) != 1) pass = 0;

    const int t1_1[] = {1, 2, 3};
    const int t2_1[] = {1, 3, 4};
    if (check_tuple_greater(t1_1, t2_1, sizeof(t1_1) / sizeof(t1_1[0])) != 0) pass = 0;

    const int t1_2[] = {1, 2, 3};
    const int t2_2[] = {2, 1, 4};
    if (check_tuple_greater(t1_2, t2_2, sizeof(t1_2) / sizeof(t1_2[0])) != 0) pass = 0;

    printf("%s\n", pass ? "True" : "False");

    return 0;
}