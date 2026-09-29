#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int key;
    int value;
};

struct Record {
    int key;
    int count;
};

int checkOccurrences(struct Tuple tuples[], int tupleSize, struct Record records[], int recordSize) {
    int i, j, count;

    for(i = 0; i < recordSize; i++) {
        count = 0;
        for(j = 0; j < tupleSize; j++) {
            if(records[i].key == tuples[j].key) {
                count++;
            }
        }
        if(count != records[i].count) {
            return 0;
        }
    }
    return 1;
}

int main() {
    struct Tuple tuples[] = {{1, 2}, {2, 3}, {1, 4}, {2, 5}, {1, 6}};
    struct Record records[] = {{1, 3}, {2, 2}};

    int tupleSize = sizeof(tuples) / sizeof(tuples[0]);
    int recordSize = sizeof(records) / sizeof(records[0]);

    int result = checkOccurrences(tuples, tupleSize, records, recordSize);

    if(result == 1) {
        printf("All records occur similar times in the tuples.\n");
    } else {
        printf("All records do not occur similar times in the tuples.\n");
    }

    return 0;
}