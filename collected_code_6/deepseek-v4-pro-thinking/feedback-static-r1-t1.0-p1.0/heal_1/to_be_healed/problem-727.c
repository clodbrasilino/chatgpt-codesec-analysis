#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

enum remove_status {
    REMOVE_OK = 0,
    REMOVE_EINVAL = -1,
    REMOVE_EREGCOMP = -2,
    REMOVE_EREGEXEC = -3,
    REMOVE_ESMALLBUF = -4
};

int remove_non_alphanumeric(const char *input, char *output, size_t output_size) {
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t out_pos = 0;
    const char *p;
    const char *end;

    if (input == NULL || output == NULL || output_size == 0) {
        return REMOVE_EINVAL;
    }

    ret = regcomp(&regex, "[[:alnum:]]", REG_EXTENDED);
    if (ret != 0) {
        return REMOVE_EREGCOMP;
    }

    p = input;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    end = input + strlen(input);

    while (p < end) {
        ret = regexec(&regex, p, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            regfree(&regex);
            return REMOVE_EREGEXEC;
        }

        if (match.rm_so < 0) {
            regfree(&regex);
            return REMOVE_EREGEXEC;
        }

        if (out_pos >= output_size - 1) {
            regfree(&regex);
            return REMOVE_ESMALLBUF;
        }

        output[out_pos++] = p[match.rm_so];
        p += match.rm_so + 1;
    }

    output[out_pos] = '\0';
    regfree(&regex);
    return REMOVE_OK;
}

int main(void) {
    const char input[] = "Hello, World! 123";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[128];
    int result;

    result = remove_non_alphanumeric(input, output, sizeof(output));
    if (result != REMOVE_OK) {
        fprintf(stderr, "Error: %d\n", result);
        return EXIT_FAILURE;
    }

    printf("%s\n", output);
    return EXIT_SUCCESS;
}