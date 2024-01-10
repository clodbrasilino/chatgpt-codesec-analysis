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

  const char* start = str;
  /* Possible weaknesses found:
   *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
   */
  const char* end = str + strlen(str);
  while (start < end && regexec(&regex, start, 1, matches, 0) == 0) {
    printf("Five character words found:\n");
    for(int i=matches[0].rm_so; i < matches[0].rm_eo; i++) {
      printf("%c", start[i]);
    }
    printf("\n");
    start += matches[0].rm_eo;

    if (start >= end)
      break;
  }

  regfree(&regex);
}

int main() {
  const char* str = "Write a C function to find all five characters long word in the given string by using regex.";
  findFiveCharacterWords(str);
  
  return 0;
}