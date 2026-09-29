#include <stdio.h>
#include <regex.h>
#include <string.h>

void findFiveCharacterWords(const char* str) {
  regex_t regex;
  regmatch_t matches[1];

  if (regcomp(&regex, "\\b[a-zA-Z]{5}\\b", REG_EXTENDED) != 0) {
    printf("Failed to compile regex.\n");
    return;
  }

  const char* end = str + strlen(str);
  while (regexec(&regex, str, 1, matches, 0) == 0) {
    printf("Five character words found:\n");
    for(int i=matches[0].rm_so; i < matches[0].rm_eo; i++) {
      printf("%c", str[i]);
    }
    printf("\n");
    str += matches[0].rm_eo + 1;
    if (str > end)
      break;
  }

  regfree(&regex);
}

int main() {
  const char* str = "Write a C function to find all five characters long word in the given string by using regex.";
  findFiveCharacterWords(str);
  
  return 0;
}