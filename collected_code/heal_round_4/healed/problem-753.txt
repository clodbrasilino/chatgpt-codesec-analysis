#include <stdio.h>
#include <string.h>

#define MAX_NAME_SIZE 51

struct Tuple {
    int number;
    char name[MAX_NAME_SIZE];
};

void swap(struct Tuple* a, struct Tuple* b) {
    struct Tuple temp = {0, ""};
    memcpy(&temp, a, sizeof(struct Tuple));
    memcpy(a, b, sizeof(struct Tuple));
    memcpy(b, &temp, sizeof(struct Tuple));  
}

void findMinKRecords(struct Tuple tupleList[], int n, int k) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tupleList[j].number > tupleList[j + 1].number) {
                swap(&tupleList[j], &tupleList[j + 1]);
            }
        }
    }

    for (int i = 0; i < k && i < n; i++) {
        printf("%d, %s\n", tupleList[i].number, tupleList[i].name);
    }
}

int main() {
    struct Tuple tupleList[] = {
        {25, "John"},
        {12, "Jane"},
        {7, "Mike"},
        {18, "Sarah"},
        {30, "David"},
    };
    int n = sizeof(tupleList) / sizeof(tupleList[0]);
    int k = 3;

    findMinKRecords(tupleList, n, k);

    return 0;
}