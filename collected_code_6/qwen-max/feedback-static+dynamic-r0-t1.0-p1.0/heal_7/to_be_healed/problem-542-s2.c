#include <stdio.h>
#include <regex.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int replace_chars_with_colon(char *str, size_t str_len) {
    regex_t reg;
    if (regcomp(&reg, "[ ,.]", REG_EXTENDED | REG_NEWLINE) != 0) return -1;

    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int pos = 0;

    while (regexec(&reg, str + pos, nmatch, pmatch, 0) == 0) {
        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        size_t new_str_len = str_len + 1; // Add 1 for the colon
        /* Possible weaknesses found:
         *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
         */
        char *new_str = (char *)malloc(new_str_len + 1);
        if (!new_str) return -1;

        snprintf(new_str, new_str_len + 1, "%.*s:%.*s", (int)match_len, str + pos, (int)(str_len - (pos + match_len)), str + pos + match_len);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t new_len = strlen(new_str);

        memmove(str + pos + new_len, str + pos + pmatch[0].rm_eo, str_len - (pos + pmatch[0].rm_eo) + 1);
        memmove(str + pos, new_str, new_len);

        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(new_str);

        pos += new_len - match_len;
        str_len += new_len - match_len;
    }

    regfree(&reg);
    return 0;
}

int main() {
    char input[] = "Hello, world. This is a test, of the system.";
    size_t input_len = sizeof(input) - 1;
    if (replace_chars_with_colon(input, input_len) == 0) {
        printf("%s\n", input);
    } else {
        printf("Replacement failed.\n");
    }
    return 0;
}