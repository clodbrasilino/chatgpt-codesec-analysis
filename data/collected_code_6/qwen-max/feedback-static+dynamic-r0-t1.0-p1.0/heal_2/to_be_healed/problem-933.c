#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

int camel_to_snake(const char *input, char *output) {
    regex_t re;
    regmatch_t pmatch[1];
    int reti, offset = 0;

    if (regcomp(&re, "([a-z0-9])([A-Z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return -1;
    }

    while ((reti = regexec(&re, input + offset, 1, pmatch, 0)) == 0) {
        for (int i = 0; i < pmatch[0].rm_eo; i++) {
            output[offset + i] = input[offset + i];
        }
        output[offset + pmatch[0].rm_so] = '_';
        output[offset + pmatch[0].rm_eo + 1] = tolower(input[offset + pmatch[0].rm_eo]);
        offset += pmatch[0].rm_eo + 1;
    }

    if (reti != REG_NOMATCH) {
        regfree(&re);
        return -1;
    }

    snprintf(output + offset, sizeof(output) - offset, "%s", input + offset);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (size_t i = 0; i < strlen(output); i++) {
        if (isupper(output[i])) {
            output[i] = tolower(output[i]);
        }
    }

    regfree(&re);
    return 0;
}

int main() {
    const char input[] = "ThisIsACamelCaseString";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[128];

    if (camel_to_snake(input, output) == 0) {
        printf("%s\n", output);
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}