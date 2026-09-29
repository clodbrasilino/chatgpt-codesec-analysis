#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void findWords(char *str) {
  regex_t regex;
  regmatch_t matches[2];
  char *p = str;
  int len;

  if (regcomp(&regex, "\\b\\w{4,}\\b", 0)) {
    fprintf(stderr, "Could not compile regex\n");
    exit(1);
  }

  while (!regexec(&regex, p, 2, matches, 0)) {
    len = matches[0].rm_eo - matches[0].rm_so;
    char *match = malloc(len + 1);
    if (!match) {
      fprintf(stderr, "Could not allocate memory\n");
      exit(1);
    }
    strncpy(match, p + matches[0].rm_so, len);
    match[len] = '\0';
    printf("%s\n", match);
    free(match);
    p += matches[0].rm_eo;
  }
  
  regfree(&regex);
}

int main() {
  char str[] = "This is a sample string.";
  findWords(str);
  return 0;
}