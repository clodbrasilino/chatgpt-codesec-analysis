#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    float height;
    float width;
} Student;

typedef struct {
    Student students[MAX_STUDENTS];
    size_t count;
} StudentDict;

int init_dict(StudentDict *dict) {
    if (dict == NULL) {
        return -1;
    }
    dict->count = 0;
    return 0;
}

int add_student(StudentDict *dict, const char *name, float height, float width) {
    if (dict == NULL || name == NULL || dict->count >= MAX_STUDENTS) {
        return -1;
    }
    
    size_t name_len = strlen(name);
    if (name_len == 0 || name_len >= MAX_NAME_LENGTH) {
        return -1;
    }
    
    strncpy(dict->students[dict->count].name, name, MAX_NAME_LENGTH - 1);
    dict->students[dict->count].name[MAX_NAME_LENGTH - 1] = '\0';
    dict->students[dict->count].height = height;
    dict->students[dict->count].width = width;
    dict->count++;
    
    return 0;
}

size_t filter_by_dimensions(const StudentDict *dict, float min_height, float max_height, 
                            float min_width, float max_width, Student *result, size_t result_size) {
    if (dict == NULL || result == NULL || result_size == 0) {
        return 0;
    }
    
    if (min_height > max_height || min_width > max_width) {
        return 0;
    }
    
    size_t filtered_count = 0;
    
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

void print_students(const Student *students, size_t count) {
    if (students == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        printf("Name: %s, Height: %.2f, Width: %.2f\n", 
               students[i].name, students[i].height, students[i].width);
    }
}

int main(void) {
    StudentDict dict;
    Student filtered[MAX_STUDENTS];
    
    if (init_dict(&dict) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }
    
    if (add_student(&dict, "Alice", 165.5f, 55.0f) != 0 ||
        add_student(&dict, "Bob", 180.2f, 75.5f) != 0 ||
        add_student(&dict, "Charlie", 170.0f, 65.0f) != 0 ||
        add_student(&dict, "Diana", 160.0f, 50.0f) != 0 ||
        add_student(&dict, "Eve", 175.5f, 70.0f) != 0) {
        fprintf(stderr, "Failed to add students\n");
        return EXIT_FAILURE;
    }
    
    printf("All students:\n");
    print_students(dict.students, dict.count);
    
    printf("\nFiltered students (height: 160-175, width: 50-70):\n");
    size_t filtered_count = filter_by_dimensions(&dict, 160.0f, 175.0f, 50.0f, 70.0f, 
                                                  filtered, MAX_STUDENTS);
    
    if (filtered_count > 0) {
        print_students(filtered, filtered_count);
    } else {
        printf("No students match the criteria\n");
    }
    
    return EXIT_SUCCESS;
}