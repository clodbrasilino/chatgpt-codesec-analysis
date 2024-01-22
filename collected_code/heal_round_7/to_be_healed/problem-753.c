#include <stdio.h>
#include <string.h>

#define MAX_NAME_SIZE 51

struct Tuple {
    int number;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char name[MAX_NAME_SIZE];
};

void swap(struct Tuple* a, struct Tuple* b) {
    struct Tuple temp;

    temp.number = a->number;
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(temp.name, a->name, MAX_NAME_SIZE);
    temp.name[MAX_NAME_SIZE - 1] = '\0';

    a->number = b->number;
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(a->name, b->name, MAX_NAME_SIZE);
    a->name[MAX_NAME_SIZE - 1] = '\0';

    b->number = temp.number;
    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(b->name, temp.name, MAX_NAME_SIZE);
    b->name[MAX_NAME_SIZE - 1] = '\0';
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