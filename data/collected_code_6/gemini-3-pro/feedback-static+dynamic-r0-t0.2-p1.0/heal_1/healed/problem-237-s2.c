#include <stdio.h>
#include <stdlib.h>

typedef struct {
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

    Frequency* freqs = (Frequency*)malloc(num_records * sizeof(Frequency));
    if (freqs == NULL) {
        return;
    }

    int num_freqs = 0;

    for (int i = 0; i < num_records; i++) {
        int found = 0;
        for (int j = 0; j < num_freqs; j++) {
            if (freqs[j].count == records[i].count) {
                freqs[j].occurrences++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freqs[num_freqs].count = records[i].count;
            freqs[num_freqs].occurrences = 1;
            num_freqs++;
        }
    }

    for (int i = 0; i < num_freqs; i++) {
        if (freqs[i].occurrences > 1) {
            printf("Records with count %d occur %d times.\n", freqs[i].count, freqs[i].occurrences);
        }
    }

    free(freqs);
}

int main() {
    Record records[] = {
        {5},
        {3},
        {5},
        {2},
        {3},
        {5}
    };
    int num_records = sizeof(records) / sizeof(records[0]);

    check_occurrences(records, num_records);

    return 0;
}