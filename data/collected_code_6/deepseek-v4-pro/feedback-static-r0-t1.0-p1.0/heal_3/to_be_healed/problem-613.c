#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 49

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    double value;
} Record;

typedef struct {
    Record *records;
    size_t size;
} RecordList;

double find_max_value(RecordList *list, size_t *max_index) {
    if (list == NULL || list->records == NULL || list->size == 0) {
        if (max_index != NULL) {
            *max_index = (size_t)-1;
        }
        return 0.0;
    }
    
    double max_val = list->records[0].value;
    size_t idx = 0;
    
    for (size_t i = 1; i < list->size; i++) {
        if (list->records[i].value > max_val) {
            max_val = list->records[i].value;
            idx = i;
        }
    }
    
    if (max_index != NULL) {
        *max_index = idx;
    }
    
    return max_val;
}

int main(void) {
    Record records[] = {
        {1, "Alice", 85.5},
        {2, "Bob", 92.3},
        {3, "Charlie", 78.9},
        {4, "Diana", 95.7},
        {5, "Eve", 88.2}
    };
    
    RecordList list;
    list.records = records;
    list.size = sizeof(records) / sizeof(records[0]);
    
    size_t max_index = 0;
    double max_value = find_max_value(&list, &max_index);
    
    if (max_index < list.size) {
        printf("Maximum value: %.2f\n", max_value);
        printf("Record with maximum value: ID=%d, Name=%.*s, Value=%.2f\n",
               list.records[max_index].id,
               MAX_NAME_LENGTH,
               list.records[max_index].name,
               list.records[max_index].value);
    } else {
        printf("No maximum value found.\n");
    }
    
    return 0;
}