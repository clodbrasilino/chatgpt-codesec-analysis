#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_BUFFER_SIZE 50

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_BUFFER_SIZE];
    double salary;
} TupleRecord;

static void safe_str_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    size_t src_length = strnlen(src, dest_size);
    size_t copy_length = (src_length < dest_size - 1) ? src_length : dest_size - 1;
    if (copy_length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, copy_length);
    }
    dest[copy_length] = '\0';
}

void access_initial_last(const TupleRecord *record, size_t size, int *initial_id, char *initial_name, size_t initial_name_size, double *initial_salary,
                         int *last_id, char *last_name, size_t last_name_size, double *last_salary) {
    if (record == NULL || size == 0 || initial_id == NULL || initial_name == NULL || 
        last_id == NULL || last_name == NULL || initial_name_size == 0 || 
        last_name_size == 0 || initial_salary == NULL || last_salary == NULL) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    *initial_id = record[0].id;
    safe_str_copy(initial_name, record[0].name, initial_name_size);
    *initial_salary = record[0].salary;

    *last_id = record[size - 1].id;
    safe_str_copy(last_name, record[size - 1].name, last_name_size);
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
    char initial_name[NAME_BUFFER_SIZE], last_name[NAME_BUFFER_SIZE];
    double initial_salary, last_salary;

    access_initial_last(records, size, &initial_id, initial_name, sizeof(initial_name), &initial_salary,
                        &last_id, last_name, sizeof(last_name), &last_salary);

    int initial_name_truncated = (strnlen(records[0].name, sizeof(records[0].name)) >= sizeof(initial_name));
    int last_name_truncated = (strnlen(records[size - 1].name, sizeof(records[size - 1].name)) >= sizeof(last_name));

    if (initial_name_truncated || last_name_truncated) {
        fprintf(stderr, "Warning: Name truncation detected\n");
    }

    printf("Initial record: ID=%d, Name=%s, Salary=%.2f\n", initial_id, initial_name, initial_salary);
    printf("Last record: ID=%d, Name=%s, Salary=%.2f\n", last_id, last_name, last_salary);

    return 0;
}