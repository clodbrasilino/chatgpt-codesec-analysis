#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME_LEN 50

typedef struct {
    char *name;
    int height;
    int width;
} Student;

typedef struct {
    Student *students;
    size_t count;
    size_t capacity;
} StudentDict;

static bool is_valid_name(const char *name) {
    if (name == NULL) {
        return false;
    }
    size_t len = strnlen(name, MAX_NAME_LEN);
    return (len > 0 && len < MAX_NAME_LEN);
}

int init_dict(StudentDict *dict, size_t capacity) {
    if (dict == NULL || capacity == 0 || capacity > (SIZE_MAX / sizeof(Student))) {
        return -1;
    }
    dict->students = calloc(capacity, sizeof(Student));
    if (dict->students == NULL) {
        return -1;
    }
    dict->count = 0;
    dict->capacity = capacity;
    return 0;
}

void free_dict(StudentDict *dict) {
    if (dict != NULL) {
        if (dict->students != NULL) {
            for (size_t i = 0; i < dict->count; i++) {
                free(dict->students[i].name);
            }
            free(dict->students);
        }
        dict->students = NULL;
        dict->count = 0;
        dict->capacity = 0;
    }
}

int add_student(StudentDict *dict, const char *name, int height, int width) {
    if (dict == NULL || dict->students == NULL || name == NULL || 
        dict->count >= dict->capacity) {
        return -1;
    }
    
    if (!is_valid_name(name)) {
        return -1;
    }
    
    size_t name_len = strnlen(name, MAX_NAME_LEN - 1);
    char *name_copy = malloc(name_len + 1);
    if (name_copy == NULL) {
        return -1;
    }
    
    if (name_len > 0) {
        memcpy(name_copy, name, name_len);
    }
    name_copy[name_len] = '\0';
    
    dict->students[dict->count].name = name_copy;
    dict->students[dict->count].height = height;
    dict->students[dict->count].width = width;
    dict->count++;
    return 0;
}

size_t filter_students(const StudentDict *dict, int min_height, int max_height, 
                       int min_width, int max_width, Student *result, size_t result_size) {
    size_t filtered_count = 0;
    
    if (dict == NULL || dict->students == NULL || result == NULL || 
        result_size == 0 || min_height > max_height || min_width > max_width) {
        return 0;
    }
    
    for (size_t i = 0; i < dict->count && filtered_count < result_size; i++) {
        if (dict->students[i].height >= min_height && 
            dict->students[i].height <= max_height &&
            dict->students[i].width >= min_width && 
            dict->students[i].width <= max_width) {
            result[filtered_count] = dict->students[i];
            filtered_count++;
        }
    }
    return filtered_count;
}

int main(void) {
    StudentDict dict;
    Student filtered[10];
    size_t filtered_count;

    if (init_dict(&dict, 10) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (add_student(&dict, "Alice", 165, 55) != 0 ||
        add_student(&dict, "Bob", 180, 75) != 0 ||
        add_student(&dict, "Charlie", 170, 65) != 0 ||
        add_student(&dict, "Diana", 160, 50) != 0 ||
        add_student(&dict, "Eve", 175, 70) != 0) {
        fprintf(stderr, "Failed to add students\n");
        free_dict(&dict);
        return EXIT_FAILURE;
    }

    filtered_count = filter_students(&dict, 160, 175, 50, 70, filtered, 10);

    printf("Filtered students (height 160-175, width 50-70):\n");
    for (size_t i = 0; i < filtered_count; i++) {
        printf("Name: %s, Height: %d, Width: %d\n", 
               filtered[i].name, filtered[i].height, filtered[i].width);
    }

    free_dict(&dict);
    return EXIT_SUCCESS;
}