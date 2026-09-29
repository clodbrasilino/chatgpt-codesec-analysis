#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

typedef struct {
    Range* items;
    size_t count;
    size_t capacity;
} RangeList;

int compare_ranges(const void* a, const void* b);
RangeList* create_range_list(size_t initial_capacity);
int add_range(RangeList* list, int start, int end);
void free_range_list(RangeList* list);
RangeList* find_missing_ranges(const RangeList* input_list, int start_range, int end_range);

int compare_ranges(const void* a, const void* b) {
    const Range* r1 = (const Range*)a;
    const Range* r2 = (const Range*)b;
    if (r1->start < r2->start) {
        return -1;
    }
    if (r1->start > r2->start) {
        return 1;
    }
    return 0;
}

RangeList* create_range_list(size_t initial_capacity) {
    RangeList* list = (RangeList*)malloc(sizeof(RangeList));
    if (!list) {
        return NULL;
    }
    list->items = (Range*)malloc(initial_capacity * sizeof(Range));
    if (!list->items && initial_capacity > 0) {
        free(list);
        return NULL;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return list;
}

int add_range(RangeList* list, int start, int end) {
    if (!list) {
        return -1;
    }
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Range* new_items = (Range*)realloc(list->items, new_capacity * sizeof(Range));
        if (!new_items) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count].start = start;
    list->items[list->count].end = end;
    list->count++;
    return 0;
}

void free_range_list(RangeList* list) {
    if (list) {
        if (list->items) {
            free(list->items);
        }
        free(list);
    }
}

RangeList* find_missing_ranges(const RangeList* input_list, int start_range, int end_range) {
    if (!input_list || start_range > end_range) {
        return NULL;
    }

    RangeList* missing_list = create_range_list(4);
    if (!missing_list) {
        return NULL;
    }

    if (input_list->count == 0) {
        if (add_range(missing_list, start_range, end_range) != 0) {
            free_range_list(missing_list);
            return NULL;
        }
        return missing_list;
    }

    Range* sorted_input = (Range*)malloc(input_list->count * sizeof(Range));
    if (!sorted_input) {
        free_range_list(missing_list);
        return NULL;
    }

    for (size_t i = 0; i < input_list->count; ++i) {
        sorted_input[i] = input_list->items[i];
    }

    qsort(sorted_input, input_list->count, sizeof(Range), compare_ranges);

    long long current = (long long)start_range;
    long long end_limit = (long long)end_range;

    for (size_t i = 0; i < input_list->count; ++i) {
        long long r_start = (long long)sorted_input[i].start;
        long long r_end = (long long)sorted_input[i].end;

        if (current < r_start) {
            long long missing_end = (r_start - 1 < end_limit) ? (r_start - 1) : end_limit;
            if (current <= missing_end) {
                if (add_range(missing_list, (int)current, (int)missing_end) != 0) {
                    free(sorted_input);
                    free_range_list(missing_list);
                    return NULL;
                }
            }
        }
        if (current <= r_end) {
            current = r_end + 1;
        }
        if (current > end_limit) {
            break;
        }
    }

    if (current <= end_limit) {
        if (add_range(missing_list, (int)current, (int)end_limit) != 0) {
            free(sorted_input);
            free_range_list(missing_list);
            return NULL;
        }
    }

    free(sorted_input);
    return missing_list;
}

int main(void) {
    RangeList* input = create_range_list(4);
    if (!input) {
        return EXIT_FAILURE;
    }

    if (add_range(input, 10, 15) != 0 ||
        add_range(input, 20, 25) != 0 ||
        add_range(input, 30, 35) != 0) {
        free_range_list(input);
        return EXIT_FAILURE;
    }

    RangeList* missing = find_missing_ranges(input, 5, 40);
    if (!missing) {
        free_range_list(input);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < missing->count; ++i) {
        printf("[%d, %d]\n", missing->items[i].start, missing->items[i].end);
    }

    free_range_list(missing);
    free_range_list(input);
    
    return EXIT_SUCCESS;
}