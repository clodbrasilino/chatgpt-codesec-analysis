#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int count;
} Record;

typedef struct {
    int count;
    int occurrences;
} Frequency;

void check_occurrences(Record* records, int num_records) {
    if (records == NULL || num_records <= 0) {
        return;
    }

    Frequency* frequencies = (Frequency*)calloc(num_records, sizeof(Frequency));
    if (frequencies == NULL) {
        return;
    }

    int num_frequencies = 0;

    for (int i = 0; i < num_records; i++) {
        int found = 0;
        for (int j = 0; j < num_frequencies; j++) {
            if (frequencies[j].count == records[i].count) {
                frequencies[j].occurrences++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[num_frequencies].count = records[i].count;
            frequencies[num_frequencies].occurrences = 1;
            num_frequencies++;
        }
    }

    for (int i = 0; i < num_frequencies; i++) {
        if (frequencies[i].occurrences > 1) {
            printf("Count %d occurs %d times.\n", frequencies[i].count, frequencies[i].occurrences);
        }
    }

    free(frequencies);
}

int main() {
    Record records[] = {
        {1, 5},
        {2, 3},
        {3, 5},
        {4, 2},
        {5, 3},
        {6, 5}
    };
    int num_records = sizeof(records) / sizeof(records[0]);

    check_occurrences(records, num_records);

    return 0;
}