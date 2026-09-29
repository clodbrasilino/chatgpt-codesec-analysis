#include <stdio.h>
#include <regex.h>

void findFiveCharacterWords(const char* str) {
  regex_t regex;
  regmatch_t matches;

  if (regcomp(&regex, "\\b[a-zA-Z]{5}\\b", REG_EXTENDED) != 0) {
    printf("Failed to compile regex.\n");
    return;
  }
  
  if (regexec(&regex, str, 1, &matches, 0) == 0) {
    printf("Five character words found:\n");

    char* match = (char*)str + matches.rm_so;
    while (match < str + matches.rm_eo) {
      printf("%.*s\n", (int)(str + matches.rm_eo - match), match);
      /* Possible weaknesses found:
       *  invalid operands to binary - (have 'regoff_t' {aka 'long long int'} and 'char *')
       */
      match += matches.rm_eo - match + 1;
    }
  } else {
    printf("No five character words found.\n");
  }

  regfree(&regex);
}

int main() {
  const char* str = "Write a C function to find all five characters long word in the given string by using regex.";
  findFiveCharacterWords(str);

  return 0;
}