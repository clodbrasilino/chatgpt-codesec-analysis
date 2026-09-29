#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int key;
    int *values;
    int count;
} Group;

Group* groupBySecond(Tuple* tuples, int size, int* groupSize) {
    Group* groups = (Group*)malloc(size * sizeof(Group));

    if (!groups) return NULL;

    *groupSize = 0;

    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < *groupSize; j++) {
            if (groups[j].key == tuples[i].second) {
                groups[j].values[groups[j].count++] = tuples[i].first;
                found = 1;
                break;
            }
        }
        if (!found) {
            groups[*groupSize].key = tuples[i].second;
            groups[*groupSize].values = (int*)malloc(size * sizeof(int));
            
            if (!groups[*groupSize].values) {
                for (int k = 0; k < *groupSize; k++)
                    free(groups[k].values);
                free(groups);
                return NULL;
            }

            groups[*groupSize].values[0] = tuples[i].first;
            groups[*groupSize].count = 1;
            (*groupSize)++;
        }
    }

    return groups;
}

int main() {
    Tuple tuples[] = {{1, 2}, {2, 3}, {3, 2}, {4, 3}, {5, 2}};
    int size = sizeof(tuples) / sizeof(Tuple);
    int groupSize;

    Group* groups = groupBySecond(tuples, size, &groupSize);

    if (!groups) return 1;

    for (int i = 0; i < groupSize; i++) {
        printf("Group %d: ", groups[i].key);
        for (int j = 0; j < groups[i].count; j++) {
            printf("%d ", groups[i].values[j]);
        }
        printf("\n");
    }

    for (int i = 0; i < groupSize; i++) {
        free(groups[i].values);
    }
    free(groups);

    return 0;
}