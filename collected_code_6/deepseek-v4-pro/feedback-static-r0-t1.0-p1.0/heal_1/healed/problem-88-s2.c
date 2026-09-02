#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int frequency;
} Frequency;

int compare_int(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int compare_frequency(const void *a, const void *b) {
    const Frequency *fa = (const Frequency *)a;
    const Frequency *fb = (const Frequency *)b;
    return fa->value - fb->value;
}

Frequency* get_frequency(const int *list, int length, int *unique_count) {
    if (list == NULL || length <= 0 || unique_count == NULL) {
        if (unique_count != NULL) {
            *unique_count = 0;
        }
        return NULL;
    }

    int *temp = (int *)malloc(length * sizeof(int));
    if (temp == NULL) {
        *unique_count = 0;
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        temp[i] = list[i];
    }

    qsort(temp, length, sizeof(int), compare_int);

    int capacity = 8;
    Frequency *freq = (Frequency *)malloc(capacity * sizeof(Frequency));
    if (freq == NULL) {
        free(temp);
        *unique_count = 0;
        return NULL;
    }

    int count = 0;
    int current = temp[0];
    int current_freq = 1;

    for (int i = 1; i < length; i++) {
        if (temp[i] == current) {
            current_freq++;
        } else {
            if (count >= capacity) {
                capacity *= 2;
                Frequency *new_freq = (Frequency *)realloc(freq, capacity * sizeof(Frequency));
                if (new_freq == NULL) {
                    free(freq);
                    free(temp);
                    *unique_count = 0;
                    return NULL;
                }
                freq = new_freq;
            }
            freq[count].value = current;
            freq[count].frequency = current_freq;
            count++;
            current = temp[i];
            current_freq = 1;
        }
    }

    if (count >= capacity) {
        capacity *= 2;
        Frequency *new_freq = (Frequency *)realloc(freq, capacity * sizeof(Frequency));
        if (new_freq == NULL) {
            free(freq);
            free(temp);
            *unique_count = 0;
            return NULL;
        }
        freq = new_freq;
    }
    freq[count].value = current;
    freq[count].frequency = current_freq;
    count++;

    free(temp);
    *unique_count = count;
    return freq;
}

int main(void) {
    int list[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int length = sizeof(list) / sizeof(list[0]);
    int unique_count = 0;

    Frequency *frequencies = get_frequency(list, length, &unique_count);

    if (frequencies == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Element frequencies:\n");
    for (int i = 0; i < unique_count; i++) {
        printf("%d occurs %d time%s\n", frequencies[i].value, frequencies[i].frequency, frequencies[i].frequency == 1 ? "" : "s");
    }

    free(frequencies);
    return 0;
}