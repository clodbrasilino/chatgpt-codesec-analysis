#include <stdio.h>
#include <stdbool.h>

bool check_elements_smaller(const int* tuple1, const int* tuple2, size_t size) {
    if (tuple1 == NULL || tuple2 == NULL) {
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        if (tuple2[i] >= tuple1[i]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const int tuple1[] = {5, 8, 12, 20};
    const int tuple2[] = {3, 7, 10, 15};
    size_t size = sizeof(tuple1) / sizeof(tuple1[0]);

    bool result = check_elements_smaller(tuple1, tuple2, size);

    if (result) {
        printf("All elements in the second tuple are smaller than corresponding elements in the first tuple.\n");
    } else {
        printf("Not all elements in the second tuple are smaller than corresponding elements in the first tuple.\n");
    }

    return 0;
}