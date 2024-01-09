#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

char* getSecondMostRepeatedString(char** sequence, int size) {
  if (size < 2) {
    return NULL;
  }

  // Count frequencies
  int maxFrequency = 0;
  int secondMaxFrequency = 0;

  for (int i = 0; i < size; i++) {
    int frequency = 1;

    for (int j = i + 1; j < size; j++) {
      if (sequence[i] && sequence[j] && strcmp(sequence[i], sequence[j]) == 0) {
        frequency++;
        sequence[j] = NULL; // Mark as counted
      }
    }

    if (frequency > maxFrequency) {
      secondMaxFrequency = maxFrequency;
      maxFrequency = frequency;
    } else if (frequency > secondMaxFrequency && frequency < maxFrequency) {
      secondMaxFrequency = frequency;
    }
  }

  // Find the second most repeated string
  for (int i = 0; i < size; i++) {
    if (sequence[i] && strcmp(sequence[i], "") != 0) {
      int frequency = 0;

      for (int j = 0; j < size; j++) {
        if (sequence[i] && sequence[j] && strcmp(sequence[i], sequence[j]) == 0) {
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

  char* sequence[MAX_SIZE];
  printf("Enter the strings:\n");

  for (int i = 0; i < n; i++) {
    sequence[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    scanf("%s", sequence[i]);
  }

  char* secondMostRepeatedString = getSecondMostRepeatedString(sequence, n);

  if (secondMostRepeatedString) {
    printf("The second most repeated string is: %s\n", secondMostRepeatedString);
  } else {
    printf("No second most repeated string found.\n");
  }

  // Free allocated memory
  for (int i = 0; i < n; i++) {
    free(sequence[i]);
  }

  return 0;
}