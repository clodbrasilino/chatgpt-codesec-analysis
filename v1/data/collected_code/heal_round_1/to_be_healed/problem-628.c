#include <stdio.h>

// Function to replace spaces in the given string with "%20"
void replaceSpaces(char str[], int length) {
  int spaceCount = 0, newLength, i;

  // Count spaces and find new length of the string
  for (i = 0; i < length; i++) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (str[i] == ' ')
      spaceCount++;
  }
  newLength = length + spaceCount * 2;

  // Replace spaces in the string
  for (i = length - 1; i >= 0; i--) {
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    if (str[i] == ' ') {
      str[newLength - 1] = '0';
      str[newLength - 2] = '2';
      str[newLength - 3] = '%';
      newLength -= 3;
    } else {
      /* Possible weaknesses found:
       *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
       */
      str[newLength - 1] = str[i];
      newLength--;
    }
  }
}

int main() {
  char str[] = "Write a C function";

  // Calculate the length of the string
  int length = sizeof(str) / sizeof(str[0]) - 1;

  // Replace spaces in the string
  replaceSpaces(str, length);

  // Print the modified string
  printf("%s\n", str);

  return 0;
}