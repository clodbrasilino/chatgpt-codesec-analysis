#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int width;
} Student;

void filter_students(Student* students, int n, int min_height, int max_height, int min_width, int max_width) {
    for(int i = 0; i < n; i++) {
        if(students[i].height >= min_height && students[i].height <= max_height && students[i].width >= min_width && students[i].width <= max_width) {
            printf("Student %d passes the filter\n", i+1);
        }
    }
}

int main() {
    int n = 5;
    Student students[n];

    students[0].height = 170;
    students[0].width = 60;

    students[1].height = 180;
    students[1].width = 70;

    students[2].height = 160;
    students[2].width = 55;

    students[3].height = 175;
    students[3].width = 65;

    students[4].height = 185;
    students[4].width = 75;

    filter_students(students, n, 165, 180, 60, 70);

    return 0;
}