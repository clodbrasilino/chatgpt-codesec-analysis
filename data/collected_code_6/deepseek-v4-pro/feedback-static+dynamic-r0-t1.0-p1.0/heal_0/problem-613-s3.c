#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *attributes;
    size_t attr_count;
} Record;

typedef struct {
    Record *records;
    size_t record_count;
} RecordList;

double find_max_record_attribute(RecordList *list, size_t attr_index) {
    if (list == NULL || list->records == NULL || list->record_count == 0) {
        return 0.0;
    }
    
    if (attr_index >= list->records[0].attr_count) {
        return 0.0;
    }
    
    double max_val = *(double *)list->records[0].attributes[attr_index].data;
    
    for (size_t i = 1; i < list->record_count; i++) {
        if (attr_index >= list->records[i].attr_count) {
            continue;
        }
        
        double current = *(double *)list->records[i].attributes[attr_index].data;
        if (current > max_val) {
            max_val = current;
        }
    }
    
    return max_val;
}

int main(void) {
    RecordList list;
    list.record_count = 3;
    list.records = (Record *)malloc(list.record_count * sizeof(Record));
    
    if (list.records == NULL) {
        return 1;
    }
    
    double val1 = 10.5, val2 = 20.3, val3 = 15.7;
    double val4 = 5.2, val5 = 30.1, val6 = 25.9;
    double val7 = 12.8, val8 = 18.4, val9 = 22.6;
    
    for (size_t i = 0; i < list.record_count; i++) {
        list.records[i].attr_count = 3;
        list.records[i].attributes = (Tuple *)malloc(3 * sizeof(Tuple));
        
        if (list.records[i].attributes == NULL) {
            for (size_t j = 0; j < i; j++) {
                for (size_t k = 0; k < list.records[j].attr_count; k++) {
                    free(list.records[j].attributes[k].data);
                }
                free(list.records[j].attributes);
            }
            free(list.records);
            return 1;
        }
    }
    
    list.records[0].attributes[0].data = &val1;
    list.records[0].attributes[0].size = sizeof(double);
    list.records[0].attributes[1].data = &val2;
    list.records[0].attributes[1].size = sizeof(double);
    list.records[0].attributes[2].data = &val3;
    list.records[0].attributes[2].size = sizeof(double);
    
    list.records[1].attributes[0].data = &val4;
    list.records[1].attributes[0].size = sizeof(double);
    list.records[1].attributes[1].data = &val5;
    list.records[1].attributes[1].size = sizeof(double);
    list.records[1].attributes[2].data = &val6;
    list.records[1].attributes[2].size = sizeof(double);
    
    list.records[2].attributes[0].data = &val7;
    list.records[2].attributes[0].size = sizeof(double);
    list.records[2].attributes[1].data = &val8;
    list.records[2].attributes[1].size = sizeof(double);
    list.records[2].attributes[2].data = &val9;
    list.records[2].attributes[2].size = sizeof(double);
    
    double max_attr0 = find_max_record_attribute(&list, 0);
    double max_attr1 = find_max_record_attribute(&list, 1);
    double max_attr2 = find_max_record_attribute(&list, 2);
    
    printf("Max value in attribute 0: %.2f\n", max_attr0);
    printf("Max value in attribute 1: %.2f\n", max_attr1);
    printf("Max value in attribute 2: %.2f\n", max_attr2);
    
    for (size_t i = 0; i < list.record_count; i++) {
        free(list.records[i].attributes);
    }
    free(list.records);
    
    return 0;
}