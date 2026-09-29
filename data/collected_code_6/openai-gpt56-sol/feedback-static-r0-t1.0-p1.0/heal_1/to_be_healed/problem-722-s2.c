#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char *name;
    double height;
    double width;
} Student;

typedef struct {
    Student *entries;
    size_t count;
    size_t capacity;
} StudentDictionary;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length + 1U);
    return copy;
}

static void destroy_dictionary(StudentDictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        free(dictionary->entries[i].name);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static int add_student(StudentDictionary *dictionary,
                       const char *name,
                       double height,
                       double width)
{
    Student *new_entries;
    char *name_copy;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (dictionary == NULL || name == NULL || height <= 0.0 || width <= 0.0) {
        return EINVAL;
    }

    if (dictionary->count == dictionary->capacity) {
        new_capacity = dictionary->capacity == 0U ? 4U : dictionary->capacity * 2U;

        if (new_capacity < dictionary->capacity ||
            new_capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
            return EOVERFLOW;
        }

        new_entries = realloc(dictionary->entries,
                              new_capacity * sizeof(*dictionary->entries));
        if (new_entries == NULL) {
            return ENOMEM;
        }

        dictionary->entries = new_entries;
        dictionary->capacity = new_capacity;
    }

    name_copy = duplicate_string(name);
    if (name_copy == NULL) {
        return ENOMEM;
    }

    dictionary->entries[dictionary->count].name = name_copy;
    dictionary->entries[dictionary->count].height = height;
    dictionary->entries[dictionary->count].width = width;
    ++dictionary->count;

    return 0;
}

static int filter_students(const StudentDictionary *dictionary,
                           double min_height,
                           double max_height,
                           double min_width,
                           double max_width,
                           StudentDictionary *filtered)
{
    size_t i;
    int status;

    if (dictionary == NULL || filtered == NULL ||
        min_height > max_height || min_width > max_width) {
        return EINVAL;
    }

    filtered->entries = NULL;
    filtered->count = 0U;
    filtered->capacity = 0U;

    for (i = 0U; i < dictionary->count; ++i) {
        const Student *student = &dictionary->entries[i];

        if (student->height >= min_height &&
            student->height <= max_height &&
            student->width >= min_width &&
            student->width <= max_width) {
            status = add_student(filtered,
                                 student->name,
                                 student->height,
                                 student->width);
            if (status != 0) {
                destroy_dictionary(filtered);
                return status;
            }
        }
    }

    return 0;
}

int main(void)
{
    StudentDictionary students = {NULL, 0U, 0U};
    StudentDictionary filtered = {NULL, 0U, 0U};
    size_t i;
    int status;

    status = add_student(&students, "Alice", 165.0, 45.0);
    if (status == 0) {
        status = add_student(&students, "Bob", 180.0, 52.0);
    }
    if (status == 0) {
        status = add_student(&students, "Carol", 172.0, 48.0);
    }
    if (status == 0) {
        status = add_student(&students, "David", 190.0, 60.0);
    }

    if (status != 0) {
        fprintf(stderr, "Failed to create student dictionary: %s\n",
                strerror(status));
        destroy_dictionary(&students);
        return EXIT_FAILURE;
    }

    status = filter_students(&students, 170.0, 185.0, 45.0, 55.0, &filtered);
    if (status != 0) {
        fprintf(stderr, "Failed to filter students: %s\n", strerror(status));
        destroy_dictionary(&students);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < filtered.count; ++i) {
        printf("%s: height=%.2f, width=%.2f\n",
               filtered.entries[i].name,
               filtered.entries[i].height,
               filtered.entries[i].width);
    }

    destroy_dictionary(&filtered);
    destroy_dictionary(&students);

    return EXIT_SUCCESS;
}