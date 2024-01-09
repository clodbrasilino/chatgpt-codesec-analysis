#include <regex.h>

void removeNonAlphanumeric(char *str) {
  regex_t regex;
  int reti;

  // Compile the regular expression pattern
  reti = regcomp(&regex, "[^[:alnum:]]", 0);

  if (reti == 0) {
    // Execute the regular expression
    reti = regexec(&regex, str, 0, NULL, 0);

    if (reti == 0) {
      // Remove non-alphanumeric characters by replacing them with empty string
      regfree(&regex);
      regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED);
      char *result = regreplace(str, regex);

      // Copy the modified string back to the original string
      strcpy(str, result);
    }
    regfree(&regex);
  }
}