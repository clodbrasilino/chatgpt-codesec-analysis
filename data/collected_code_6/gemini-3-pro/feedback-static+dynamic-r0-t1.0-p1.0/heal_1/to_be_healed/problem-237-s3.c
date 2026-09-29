#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int value;
    int count;
} Record;

typedef struct {
    int count;
    int frequency;
} FrequencyMap;

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
void check_occurrences(int* tuples, int num_tuples) {
    if (tuples == NULL || num_tuples <= 0) {
        return;
    }

    Record* records = (Record*)malloc(num_tuples * sizeof(Record));
    if (records == NULL) {
        return;
    }

    int num_records = 0;
    for (int i = 0; i < num_tuples; i++) {
        int found = 0;
        for (int j = 0; j < num_records; j++) {
            if (records[j].value == tuples[i]) {
                records[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            records[num_records].value = tuples[i];
            records[num_records].count = 1;
            num_records++;
        }
    }

    FrequencyMap* freq_map = (FrequencyMap*)malloc(num_records * sizeof(FrequencyMap));
    if (freq_map == NULL) {
        free(records);
        return;
    }

    int num_freqs = 0;
    for (int i = 0; i < num_records; i++) {
        int found = 0;
        for (int j = 0; j < num_freqs; j++) {
            if (freq_map[j].count == records[i].count) {
                freq_map[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freq_map[num_freqs].count = records[i].count;
            freq_map[num_freqs].frequency = 1;
            num_freqs++;
        }
    }

    for (int i = 0; i < num_freqs; i++) {
        if (freq_map[i].frequency > 1) {
            printf("Records occurring %d times: ", freq_map[i].count);
            for (int j = 0; j < num_records; j++) {
                if (records[j].count == freq_map[i].count) {
                    printf("%d ", records[j].value);
                }
            }
            printf("\n");
        }
    }

    free(freq_map);
    free(records);
}

int main(void) {
    int tuples[] = {1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5};
    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);

    check_occurrences(tuples, num_tuples);

    return 0;
}