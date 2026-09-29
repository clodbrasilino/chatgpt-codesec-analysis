#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#define MAX_NAME_LEN 64

typedef struct {
    char *name;
    int value;
} Record;

typedef struct {
    Record *records;
    size_t count;
    size_t capacity;
} RecordList;

typedef struct {
    char *name;
    int value;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

static int safe_strnlen(const char *str, size_t maxlen, size_t *len)
{
    if (str == NULL || len == NULL) {
        return -1;
    }

    size_t i;
    for (i = 0; i < maxlen; i++) {
        if (str[i] == '\0') {
            *len = i;
            return 0;
        }
    }

    return -1;
}

static int safe_strcpy(char *dest, size_t dest_size, const char *src)
{
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }

    size_t src_len;
    if (safe_strnlen(src, dest_size, &src_len) != 0) {
        return -1;
    }

    if (src_len >= dest_size) {
        return -1;
    }

    if (src_len + 1 > dest_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
    return 0;
}

static char *safe_strdup(const char *src)
{
    if (src == NULL) {
        return NULL;
    }

    size_t len;
    if (safe_strnlen(src, MAX_NAME_LEN, &len) != 0) {
        return NULL;
    }

    if (len >= MAX_NAME_LEN) {
        return NULL;
    }

    if (len + 1 > SIZE_MAX) {
        return NULL;
    }

    char *dest = (char *)malloc(len + 1);
    if (dest == NULL) {
        return NULL;
    }

    if (len + 1 > MAX_NAME_LEN) {
        free(dest);
        return NULL;
    }

    if (safe_strcpy(dest, len + 1, src) != 0) {
        free(dest);
        return NULL;
    }

    return dest;
}

int record_list_init(RecordList *list, size_t capacity)
{
    if (list == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(Record)) {
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
        if (list->records != NULL) {
            for (size_t i = 0; i < list->count; i++) {
                free(list->records[i].name);
                list->records[i].name = NULL;
            }
            free(list->records);
        }
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

    char *name_copy = safe_strdup(name);
    if (name_copy == NULL) {
        return -1;
    }

    list->records[list->count].name = name_copy;
    list->records[list->count].value = value;
    list->count++;

    return 0;
}

int tuple_list_init(TupleList *list, size_t capacity)
{
    if (list == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(Tuple)) {
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
        if (list->tuples != NULL) {
            for (size_t i = 0; i < list->count; i++) {
                free(list->tuples[i].name);
                list->tuples[i].name = NULL;
            }
            free(list->tuples);
        }
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

    char *name_copy = safe_strdup(name);
    if (name_copy == NULL) {
        return -1;
    }

    list->tuples[list->count].name = name_copy;
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