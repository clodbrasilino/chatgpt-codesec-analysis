#include <stdio.h>

#define MAX_STUDENTS 100

typedef struct {
    int height;
    int width;
} Student;

void filter_students(Student students[], int n, int minHeight, int minWidth) {
    for(int i = 0; i < n; i++) {
        if(students[i].height >= minHeight && students[i].width >= minWidth) {
            printf("Student %d passes the filter\n", i+1);
        }
    }
}

int main() {
    Student students[MAX_STUDENTS];
    int n;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter height and width for student %d: ", i+1);
        scanf("%d%d", &students[i].height, &students[i].width);
    }

    int minHeight, minWidth;
    printf("Enter minimum height and width to filter: ");
    scanf("%d%d", &minHeight, &minWidth);

    filter_students(students, n, minHeight, minWidth);

    return 0;
}