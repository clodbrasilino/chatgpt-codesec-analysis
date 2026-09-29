#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

char* getSecondMostRepeatedString(char** sequence, int size) {
  if (size < 2) {
    return NULL;
  }

  int maxFrequency = 0;
  int secondMaxFrequency = 0;
  
  for (int i = 0; i < size; i++) {
    if (!sequence[i]) continue;
    int frequency = 1;

    for (int j = i + 1; j < size; j++) {
      if (sequence[j]) {
        if (strcmp(sequence[i], sequence[j]) == 0) {
          frequency++;
          sequence[j] = NULL;
        }
      }
    }

    if (frequency > maxFrequency) {
      secondMaxFrequency = maxFrequency;
      maxFrequency = frequency;
    } else if (frequency > secondMaxFrequency && frequency < maxFrequency) {
      secondMaxFrequency = frequency;
    }
  }

  for (int i = 0; i < size; i++) {
    if (sequence[i]) {
      int frequency = 0;

      for (int j = 0; j < size; j++) {
        if (sequence[j]) {
          if (strcmp(sequence[i], sequence[j]) == 0) {
            frequency++;
          }
        }
      }
      if (frequency == secondMaxFrequency) {
        return sequence[i];
      }
    }
  }
  return NULL;
}

int main() {
  int n = 0;
  
  printf("Enter the number of strings: ");
  scanf("%d", &n);
  /* Possible weaknesses found:
   *   Check buffer boundaries if used in a loop including recursive loops  (CWE-120, CWE-20).
   */
  getchar();

  if (n > MAX_SIZE) n = MAX_SIZE;

  char* sequence[MAX_SIZE];
  printf("Enter the strings:\n");
  
  for (int i = 0; i < n; i++) {
    sequence[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    if (!sequence[i]) {
      printf("Memory allocation failed\n");
      return -1;
    }

    fgets(sequence[i], MAX_SIZE, stdin);
    // Removing '\n'
    sequence[i][strcspn(sequence[i], "\n")] = '\0';
  }

  char* secondMostRepeatedString = getSecondMostRepeatedString(sequence, n);

  if (secondMostRepeatedString) {
    printf("The second most repeated string is: %s\n", secondMostRepeatedString);
  } else {
    printf("No second most repeated string found.\n");
  }

  for (int i = 0; i < n; i++) {
    free(sequence[i]);
  }
  return 0;
}