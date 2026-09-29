#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcmp'
  */

typedef struct {
    int type;
    union {
        int intVal;
        float floatVal;
        char* strVal;
    } value;
} HeterogeneousElement;

int compareInts(const void* a, const void* b) {
    return (*(HeterogeneousElement*)a).value.intVal - (*(HeterogeneousElement*)b).value.intVal;
}

int compareFloats(const void* a, const void* b) {
    if ((*(HeterogeneousElement*)a).value.floatVal < (*(HeterogeneousElement*)b).value.floatVal) return -1;
    if ((*(HeterogeneousElement*)a).value.floatVal > (*(HeterogeneousElement*)b).value.floatVal) return 1;
    return 0;
}

int compareStrings(const void* a, const void* b) {
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strcmp'
     *  call to undeclared library function 'strcmp' with type 'int (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strcmp' [-Wimplicit-function-declaration]
     */
    return strcmp((*(HeterogeneousElement*)a).value.strVal, (*(HeterogeneousElement*)b).value.strVal);
}

void findMinValue(HeterogeneousElement* arr, int n, HeterogeneousElement* min) {
    *min = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i].type == min->type) {
            switch (arr[i].type) {
                case 1: 
                    if (compareInts(&arr[i], min) < 0)
                        *min = arr[i];
                    break;
                case 2: 
                    if (compareFloats(&arr[i], min) < 0)
                        *min = arr[i];
                    break;
                case 3: 
                    if (compareStrings(&arr[i], min) < 0)
                        *min = arr[i];
                    break;
            }
        }
    }
}

int main() {
    HeterogeneousElement elements[] = {
        {1, .value.intVal = 10},
        {1, .value.intVal = 5},
        {1, .value.intVal = 15},
        {2, .value.floatVal = 10.5f},
        {2, .value.floatVal = 5.5f},
        {2, .value.floatVal = 15.5f},
        {3, .value.strVal = "apple"},
        {3, .value.strVal = "banana"},
        {3, .value.strVal = "cherry"}
    };
    int n = sizeof(elements) / sizeof(elements[0]);
    HeterogeneousElement min;

    for (int i = 1; i <= 3; ++i) {
        for (int j = 0; j < n; ++j) {
            if (elements[j].type == i) {
                min.type = i;
                findMinValue(elements, n, &min);
                break;
            }
        }

        switch (min.type) {
            case 1:
                printf("Minimum Integer: %d\n", min.value.intVal);
                break;
            case 2:
                printf("Minimum Float: %.1f\n", min.value.floatVal);
                break;
            case 3:
                printf("Minimum String: %s\n", min.value.strVal);
                break;
        }
    }

    return 0;
}