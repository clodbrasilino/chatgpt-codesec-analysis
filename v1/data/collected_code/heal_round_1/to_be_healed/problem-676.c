#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcpy'
  *  'NULL' is defined in header '<stddef.h>'; did you forget to '#include <stddef.h>'?
  */

void removeNonAlphanumeric(char *str) {
  regex_t regex;
  int reti;

  // Compile the regular expression pattern
  reti = regcomp(&regex, "[^[:alnum:]]", 0);

  if (reti == 0) {
    // Execute the regular expression
    /* Possible weaknesses found:
     *  'NULL' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  Cannot determine that 'str[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    reti = regexec(&regex, str, 0, NULL, 0);

    if (reti == 0) {
      // Remove non-alphanumeric characters by replacing them with empty string
      regfree(&regex);
      regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED);
      /* Possible weaknesses found:
       *  implicit declaration of function 'regreplace' [-Wimplicit-function-declaration]
       *  initialization of 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
       */
      char *result = regreplace(str, regex);

      // Copy the modified string back to the original string
      /* Possible weaknesses found:
       *  include '<string.h>' or provide a declaration of 'strcpy'
       *  incompatible implicit declaration of built-in function 'strcpy' [-Wbuiltin-declaration-mismatch]
       *  implicit declaration of function 'strcpy' [-Wimplicit-function-declaration]
       *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
       */
      strcpy(str, result);
    }
    regfree(&regex);
  }
}