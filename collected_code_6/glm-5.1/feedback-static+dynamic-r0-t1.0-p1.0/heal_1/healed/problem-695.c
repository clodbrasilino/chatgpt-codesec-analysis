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
    int t1[] = {1, 2, 3, 4, 5};
    int t2[] = {2, 3, 4, 5, 6};
    size_t size = sizeof(t1) / sizeof(t1[0]);

    int result = check_tuple_greater(t1, t2, size);
    printf("%d\n", result);

    return 0;
}