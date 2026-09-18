#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *str;
    size_t count;
} StringFreq;

const char *get_second_most_frequent(const char **sequence, size_t size) {
    if (!sequence || size == 0) {
        return NULL;
    }

    StringFreq *freqs = (StringFreq *)calloc(size, sizeof(StringFreq));
    if (!freqs) {
        return NULL;
    }

    size_t unique_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (!sequence[i]) {
            continue;
        }
        
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (strcmp(freqs[j].str, sequence[i]) == 0) {
                freqs[j].count++;
                found = 1;
                break;
            }
        }
        
        if (!found) {
            freqs[unique_count].str = sequence[i];
            freqs[unique_count].count = 1;
            unique_count++;
        }
    }

    size_t max_count = 0;
    size_t sec_max_count = 0;
    const char *max_str = NULL;
    const char *sec_max_str = NULL;

    for (size_t i = 0; i < unique_count; i++) {
        if (freqs[i].count > max_count) {
            sec_max_count = max_count;
            sec_max_str = max_str;
            max_count = freqs[i].count;
            max_str = freqs[i].str;
        } else if (freqs[i].count > sec_max_count) {
            sec_max_count = freqs[i].count;
            sec_max_str = freqs[i].str;
        }
    }

    free(freqs);
    return sec_max_str;
}

int main(void) {
    const char *sequence[] = {
        "apple", "banana", "apple", "orange", "banana", 
        "apple", "kiwi", "orange", "orange", "orange"
    };
    
    size_t size = sizeof(sequence) / sizeof(sequence[0]);
    const char *result = get_second_most_frequent(sequence, size);

    if (result) {
        printf("%s\n", result);
    }

    return 0;
}