#include <stdio.h>
#include <stdlib.h>

int check_tuples(const int *t1, const int *t2, size_t size) {
    if (t1 == NULL || t2 == NULL || size == 0) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        if (t2[i] <= t1[i]) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    size_t size = 5;
    int *t1 = malloc(size * sizeof(int));
    int *t2 = malloc(size * sizeof(int));
    if (t1 == NULL || t2 == NULL) {
        free(t1);
        free(t2);
        return 1;
    }
    t1[0] = 1; t1[1] = 2; t1[2] = 3; t1[3] = 4; t1[4] = 5;
    t2[0] = 2; t2[1] = 3; t2[2] = 4; t2[3] = 5; t2[4] = 6;
    int result = check_tuples(t1, t2, size);
    printf("%d\n", result);
    free(t1);
    free(t2);
    return 0;
}