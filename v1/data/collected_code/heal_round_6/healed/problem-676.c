#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void removeNonAlphanumeric(char *str, size_t str_length);
char *regreplace(char *str, regex_t regex);

int main() {
    char string[] = "Hello, World! 123 #^&%$*";
    removeNonAlphanumeric(string, strlen(string));

    printf("%s", string);
    return 0;
}

void removeNonAlphanumeric(char *str, size_t str_length) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, "[^[:alnum:]]", 0);

  if (reti == 0) {
    reti = regexec(&regex, str, 0, NULL, 0);

    if (reti == 0) {
      regfree(&regex);
      regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED);
      char *result = regreplace(str, regex);
      if(result == NULL) return;
      
      size_t length = str_length;
      length = length >= str_length ? str_length - 1 : length;

      memmove(str, result, length);
      str[length] = '\0';
    }

    regfree(&regex);
  }
} 

char *regreplace(char *str, regex_t regex) {
    if (str == NULL) return NULL;
    return str;
}