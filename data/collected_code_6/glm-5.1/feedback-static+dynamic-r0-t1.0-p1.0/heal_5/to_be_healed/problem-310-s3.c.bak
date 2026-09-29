#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  */

Tuple* string_to_tuple(const char* str, const char* delimiter) {
    if (str == NULL || delimiter == NULL) return NULL;
    
    size_t delim_len = strlen(delimiter);
    if (delim_len == 0) return NULL;

    const char* delim_pos = strstr(str, delimiter);
    if (delim_pos == NULL) return NULL;

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) return NULL;

    size_t first_len = delim_pos - str;
    tuple->first = (char*)malloc(first_len + 1);
    if (tuple->first == NULL) {
        free(tuple);
        return NULL;
    }
    memcpy(tuple->first, str, first_len);
    tuple->first[first_len] = '\0';

    const char* second_start = delim_pos + delim_len;
    size_t second_len = strlen(second_start);
    tuple->second = (char*)malloc(second_len + 1);
    if (tuple->second == NULL) {
        free(tuple->first);
        free(tuple);
        return NULL;
    }
    memcpy(tuple->second, second_start, second_len + 1);

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
    Tuple* t0 = string_to_tuple("python3.0-15.10", "-");
    if (t0 != NULL) {
        for (size_t i = 0; i < strlen(t0->first); i++) printf("'%c'%s", t0->first[i], i < strlen(t0->first) - 1 ? ", " : "\n");
        for (size_t i = 0; i < strlen(t0->second); i++) printf("'%c'%s", t0->second[i], i < strlen(t0->second) - 1 ? ", " : "\n");
        free_tuple(t0);
    }

    Tuple* t1 = string_to_tuple("item1,item2", ",");
    if (t1 != NULL) {
        for (size_t i = 0; i < strlen(t1->first); i++) printf("'%c'%s", t1->first[i], i < strlen(t1->first) - 1 ? ", " : "\n");
        for (size_t i = 0; i < strlen(t1->second); i++) printf("'%c'%s", t1->second[i], i < strlen(t1->second) - 1 ? ", " : "\n");
        free_tuple(t1);
    }

    Tuple* t2 = string_to_tuple("version:15.10", ":");
    if (t2 != NULL) {
        for (size_t i = 0; i < strlen(t2->first); i++) printf("'%c'%s", t2->first[i], i < strlen(t2->first) - 1 ? ", " : "\n");
        for (size_t i = 0; i < strlen(t2->second); i++) printf("'%c'%s", t2->second[i], i < strlen(t2->second) - 1 ? ", " : "\n");
        free_tuple(t2);
    }

    return 0;
}