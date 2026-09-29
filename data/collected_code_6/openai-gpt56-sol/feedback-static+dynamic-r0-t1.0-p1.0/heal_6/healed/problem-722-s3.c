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
    Student *students;
    size_t count;
} StudentDictionary;

static char *duplicate_string(const char *source, size_t maximum_length)
{
    const char *terminator;
    size_t length;
    size_t allocation_size;
    char *copy;

    if (source == NULL || maximum_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', maximum_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    allocation_size = length + 1U;
    copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (snprintf(copy, allocation_size, "%s", source) < 0) {
        free(copy);
        return NULL;
    }

    return copy;
}

static void free_dictionary(StudentDictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    if (dictionary->students != NULL) {
        for (size_t i = 0U; i < dictionary->count; ++i) {
            free(dictionary->students[i].name);
        }
    }

    free(dictionary->students);
    dictionary->students = NULL;
    dictionary->count = 0U;
}

static int student_matches(const Student *student,
                           double minimum_height,
                           double maximum_height,
                           double minimum_width,
                           double maximum_width)
{
    return student != NULL &&
           student->height >= minimum_height &&
           student->height <= maximum_height &&
           student->width >= minimum_width &&
           student->width <= maximum_width;
}

static int filter_students(const StudentDictionary *source,
                           size_t maximum_name_length,
                           double minimum_height,
                           double maximum_height,
                           double minimum_width,
                           double maximum_width,
                           StudentDictionary *result)
{
    StudentDictionary temporary = {NULL, 0U};
    size_t match_count = 0U;

    if (source == NULL ||
        result == NULL ||
        source == result ||
        maximum_name_length == 0U ||
        (source->count > 0U && source->students == NULL) ||
        minimum_height > maximum_height ||
        minimum_width > maximum_width) {
        return -1;
    }

    for (size_t i = 0U; i < source->count; ++i) {
        const Student *student = &source->students[i];

        if (student->name == NULL ||
            memchr(student->name, '\0', maximum_name_length) == NULL) {
            return -1;
        }

        if (student_matches(student,
                            minimum_height,
                            maximum_height,
                            minimum_width,
                            maximum_width)) {
            if (match_count == SIZE_MAX) {
                return -1;
            }
            ++match_count;
        }
    }

    if (match_count != 0U) {
        if (match_count > SIZE_MAX / sizeof(*temporary.students)) {
            return -1;
        }

        temporary.students = calloc(match_count, sizeof(*temporary.students));
        if (temporary.students == NULL) {
            return -1;
        }

        for (size_t i = 0U; i < source->count; ++i) {
            const Student *student = &source->students[i];
            Student *destination;

            if (!student_matches(student,
                                 minimum_height,
                                 maximum_height,
                                 minimum_width,
                                 maximum_width)) {
                continue;
            }

            if (temporary.count >= match_count) {
                free_dictionary(&temporary);
                return -1;
            }

            destination = &temporary.students[temporary.count];
            destination->name =
                duplicate_string(student->name, maximum_name_length);

            if (destination->name == NULL) {
                free_dictionary(&temporary);
                return -1;
            }

            destination->height = student->height;
            destination->width = student->width;
            ++temporary.count;
        }

        if (temporary.count != match_count) {
            free_dictionary(&temporary);
            return -1;
        }
    }

    free_dictionary(result);
    *result = temporary;
    return 0;
}

int main(void)
{
    enum { MAXIMUM_NAME_LENGTH = 256 };

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
                        MAXIMUM_NAME_LENGTH,
                        170.0,
                        185.0,
                        60.0,
                        80.0,
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