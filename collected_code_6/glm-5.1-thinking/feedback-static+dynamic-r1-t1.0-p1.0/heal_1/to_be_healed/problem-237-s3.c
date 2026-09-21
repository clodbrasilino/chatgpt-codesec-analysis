#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int record;
    size_t count;
} RecordFreq;

typedef struct {
    size_t frequency;
    size_t record_count;
} FreqFreq;

int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

FreqFreq* get_frequency_of_frequencies(const int* records, size_t num_records, size_t* out_size) {
    if (records == NULL || num_records == 0 || out_size == NULL) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    int* sorted_records = (int*)malloc(num_records * sizeof(int));
    if (sorted_records == NULL) {
        *out_size = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted_records, records, num_records * sizeof(int));
    qsort(sorted_records, num_records, sizeof(int), compare_ints);

    RecordFreq* rec_freqs = (RecordFreq*)malloc(num_records * sizeof(RecordFreq));
    if (rec_freqs == NULL) {
        free(sorted_records);
        *out_size = 0;
        return NULL;
    }

    size_t rec_freqs_size = 0;
    size_t i = 0;
    while (i < num_records) {
        int current_record = sorted_records[i];
        size_t count = 0;
        while (i < num_records && sorted_records[i] == current_record) {
            count++;
            i++;
        }
        rec_freqs[rec_freqs_size].record = current_record;
        rec_freqs[rec_freqs_size].count = count;
        rec_freqs_size++;
    }

    free(sorted_records);

    FreqFreq* result = (FreqFreq*)malloc(rec_freqs_size * sizeof(FreqFreq));
    if (result == NULL) {
        free(rec_freqs);
        *out_size = 0;
        return NULL;
    }

    size_t result_size = 0;
    for (size_t j = 0; j < rec_freqs_size; j++) {
        size_t current_freq = rec_freqs[j].count;
        int found = 0;
        for (size_t k = 0; k < result_size; k++) {
            if (result[k].frequency == current_freq) {
                result[k].record_count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            result[result_size].frequency = current_freq;
            result[result_size].record_count = 1;
            result_size++;
        }
    }

    free(rec_freqs);

    if (result_size == 0) {
        free(result);
        *out_size = 0;
        return NULL;
    }

    FreqFreq* trimmed_result = (FreqFreq*)realloc(result, result_size * sizeof(FreqFreq));
    if (trimmed_result != NULL) {
        result = trimmed_result;
    }

    *out_size = result_size;
    return result;
}

int main(void) {
    int records[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5};
    size_t num_records = sizeof(records) / sizeof(records[0]);
    size_t out_size = 0;

    FreqFreq* result = get_frequency_of_frequencies(records, num_records, &out_size);

    if (result != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("Frequency %zu occurs for %zu record(s)\n", result[i].frequency, result[i].record_count);
        }
        free(result);
    } else {
        printf("No results or memory allocation failed.\n");
    }

    return 0;
}