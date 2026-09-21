#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 49
#define NAME_BUFFER_SIZE 50

typedef struct {
    int id;
    char name[NAME_BUFFER_SIZE];
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
    
    size_t records_count = sizeof(records) / sizeof(records[0]);
    for (size_t i = 0; i < records_count; i++) {
        records[i].name[MAX_NAME_LENGTH] = '\0';
    }
    
    RecordList list;
    list.records = records;
    list.size = records_count;
    
    size_t max_index = 0;
    double max_value = find_max_value(&list, &max_index);
    
    if (max_index < list.size) {
        printf("Maximum value: %.2f\n", max_value);
        printf("Record with maximum value: ID=%d, Name=%.49s, Value=%.2f\n",
               list.records[max_index].id,
               list.records[max_index].name,
               list.records[max_index].value);
    } else {
        printf("No records found.\n");
    }
    
    return 0;
}