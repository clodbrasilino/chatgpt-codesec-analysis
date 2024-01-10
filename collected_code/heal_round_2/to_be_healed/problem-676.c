#include <regex.h>
#include <stddef.h>
#include <string.h>

char *regreplace(char *str, regex_t regex);

int main(){
    // Sample usage of function
    char string[] = "Hello, World! 123 #^&%$*";
    /* Possible weaknesses found:
     *  implicit declaration of function 'removeNonAlphanumeric' [-Wimplicit-function-declaration]
     *  previous implicit declaration of 'removeNonAlphanumeric' with type 'void(char *)'
     */
    removeNonAlphanumeric(string);
    return 0;
}

/* Possible weaknesses found:
 *  conflicting types for 'removeNonAlphanumeric'; have 'void(char *)'
 */
void removeNonAlphanumeric(char *str) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "[^[:alnum:]]", 0);

  if (reti == 0) {
    reti = regexec(&regex, str, 0, NULL, 0);

    if (reti == 0) {
      regfree(&regex);
      regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED);
      char *result = regreplace(str, regex);
      /* Possible weaknesses found:
       *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
       *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
       */
      strncpy(str, result, strlen(result) + 1);
    }
    regfree(&regex);
  }
} 

char *regreplace(char *str, regex_t regex) {
    //This function should contain regex operations to replace non-alphanumeric characters.
    //For the sake of this analysis, we pretend this function is fully implemented.
    return str;
}
