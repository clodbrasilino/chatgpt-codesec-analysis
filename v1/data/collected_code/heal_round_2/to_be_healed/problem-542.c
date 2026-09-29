#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void replace_chars(char *str) {
   const char *replace = ":";
   regex_t regex;
   regmatch_t pmatch[1];
   const size_t nmatch = 1;
   regcomp(&regex, "[ ,.]", REG_EXTENDED);
   
   /* Possible weaknesses found:
    *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
    */
   size_t len = strlen(str) + 1;
   char *new_str = malloc(len);
   /* Possible weaknesses found:
    *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
    */
   strcpy(new_str, str);

   while (regexec(&regex, new_str, nmatch, pmatch, 0) == 0) {
       int size = pmatch[0].rm_eo - pmatch[0].rm_so;
       memmove(&new_str[pmatch[0].rm_so + 1], &new_str[pmatch[0].rm_eo], len - pmatch[0].rm_eo);
       new_str[pmatch[0].rm_so] = replace[0];
       len = len - size;
   }

   /* Possible weaknesses found:
    *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
    */
   strcpy(str, new_str);

   free(new_str);
   regfree(&regex);
}

int main() {
    char str[] = "This is a string, with spaces and commas.";
    replace_chars(str);
    printf("%s\n", str);
    return 0;
}