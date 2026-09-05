#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LEN 50

typedef struct {
    char name[MAX_NAME_LEN];
    float height;
    float width;
} Student;

typedef struct {
    Student *students;
    size_t count;
    size_t capacity;
} StudentDict;

bool dict_init(StudentDict *dict, size_t initial_capacity) {
    if (dict == NULL || initial_capacity == 0) {
        return false;
    }
    dict->students = malloc(initial_capacity * sizeof(Student));
    if (dict->students == NULL) {
        return false;
    }
    dict->count = 0;
    dict->capacity = initial_capacity;
    return true;
}

bool dict_add(StudentDict *dict, const char *name, float height, float width) {
    if (dict == NULL || name == NULL) {
        return false;
    }
    if (dict->count >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        Student *temp = realloc(dict->students, new_capacity * sizeof(Student));
        if (temp == NULL) {
            return false;
        }
        dict->students = temp;
        dict->capacity = new_capacity;
    }
    strncpy(dict->students[dict->count].name, name, MAX_NAME_LEN - 1);
    dict->students[dict->count].name[MAX_NAME_LEN - 1] = '\0';
    dict->students[dict->count].height = height;
    dict->students[dict->count].width = width;
    dict->count++;
    return true;
}

void dict_free(StudentDict *dict) {
    if (dict != NULL) {
        free(dict->students);
        dict->students = NULL;
        dict->count = 0;
        dict->capacity = 0;
    }
}

size_t filter_students(const StudentDict *dict, float min_height, float max_height,
                       float min_width, float max_width, StudentDict *result) {
    if (dict == NULL || result == NULL) {
        return 0;
    }
    size_t filtered_count = 0;
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->students[i].height >= min_height && dict->students[i].height <= max_height &&
            dict->students[i].width >= min_width && dict->students[i].width <= max_width) {
            if (!dict_add(result, dict->students[i].name, dict->students[i].height, dict->students[i].width)) {
                return filtered_count;
            }
            filtered_count++;
        }
    }
    return filtered_count;
}

void print_students(const StudentDict *dict) {
    if (dict == NULL) {
        return;
    }
    for (size_t i = 0; i < dict->count; i++) {
        printf("Name: %s, Height: %.2f, Width: %.2f\n",
               dict->students[i].name, dict->students[i].height, dict->students[i].width);
    }
}

int main(void) {
    StudentDict students;
    StudentDict filtered;

    if (!dict_init(&students, 10)) {
        fprintf(stderr, "Failed to initialize students dictionary\n");
        return EXIT_FAILURE;
    }

    if (!dict_init(&filtered, 10)) {
        fprintf(stderr, "Failed to initialize filtered dictionary\n");
        dict_free(&students);
        return EXIT_FAILURE;
    }

    if (!dict_add(&students, "Alice", 165.5f, 55.0f)) {
        fprintf(stderr, "Failed to add student\n");
        dict_free(&students);
        dict_free(&filtered);
        return EXIT_FAILURE;
    }
    if (!dict_add(&students, "Bob", 180.2f, 75.5f)) {
        fprintf(stderr, "Failed to add student\n");
        dict_free(&students);
        dict_free(&filtered);
        return EXIT_FAILURE;
    }
    if (!dict_add(&students, "Charlie", 170.0f, 65.0f)) {
        fprintf(stderr, "Failed to add student\n");
        dict_free(&students);
        dict_free(&filtered);
        return EXIT_FAILURE;
    }
    if (!dict_add(&students, "Diana", 155.3f, 50.2f)) {
        fprintf(stderr, "Failed to add student\n");
        dict_free(&students);
        dict_free(&filtered);
        return EXIT_FAILURE;
    }
    if (!dict_add(&students, "Eve", 175.8f, 68.9f)) {
        fprintf(stderr, "Failed to add student\n");
        dict_free(&students);
        dict_free(&filtered);
        return EXIT_FAILURE;
    }

    printf("All students:\n");
    print_students(&students);

    float min_height = 160.0f;
    float max_height = 178.0f;
    float min_width = 52.0f;
    float max_width = 70.0f;

    size_t count = filter_students(&students, min_height, max_height, min_width, max_width, &filtered);

    printf("\nFiltered students (height: %.2f-%.2f, width: %.2f-%.2f):\n",
           min_height, max_height, min_width, max_width);
    printf("Found %zu students:\n", count);
    print_students(&filtered);

    dict_free(&students);
    dict_free(&filtered);

    return EXIT_SUCCESS;
}