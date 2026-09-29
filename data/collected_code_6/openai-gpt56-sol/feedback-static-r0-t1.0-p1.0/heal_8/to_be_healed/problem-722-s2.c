#include <errno.h>
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

static int duplicate_string(const char *source,
                            size_t source_size,
                            char **destination,
                            size_t *destination_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || destination == NULL ||
        destination_length == NULL || source_size == 0U) {
        return EINVAL;
    }

    *destination = NULL;
    *destination_length = 0U;

    terminator = memchr(source, '\0', source_size);
    if (terminator == NULL) {
        return EINVAL;
    }

    length = (size_t)(terminator - source);
    if (length > SIZE_MAX - 1U) {
        return EOVERFLOW;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return ENOMEM;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    *destination = copy;
    *destination_length = length;
    return 0;
}

static int dictionary_is_valid(const StudentDictionary *dictionary)
{
    if (dictionary == NULL || dictionary->count > dictionary->capacity) {
        return 0;
    }

    if (dictionary->capacity == 0U) {
        return dictionary->entries == NULL && dictionary->count == 0U;
    }

    return dictionary->entries != NULL;
}

static void destroy_dictionary(StudentDictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (size_t i = 0U; i < dictionary->count; ++i) {
            free(dictionary->entries[i].name);
            dictionary->entries[i].name = NULL;
            dictionary->entries[i].name_length = 0U;
            dictionary->entries[i].height = 0.0;
            dictionary->entries[i].width = 0.0;
        }
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
    dictionary->capacity = 0U;
}

static int reserve_students(StudentDictionary *dictionary,
                            size_t required_capacity)
{
    size_t maximum_capacity;
    size_t new_capacity;
    Student *new_entries;

    if (!dictionary_is_valid(dictionary)) {
        return EINVAL;
    }

    if (required_capacity <= dictionary->capacity) {
        return 0;
    }

    maximum_capacity = SIZE_MAX / sizeof(*dictionary->entries);
    if (required_capacity > maximum_capacity) {
        return EOVERFLOW;
    }

    new_capacity = dictionary->capacity == 0U ? 4U : dictionary->capacity;

    while (new_capacity < required_capacity) {
        if (new_capacity > maximum_capacity / 2U) {
            new_capacity = required_capacity;
            break;
        }
        new_capacity *= 2U;
    }

    new_entries = realloc(dictionary->entries,
                          new_capacity * sizeof(*new_entries));
    if (new_entries == NULL) {
        return ENOMEM;
    }

    dictionary->entries = new_entries;
    dictionary->capacity = new_capacity;
    return 0;
}

static int add_student_n(StudentDictionary *dictionary,
                         const char *name,
                         size_t name_size,
                         double height,
                         double width)
{
    char *name_copy;
    size_t name_length;
    int status;

    if (!dictionary_is_valid(dictionary) ||
        name == NULL ||
        name_size == 0U ||
        !(height > 0.0) ||
        !(width > 0.0)) {
        return EINVAL;
    }

    status = duplicate_string(name, name_size, &name_copy, &name_length);
    if (status != 0) {
        return status;
    }

    if (dictionary->count == SIZE_MAX) {
        free(name_copy);
        return EOVERFLOW;
    }

    status = reserve_students(dictionary, dictionary->count + 1U);
    if (status != 0) {
        free(name_copy);
        return status;
    }

    dictionary->entries[dictionary->count] = (Student){
        .name = name_copy,
        .name_length = name_length,
        .height = height,
        .width = width
    };
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

    if (!dictionary_is_valid(dictionary) ||
        !dictionary_is_valid(filtered) ||
        dictionary == filtered ||
        !(min_height <= max_height) ||
        !(min_width <= max_width)) {
        return EINVAL;
    }

    for (size_t i = 0U; i < dictionary->count; ++i) {
        const Student *student = &dictionary->entries[i];
        int status;

        if (student->name == NULL ||
            student->name_length == SIZE_MAX ||
            student->name[student->name_length] != '\0' ||
            memchr(student->name, '\0', student->name_length) != NULL) {
            destroy_dictionary(&result);
            return EINVAL;
        }

        if (student->height < min_height ||
            student->height > max_height ||
            student->width < min_width ||
            student->width > max_width) {
            continue;
        }

        status = add_student_n(&result,
                               student->name,
                               student->name_length + 1U,
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
    int status;

    status = add_student_n(&students, "Alice", sizeof("Alice"), 165.0, 45.0);
    if (status == 0) {
        status = add_student_n(&students, "Bob", sizeof("Bob"), 180.0, 52.0);
    }
    if (status == 0) {
        status = add_student_n(&students, "Carol", sizeof("Carol"), 172.0,
                               48.0);
    }
    if (status == 0) {
        status = add_student_n(&students, "David", sizeof("David"), 190.0,
                               60.0);
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

    for (size_t i = 0U; i < filtered.count; ++i) {
        printf("%s: height=%.2f, width=%.2f\n",
               filtered.entries[i].name,
               filtered.entries[i].height,
               filtered.entries[i].width);
    }

    destroy_dictionary(&filtered);
    destroy_dictionary(&students);
    return EXIT_SUCCESS;
}