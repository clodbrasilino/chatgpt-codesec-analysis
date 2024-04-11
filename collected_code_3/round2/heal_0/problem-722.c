#include <stdio.h>

typedef struct {
    int height;
    int width;
} Student;

void filter_students(Student students[], int n, int min_height, int max_height, int min_width, int max_width) {
    for(int i = 0; i < n; i++) {
        if(students[i].height >= min_height && students[i].height <= max_height && students[i].width >= min_width && students[i].width <= max_width) {
            printf("Student %d meets the criteria\n", i+1);
        }
    }
}

int main() {
    Student students[] = {
        {170, 60},
        {180, 70},
        {160, 50},
        {175, 65}
    };

    int n = sizeof(students) / sizeof(Student);

    filter_students(students, n, 165, 180, 60, 70);

    return 0;
}