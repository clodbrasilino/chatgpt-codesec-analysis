#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char *name;
    int height;
    int width;
} Student;

int filterStudents(Student *students, size_t len, int minHeight, int minWidth, Student ***filtered) {
    size_t i, filteredLen = 0;
    *filtered = NULL;
    for (i = 0; i < len; i++) {
        if (students[i].height >= minHeight && students[i].width >= minWidth) {
            /* Possible weaknesses found:
             *  leak of 'filtered' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            *filtered = realloc(*filtered, sizeof(Student*) * (filteredLen + 1));
            if (*filtered == NULL) {
                return -1;
            }
            (*filtered)[filteredLen] = &students[i];
            filteredLen++;
        }
    }
    return filteredLen;
}

int main() {
    Student students[] = {
        {"Alice", 160, 50},
        {"Bob", 175, 60},
        {"Charlie", 155, 45},
        {"Dave", 180, 65}
    };
    Student **filtered;
    int filteredLen;
    int i;
    filteredLen = filterStudents(students, 4, 160, 50, &filtered);
    if (filteredLen == -1) {
        printf("Memory allocation error\n");
        return 1;
    }
    for (i = 0; i < filteredLen; i++) {
        printf("Name: %s, Height: %d, Width: %d\n", filtered[i]->name, filtered[i]->height, filtered[i]->width);
    }
    free(filtered);
    return 0;
}