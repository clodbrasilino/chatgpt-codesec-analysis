#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define NAME_SIZE 64

typedef struct {
    char name[NAME_SIZE];
    float height;
    float width;
} Student;

typedef struct {
    Student *students;
    int count;
    int capacity;
} StudentDict;

typedef struct {
    Student *students;
    int count;
} FilteredResult;

static int is_overflow_multiply(size_t a, size_t b, size_t *result) {
    if (a > 0 && b > SIZE_MAX / a) {
        return -1;
    }
    *result = a * b;
    return 0;
}

int student_dict_init(StudentDict *dict, int initial_capacity) {
    if (!dict || initial_capacity <= 0) {
        return -1;
    }
    
    size_t alloc_size;
    if (is_overflow_multiply((size_t)initial_capacity, sizeof(Student), &alloc_size) != 0) {
        return -1;
    }
    
    dict->students = (Student *)malloc(alloc_size);
    if (!dict->students) {
        return -1;
    }
    dict->count = 0;
    dict->capacity = initial_capacity;
    return 0;
}

void student_dict_free(StudentDict *dict) {
    if (dict && dict->students) {
        free(dict->students);
        dict->students = NULL;
        dict->count = 0;
        dict->capacity = 0;
    }
}

int student_dict_add(StudentDict *dict, const char *name, float height, float width) {
    if (!dict || !name) {
        return -1;
    }

    size_t name_len = strnlen(name, NAME_SIZE);
    if (name_len >= NAME_SIZE) {
        return -1;
    }

    if (dict->count >= dict->capacity) {
        if (dict->capacity <= 0) {
            return -1;
        }
        
        if (dict->capacity > INT_MAX / 2) {
            return -1;
        }
        
        int new_capacity = dict->capacity * 2;
        
        if (new_capacity < dict->capacity) {
            return -1;
        }
        
        size_t alloc_size;
        if (is_overflow_multiply((size_t)new_capacity, sizeof(Student), &alloc_size) != 0) {
            return -1;
        }
        
        Student *new_students = (Student *)realloc(dict->students, alloc_size);
        if (!new_students) {
            return -1;
        }
        dict->students = new_students;
        dict->capacity = new_capacity;
    }

    if (dict->count >= dict->capacity) {
        return -1;
    }

    size_t dest_size = sizeof(dict->students[dict->count].name);
    if (name_len >= dest_size) {
        return -1;
    }
    
    memcpy(dict->students[dict->count].name, name, name_len);
    dict->students[dict->count].name[name_len] = '\0';
    dict->students[dict->count].height = height;
    dict->students[dict->count].width = width;
    dict->count++;
    return 0;
}

FilteredResult filter_students(const StudentDict *dict, float min_height, float max_height,
                                float min_width, float max_width) {
    FilteredResult result;
    result.students = NULL;
    result.count = 0;

    if (!dict || dict->count <= 0) {
        return result;
    }

    size_t alloc_size;
    if (is_overflow_multiply((size_t)dict->count, sizeof(Student), &alloc_size) != 0) {
        return result;
    }

    result.students = (Student *)malloc(alloc_size);
    if (!result.students) {
        return result;
    }

    for (int i = 0; i < dict->count; i++) {
        if (dict->students[i].height >= min_height && dict->students[i].height <= max_height &&
            dict->students[i].width >= min_width && dict->students[i].width <= max_width) {
            if (result.count < dict->count) {
                memcpy(&result.students[result.count], &dict->students[i], sizeof(Student));
                result.count++;
            }
        }
    }

    if (result.count == 0) {
        free(result.students);
        result.students = NULL;
    }

    return result;
}

void filtered_result_free(FilteredResult *result) {
    if (result && result->students) {
        free(result->students);
        result->students = NULL;
        result->count = 0;
    }
}

int main(void) {
    StudentDict dict;
    if (student_dict_init(&dict, 5) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    student_dict_add(&dict, "Alice", 170.5f, 60.2f);
    student_dict_add(&dict, "Bob", 182.0f, 78.5f);
    student_dict_add(&dict, "Charlie", 165.0f, 55.0f);
    student_dict_add(&dict, "Diana", 175.5f, 68.3f);
    student_dict_add(&dict, "Eve", 158.3f, 48.9f);

    FilteredResult filtered = filter_students(&dict, 160.0f, 180.0f, 50.0f, 75.0f);

    if (filtered.students != NULL) {
        printf("Filtered students:\n");
        for (int i = 0; i < filtered.count; i++) {
            printf("%s: height=%.1f, width=%.1f\n",
                   filtered.students[i].name,
                   filtered.students[i].height,
                   filtered.students[i].width);
        }
    } else {
        printf("No students match the criteria.\n");
    }

    filtered_result_free(&filtered);
    student_dict_free(&dict);

    return EXIT_SUCCESS;
}