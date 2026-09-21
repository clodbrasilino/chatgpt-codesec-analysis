#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME_LEN 64

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LEN];
    double height;
    double width;
} Student;

typedef struct {
    Student *entries;
    size_t count;
    size_t capacity;
} StudentDict;

int dict_init(StudentDict *dict, size_t initial_capacity);
int dict_add(StudentDict *dict, const char *name, double height, double width);
int dict_filter(const StudentDict *src, StudentDict *dst,
                double min_height, double min_width);
void dict_free(StudentDict *dict);
void dict_print(const StudentDict *dict);

int dict_init(StudentDict *dict, size_t initial_capacity)
{
    if (dict == NULL || initial_capacity == 0) {
        return -1;
    }
    if (initial_capacity > SIZE_MAX / sizeof(Student)) {
        return -1;
    }
    dict->entries = malloc(initial_capacity * sizeof(Student));
    if (dict->entries == NULL) {
        return -1;
    }
    dict->count = 0;
    dict->capacity = initial_capacity;
    return 0;
}

int dict_add(StudentDict *dict, const char *name, double height, double width)
{
    size_t name_len;

    if (dict == NULL || name == NULL || dict->entries == NULL) {
        return -1;
    }
    name_len = strnlen(name, MAX_NAME_LEN);
    if (name_len >= MAX_NAME_LEN) {
        return -1;
    }
    if (dict->count == dict->capacity) {
        if (dict->capacity > SIZE_MAX / (2 * sizeof(Student))) {
            return -1;
        }
        size_t new_capacity = dict->capacity * 2;
        Student *tmp = realloc(dict->entries, new_capacity * sizeof(Student));
        if (tmp == NULL) {
            return -1;
        }
        dict->entries = tmp;
        dict->capacity = new_capacity;
    }
    if (name_len > sizeof(dict->entries[dict->count].name) - 1) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->entries[dict->count].name, name, name_len);
    dict->entries[dict->count].name[name_len] = '\0';
    dict->entries[dict->count].height = height;
    dict->entries[dict->count].width = width;
    dict->count++;
    return 0;
}

int dict_filter(const StudentDict *src, StudentDict *dst,
                double min_height, double min_width)
{
    if (src == NULL || dst == NULL || src->entries == NULL) {
        return -1;
    }
    for (size_t i = 0; i < src->count; i++) {
        if (src->entries[i].height >= min_height &&
            src->entries[i].width >= min_width) {
            if (dict_add(dst, src->entries[i].name,
                         src->entries[i].height,
                         src->entries[i].width) != 0) {
                return -1;
            }
        }
    }
    return 0;
}

void dict_free(StudentDict *dict)
{
    if (dict != NULL) {
        free(dict->entries);
        dict->entries = NULL;
        dict->count = 0;
        dict->capacity = 0;
    }
}

void dict_print(const StudentDict *dict)
{
    if (dict == NULL || dict->entries == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->count; i++) {
        printf("%s: height=%.2f, width=%.2f\n",
               dict->entries[i].name,
               dict->entries[i].height,
               dict->entries[i].width);
    }
}

int main(void)
{
    StudentDict students;
    StudentDict filtered;

    if (dict_init(&students, 4) != 0) {
        fprintf(stderr, "Failed to initialize student dictionary\n");
        return EXIT_FAILURE;
    }
    if (dict_init(&filtered, 4) != 0) {
        fprintf(stderr, "Failed to initialize filtered dictionary\n");
        dict_free(&students);
        return EXIT_FAILURE;
    }

    if (dict_add(&students, "Alice", 165.5, 40.0) != 0 ||
        dict_add(&students, "Bob", 180.2, 55.3) != 0 ||
        dict_add(&students, "Carol", 158.0, 38.5) != 0 ||
        dict_add(&students, "Dave", 175.0, 50.0) != 0) {
        fprintf(stderr, "Failed to add student\n");
        dict_free(&students);
        dict_free(&filtered);
        return EXIT_FAILURE;
    }

    if (dict_filter(&students, &filtered, 160.0, 45.0) != 0) {
        fprintf(stderr, "Failed to filter students\n");
        dict_free(&students);
        dict_free(&filtered);
        return EXIT_FAILURE;
    }

    printf("All students:\n");
    dict_print(&students);
    printf("\nFiltered students (height >= 160.0, width >= 45.0):\n");
    dict_print(&filtered);

    dict_free(&students);
    dict_free(&filtered);
    return EXIT_SUCCESS;
}