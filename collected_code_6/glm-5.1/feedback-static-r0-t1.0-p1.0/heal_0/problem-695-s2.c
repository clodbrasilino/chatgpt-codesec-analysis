#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool check_elements_greater(Tuple t1, Tuple t2) {
    if (t1.elements == NULL || t2.elements == NULL) {
        return false;
    }

    if (t1.size != t2.size) {
        return false;
    }

    for (size_t i = 0; i < t2.size; i++) {
        if (t2.elements[i] <= t1.elements[i]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {2, 3, 4, 5};

    Tuple t1 = {arr1, 4};
    Tuple t2 = {arr2, 4};

    bool result = check_elements_greater(t1, t2);
    printf("%d\n", result);

    return 0;
}