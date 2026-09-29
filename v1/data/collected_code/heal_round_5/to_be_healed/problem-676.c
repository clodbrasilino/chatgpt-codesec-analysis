#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void removeNonAlphanumeric(char *str);
char *regreplace(char *str, regex_t regex);

int main() {
    char string[] = "Hello, World! 123 #^&%$*";
    removeNonAlphanumeric(string);

    printf("%s", string);
    return 0;
}

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
       *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
       */
      size_t length = strlen(result);
      /* Possible weaknesses found:
       *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
       */
      length = length >= strlen(str) ? strlen(str) - 1 : length;

      /* Possible weaknesses found:
       *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
       */
      strncpy(str, result, length);
      str[length] = '\0';
    }

    regfree(&regex);
  }
} 

char *regreplace(char *str, regex_t regex) {
    return str;
}