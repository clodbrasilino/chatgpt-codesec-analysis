#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define STUDENT_NAME_MAX 49

typedef struct {
    char name[STUDENT_NAME_MAX + 1];
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

int student_dict_init(StudentDict *dict, int initial_capacity) {
    if (!dict || initial_capacity <= 0) {
        return -1;
    }
    
    if ((size_t)initial_capacity > SIZE_MAX / sizeof(Student)) {
        return -1;
    }
    
    dict->students = (Student *)malloc(sizeof(Student) * (size_t)initial_capacity);
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

static int copy_student_name(char *dest, size_t dest_size, const char *src) {
    if (!dest || dest_size == 0 || !src) {
        return -1;
    }
    
    size_t src_len = strnlen(src, dest_size);
    if (src_len >= dest_size) {
        return -1;
    }
    
    if (src_len >= dest_size) {
        return -1;
    }
    
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return 0;
}

int student_dict_add(StudentDict *dict, const char *name, float height, float width) {
    if (!dict || !name || dict->capacity <= 0) {
        return -1;
    }
    
    size_t name_len = strnlen(name, STUDENT_NAME_MAX + 1);
    if (name_len > STUDENT_NAME_MAX) {
        return -1;
    }
    
    if (dict->count >= dict->capacity) {
        if (dict->capacity > INT_MAX / 2) {
            return -1;
        }
        int new_capacity = dict->capacity * 2;
        if (new_capacity < 0 || (size_t)new_capacity > SIZE_MAX / sizeof(Student)) {
            return -1;
        }
        Student *new_students = (Student *)realloc(dict->students, sizeof(Student) * (size_t)new_capacity);
        if (!new_students) {
            return -1;
        }
        dict->students = new_students;
        dict->capacity = new_capacity;
    }
    
    if (copy_student_name(dict->students[dict->count].name, 
                          sizeof(dict->students[dict->count].name), 
                          name) != 0) {
        return -1;
    }
    
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

    if (!dict || dict->count == 0) {
        return result;
    }

    if ((size_t)dict->count > SIZE_MAX / sizeof(Student)) {
        return result;
    }

    result.students = (Student *)malloc(sizeof(Student) * (size_t)dict->count);
    if (!result.students) {
        return result;
    }
    memset(result.students, 0, sizeof(Student) * (size_t)dict->count);

    for (int i = 0; i < dict->count; i++) {
        if (dict->students[i].height >= min_height && dict->students[i].height <= max_height &&
            dict->students[i].width >= min_width && dict->students[i].width <= max_width) {
            if (result.count < dict->count) {
                if (copy_student_name(result.students[result.count].name,
                                      sizeof(result.students[result.count].name),
                                      dict->students[i].name) != 0) {
                    continue;
                }
                result.students[result.count].height = dict->students[i].height;
                result.students[result.count].width = dict->students[i].width;
                result.count++;
            }
        }
    }

    if (result.count == 0) {
        free(result.students);
        result.students = NULL;
    } else if (result.count < dict->count) {
        Student *temp = (Student *)realloc(result.students, sizeof(Student) * (size_t)result.count);
        if (temp) {
            result.students = temp;
        }
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