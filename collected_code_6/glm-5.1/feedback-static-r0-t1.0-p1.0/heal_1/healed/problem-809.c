#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check_tuples(const int *tuple1, const int *tuple2, size_t size) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; i++) {
        if (tuple2[i] >= tuple1[i]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int t1_1[] = {5, 10, 15};
    int t2_1[] = {2, 5, 8};
    size_t size1 = sizeof(t1_1) / sizeof(t1_1[0]);

    bool result1 = check_tuples(t1_1, t2_1, size1);
    printf("%d\n", result1);

    int t1_2[] = {5, 10, 15};
    int t2_2[] = {6, 5, 8};
    size_t size2 = sizeof(t1_2) / sizeof(t1_2[0]);

    bool result2 = check_tuples(t1_2, t2_2, size2);
    printf("%d\n", result2);

    bool result3 = check_tuples(NULL, t2_2, size2);
    printf("%d\n", result3);

    return 0;
}