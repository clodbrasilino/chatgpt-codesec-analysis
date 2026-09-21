#include <stdio.h>
#include <string.h>
#include <regex.h>

void swap_spaces_underscores(char *str, size_t len) {
    regex_t space_regex, underscore_regex;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char tmp[1024];
    regmatch_t pmatch;

    if (regcomp(&space_regex, " ", REG_EXTENDED) || regcomp(&underscore_regex, "_", REG_EXTENDED)) {
        return;
    }

    while (regexec(&space_regex, str, 1, &pmatch, 0) == 0 && pmatch.rm_eo <= len) {
        size_t copy_len = pmatch.rm_so + 1 + (len - pmatch.rm_eo);
        snprintf(tmp, sizeof(tmp), "%.*s_%.*s", (int)pmatch.rm_so, str, (int)(len - pmatch.rm_eo), str + pmatch.rm_eo);
        if (copy_len + 1 <= len) {
            memmove(str, tmp, copy_len);
            str[copy_len] = '\0';
        } else {
            break;
        }
    }

    while (regexec(&underscore_regex, str, 1, &pmatch, 0) == 0 && pmatch.rm_eo <= len) {
        size_t copy_len = pmatch.rm_so + 1 + (len - pmatch.rm_eo);
        snprintf(tmp, sizeof(tmp), "%.*s %.*s", (int)pmatch.rm_so, str, (int)(len - pmatch.rm_eo), str + pmatch.rm_eo);
        if (copy_len + 1 <= len) {
            memmove(str, tmp, copy_len);
            str[copy_len] = '\0';
        } else {
            break;
        }
    }

    regfree(&space_regex);
    regfree(&underscore_regex);
}

int main() {
    char test_str[] = "Hello World and_Hello_Under_Score";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(test_str);

    swap_spaces_underscores(test_str, len);

    printf("%s\n", test_str);

    return 0;
}