#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LEN 64

typedef struct {
    char name[MAX_NAME_LEN];
    int value;
} Record;

typedef struct {
    Record *records;
    size_t count;
    size_t capacity;
} RecordList;

typedef struct {
    char name[MAX_NAME_LEN];
    int value;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

int record_list_init(RecordList *list, size_t capacity)
{
    if (list == NULL || capacity == 0) {
        return -1;
    }
    
    list->records = (Record *)calloc(capacity, sizeof(Record));
    if (list->records == NULL) {
        return -1;
    }
    
    list->count = 0;
    list->capacity = capacity;
    return 0;
}

void record_list_free(RecordList *list)
{
    if (list != NULL) {
        free(list->records);
        list->records = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int record_list_add(RecordList *list, const char *name, int value)
{
    if (list == NULL || name == NULL) {
        return -1;
    }
    
    if (list->count >= list->capacity) {
        return -1;
    }
    
    size_t name_len = strlen(name);
    if (name_len >= MAX_NAME_LEN) {
        return -1;
    }
    
    strncpy(list->records[list->count].name, name, MAX_NAME_LEN - 1);
    list->records[list->count].name[MAX_NAME_LEN - 1] = '\0';
    list->records[list->count].value = value;
    list->count++;
    
    return 0;
}

int tuple_list_init(TupleList *list, size_t capacity)
{
    if (list == NULL || capacity == 0) {
        return -1;
    }
    
    list->tuples = (Tuple *)calloc(capacity, sizeof(Tuple));
    if (list->tuples == NULL) {
        return -1;
    }
    
    list->count = 0;
    list->capacity = capacity;
    return 0;
}

void tuple_list_free(TupleList *list)
{
    if (list != NULL) {
        free(list->tuples);
        list->tuples = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int tuple_list_add(TupleList *list, const char *name, int value)
{
    if (list == NULL || name == NULL) {
        return -1;
    }
    
    if (list->count >= list->capacity) {
        return -1;
    }
    
    size_t name_len = strlen(name);
    if (name_len >= MAX_NAME_LEN) {
        return -1;
    }
    
    strncpy(list->tuples[list->count].name, name, MAX_NAME_LEN - 1);
    list->tuples[list->count].name[MAX_NAME_LEN - 1] = '\0';
    list->tuples[list->count].value = value;
    list->count++;
    
    return 0;
}

int find_max_value_in_tuple_list(const TupleList *list, int *max_value)
{
    if (list == NULL || max_value == NULL) {
        return -1;
    }
    
    if (list->count == 0 || list->tuples == NULL) {
        return -1;
    }
    
    int max = list->tuples[0].value;
    
    for (size_t i = 1; i < list->count; i++) {
        if (list->tuples[i].value > max) {
            max = list->tuples[i].value;
        }
    }
    
    *max_value = max;
    return 0;
}

int find_max_value_in_record_list(const RecordList *list, int *max_value)
{
    if (list == NULL || max_value == NULL) {
        return -1;
    }
    
    if (list->count == 0 || list->records == NULL) {
        return -1;
    }
    
    int max = list->records[0].value;
    
    for (size_t i = 1; i < list->count; i++) {
        if (list->records[i].value > max) {
            max = list->records[i].value;
        }
    }
    
    *max_value = max;
    return 0;
}

int main(void)
{
    RecordList record_list;
    TupleList tuple_list;
    int max_value;
    
    if (record_list_init(&record_list, 10) != 0) {
        fprintf(stderr, "Failed to initialize record list\n");
        return EXIT_FAILURE;
    }
    
    if (tuple_list_init(&tuple_list, 10) != 0) {
        fprintf(stderr, "Failed to initialize tuple list\n");
        record_list_free(&record_list);
        return EXIT_FAILURE;
    }
    
    if (record_list_add(&record_list, "Record1", 42) != 0 ||
        record_list_add(&record_list, "Record2", 78) != 0 ||
        record_list_add(&record_list, "Record3", 15) != 0 ||
        record_list_add(&record_list, "Record4", 93) != 0) {
        fprintf(stderr, "Failed to add records\n");
        record_list_free(&record_list);
        tuple_list_free(&tuple_list);
        return EXIT_FAILURE;
    }
    
    if (tuple_list_add(&tuple_list, "Tuple1", 25) != 0 ||
        tuple_list_add(&tuple_list, "Tuple2", 67) != 0 ||
        tuple_list_add(&tuple_list, "Tuple3", 89) != 0 ||
        tuple_list_add(&tuple_list, "Tuple4", 34) != 0) {
        fprintf(stderr, "Failed to add tuples\n");
        record_list_free(&record_list);
        tuple_list_free(&tuple_list);
        return EXIT_FAILURE;
    }
    
    if (find_max_value_in_record_list(&record_list, &max_value) == 0) {
        printf("Maximum value in record list: %d\n", max_value);
    } else {
        fprintf(stderr, "Failed to find maximum value in record list\n");
    }
    
    if (find_max_value_in_tuple_list(&tuple_list, &max_value) == 0) {
        printf("Maximum value in tuple list: %d\n", max_value);
    } else {
        fprintf(stderr, "Failed to find maximum value in tuple list\n");
    }
    
    record_list_free(&record_list);
    tuple_list_free(&tuple_list);
    
    return EXIT_SUCCESS;
}