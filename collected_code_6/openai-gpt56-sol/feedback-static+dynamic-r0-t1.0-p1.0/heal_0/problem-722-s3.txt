#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    double height;
    double width;
} Student;

typedef struct {
    Student *students;
    size_t count;
} StudentDictionary;

static char *duplicate_string(const char *source)
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
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0U; i < dictionary->count; ++i) {
        free(dictionary->students[i].name);
    }

    free(dictionary->students);
    dictionary->students = NULL;
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
    size_t result_index = 0U;

    if (source == NULL || result == NULL ||
        (source->count > 0U && source->students == NULL) ||
        min_height > max_height || min_width > max_width) {
        return -1;
    }

    result->students = NULL;
    result->count = 0U;

    for (i = 0U; i < source->count; ++i) {
        const Student *student = &source->students[i];

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
        return 0;
    }

    if (matches > SIZE_MAX / sizeof(*result->students)) {
        return -1;
    }

    result->students = calloc(matches, sizeof(*result->students));
    if (result->students == NULL) {
        return -1;
    }

    result->count = matches;

    for (i = 0U; i < source->count; ++i) {
        const Student *student = &source->students[i];

        if (student->height >= min_height &&
            student->height <= max_height &&
            student->width >= min_width &&
            student->width <= max_width) {
            result->students[result_index] = *student;
            result->students[result_index].name = duplicate_string(student->name);

            if (result->students[result_index].name == NULL) {
                free_dictionary(result);
                return -1;
            }

            ++result_index;
        }
    }

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
    size_t i;

    if (filter_students(&dictionary, 170.0, 185.0, 60.0, 80.0, &filtered) != 0) {
        fputs("Unable to filter students.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < filtered.count; ++i) {
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