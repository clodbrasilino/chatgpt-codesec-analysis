#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    double salary;
} TupleRecord;

void access_initial_last(const TupleRecord *record, size_t size, int *initial_id, char *initial_name, double *initial_salary,
                         int *last_id, char *last_name, double *last_salary) {
    if (record == NULL || size == 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    *initial_id = record[0].id;
    strncpy(initial_name, record[0].name, 49);
    initial_name[49] = '\0';
    *initial_salary = record[0].salary;

    *last_id = record[size - 1].id;
    strncpy(last_name, record[size - 1].name, 49);
    last_name[49] = '\0';
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
    char initial_name[50], last_name[50];
    double initial_salary, last_salary;

    access_initial_last(records, size, &initial_id, initial_name, &initial_salary,
                        &last_id, last_name, &last_salary);

    printf("Initial record: ID=%d, Name=%s, Salary=%.2f\n", initial_id, initial_name, initial_salary);
    printf("Last record: ID=%d, Name=%s, Salary=%.2f\n", last_id, last_name, last_salary);

    return 0;
}