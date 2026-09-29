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

static char *copy_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void free_dictionary(StudentDictionary *dictionary)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    if (dictionary->entries != NULL) {
        for (i = 0U; i < dictionary->count; ++i) {
            free(dictionary->entries[i].name);
            dictionary->entries[i].name = NULL;
        }
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
    size_t i;
    size_t matches = 0U;
    size_t output_index = 0U;

    if (source == NULL || result == NULL || source == result ||
        (source->count > 0U && source->entries == NULL) ||
        min_height > max_height || min_width > max_width) {
        return -1;
    }

    result->entries = NULL;
    result->count = 0U;

    for (i = 0U; i < source->count; ++i) {
        const Student *student = &source->entries[i];

        if (student->name == NULL) {
            return -1;
        }

        if (student->height >= min_height &&
            student->height <= max_height &&
            student->width >= min_width &&
            student->width <= max_width) {
            if (matches == SIZE_MAX) {
                return -1;
            }
            ++matches;
        }
    }

    if (matches == 0U) {
        return 0;
    }

    if (matches > SIZE_MAX / sizeof(*result->entries)) {
        return -1;
    }

    result->entries = calloc(matches, sizeof(*result->entries));
    if (result->entries == NULL) {
        return -1;
    }

    for (i = 0U; i < source->count; ++i) {
        const Student *student = &source->entries[i];

        if (student->height >= min_height &&
            student->height <= max_height &&
            student->width >= min_width &&
            student->width <= max_width) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t name_length = strlen(student->name);

            result->entries[output_index].name =
                copy_string(student->name, name_length);

            if (result->entries[output_index].name == NULL) {
                result->count = output_index;
                free_dictionary(result);
                return -1;
            }

            result->entries[output_index].height = student->height;
            result->entries[output_index].width = student->width;
            ++output_index;
            result->count = output_index;
        }
    }

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
    size_t i;

    if (filter_students(&dictionary, 160.0, 175.0, 40.0, 50.0,
                        &filtered) != 0) {
        fputs("Failed to filter students.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < filtered.count; ++i) {
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