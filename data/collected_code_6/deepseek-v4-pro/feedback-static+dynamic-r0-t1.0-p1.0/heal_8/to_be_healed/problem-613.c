#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 49
#define NAME_BUFFER_SIZE 50

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

void safe_strncpy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return;
    }
    
    size_t src_len = strnlen(src, dest_size - 1);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
}

int main(void) {
    Record records[5];
    
    records[0].id = 1;
    safe_strncpy(records[0].name, "Alice", NAME_BUFFER_SIZE);
    records[0].value = 85.5;
    
    records[1].id = 2;
    safe_strncpy(records[1].name, "Bob", NAME_BUFFER_SIZE);
    records[1].value = 92.3;
    
    records[2].id = 3;
    safe_strncpy(records[2].name, "Charlie", NAME_BUFFER_SIZE);
    records[2].value = 78.9;
    
    records[3].id = 4;
    safe_strncpy(records[3].name, "Diana", NAME_BUFFER_SIZE);
    records[3].value = 95.7;
    
    records[4].id = 5;
    safe_strncpy(records[4].name, "Eve", NAME_BUFFER_SIZE);
    records[4].value = 88.2;
    
    size_t records_count = sizeof(records) / sizeof(records[0]);
    
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