#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
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

int student_dict_add(StudentDict *dict, const char *name, float height, float width) {
    if (!dict || !name || dict->capacity <= 0) {
        return -1;
    }
    
    size_t name_len = 0;
    while (name_len < sizeof(dict->students[0].name) - 1 && name[name_len] != '\0') {
        name_len++;
    }
    
    if (name[name_len] != '\0') {
        return -1;
    }
    
    if (dict->count >= dict->capacity) {
        if (dict->capacity > INT_MAX / 2) {
            return -1;
        }
        int new_capacity = dict->capacity * 2;
        Student *new_students = (Student *)realloc(dict->students, sizeof(Student) * (size_t)new_capacity);
        if (!new_students) {
            return -1;
        }
        dict->students = new_students;
        dict->capacity = new_capacity;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dict->students[dict->count].name, name, name_len + 1);
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

    result.students = (Student *)malloc(sizeof(Student) * (size_t)dict->count);
    if (!result.students) {
        return result;
    }

    for (int i = 0; i < dict->count; i++) {
        if (dict->students[i].height >= min_height && dict->students[i].height <= max_height &&
            dict->students[i].width >= min_width && dict->students[i].width <= max_width) {
            if (result.count < dict->count) {
                result.students[result.count] = dict->students[i];
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