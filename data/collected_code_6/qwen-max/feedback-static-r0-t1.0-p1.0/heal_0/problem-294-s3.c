#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void *value;
    int type; // 0 for int, 1 for float, 2 for other
} HeteroElement;

int compareInt(void *a, void *b) {
    return *(int *)a - *(int *)b;
}

int compareFloat(void *a, void *b) {
    float fa = *(float *)a;
    float fb = *(float *)b;
    if (fa > fb) return 1;
    else if (fa < fb) return -1;
    else return 0;
}

void *findMaxValue(HeteroElement *list, size_t length) {
    if (length == 0) return NULL;
    
    void *maxValue = list[0].value;
    int maxType = list[0].type;

    for (size_t i = 1; i < length; ++i) {
        void *currentValue = list[i].value;
        int currentType = list[i].type;

        if (maxType == currentType) {
            switch (maxType) {
                case 0:
                    if (compareInt(maxValue, currentValue) < 0) {
                        maxValue = currentValue;
                    }
                    break;
                case 1:
                    if (compareFloat(maxValue, currentValue) < 0) {
                        maxValue = currentValue;
                    }
                    break;
                default:
                    // Handle other types if necessary
                    break;
            }
        } else {
            // If types are different, handle as needed (e.g., prioritize one type over another)
            // For simplicity, prioritize the first type encountered
            continue;
        }
    }

    return maxValue;
}

int main() {
    HeteroElement list[] = {
        { .value = (void *)(int[]){10}, .type = 0 },
        { .value = (void *)(float[]){3.5}, .type = 1 },
        { .value = (void *)(int[]){20}, .type = 0 },
        { .value = (void *)(float[]){6.7}, .type = 1 },
        { .value = (void *)(char[]){'A'}, .type = 2 }
    };

    size_t length = sizeof(list) / sizeof(list[0]);
    void *maxValue = findMaxValue(list, length);

    if (maxValue != NULL) {
        if (list[0].type == 0) {
            printf("Max Value: %d\n", *(int *)maxValue);
        } else if (list[0].type == 1) {
            printf("Max Value: %f\n", *(float *)maxValue);
        } else {
            // Handle other types if necessary
            printf("Max Value: (other type)\n");
        }
    } else {
        printf("List is empty.\n");
    }

    return 0;
}