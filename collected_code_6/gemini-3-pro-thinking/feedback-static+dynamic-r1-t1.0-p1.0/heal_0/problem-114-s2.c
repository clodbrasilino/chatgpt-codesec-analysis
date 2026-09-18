#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple tuple;
    size_t frequency;
} TupleFrequency;

typedef struct {
    TupleFrequency *items;
    size_t size;
    size_t capacity;
} FrequencyList;

FrequencyList* create_frequency_list(size_t initial_capacity);
void destroy_frequency_list(FrequencyList *list);
FrequencyList* calculate_tuple_frequencies(const Tuple *tuples, size_t tuple_count);

FrequencyList* create_frequency_list(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    FrequencyList *list = malloc(sizeof(FrequencyList));
    if (!list) {
        return NULL;
    }

    list->items = malloc(initial_capacity * sizeof(TupleFrequency));
    if (!list->items) {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = initial_capacity;

    return list;
}

void destroy_frequency_list(FrequencyList *list) {
    if (list) {
        if (list->items) {
            free(list->items);
        }
        free(list);
    }
}

FrequencyList* calculate_tuple_frequencies(const Tuple *tuples, size_t tuple_count) {
    if (!tuples || tuple_count == 0) {
        return NULL;
    }

    FrequencyList *list = create_frequency_list(tuple_count);
    if (!list) {
        return NULL;
    }

    for (size_t i = 0; i < tuple_count; i++) {
        bool found = false;

        for (size_t j = 0; j < list->size; j++) {
            if (list->items[j].tuple.first == tuples[i].first &&
                list->items[j].tuple.second == tuples[i].second) {
                list->items[j].frequency++;
                found = true;
                break;
            }
        }

        if (!found) {
            if (list->size >= list->capacity) {
                size_t new_capacity = list->capacity * 2;
                TupleFrequency *new_items = realloc(list->items, new_capacity * sizeof(TupleFrequency));
                if (!new_items) {
                    destroy_frequency_list(list);
                    return NULL;
                }
                list->items = new_items;
                list->capacity = new_capacity;
            }

            list->items[list->size].tuple = tuples[i];
            list->items[list->size].frequency = 1;
            list->size++;
        }
    }

    return list;
}

int main(void) {
    Tuple input_tuples[] = {
        {1, 2}, {3, 4}, {1, 2}, {5, 6},
        {3, 4}, {1, 2}, {7, 8}, {5, 6}
    };
    
    size_t tuple_count = sizeof(input_tuples) / sizeof(input_tuples[0]);

    FrequencyList *freq_list = calculate_tuple_frequencies(input_tuples, tuple_count);

    if (!freq_list) {
        fprintf(stderr, "Failed to calculate frequencies or empty input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < freq_list->size; i++) {
        printf("Tuple: (%d, %d), Frequency: %zu\n", 
               freq_list->items[i].tuple.first, 
               freq_list->items[i].tuple.second, 
               freq_list->items[i].frequency);
    }

    destroy_frequency_list(freq_list);

    return EXIT_SUCCESS;
}