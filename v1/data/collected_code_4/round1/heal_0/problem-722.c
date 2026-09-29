#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int height;
  int width;
} Student;

Student* filterStudents(Student* students, int size, int minHeight, int minWidth, int* resultSize) {
  Student* filteredStudents = malloc(size * sizeof(Student));

  if (!filteredStudents) {
    printf("Allocation error.");
    exit(1);
  }

  int j = 0;
  for(int i=0; i<size; i++) {
    if (students[i].height > minHeight && students[i].width > minWidth) {
      filteredStudents[j] = students[i];
      j++;
    }
  }

  *resultSize = j;

  Student* temp = realloc(filteredStudents, j * sizeof(Student));

  if (j > 0 && !temp) {
    printf("Reallocation error.");
    free(filteredStudents);
    exit(1);
  } else {
    filteredStudents = temp;
  }

  return filteredStudents;
}

int main() {
  int size = 4;
  Student students[4] = {
      {170, 70}, 
      {160, 60}, 
      {180, 72}, 
      {165, 65}
  };

  int resultSize;
  Student* filteredStudents = filterStudents(students, size, 165, 65, &resultSize);

  for(int i=0; i<resultSize; i++) {
    printf("Student %d: height %d, width %d\n", i+1, filteredStudents[i].height, filteredStudents[i].width);
  }

  free(filteredStudents);

  return 0;
}