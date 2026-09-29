#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 64

typedef struct StudentEntry {
    char *name;
    double height;
    double width;
    struct StudentEntry *next;
} StudentEntry;

typedef struct {
    StudentEntry *head;
    size_t count;
} StudentDict;

static StudentDict *dict_create(void)
{
    StudentDict *dict = malloc(sizeof(StudentDict));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;
    dict->count = 0;
    return dict;
}

static int dict_insert(StudentDict *dict, const char *name, double height, double width)
{
    StudentEntry *entry;
    size_t name_len;

    if (dict == NULL || name == NULL) {
        return -1;
    }

    name_len = strnlen(name, MAX_NAME_LEN);
    if (name_len == 0 || name_len >= MAX_NAME_LEN) {
        return -1;
    }

    entry = malloc(sizeof(StudentEntry));
    if (entry == NULL) {
        return -1;
    }

    entry->name = malloc(name_len + 1);
    if (entry->name == NULL) {
        free(entry);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(entry->name, name, name_len);
    entry->name[name_len] = '\0';

    entry->height = height;
    entry->width = width;
    entry->next = dict->head;
    dict->head = entry;
    dict->count++;
    return 0;
}

static void dict_destroy(StudentDict *dict)
{
    StudentEntry *current;
    StudentEntry *next;

    if (dict == NULL) {
        return;
    }

    current = dict->head;
    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    free(dict);
}

static StudentDict *filter_students(const StudentDict *dict, double min_height, double min_width)
{
    StudentDict *filtered;
    const StudentEntry *current;

    if (dict == NULL) {
        return NULL;
    }

    filtered = dict_create();
    if (filtered == NULL) {
        return NULL;
    }

    current = dict->head;
    while (current != NULL) {
        if (current->height >= min_height && current->width >= min_width) {
            if (dict_insert(filtered, current->name, current->height, current->width) != 0) {
                dict_destroy(filtered);
                return NULL;
            }
        }
        current = current->next;
    }
    return filtered;
}

static void dict_print(const StudentDict *dict)
{
    const StudentEntry *current;

    if (dict == NULL) {
        return;
    }

    current = dict->head;
    while (current != NULL) {
        printf("%s: height=%.2f, width=%.2f\n", current->name, current->height, current->width);
        current = current->next;
    }
}

int main(void)
{
    StudentDict *students;
    StudentDict *filtered;

    students = dict_create();
    if (students == NULL) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_insert(students, "Alice", 165.5, 45.0) != 0 ||
        dict_insert(students, "Bob", 180.2, 60.5) != 0 ||
        dict_insert(students, "Carol", 155.0, 40.2) != 0 ||
        dict_insert(students, "Dave", 175.8, 55.3) != 0) {
        fprintf(stderr, "Failed to insert student\n");
        dict_destroy(students);
        return EXIT_FAILURE;
    }

    printf("All students:\n");
    dict_print(students);

    filtered = filter_students(students, 160.0, 50.0);
    if (filtered == NULL) {
        fprintf(stderr, "Failed to filter students\n");
        dict_destroy(students);
        return EXIT_FAILURE;
    }

    printf("\nFiltered students (height >= 160.0, width >= 50.0):\n");
    dict_print(filtered);

    dict_destroy(filtered);
    dict_destroy(students);
    return EXIT_SUCCESS;
}