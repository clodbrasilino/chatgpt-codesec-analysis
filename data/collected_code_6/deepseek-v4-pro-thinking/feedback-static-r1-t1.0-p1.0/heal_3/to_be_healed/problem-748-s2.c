#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_line(void)
{
    size_t cap = 128;
    size_t len = 0;
    char *buf = malloc(cap);
    int ch;

    if (!buf)
        return NULL;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[len++] = (char)ch;
    }
    if (ch == EOF && len == 0) {
        free(buf);
        return NULL;
    }
    buf[len] = '\0';
    {
        char *tmp = realloc(buf, len + 1);
        if (tmp)
            buf = tmp;
    }
    return buf;
}

static int safe_copy(char *dst, size_t dst_size, size_t *pos,
                     const char *src, size_t n)
{
    if (*pos + n >= dst_size)
        return 0;
    for (size_t i = 0; i < n; i++)
        dst[(*pos)++] = src[i];
    return 1;
}

char *insert_spaces(const char *str)
{
    regex_t regex;
    char *output = NULL;
    size_t max_len, pos = 0, offset = 0;
    int status;

    if (!str)
        return NULL;

    status = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (status != 0)
        return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    max_len = strlen(str) * 2 + 1;
    output = malloc(max_len);
    if (!output) {
        regfree(&regex);
        return NULL;
    }

    while ((status = regexec(&regex, str + offset, 1, NULL, 0)) == 0) {
        regmatch_t match;
        if (regexec(&regex, str + offset, 1, &match, 0) != 0)
            break;
        size_t match_start = offset + match.rm_so;
        size_t match_end   = offset + match.rm_eo;
        size_t seg_len     = match_start - offset;

        if (!safe_copy(output, max_len, &pos, str + offset, seg_len)) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        if (match_start > 0 && !isspace((unsigned char)str[match_start - 1])) {
            if (pos >= max_len - 1) {
                free(output);
                regfree(&regex);
                return NULL;
            }
            output[pos++] = ' ';
        }

        if (!safe_copy(output, max_len, &pos, str + match_start,
                       match_end - match_start)) {
            free(output);
            regfree(&regex);
            return NULL;
        }

        offset = match_end;
    }

    if (status != REG_NOMATCH) {
        free(output);
        regfree(&regex);
        return NULL;
    }

    {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t rem = strlen(str + offset);
        if (!safe_copy(output, max_len, &pos, str + offset, rem)) {
            free(output);
            regfree(&regex);
            return NULL;
        }
    }

    output[pos] = '\0';
    regfree(&regex);
    return output;
}

int main(void)
{
    char *input = read_line();
    if (!input)
        return 1;

    char *result = insert_spaces(input);
    free(input);

    if (!result) {
        fputs("Error processing string\n", stderr);
        return 1;
    }

    puts(result);
    free(result);
    return 0;
}