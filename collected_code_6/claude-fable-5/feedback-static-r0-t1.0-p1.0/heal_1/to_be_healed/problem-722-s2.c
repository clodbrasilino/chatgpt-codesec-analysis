#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 64

typedef struct StudentEntry {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LEN];
    double height;
    double weight;
} StudentEntry;

typedef struct StudentDict {
    StudentEntry *entries;
    size_t count;
    size_t capacity;
} StudentDict;

static StudentDict *dict_create(size_t initial_capacity)
{
    StudentDict *dict = NULL;

    if (initial_capacity == 0U) {
        return NULL;
    }

    dict = malloc(sizeof(StudentDict));
    if (dict == NULL) {
        return NULL;
    }

    dict->entries = malloc(initial_capacity * sizeof(StudentEntry));
    if (dict->entries == NULL) {
        free(dict);
        return NULL;
    }

    dict->count = 0U;
    dict->capacity = initial_capacity;
    return dict;
}

static void dict_destroy(StudentDict *dict)
{
    if (dict != NULL) {
        free(dict->entries);
        dict->entries = NULL;
        dict->count = 0U;
        dict->capacity = 0U;
        free(dict);
    }
}

static int dict_add(StudentDict *dict, const char *name, double height, double weight)
{
    StudentEntry *new_entries = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     *  Variable 'new_capacity' is assigned a value that is never used. [unreadVariable]
     */
    size_t new_capacity = 0U;
    size_t name_len = 0U;

    if ((dict == NULL) || (name == NULL)) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    name_len = strlen(name);
    if (name_len >= MAX_NAME_LEN) {
        return -1;
    }

    if (dict->count == dict->capacity) {
        if (dict->capacity > (SIZE_MAX / (2U * sizeof(StudentEntry)))) {
            return -1;
        }
        new_capacity = dict->capacity * 2U;
        new_entries = realloc(dict->entries, new_capacity * sizeof(StudentEntry));
        if (new_entries == NULL) {
            return -1;
        }
        dict->entries = new_entries;
        dict->capacity = new_capacity;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->entries[dict->count].name, name, name_len + 1U);
    dict->entries[dict->count].height = height;
    dict->entries[dict->count].weight = weight;
    dict->count += 1U;
    return 0;
}

static StudentDict *filter_students(const StudentDict *dict, double min_height, double min_weight)
{
    StudentDict *result = NULL;
    size_t i = 0U;

    if (dict == NULL) {
        return NULL;
    }

    result = dict_create((dict->count > 0U) ? dict->count : 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < dict->count; i++) {
        if ((dict->entries[i].height >= min_height) &&
            (dict->entries[i].weight >= min_weight)) {
            if (dict_add(result, dict->entries[i].name,
                         dict->entries[i].height,
                         dict->entries[i].weight) != 0) {
                dict_destroy(result);
                return NULL;
            }
        }
    }

    return result;
}

static void dict_print(const StudentDict *dict)
{
    size_t i = 0U;

    if (dict == NULL) {
        return;
    }

    for (i = 0U; i < dict->count; i++) {
        if (printf("%s: height=%.2f, weight=%.2f\n",
                   dict->entries[i].name,
                   dict->entries[i].height,
                   dict->entries[i].weight) < 0) {
            return;
        }
    }
}

int main(void)
{
    StudentDict *students = NULL;
    StudentDict *filtered = NULL;
    int status = EXIT_SUCCESS;

    students = dict_create(8U);
    if (students == NULL) {
        (void)fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if ((dict_add(students, "Cierra Vega", 6.2, 70.0) != 0) ||
        (dict_add(students, "Alden Cantrell", 5.9, 65.0) != 0) ||
        (dict_add(students, "Kierra Gentry", 6.0, 68.0) != 0) ||
        (dict_add(students, "Pierre Cox", 5.8, 66.0) != 0)) {
        (void)fprintf(stderr, "Failed to add student\n");
        dict_destroy(students);
        return EXIT_FAILURE;
    }

    filtered = filter_students(students, 6.0, 70.0);
    if (filtered == NULL) {
        (void)fprintf(stderr, "Failed to filter students\n");
        status = EXIT_FAILURE;
    } else {
        if (printf("Students with height >= 6.0 and weight >= 70.0:\n") < 0) {
            status = EXIT_FAILURE;
        } else {
            dict_print(filtered);
        }
        dict_destroy(filtered);
    }

    dict_destroy(students);
    return status;
}