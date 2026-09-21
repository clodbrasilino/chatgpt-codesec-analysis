#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    size_t name_length;
    double height;
    double width;
} Student;

typedef struct {
    Student *entries;
    size_t count;
    size_t capacity;
} StudentDictionary;

static int duplicate_string(const char *source, size_t source_length, char **copy)
{
    char *result;

    if (source == NULL || copy == NULL) {
        return EINVAL;
    }

    *copy = NULL;

    if (source_length == SIZE_MAX) {
        return EOVERFLOW;
    }

    result = malloc(source_length + 1U);
    if (result == NULL) {
        return ENOMEM;
    }

    if (source_length > 0U) {
        memcpy(result, source, source_length);
    }

    result[source_length] = '\0';
    *copy = result;

    return 0;
}

static void destroy_dictionary(StudentDictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (i = 0U; i < dictionary->count; ++i) {
            free(dictionary->entries[i].name);
            dictionary->entries[i].name = NULL;
            dictionary->entries[i].name_length = 0U;
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static int add_student(StudentDictionary *dictionary,
                       const char *name,
                       size_t name_length,
                       double height,
                       double width)
{
    char *name_copy = NULL;
    int status;

    if (dictionary == NULL || name == NULL ||
        !isfinite(height) || !isfinite(width) ||
        height <= 0.0 || width <= 0.0 ||
        dictionary->count > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL) ||
        (dictionary->capacity == 0U && dictionary->entries != NULL)) {
        return EINVAL;
    }

    if (memchr(name, '\0', name_length) != NULL) {
        return EINVAL;
    }

    status = duplicate_string(name, name_length, &name_copy);
    if (status != 0) {
        return status;
    }

    if (dictionary->count == dictionary->capacity) {
        size_t new_capacity;
        Student *new_entries;

        if (dictionary->capacity == 0U) {
            new_capacity = 4U;
        } else {
            if (dictionary->capacity > SIZE_MAX / 2U) {
                free(name_copy);
                return EOVERFLOW;
            }

            new_capacity = dictionary->capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(*dictionary->entries)) {
            free(name_copy);
            return EOVERFLOW;
        }

        new_entries = realloc(dictionary->entries,
                              new_capacity * sizeof(*dictionary->entries));
        if (new_entries == NULL) {
            free(name_copy);
            return ENOMEM;
        }

        dictionary->entries = new_entries;
        dictionary->capacity = new_capacity;
    }

    dictionary->entries[dictionary->count].name = name_copy;
    dictionary->entries[dictionary->count].name_length = name_length;
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
    StudentDictionary result = {NULL, 0U, 0U};
    size_t i;

    if (dictionary == NULL || filtered == NULL ||
        dictionary == filtered ||
        dictionary->count > dictionary->capacity ||
        (dictionary->capacity != 0U && dictionary->entries == NULL) ||
        (dictionary->capacity == 0U && dictionary->entries != NULL) ||
        !isfinite(min_height) || !isfinite(max_height) ||
        !isfinite(min_width) || !isfinite(max_width) ||
        min_height > max_height || min_width > max_width) {
        return EINVAL;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        const Student *student = &dictionary->entries[i];
        int status;

        if (student->name == NULL ||
            memchr(student->name, '\0', student->name_length) != NULL ||
            student->name[student->name_length] != '\0' ||
            !isfinite(student->height) ||
            !isfinite(student->width) ||
            student->height <= 0.0 ||
            student->width <= 0.0) {
            destroy_dictionary(&result);
            return EINVAL;
        }

        if (student->height < min_height ||
            student->height > max_height ||
            student->width < min_width ||
            student->width > max_width) {
            continue;
        }

        status = add_student(&result,
                             student->name,
                             student->name_length,
                             student->height,
                             student->width);
        if (status != 0) {
            destroy_dictionary(&result);
            return status;
        }
    }

    destroy_dictionary(filtered);
    *filtered = result;

    return 0;
}

int main(void)
{
    StudentDictionary students = {NULL, 0U, 0U};
    StudentDictionary filtered = {NULL, 0U, 0U};
    size_t i;
    int status;

    status = add_student(&students, "Alice", sizeof("Alice") - 1U, 165.0, 45.0);
    if (status == 0) {
        status = add_student(&students, "Bob", sizeof("Bob") - 1U, 180.0, 52.0);
    }
    if (status == 0) {
        status = add_student(&students, "Carol", sizeof("Carol") - 1U, 172.0, 48.0);
    }
    if (status == 0) {
        status = add_student(&students, "David", sizeof("David") - 1U, 190.0, 60.0);
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
        destroy_dictionary(&filtered);
        destroy_dictionary(&students);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < filtered.count; ++i) {
        printf("%.*s: height=%.2f, width=%.2f\n",
               (int)filtered.entries[i].name_length,
               filtered.entries[i].name,
               filtered.entries[i].height,
               filtered.entries[i].width);
    }

    destroy_dictionary(&filtered);
    destroy_dictionary(&students);

    return EXIT_SUCCESS;
}