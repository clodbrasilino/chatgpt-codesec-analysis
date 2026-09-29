/* Possible weaknesses found:
 *  stray '`' in program
 */
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_char(char* str, char old_char, char new_char) {
  if (str == NULL) {
    printf("Error: String is NULL.\n");
    return;
  }

  for (int i = 0; i < strlen(str); i++) {
    if (str[i] == old_char) {
      str[i] = new_char;
    }
  }
}

int main() {
  char str[] = "Hello World!";
  char old_char = 'o';
  char new_char = '0';

  printf("Original string: %s\n", str);
  replace_char(str, old_char, new_char);
  printf("Modified string: %s\n", str);

  return 0;
}