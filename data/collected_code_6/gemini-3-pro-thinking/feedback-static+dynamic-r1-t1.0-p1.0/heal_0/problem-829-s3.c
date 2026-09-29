#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *str;
    size_t count;
} StringFrequency;

const char *get_second_most_frequent(const char **sequence, size_t length) {
    if (sequence == NULL || length < 2) {
        return NULL;
    }

    StringFrequency *freq_arr = (StringFrequency *)malloc(length * sizeof(StringFrequency));
    if (freq_arr == NULL) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < length; ++i) {
        if (sequence[i] == NULL) {
            continue;
        }

        int found = 0;
        for (size_t j = 0; j < unique_count; ++j) {
            if (strcmp(freq_arr[j].str, sequence[i]) == 0) {
                freq_arr[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            freq_arr[unique_count].str = sequence[i];
            freq_arr[unique_count].count = 1;
            unique_count++;
        }
    }

    if (unique_count < 2) {
        free(freq_arr);
        return NULL;
    }

    size_t first_max = 0;
    size_t sec_max = 0;
    const char *first_str = NULL;
    const char *second_str = NULL;

    for (size_t i = 0; i < unique_count; ++i) {
        if (freq_arr[i].count > first_max) {
            sec_max = first_max;
            second_str = first_str;

            first_max = freq_arr[i].count;
            first_str = freq_arr[i].str;
        } else if (freq_arr[i].count > sec_max && freq_arr[i].count < first_max) {
            sec_max = freq_arr[i].count;
            second_str = freq_arr[i].str;
        }
    }

    free(freq_arr);
    return second_str;
}

int main(void) {
    const char *sequence[] = {
        "aaa", "bbb", "ccc", "bbb", "aaa", "aaa"
    };
    size_t length = sizeof(sequence) / sizeof(sequence[0]);

    const char *result = get_second_most_frequent(sequence, length);

    if (result != NULL) {
        printf("%s\n", result);
    }

    return 0;
}