#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int height;
    int width;
} Student;

typedef struct {
    Student* students;
    size_t count;
    size_t capacity;
} Dictionary;

Dictionary* create_dictionary(size_t capacity) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->students = (Student*)malloc(capacity * sizeof(Student));
    if (!dict->students) {
        free(dict);
        return NULL;
    }
    dict->count = 0;
    dict->capacity = capacity;
    return dict;
}

void free_dictionary(Dictionary* dict) {
    if (dict) {
        free(dict->students);
        free(dict);
    }
}

int add_student(Dictionary* dict, int id, int height, int width) {
    if (!dict || dict->count >= dict->capacity) {
        return -1;
    }
    dict->students[dict->count].id = id;
    dict->students[dict->count].height = height;
    dict->students[dict->count].width = width;
    dict->count++;
    return 0;
}

Dictionary* filter_students(const Dictionary* dict, int min_height, int min_width) {
    if (!dict) {
        return NULL;
    }
    
    Dictionary* filtered_dict = create_dictionary(dict->capacity);
    if (!filtered_dict) {
        return NULL;
    }
    
    for (size_t i = 0; i < dict->count; i++) {
        if (dict->students[i].height >= min_height && dict->students[i].width >= min_width) {
            if (add_student(filtered_dict, dict->students[i].id, dict->students[i].height, dict->students[i].width) != 0) {
                free_dictionary(filtered_dict);
                return NULL;
            }
        }
    }
    
    return filtered_dict;
}

int main() {
    Dictionary* dict = create_dictionary(5);
    if (!dict) {
        return 1;
    }
    
    add_student(dict, 1, 170, 60);
    add_student(dict, 2, 160, 50);
    add_student(dict, 3, 180, 75);
    add_student(dict, 4, 165, 55);
    add_student(dict, 5, 175, 70);
    
    Dictionary* filtered = filter_students(dict, 170, 60);
    if (!filtered) {
        free_dictionary(dict);
        return 1;
    }
    
    for (size_t i = 0; i < filtered->count; i++) {
        printf("ID: %d, Height: %d, Width: %d\n", filtered->students[i].id, filtered->students[i].height, filtered->students[i].width);
    }
    
    free_dictionary(filtered);
    free_dictionary(dict);
    
    return 0;
}