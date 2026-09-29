#include <stdio.h>
#include <regex.h>

void find_characters(const char* str) {
  regex_t regex;

  // Create regex pattern to match uppercase letters
  regcomp(&regex, "[A-Z]", REG_EXTENDED);
  regmatch_t matches[1];
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    /* Possible weaknesses found:
     *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
     */
    printf("Uppercase letter found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, &str[matches[0].rm_so]);
    /* Possible weaknesses found:
     *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
     */
    str += matches[0].rm_eo;
  }
  regfree(&regex);

  // Create regex pattern to match lowercase letters
  regcomp(&regex, "[a-z]", REG_EXTENDED);
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    /* Possible weaknesses found:
     *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
     */
    printf("Lowercase letter found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, &str[matches[0].rm_so]);
    /* Possible weaknesses found:
     *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
     */
    str += matches[0].rm_eo;
  }
  regfree(&regex);

  // Create regex pattern to match special characters
  regcomp(&regex, "[^A-Za-z0-9]", REG_EXTENDED);
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    /* Possible weaknesses found:
     *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
     */
    printf("Special character found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, &str[matches[0].rm_so]);
    /* Possible weaknesses found:
     *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
     */
    str += matches[0].rm_eo;
  }
  regfree(&regex);

  // Create regex pattern to match numeric values
  regcomp(&regex, "[0-9]", REG_EXTENDED);
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    /* Possible weaknesses found:
     *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
     */
    printf("Numeric value found: %.*s\n", matches[0].rm_eo - matches[0].rm_so, &str[matches[0].rm_so]);
    /* Possible weaknesses found:
     *  Cannot determine that 'matches[0]' is initialized [premium-bughuntingUninit]
     */
    str += matches[0].rm_eo;
  }
  regfree(&regex);
}

int main() {
  const char* str = "Hello, World! 123";
  find_characters(str);
  return 0;
}