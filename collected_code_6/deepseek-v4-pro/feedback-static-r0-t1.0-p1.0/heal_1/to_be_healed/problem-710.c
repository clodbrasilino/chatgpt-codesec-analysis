#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    double salary;
} Tuple;

typedef struct {
    int first_id;
    char first_name[50];
    double first_salary;
    int last_id;
    char last_name[50];
    double last_salary;
    int has_data;
} TupleAccessResult;

TupleAccessResult access_tuple_data(Tuple *records, int count) {
    TupleAccessResult result;
    
    if (records == NULL || count <= 0) {
        result.has_data = 0;
        /* Possible weaknesses found:
         *  Uninitialized variables: result.first_id, result.first_salary, result.last_id, result.last_salary [uninitvar]
         */
        return result;
    }
    
    result.first_id = records[0].id;
    strncpy(result.first_name, records[0].name, sizeof(result.first_name) - 1);
    result.first_name[sizeof(result.first_name) - 1] = '\0';
    result.first_salary = records[0].salary;
    
    result.last_id = records[count - 1].id;
    strncpy(result.last_name, records[count - 1].name, sizeof(result.last_name) - 1);
    result.last_name[sizeof(result.last_name) - 1] = '\0';
    result.last_salary = records[count - 1].salary;
    
    result.has_data = 1;
    return result;
}

int main(void) {
    Tuple records[] = {
        {1, "Alice", 55000.0},
        {2, "Bob", 60000.0},
        {3, "Charlie", 65000.0},
        {4, "Diana", 70000.0}
    };
    
    int count = sizeof(records) / sizeof(records[0]);
    TupleAccessResult result = access_tuple_data(records, count);
    
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