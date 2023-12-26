#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tupleToList(char tuple[], char string[], char list[]) {
  int i, j;

  /* Possible weaknesses found:
   *  Cannot determine that 'list[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
   *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused). Risk is low because the source is a constant character.
   */
  strcpy(list, "");

  /* Possible weaknesses found:
   *  Cannot determine that 'tuple[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
   *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
   */
  for(i = 0; i < strlen(tuple); i++) {
    /* Possible weaknesses found:
     *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
     */
    strncat(list, tuple + i, 1);
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when concatenating to destination  [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or  snprintf (warning: strncat is easily misused).
     *  Cannot determine that 'string[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    strcat(list, string);
  }
}

int main() {
  char tuple[] = "12345";
  char string[] = "-";
  /* Possible weaknesses found:
   *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
   */
  char list[50];

  tupleToList(tuple, string, list);

  /* Possible weaknesses found:
   *  Cannot determine that 'list[0]' is initialized [premium-bughuntingUninit]
   */
  printf("%s\n", list);

  return 0;
}