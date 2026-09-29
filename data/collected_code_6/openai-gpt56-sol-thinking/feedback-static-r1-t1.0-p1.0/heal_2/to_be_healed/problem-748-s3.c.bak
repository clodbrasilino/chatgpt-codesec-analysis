#include <ctype.h>
#include <errno.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *insert_spaces_before_capitals(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_length;
    size_t source_offset = 0;
    size_t destination_offset = 0;
    int status;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        errno = status == REG_ESPACE ? ENOMEM : EINVAL;
        return NULL;
    }

    input_length = strlen(input);
    if (input_length > (SIZE_MAX - 1) / 2) {
        regfree(&regex);
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(input_length * 2 + 1);
    if (result == NULL) {
        int saved_errno = errno;
        regfree(&regex);
        errno = saved_errno;
        return NULL;
    }

    while ((status = regexec(&regex, input + source_offset,
                             1, &match, 0)) == 0) {
        size_t match_start;
        size_t match_end;
        size_t segment_length;

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            free(result);
            regfree(&regex);
            errno = EINVAL;
            return NULL;
        }

        if ((size_t)match.rm_eo > input_length - source_offset) {
            free(result);
            regfree(&regex);
            errno = EINVAL;
            return NULL;
        }

        match_start = source_offset + (size_t)match.rm_so;
        match_end = source_offset + (size_t)match.rm_eo;
        segment_length = match_start - source_offset;

        memcpy(result + destination_offset,
               input + source_offset,
               segment_length);
        destination_offset += segment_length;

        if (match_start > 0 &&
            !isspace((unsigned char)input[match_start - 1])) {
            result[destination_offset++] = ' ';
        }

        segment_length = match_end - match_start;
        memcpy(result + destination_offset,
               input + match_start,
               segment_length);
        destination_offset += segment_length;
        source_offset = match_end;
    }

    if (status != REG_NOMATCH) {
        free(result);
        regfree(&regex);
        errno = status == REG_ESPACE ? ENOMEM : EINVAL;
        return NULL;
    }

    memcpy(result + destination_offset,
           input + source_offset,
           input_length - source_offset);
    destination_offset += input_length - source_offset;
    result[destination_offset] = '\0';

    regfree(&regex);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = insert_spaces_before_capitals(argv[1]);
    if (result == NULL) {
        perror("insert_spaces_before_capitals");
        return EXIT_FAILURE;
    }

    errno = 0;

    if (fputs(result, stdout) == EOF ||
        fputc('\n', stdout) == EOF ||
        fflush(stdout) == EOF) {
        if (errno == 0) {
            errno = EIO;
        }

        perror("output");
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}