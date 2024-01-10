#include <regex.h>
#include <stddef.h>
#include <string.h>

void removeNonAlphanumeric(char *str);
char *regreplace(char *str, regex_t regex);

int main(){
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

      size_t length = strlen(result);
      if(length >= strlen(str)) {
        length = strlen(str)-1;
      }

      strncpy(str, result, length);
      str[length] = '\0';
    }
    regfree(&regex);
  }
} 

char *regreplace(char *str, regex_t regex) {
    return str;
}