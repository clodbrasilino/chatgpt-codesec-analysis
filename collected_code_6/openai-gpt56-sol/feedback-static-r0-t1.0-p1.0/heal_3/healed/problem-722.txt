#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    double height;
    double width;
} Student;

typedef struct {
    Student *entries;
    size_t count;
} StudentDictionary;

static char *copy_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static void free_dictionary(StudentDictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    for (size_t i = 0U; i < dictionary->count; ++i) {
        free(dictionary->entries[i].name);
    }

    free(dictionary->entries);
    dictionary->entries = NULL;
    dictionary->count = 0U;
}

static int filter_students(const StudentDictionary *source,
                           double min_height,
                           double max_height,
                           double min_width,
                           double max_width,
                           StudentDictionary *result)
{
    StudentDictionary temporary = {NULL, 0U};
    size_t matches = 0U;

    if (source == NULL ||
        result == NULL ||
        source == result ||
        (source->count != 0U && source->entries == NULL) ||
        min_height > max_height ||
        min_width > max_width) {
        return -1;
    }

    for (size_t i = 0U; i < source->count; ++i) {
        const Student *student = &source->entries[i];

        if (student->name == NULL) {
            return -1;
        }

        if (student->height >= min_height &&
            student->height <= max_height &&
            student->width >= min_width &&
            student->width <= max_width) {
            ++matches;
        }
    }

    if (matches == 0U) {
        result->entries = NULL;
        result->count = 0U;
        return 0;
    }

    if (matches > SIZE_MAX / sizeof(*temporary.entries)) {
        return -1;
    }

    temporary.entries = calloc(matches, sizeof(*temporary.entries));
    if (temporary.entries == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < source->count; ++i) {
        const Student *student = &source->entries[i];

        if (student->height >= min_height &&
            student->height <= max_height &&
            student->width >= min_width &&
            student->width <= max_width) {
            Student *destination = &temporary.entries[temporary.count];

            destination->name = copy_string(student->name);
            if (destination->name == NULL) {
                free_dictionary(&temporary);
                return -1;
            }

            destination->height = student->height;
            destination->width = student->width;
            ++temporary.count;
        }
    }

    result->entries = temporary.entries;
    result->count = temporary.count;
    return 0;
}

int main(void)
{
    Student students[] = {
        {"Alice", 165.0, 45.0},
        {"Bob", 180.0, 55.0},
        {"Carol", 172.0, 48.0},
        {"David", 158.0, 42.0}
    };
    StudentDictionary dictionary = {
        students,
        sizeof(students) / sizeof(students[0])
    };
    StudentDictionary filtered = {NULL, 0U};

    if (filter_students(&dictionary, 160.0, 175.0, 40.0, 50.0,
                        &filtered) != 0) {
        fputs("Failed to filter students.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < filtered.count; ++i) {
        if (printf("%s: height=%.1f, width=%.1f\n",
                   filtered.entries[i].name,
                   filtered.entries[i].height,
                   filtered.entries[i].width) < 0) {
            free_dictionary(&filtered);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(&filtered);
    return EXIT_SUCCESS;
}