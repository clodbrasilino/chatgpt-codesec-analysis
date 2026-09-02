#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Element {
    int type; // 1 for int, 2 for float
    union {
        int i;
        float f;
    } value;
} Element;

float findMaxValue(const Element *list, size_t length) {
    if (length == 0) return -INFINITY;

    float maxVal = -INFINITY;
    for (size_t i = 0; i < length; ++i) {
        if (list[i].type == 1) {
            if (list[i].value.i > maxVal) maxVal = list[i].value.i;
        } else if (list[i].type == 2) {
            if (list[i].value.f > maxVal) maxVal = list[i].value.f;
        }
    }
    return maxVal;
}

int main() {
    Element elements[] = {
        {1, .value.i = 10},
        {2, .value.f = 20.5f},
        {1, .value.i = 30},
        {2, .value.f = 15.8f}
    };
    size_t length = sizeof(elements) / sizeof(elements[0]);

    float maxVal = findMaxValue(elements, length);
    printf("Maximum value: %f\n", maxVal);

    return 0;
}