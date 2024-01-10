#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

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
  /* Possible weaknesses found:
   *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
   */
  scanf("%d", &n);

  /* Possible weaknesses found:
   *  Cannot determine that 'sequence[100]' is initialized [premium-bughuntingUninit]
   */
  char* sequence[MAX_SIZE];
  printf("Enter the strings:\n");

  for (int i = 0; i < n; i++) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     */
    sequence[i] = (char*)malloc(MAX_SIZE * sizeof(char));
    /* Possible weaknesses found:
     *  Cannot determine that 'sequence[i][0]' is initialized [premium-bughuntingUninit]
     *   The scanf() family's %s operation, without a limit specification, permits  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a  different input function.
     */
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
    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(sequence[i]);
  }

  return 0;
}