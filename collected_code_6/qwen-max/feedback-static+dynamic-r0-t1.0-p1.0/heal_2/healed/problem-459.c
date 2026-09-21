#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

void remove_uppercase_substrings(char *str) {
    regex_t reg;
    regmatch_t matches[1];
    int status = regcomp(&reg, "[A-Z]+", REG_EXTENDED);
    if (!status) {
        char *result = NULL;
        size_t result_size = 0;
        int last_index = 0;
        while (!regexec(&reg, str + last_index, 1, matches, 0)) {
            int match_start = matches[0].rm_so + last_index;
            int match_end = matches[0].rm_eo + last_index;
            result_size += match_start - last_index;
            last_index = match_end;
        }
        result_size += strlen(str + last_index) + 1; // +1 for null terminator
        result = (char *)malloc(result_size);
        if (result) {
            last_index = 0;
            char *p = result;
            while (!regexec(&reg, str + last_index, 1, matches, 0)) {
                int match_start = matches[0].rm_so + last_index;
                int match_end = matches[0].rm_eo + last_index;
                strncpy(p, str + last_index, match_start - last_index);
                p += match_start - last_index;
                last_index = match_end;
            }
            strcpy(p, str + last_index);
            strcpy(str, result);
            free(result);
        }
        regfree(&reg);
    }
}

int main() {
    char test_string[] = "tHis IS a TeSt String";
    remove_uppercase_substrings(test_string);
    printf("%s\n", test_string);
    return 0;
}