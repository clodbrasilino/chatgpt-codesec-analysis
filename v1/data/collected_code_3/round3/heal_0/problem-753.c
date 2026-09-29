#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Record;

int compare(const void* a, const void* b) {
    Record* recordA = (Record*)a;
    Record* recordB = (Record*)b;
    return recordA->value - recordB->value;
}

void findMinKRecords(Record* records, int n, int k) {
    qsort(records, n, sizeof(Record), compare);

    for(int i = 0; i < k; i++) {
        printf("ID: %d, Value: %d\n", records[i].id, records[i].value);
    }
}

int main() {
    Record records[] = {{1, 20}, {2, 15}, {3, 30}, {4, 10}, {5, 25}};
    int n = sizeof(records) / sizeof(records[0]);
    int k = 3;

    findMinKRecords(records, n, k);

    return 0;
}