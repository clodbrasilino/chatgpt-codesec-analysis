#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

int increment_numbers_in_string(char *str, int k)
{
    if (str == NULL)
    {
        return -1;
    }

    size_t len = strlen(str);
    size_t i = 0;

    while (i < len)
    {
        if (isdigit((unsigned char)str[i]))
        {
            size_t start = i;
            long long num = 0;
            int overflow = 0;

            while (i < len && isdigit((unsigned char)str[i]))
            {
                int digit = str[i] - '0';
                if (num > (LLONG_MAX - digit) / 10)
                {
                    overflow = 1;
                }
                else
                {
                    num = num * 10 + digit;
                }
                i++;
            }

            if (overflow)
            {
                return -1;
            }

            if (k > 0 && num > LLONG_MAX - k)
            {
                return -1;
            }
            if (k < 0 && num < LLONG_MIN - k)
            {
                return -1;
            }

            num += k;

            char num_buf[32];
            int num_len = snprintf(num_buf, sizeof(num_buf), "%lld", num);
            if (num_len < 0 || (size_t)num_len >= sizeof(num_buf))
            {
                return -1;
            }

            size_t old_num_len = i - start;
            size_t new_num_len = (size_t)num_len;

            if (new_num_len > old_num_len)
            {
                size_t shift = new_num_len - old_num_len;
                if (len + shift + 1 > len + 1)
                {
                    memmove(str + start + new_num_len, str + start + old_num_len, len - start - old_num_len + 1);
                    len += shift;
                }
            }
            else if (new_num_len < old_num_len)
            {
                size_t shift = old_num_len - new_num_len;
                memmove(str + start + new_num_len, str + start + old_num_len, len - start - old_num_len + 1);
                len -= shift;
            }

            memcpy(str + start, num_buf, new_num_len);
            i = start + new_num_len;
        }
        else
        {
            i++;
        }
    }

    return 0;
}

int main(void)
{
    char buffer[256];
    int k;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    printf("Enter increment value k: ");
    if (scanf("%d", &k) != 1)
    {
        fprintf(stderr, "Invalid input for k\n");
        return EXIT_FAILURE;
    }

    if (increment_numbers_in_string(buffer, k) != 0)
    {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}