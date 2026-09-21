#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 64

typedef struct {
    char first[MAX_STRING_LENGTH];
    char second[MAX_STRING_LENGTH];
} Tuple;

static bool is_valid_string(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }
    
    size_t i;
    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            return true;
        }
    }
    return false;
}

int compare_tuples(const void *a, const void *b)
{
    const Tuple *tuple_a = (const Tuple *)a;
    const Tuple *tuple_b = (const Tuple *)b;
    
    if (!is_valid_string(tuple_a->first, sizeof(tuple_a->first)) ||
        !is_valid_string(tuple_b->first, sizeof(tuple_b->first))) {
        return 0;
    }
    
    return strncmp(tuple_a->first, tuple_b->first, sizeof(tuple_a->first) - 1);
}

int sort_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL || count == 0) {
        return -1;
    }
    
    size_t i;
    for (i = 0; i < count; i++) {
        if (!is_valid_string(tuples[i].first, sizeof(tuples[i].first)) ||
            !is_valid_string(tuples[i].second, sizeof(tuples[i].second))) {
            return -1;
        }
    }
    
    qsort(tuples, count, sizeof(Tuple), compare_tuples);
    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {"banana", "yellow"},
        {"apple", "red"},
        {"cherry", "dark red"},
        {"date", "brown"}
    };
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t i;

    if (sort_tuples(tuples, count) != 0) {
        fprintf(stderr, "Error: failed to sort tuples\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%s: %s\n", tuples[i].first, tuples[i].second);
    }

    return EXIT_SUCCESS;
}