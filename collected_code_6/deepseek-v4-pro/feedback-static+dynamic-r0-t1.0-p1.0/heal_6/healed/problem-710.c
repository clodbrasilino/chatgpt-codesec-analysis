#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NAME_SIZE 50

typedef struct {
    int id;
    char name[NAME_SIZE];
    double salary;
} Tuple;

typedef struct {
    int first_id;
    char first_name[NAME_SIZE];
    double first_salary;
    int last_id;
    char last_name[NAME_SIZE];
    double last_salary;
    int has_data;
    int error;
} TupleAccessResult;

TupleAccessResult access_tuple_data(const Tuple *records, size_t count) {
    TupleAccessResult result;
    size_t name_len;
    size_t max_copy;
    
    memset(&result, 0, sizeof(result));
    
    if (records == NULL || count == 0) {
        result.has_data = 0;
        result.error = 1;
        return result;
    }
    
    result.first_id = records[0].id;
    name_len = strnlen(records[0].name, NAME_SIZE);
    max_copy = (name_len < NAME_SIZE) ? name_len : (NAME_SIZE - 1);
    memcpy(result.first_name, records[0].name, max_copy);
    result.first_name[max_copy] = '\0';
    result.first_salary = records[0].salary;
    
    result.last_id = records[count - 1].id;
    name_len = strnlen(records[count - 1].name, NAME_SIZE);
    max_copy = (name_len < NAME_SIZE) ? name_len : (NAME_SIZE - 1);
    memcpy(result.last_name, records[count - 1].name, max_copy);
    result.last_name[max_copy] = '\0';
    result.last_salary = records[count - 1].salary;
    
    result.has_data = 1;
    result.error = 0;
    return result;
}

int main(void) {
    Tuple records[] = {
        {1, "Alice", 55000.0},
        {2, "Bob", 60000.0},
        {3, "Charlie", 65000.0},
        {4, "Diana", 70000.0}
    };
    
    size_t count = sizeof(records) / sizeof(records[0]);
    TupleAccessResult result = access_tuple_data(records, count);
    
    if (result.error) {
        printf("Error accessing tuple data.\n");
        return 1;
    }
    
    if (result.has_data) {
        printf("First record: ID=%d, Name=%s, Salary=%.2f\n", 
               result.first_id, result.first_name, result.first_salary);
        printf("Last record: ID=%d, Name=%s, Salary=%.2f\n", 
               result.last_id, result.last_name, result.last_salary);
    } else {
        printf("No valid data to access.\n");
    }
    
    return 0;
}