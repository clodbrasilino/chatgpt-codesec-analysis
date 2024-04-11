#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int count;
} Record;

int findOccurrences(Record records[], int n, int x) {
    int i;
    for (i = 0; i < n; i++) {
        if (records[i].count == x) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Record records[] = {{1, 3}, {2, 2}, {3, 1}, {4, 3}, {5, 2}};
    int n = sizeof(records) / sizeof(records[0]);
    int x = 2;

    if (findOccurrences(records, n, x)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}