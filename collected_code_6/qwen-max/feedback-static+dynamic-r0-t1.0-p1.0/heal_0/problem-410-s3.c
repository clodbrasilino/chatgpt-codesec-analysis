#include <stdio.h>
#include <limits.h>

typedef enum { INT, FLOAT } ElementType;

typedef struct {
    ElementType type;
    union {
        int iValue;
        float fValue;
    };
} Element;

int compareElements(const Element *a, const Element *b) {
    if (a->type == INT && b->type == INT) {
        return a->iValue - b->iValue;
    } else if (a->type == FLOAT && b->type == FLOAT) {
        return a->fValue < b->fValue ? -1 : (a->fValue > b->fValue ? 1 : 0);
    }
    return 0;
}

Element* findMinElement(Element *list, size_t len) {
    if (len == 0) return NULL;
    Element *min = &list[0];
    for (size_t i = 1; i < len; i++) {
        if (compareElements(&list[i], min) < 0) {
            min = &list[i];
        }
    }
    return min;
}

int main() {
    Element list[] = {
        {INT, .iValue = 10},
        {FLOAT, .fValue = 2.3f},
        {INT, .iValue = 5},
        {FLOAT, .fValue = -4.6f}
    };

    size_t length = sizeof(list) / sizeof(list[0]);
    Element *min = findMinElement(list, length);

    if (min != NULL) {
        if (min->type == INT) {
            printf("Minimum value: %d\n", min->iValue);
        } else if (min->type == FLOAT) {
            printf("Minimum value: %.2f\n", min->fValue);
        }
    } else {
        printf("List is empty\n");
    }

    return 0;
}