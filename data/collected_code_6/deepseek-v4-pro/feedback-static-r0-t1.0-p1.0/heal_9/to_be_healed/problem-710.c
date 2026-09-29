#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
    double salary;
} Tuple;

typedef struct {
    int first_id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first_name[50];
    double first_salary;
    int last_id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char last_name[50];
    double last_salary;
    int has_data;
} TupleAccessResult;

static void safe_copy_string(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || dest_size == 0) {
        return;
    }
    
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }
    
    size_t i;
    for (i = 0; i < dest_size - 1; i++) {
        if (src[i] == '\0') {
            break;
        }
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

TupleAccessResult access_tuple_data(const Tuple *records, int count) {
    TupleAccessResult result;
    memset(&result, 0, sizeof(result));
    
    if (records == NULL || count <= 0) {
        result.has_data = 0;
        return result;
    }
    
    result.first_id = records[0].id;
    safe_copy_string(result.first_name, sizeof(result.first_name), records[0].name);
    result.first_salary = records[0].salary;
    
    if (count > 1) {
        result.last_id = records[count - 1].id;
        safe_copy_string(result.last_name, sizeof(result.last_name), records[count - 1].name);
        result.last_salary = records[count - 1].salary;
    } else {
        result.last_id = records[0].id;
        safe_copy_string(result.last_name, sizeof(result.last_name), records[0].name);
        result.last_salary = records[0].salary;
    }
    
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