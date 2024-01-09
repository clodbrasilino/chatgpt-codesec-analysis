#include <stdio.h>

#define MAX_STUDENTS 100

typedef struct {
    int height;
    int width;
} Student;

void filterStudents(Student students[], int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].height > 150 && students[i].width > 50) {
            printf("Student %d: height = %d, width = %d\n", i + 1, students[i].height, students[i].width);
        }
    }
}

int main() {
    // Example usage
    Student students[MAX_STUDENTS] = {
        {165, 60},  // Student 1
        {160, 55},  // Student 2
        {170, 70},  // Student 3
        {155, 45},  // Student 4
    };
    int numStudents = 4;

    filterStudents(students, numStudents);

    return 0;
}