#include <stdio.h>
#include <regex.h>

void find_characters(const char* str) {
  regex_t regex;
  regmatch_t matches[1];

  regcomp(&regex, "[A-Z]", REG_EXTENDED);
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    printf("Uppercase letter found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, &str[matches[0].rm_so]);
    str += matches[0].rm_eo;
  }
  regfree(&regex);

  regcomp(&regex, "[a-z]", REG_EXTENDED);
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    printf("Lowercase letter found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, &str[matches[0].rm_so]);
    str += matches[0].rm_eo;
  }
  regfree(&regex);

  regcomp(&regex, "[^A-Za-z0-9]", REG_EXTENDED);
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    printf("Special character found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, &str[matches[0].rm_so]);
    str += matches[0].rm_eo;
  }
  regfree(&regex);

  regcomp(&regex, "[0-9]", REG_EXTENDED);
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    printf("Numeric value found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, &str[matches[0].rm_so]);
    str += matches[0].rm_eo;
  }
  regfree(&regex);
}

int main() {
  const char* str = "Hello, World! 123";
  find_characters(str);
  return 0;
}