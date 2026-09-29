#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int element;
    int frequency;
} FreqEntry;

int compare_entries(const void *a, const void *b) {
    const FreqEntry *entry_a = (const FreqEntry *)a;
    const FreqEntry *entry_b = (const FreqEntry *)b;
    return (entry_a->element > entry_b->element) - (entry_a->element < entry_b->element);
}

void find_frequencies(const int *list, int size, FreqEntry **result, int *result_size) {
    if (result == NULL) {
        return;
    }
    if (result_size == NULL) {
        *result = NULL;
        return;
    }
    if (list == NULL || size <= 0) {
        *result = NULL;
        *result_size = 0;
        return;
    }

    FreqEntry *entries = (FreqEntry *)malloc((size_t)size * sizeof(FreqEntry));
    if (entries == NULL) {
        *result = NULL;
        *result_size = 0;
        return;
    }

    for (int i = 0; i < size; i++) {
        entries[i].element = list[i];
        entries[i].frequency = 1;
    }

    qsort(entries, (size_t)size, sizeof(FreqEntry), compare_entries);

    int unique_count = 0;
    for (int i = 1; i < size; i++) {
        if (entries[i].element == entries[unique_count].element) {
            entries[unique_count].frequency++;
        } else {
            unique_count++;
            entries[unique_count].element = entries[i].element;
            entries[unique_count].frequency = 1;
        }
    }
    unique_count++;

    FreqEntry *shrunk = (FreqEntry *)realloc(entries, (size_t)unique_count * sizeof(FreqEntry));
    if (shrunk == NULL && unique_count > 0) {
        free(entries);
        *result = NULL;
        *result_size = 0;
        return;
    }

    *result = shrunk;
    *result_size = unique_count;
}

int main(void) {
    int list[] = {4, 2, 2, 8, 3, 3, 3, 4, 4, 4, 4, 1};
    int size = (int)(sizeof(list) / sizeof(list[0]));
    FreqEntry *frequencies = NULL;
    int freq_size = 0;

    find_frequencies(list, size, &frequencies, &freq_size);

    if (frequencies == NULL || freq_size <= 0) {
        fprintf(stderr, "Failed to compute frequencies\n");
        return 1;
    }

    for (int i = 0; i < freq_size; i++) {
        printf("%d: %d\n", frequencies[i].element, frequencies[i].frequency);
    }

    free(frequencies);
    return 0;
}