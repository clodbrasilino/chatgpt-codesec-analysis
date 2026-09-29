#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 255

typedef struct {
    char* name;
    int height;
    int width;
} Student;

typedef struct {
    Student* students;
    size_t count;
    size_t capacity;
} StudentDict;

StudentDict* create_dict(size_t initial_capacity) {
    if (initial_capacity == 0) {
        return NULL;
    }
    
    StudentDict* dict = (StudentDict*)malloc(sizeof(StudentDict));
    if (!dict) {
        return NULL;
    }
    
    dict->students = (Student*)malloc(initial_capacity * sizeof(Student));
    if (!dict->students) {
        free(dict);
        return NULL;
    }
    
    dict->count = 0;
    dict->capacity = initial_capacity;
    return dict;
}

void free_dict(StudentDict* dict) {
    if (dict) {
        if (dict->students) {
            for (size_t i = 0; i < dict->count; i++) {
                free(dict->students[i].name);
            }
            free(dict->students);
        }
        free(dict);
    }
}

int add_student(StudentDict* dict, const char* name, int height, int width) {
    if (!dict || !name) {
        return 0;
    }
    
    if (dict->count >= dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        Student* new_students = (Student*)realloc(dict->students, new_capacity * sizeof(Student));
        if (!new_students) {
            return 0;
        }
        dict->students = new_students;
        dict->capacity = new_capacity;
    }
    
    size_t name_len = 0;
    while (name_len < MAX_NAME_LEN && name[name_len] != '\0') {
        name_len++;
    }
    
    dict->students[dict->count].name = (char*)malloc(name_len + 1);
    if (!dict->students[dict->count].name) {
        return 0;
    }
    
    snprintf(dict->students[dict->count].name, name_len + 1, "%s", name);
    
    dict->students[dict->count].height = height;
    dict->students[dict->count].width = width;
    dict->count++;
    
    return 1;
}

StudentDict* filter_students(const StudentDict* input_dict, int min_height, int min_width) {
    if (!input_dict) {
        return NULL;
    }
    
    StudentDict* filtered_dict = create_dict(input_dict->capacity > 0 ? input_dict->capacity : 1);
    if (!filtered_dict) {
        return NULL;
    }
    
    for (size_t i = 0; i < input_dict->count; i++) {
        if (input_dict->students[i].height >= min_height && input_dict->students[i].width >= min_width) {
            if (!add_student(filtered_dict, input_dict->students[i].name, input_dict->students[i].height, input_dict->students[i].width)) {
                free_dict(filtered_dict);
                return NULL;
            }
        }
    }
    
    return filtered_dict;
}

void print_dict(const StudentDict* dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->count; i++) {
        printf("Name: %s, Height: %d, Width: %d\n", dict->students[i].name, dict->students[i].height, dict->students[i].width);
    }
}

int main(void) {
    StudentDict* dict = create_dict(5);
    if (!dict) {
        return 1;
    }
    
    add_student(dict, "Alice", 165, 55);
    add_student(dict, "Bob", 180, 80);
    add_student(dict, "Charlie", 175, 70);
    add_student(dict, "Diana", 160, 50);
    
    StudentDict* filtered = filter_students(dict, 170, 60);
    if (filtered) {
        print_dict(filtered);
        free_dict(filtered);
    }
    
    free_dict(dict);
    return 0;
}