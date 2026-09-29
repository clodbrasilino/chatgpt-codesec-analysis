#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *items;
    int count;
} Tuple;

typedef struct {
    int hash;
    int frequency;
} Record;

typedef struct {
    int frequency;
    int count;
} FreqResult;

static int compute_hash(const Tuple *t) {
    int h = 0;
    for (int i = 0; i < t->count; i++) {
        h = h * 31 + t->items[i];
    }
    return h;
}

int check_similar_occurrences(Tuple *tuples, int num_tuples, FreqResult **results, int *num_results) {
    if (tuples == NULL || num_tuples <= 0 || results == NULL || num_results == NULL) {
        return -1;
    }

    int capacity = 16;
    Record *records = (Record *)malloc(capacity * sizeof(Record));
    if (records == NULL) {
        return -1;
    }

    int unique_count = 0;

    for (int i = 0; i < num_tuples; i++) {
        if (tuples[i].items == NULL || tuples[i].count <= 0) {
            free(records);
            return -1;
        }

        int h = compute_hash(&tuples[i]);
        int found = 0;

        for (int j = 0; j < unique_count; j++) {
            if (records[j].hash == h) {
                records[j].frequency++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (unique_count >= capacity) {
                capacity *= 2;
                Record *temp = (Record *)realloc(records, capacity * sizeof(Record));
                if (temp == NULL) {
                    free(records);
                    return -1;
                }
                records = temp;
            }
            records[unique_count].hash = h;
            records[unique_count].frequency = 1;
            unique_count++;
        }
    }

    int freq_capacity = 8;
    FreqResult *freqs = (FreqResult *)malloc(freq_capacity * sizeof(FreqResult));
    if (freqs == NULL) {
        free(records);
        return -1;
    }

    int freq_count = 0;

    for (int i = 0; i < unique_count; i++) {
        int f = records[i].frequency;
        int found = 0;

        for (int j = 0; j < freq_count; j++) {
            if (freqs[j].frequency == f) {
                freqs[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (freq_count >= freq_capacity) {
                freq_capacity *= 2;
                FreqResult *temp = (FreqResult *)realloc(freqs, freq_capacity * sizeof(FreqResult));
                if (temp == NULL) {
                    free(records);
                    free(freqs);
                    return -1;
                }
                freqs = temp;
            }
            freqs[freq_count].frequency = f;
            freqs[freq_count].count = 1;
            freq_count++;
        }
    }

    free(records);

    *results = freqs;
    *num_results = freq_count;

    return 0;
}

int main() {
    int a1[] = {1, 2};
    int a2[] = {3, 4};
    int a3[] = {1, 2};
    int a4[] = {5, 6};
    int a5[] = {3, 4};
    int a6[] = {1, 2};

    Tuple tuples[] = {
        {a1, 2},
        {a2, 2},
        {a3, 2},
        {a4, 2},
        {a5, 2},
        {a6, 2}
    };

    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    FreqResult *results = NULL;
    int num_results = 0;

    int ret = check_similar_occurrences(tuples, num_tuples, &results, &num_results);

    if (ret == 0) {
        for (int i = 0; i < num_results; i++) {
            printf("Frequency: %d, Count of such records: %d\n", results[i].frequency, results[i].count);
        }
        free(results);
    } else {
        printf("Error occurred during processing.\n");
    }

    return 0;
}