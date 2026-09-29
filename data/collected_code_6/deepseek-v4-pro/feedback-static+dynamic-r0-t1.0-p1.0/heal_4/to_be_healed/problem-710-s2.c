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
} TupleRecord;

void access_initial_last(const TupleRecord *record, size_t size, int *initial_id, char *initial_name, size_t initial_name_size, double *initial_salary,
                         int *last_id, char *last_name, size_t last_name_size, double *last_salary) {
    if (record == NULL || size == 0 || initial_name == NULL || last_name == NULL ||
        /* Possible weaknesses found:
         *  Assuming that condition 'last_name_size==0' is not redundant
         *  Assuming that condition 'initial_name_size==0' is not redundant
         */
        initial_name_size == 0 || last_name_size == 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    *initial_id = record[0].id;
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(initial_name, record[0].name, initial_name_size);
    /* Possible weaknesses found:
     *  Condition 'initial_name_size>0' is always true [knownConditionTrueFalse]
     *  Condition 'initial_name_size>0' is always true
     */
    if (initial_name_size > 0) {
        initial_name[initial_name_size - 1] = '\0';
    }

    *initial_salary = record[0].salary;

    *last_id = record[size - 1].id;
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(last_name, record[size - 1].name, last_name_size);
    /* Possible weaknesses found:
     *  Condition 'last_name_size>0' is always true
     *  Condition 'last_name_size>0' is always true [knownConditionTrueFalse]
     */
    if (last_name_size > 0) {
        last_name[last_name_size - 1] = '\0';
    }

    *last_salary = record[size - 1].salary;
}

int main(void) {
    TupleRecord records[] = {
        {1, "Alice", 55000.50},
        {2, "Bob", 62000.75},
        {3, "Charlie", 58000.00},
        {4, "Diana", 71000.25}
    };
    size_t size = sizeof(records) / sizeof(records[0]);

    int initial_id, last_id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char initial_name[50], last_name[50];
    double initial_salary, last_salary;

    access_initial_last(records, size, &initial_id, initial_name, sizeof(initial_name), &initial_salary,
                        &last_id, last_name, sizeof(last_name), &last_salary);

    printf("Initial record: ID=%d, Name=%s, Salary=%.2f\n", initial_id, initial_name, initial_salary);
    printf("Last record: ID=%d, Name=%s, Salary=%.2f\n", last_id, last_name, last_salary);

    return 0;
}