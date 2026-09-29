#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;

Tuple* string_to_tuple(const char* str, const char* delimiter) {
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t delim_len = strlen(delimiter);

    if (delim_len == 0) {
        return NULL;
    }

    const char* delim_pos = strstr(str, delimiter);
    if (delim_pos == NULL) {
        return NULL;
    }

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    size_t first_len = delim_pos - str;
    tuple->first = (char*)malloc(first_len + 1);
    if (tuple->first == NULL) {
        free(tuple);
        return NULL;
    }
    strncpy(tuple->first, str, first_len);
    tuple->first[first_len] = '\0';

    const char* second_start = delim_pos + delim_len;
    size_t second_len = strlen(second_start);
    tuple->second = (char*)malloc(second_len + 1);
    if (tuple->second == NULL) {
        free(tuple->first);
        free(tuple);
        return NULL;
    }
    strncpy(tuple->second, second_start, second_len);
    tuple->second[second_len] = '\0';

    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->first);
        free(tuple->second);
        free(tuple);
    }
}

int main(void) {
    const char* test0_str = "python3.0-15.10";
    const char* test0_delim = "-";
    Tuple* t0 = string_to_tuple(test0_str, test0_delim);
    if (t0 != NULL) {
        printf("First: %s, Second: %s\n", t0->first, t0->second);
        free_tuple(t0);
    }

    const char* test1_str = "item1,item2";
    const char* test1_delim = ",";
    Tuple* t1 = string_to_tuple(test1_str, test1_delim);
    if (t1 != NULL) {
        printf("First: %s, Second: %s\n", t1->first, t1->second);
        free_tuple(t1);
    }

    const char* test2_str = "version:15.10";
    const char* test2_delim = ":";
    Tuple* t2 = string_to_tuple(test2_str, test2_delim);
    if (t2 != NULL) {
        printf("First: %s, Second: %s\n", t2->first, t2->second);
        free_tuple(t2);
    }

    return 0;
}