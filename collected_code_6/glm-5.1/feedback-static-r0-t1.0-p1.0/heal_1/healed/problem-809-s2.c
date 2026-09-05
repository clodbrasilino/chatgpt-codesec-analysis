#include <stdio.h>
#include <stdlib.h>

int check_tuples(const int *t1, const int *t2, size_t size) {
    int status = 1;
    if (t1 == NULL || t2 == NULL) {
        status = 0;
    } else {
        for (size_t i = 0; i < size; i++) {
            if (t2[i] >= t1[i]) {
                status = 0;
                break;
            }
        }
    }
    return status;
}

int main(void) {
    const int t1[] = {10, 20, 30, 40};
    const int t2[] = {1, 2, 3, 4};
    size_t size = sizeof(t1) / sizeof(t1[0]);

    int result = check_tuples(t1, t2, size);
    printf("%d\n", result);

    return 0;
}