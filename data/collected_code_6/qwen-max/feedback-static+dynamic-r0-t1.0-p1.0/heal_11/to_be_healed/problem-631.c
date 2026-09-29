#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void swap_whitespace_underscore(char *str, size_t len) {
    regex_t re;
    regmatch_t match;

    if (regcomp(&re, " ", REG_EXTENDED)) return;

    char *new_str = (char *)malloc(len + 1);
    if (!new_str) return;
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_str, str, len);
    new_str[len] = '\0';

    while (regexec(&re, new_str, 1, &match, 0) == 0) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = '_';
        len++;
        /* Possible weaknesses found:
         * ASan: heap-buffer-overflow (AFL crash: id:000004,sig:06,src:000000,time:16383,execs:5205,op:havoc,rep:13)
         */
        new_str[len] = '\0';
    }
    regfree(&re);

    if (regcomp(&re, "_", REG_EXTENDED)) return;
    while (regexec(&re, new_str, 1, &match, 0) == 0) {
        memmove(new_str + match.rm_so + 1, new_str + match.rm_so, len - match.rm_so);
        new_str[match.rm_so] = ' ';
        len++;
        new_str[len] = '\0';
    }
    regfree(&re);

    snprintf(str, len + 1, "%s", new_str);
    free(new_str);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000000,time:25,execs:17,op:havoc,rep:10; likely memory-safety defect
  */

int main() {
    char *input = NULL;
    size_t input_size = 0;
    ssize_t read_len = getline(&input, &input_size, stdin);

    if (read_len != -1) {
        input[strcspn(input, "\n")] = 0;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0) {
            swap_whitespace_underscore(input, len);
            printf("%s\n", input);
        }
        free(input);
    }
    return 0;
}