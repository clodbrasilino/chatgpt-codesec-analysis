#include <regex.h>
#include <stddef.h>
#include <string.h>

char *regreplace(char *str, regex_t regex);

int main(){
    // Sample usage of function
    char string[] = "Hello, World! 123 #^&%$*";
    removeNonAlphanumeric(string);
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
