#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int count;
} Record;

int compare(const void *a, const void *b) {
    return ((Record *)a)->count - ((Record *)b)->count;
}

int checkOccurrences(Record *records, int n) {
    qsort(records, n, sizeof(Record), compare);
    int current_count = records[0].count;
    int group_size = 1;
    for (int i = 1; i < n; i++) {
        if (records[i].count == current_count) {
            group_size++;
        } else {
            if (group_size > 1) {
                return 1;
            }
            group_size = 1;
            current_count = records[i].count;
        }
    }
    if (group_size > 1) {
        return 1;
    }
    return 0;
}

int main() {
    Record records[] = {{1, 3}, {2, 3}, {3, 2}, {4, 2}, {5, 1}};
    int n = sizeof(records) / sizeof(records[0]);
    int result = checkOccurrences(records, n);
    if (result) {
        puts("There are records with the same occurrences.");
    } else {
        puts("All records have unique occurrences.");
    }
    return 0;
}