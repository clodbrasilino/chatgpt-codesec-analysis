#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
      if (sequence[j] && strcmp(sequence[i], sequence[j]) == 0) {
        frequency++;
        sequence[j] = NULL;
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
    if (sequence[i] && strcmp(sequence[i], "") != 0) {
      int frequency = 1;

      for (int j = i + 1; j < size; j++) {
        if (sequence[j] && strcmp(sequence[i], sequence[j]) == 0) {
          frequency++;
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
  int n;
  printf("Enter the number of strings: ");
  scanf("%d", &n);

  if (n > MAX_SIZE)
      n = MAX_SIZE;

  char* sequence[MAX_SIZE];
  printf("Enter the strings:\n");

  for (int i = 0; i < n; i++) {
    sequence[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    scanf("%99s", sequence[i]);
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