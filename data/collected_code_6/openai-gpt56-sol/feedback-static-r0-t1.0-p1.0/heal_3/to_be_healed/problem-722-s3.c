#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    double height;
    double width;
} Student;

typedef struct {
    Student *students;
    size_t count;
} StudentDictionary;

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || max_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
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
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->students != NULL) {
        for (size_t i = 0U; i < dictionary->count; ++i) {
            free((void *)dictionary->students[i].name);
        }

        free(dictionary->students);
    }

    dictionary->students = NULL;
    dictionary->count = 0U;
}

static int filter_students(const StudentDictionary *source,
                           double min_height,
                           double max_height,
                           double min_width,
                           double max_width,
                           size_t max_name_length,
                           StudentDictionary *result)
{
    size_t matches = 0U;
    size_t result_index = 0U;

    if (source == NULL ||
        result == NULL ||
        source == result ||
        max_name_length == 0U ||
        (source->count != 0U && source->students == NULL) ||
        min_height > max_height ||
        min_width > max_width) {
        return -1;
    }

    result->students = NULL;
    result->count = 0U;

    for (size_t i = 0U; i < source->count; ++i) {
        const Student *student = &source->students[i];

        if (student->name == NULL ||
            memchr(student->name, '\0', max_name_length) == NULL) {
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

    if (matches > SIZE_MAX / sizeof(*result->students)) {
        return -1;
    }

    result->students = calloc(matches, sizeof(*result->students));
    if (result->students == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < source->count; ++i) {
        const Student *student = &source->students[i];

        if (student->height >= min_height &&
            student->height <= max_height &&
            student->width >= min_width &&
            student->width <= max_width) {
            Student *destination = &result->students[result_index];

            destination->name =
                duplicate_string(student->name, max_name_length);

            if (destination->name == NULL) {
                result->count = result_index;
                free_dictionary(result);
                return -1;
            }

            destination->height = student->height;
            destination->width = student->width;
            ++result_index;
        }
    }

    result->count = result_index;
    return 0;
}

int main(void)
{
    Student students[] = {
        {"Alice", 165.0, 50.0},
        {"Bob", 180.0, 75.0},
        {"Carol", 172.0, 65.0},
        {"David", 190.0, 90.0}
    };

    StudentDictionary dictionary = {
        students,
        sizeof(students) / sizeof(students[0])
    };
    StudentDictionary filtered = {NULL, 0U};

    if (filter_students(&dictionary,
                        170.0,
                        185.0,
                        60.0,
                        80.0,
                        256U,
                        &filtered) != 0) {
        fputs("Unable to filter students.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < filtered.count; ++i) {
        if (printf("%s: height=%.2f, width=%.2f\n",
                   filtered.students[i].name,
                   filtered.students[i].height,
                   filtered.students[i].width) < 0) {
            free_dictionary(&filtered);
            return EXIT_FAILURE;
        }
    }

    free_dictionary(&filtered);
    return EXIT_SUCCESS;
}