#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int count;
} RecordCount;

typedef struct {
    int count;
    int occurrences;
} FrequencyCount;

void check_similar_occurrences(int* tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return;
    }

    RecordCount* record_counts = (RecordCount*)calloc(size, sizeof(RecordCount));
    if (record_counts == NULL) {
        return;
    }

    int unique_records = 0;
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < unique_records; j++) {
            if (record_counts[j].id == tuples[i]) {
                record_counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            record_counts[unique_records].id = tuples[i];
            record_counts[unique_records].count = 1;
            unique_records++;
        }
    }

    FrequencyCount* freq_counts = (FrequencyCount*)calloc(unique_records, sizeof(FrequencyCount));
    if (freq_counts == NULL) {
        free(record_counts);
        return;
    }

    int unique_freqs = 0;
    for (int i = 0; i < unique_records; i++) {
        int found = 0;
        for (int j = 0; j < unique_freqs; j++) {
            if (freq_counts[j].count == record_counts[i].count) {
                freq_counts[j].occurrences++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq_counts[unique_freqs].count = record_counts[i].count;
            freq_counts[unique_freqs].occurrences = 1;
            unique_freqs++;
        }
    }

    for (int i = 0; i < unique_freqs; i++) {
        if (freq_counts[i].occurrences > 1) {
            printf("Frequency %d occurs %d times.\n", freq_counts[i].count, freq_counts[i].occurrences);
        }
    }

    free(freq_counts);
    free(record_counts);
}

int main(void) {
    int tuples[] = {1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5};
    int size = sizeof(tuples) / sizeof(tuples[0]);

    check_similar_occurrences(tuples, size);

    return 0;
}