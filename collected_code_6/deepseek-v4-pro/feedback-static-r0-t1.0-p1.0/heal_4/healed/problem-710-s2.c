#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    double salary;
} TupleRecord;

static void safe_str_copy(char *dest, const char *src, size_t dest_size) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    size_t i;
    for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
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
    char initial_name[50], last_name[50];
    double initial_salary, last_salary;

    access_initial_last(records, size, &initial_id, initial_name, sizeof(initial_name), &initial_salary,
                        &last_id, last_name, sizeof(last_name), &last_salary);

    int initial_name_truncated = (strlen(records[0].name) >= sizeof(initial_name));
    int last_name_truncated = (strlen(records[size - 1].name) >= sizeof(last_name));

    if (initial_name_truncated || last_name_truncated) {
        fprintf(stderr, "Warning: Name truncation detected\n");
    }

    printf("Initial record: ID=%d, Name=%s, Salary=%.2f\n", initial_id, initial_name, initial_salary);
    printf("Last record: ID=%d, Name=%s, Salary=%.2f\n", last_id, last_name, last_salary);

    return 0;
}