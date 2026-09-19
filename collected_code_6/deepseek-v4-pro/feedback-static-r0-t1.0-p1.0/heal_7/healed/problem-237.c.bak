#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int times;
} Record;

typedef struct {
    int count;
    int capacity;
    int *values;
} IntArray;

typedef struct {
    int *items;
    int count;
    int capacity;
} RecordMap;

void init_int_array(IntArray *arr) {
    if (arr == NULL) {
        exit(EXIT_FAILURE);
    }
    arr->count = 0;
    arr->capacity = 4;
    arr->values = (int*)malloc((size_t)arr->capacity * sizeof(int));
    if (arr->values == NULL) {
        exit(EXIT_FAILURE);
    }
}

void free_int_array(IntArray *arr) {
    if (arr == NULL) {
        return;
    }
    free(arr->values);
    arr->values = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

void append_int(IntArray *arr, int value) {
    if (arr == NULL) {
        exit(EXIT_FAILURE);
    }
    if (arr->count == arr->capacity) {
        int new_capacity = arr->capacity * 2;
        int *temp = (int*)realloc(arr->values, (size_t)new_capacity * sizeof(int));
        if (temp == NULL) {
            free_int_array(arr);
            exit(EXIT_FAILURE);
        }
        arr->values = temp;
        arr->capacity = new_capacity;
    }
    arr->values[arr->count++] = value;
}

void init_record_map(RecordMap *map) {
    if (map == NULL) {
        exit(EXIT_FAILURE);
    }
    map->count = 0;
    map->capacity = 8;
    map->items = (int*)calloc((size_t)map->capacity, sizeof(int));
    if (map->items == NULL) {
        exit(EXIT_FAILURE);
    }
}

void free_record_map(RecordMap *map) {
    if (map == NULL) {
        return;
    }
    free(map->items);
    map->items = NULL;
    map->count = 0;
    map->capacity = 0;
}

void insert_record_map(RecordMap *map, int value) {
    if (map == NULL) {
        exit(EXIT_FAILURE);
    }
    if (map->count == map->capacity) {
        int new_capacity = map->capacity * 2;
        int *temp = (int*)realloc(map->items, (size_t)new_capacity * sizeof(int));
        if (temp == NULL) {
            free_record_map(map);
            exit(EXIT_FAILURE);
        }
        map->items = temp;
        map->capacity = new_capacity;
    }
    map->items[map->count++] = value;
}

int find_record_map(const RecordMap *map, int value) {
    if (map == NULL) {
        return -1;
    }
    for (int i = 0; i < map->count; i++) {
        if (map->items[i] == value) {
            return i;
        }
    }
    return -1;
}

void find_similar_time_records(const Record *records, int n, IntArray *result) {
    RecordMap *unique_counts = NULL;
    int *freq = NULL;
    int unique_count = 0;
    
    if (records == NULL || result == NULL || n <= 0) {
        if (result != NULL) {
            result->count = 0;
            result->capacity = 0;
            result->values = NULL;
        }
        return;
    }
    
    unique_counts = (RecordMap*)malloc(sizeof(RecordMap));
    if (unique_counts == NULL) {
        exit(EXIT_FAILURE);
    }
    init_record_map(unique_counts);
    
    for (int i = 0; i < n; i++) {
        int occurrences = records[i].times;
        if (find_record_map(unique_counts, occurrences) == -1) {
            insert_record_map(unique_counts, occurrences);
        }
    }
    
    unique_count = unique_counts->count;
    freq = (int*)calloc((size_t)unique_count, sizeof(int));
    if (freq == NULL) {
        free_record_map(unique_counts);
        free(unique_counts);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; i++) {
        int idx = find_record_map(unique_counts, records[i].times);
        if (idx != -1) {
            freq[idx]++;
        }
    }
    
    result->count = 0;
    result->capacity = 4;
    result->values = (int*)malloc((size_t)result->capacity * sizeof(int));
    if (result->values == NULL) {
        free(freq);
        free_record_map(unique_counts);
        free(unique_counts);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < unique_count; i++) {
        int current_freq = freq[i];
        int has_match = 0;
        for (int j = 0; j < unique_count; j++) {
            if (i != j && freq[j] == current_freq) {
                has_match = 1;
                break;
            }
        }
        if (has_match) {
            for (int k = 0; k < n; k++) {
                if (records[k].times == unique_counts->items[i]) {
                    append_int(result, records[k].id);
                }
            }
        }
    }
    
    free(freq);
    free_record_map(unique_counts);
    free(unique_counts);
}

int main(void) {
    Record records[] = {
        {1, "alpha", 5},
        {2, "beta", 3},
        {3, "gamma", 5},
        {4, "delta", 7},
        {5, "epsilon", 3},
        {6, "zeta", 7},
        {7, "eta", 7},
        {8, "theta", 3}
    };
    int n = sizeof(records) / sizeof(records[0]);
    IntArray result;
    
    init_int_array(&result);
    find_similar_time_records(records, n, &result);
    
    printf("Records with similar occurrence times: ");
    for (int i = 0; i < result.count; i++) {
        printf("%d ", result.values[i]);
    }
    printf("\n");
    
    free_int_array(&result);
    
    return 0;
}