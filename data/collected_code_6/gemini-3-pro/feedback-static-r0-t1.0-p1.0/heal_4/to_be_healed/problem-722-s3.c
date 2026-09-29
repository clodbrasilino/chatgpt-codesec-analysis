#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 1024

typedef struct {
    char* name;
    float height;
    float width;
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

int add_student(StudentDict* dict, const char* name, float height, float width) {
    if (!dict || !name) {
        return -1;
    }

    if (dict->count == dict->capacity) {
        size_t new_capacity = dict->capacity * 2;
        Student* temp = (Student*)realloc(dict->students, new_capacity * sizeof(Student));
        if (!temp) {
            return -1;
        }
        dict->students = temp;
        dict->capacity = new_capacity;
    }

    size_t name_len = 0;
    /* Possible weaknesses found:
     *  Array index 'name_len' is used before limits check. [arrayIndexThenCheck]
     */
    while (name[name_len] != '\0' && name_len < MAX_NAME_LEN) {
        name_len++;
    }

    dict->students[dict->count].name = (char*)malloc(name_len + 1);
    if (!dict->students[dict->count].name) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->students[dict->count].name, name, name_len);
    dict->students[dict->count].name[name_len] = '\0';
    
    dict->students[dict->count].height = height;
    dict->students[dict->count].width = width;
    dict->count++;

    return 0;
}

void destroy_dict(StudentDict* dict) {
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

StudentDict* filter_students(const StudentDict* input_dict, float min_height, float max_height, float min_width, float max_width) {
    if (!input_dict) {
        return NULL;
    }

    StudentDict* filtered = create_dict(input_dict->capacity > 0 ? input_dict->capacity : 1);
    if (!filtered) {
        return NULL;
    }

    for (size_t i = 0; i < input_dict->count; i++) {
        const Student* s = &input_dict->students[i];
        if (s->height >= min_height && s->height <= max_height &&
            s->width >= min_width && s->width <= max_width) {
            if (add_student(filtered, s->name, s->height, s->width) != 0) {
                destroy_dict(filtered);
                return NULL;
            }
        }
    }

    return filtered;
}

int main(void) {
    StudentDict* dict = create_dict(5);
    if (!dict) {
        return 1;
    }

    add_student(dict, "Alice", 165.5, 45.0);
    add_student(dict, "Bob", 180.0, 50.0);
    add_student(dict, "Charlie", 170.2, 48.5);
    add_student(dict, "David", 150.0, 40.0);
    add_student(dict, "Eve", 190.0, 55.0);

    StudentDict* filtered = filter_students(dict, 160.0, 185.0, 42.0, 52.0);
    if (!filtered) {
        destroy_dict(dict);
        return 1;
    }

    for (size_t i = 0; i < filtered->count; i++) {
        printf("Name: %s, Height: %.1f, Width: %.1f\n", 
               filtered->students[i].name, 
               filtered->students[i].height, 
               filtered->students[i].width);
    }

    destroy_dict(filtered);
    destroy_dict(dict);

    return 0;
}