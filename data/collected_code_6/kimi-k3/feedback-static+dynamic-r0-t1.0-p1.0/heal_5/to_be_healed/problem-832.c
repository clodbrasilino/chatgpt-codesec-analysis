#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>
#include <limits.h>

int extract_max_number(const char *str, long *result)
{
    regex_t regex;
    regmatch_t match[1];
    const char *cursor = str;
    long max_value = LONG_MIN;
    int found = 0;
    int ret;
    size_t str_len;

    if (str == NULL || result == NULL)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    str_len = strlen(str);

    ret = regcomp(&regex, "-?[0-9]+", REG_EXTENDED);
    if (ret != 0)
    {
        return -1;
    }

    while (regexec(&regex, cursor, 1, match, 0) == 0)
    {
        char *endptr = NULL;
        long value;
        regoff_t start = match[0].rm_so;
        regoff_t end = match[0].rm_eo;
        size_t len = (size_t)(end - start);
        size_t cursor_offset = (size_t)(cursor - str);
        size_t remaining;
        char *num_buffer;

        if (start < 0 || end < 0 || end < start)
        {
            break;
        }

        if (cursor_offset > str_len)
        {
            break;
        }

        remaining = str_len - cursor_offset;

        if ((size_t)end > remaining)
        {
            break;
        }

        if (len == 0)
        {
            cursor += 1;
            continue;
        }

        num_buffer = malloc(len + 1);
        if (num_buffer == NULL)
        {
            cursor += end;
            continue;
        }

        if ((size_t)start <= remaining && len <= (remaining - (size_t)start))
        {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num_buffer, cursor + start, len);
            num_buffer[len] = '\0';
        }
        else
        {
            free(num_buffer);
            cursor += end;
            continue;
        }

        errno = 0;
        value = strtol(num_buffer, &endptr, 10);

        if (errno == 0 && endptr != num_buffer && *endptr == '\0')
        {
            if (!found || value > max_value)
            {
                max_value = value;
                found = 1;
            }
        }

        free(num_buffer);
        cursor += end;
    }

    regfree(&regex);

    if (!found)
    {
        return -1;
    }

    *result = max_value;
    return 0;
}

int main(void)
{
    const char *test_strings[] = {
        "The temperature ranges from -5 to 42 degrees with peak at 100",
        "Values: 10, 200, 30, -40, 500",
        "No numbers here",
        "Single number: 7"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++)
    {
        long max_value;

        if (extract_max_number(test_strings[i], &max_value) == 0)
        {
            printf("String: \"%s\"\n", test_strings[i]);
            printf("Maximum number: %ld\n\n", max_value);
        }
        else
        {
            printf("String: \"%s\"\n", test_strings[i]);
            printf("No numbers found.\n\n");
        }
    }

    return 0;
}