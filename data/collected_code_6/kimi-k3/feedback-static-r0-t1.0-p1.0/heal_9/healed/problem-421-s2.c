#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

static int safe_strlen(const char *s, size_t maxlen, size_t *out_len)
{
    const char *end;
    
    if (s == NULL || out_len == NULL)
    {
        return -1;
    }
    
    end = memchr(s, '\0', maxlen);
    if (end == NULL)
    {
        return -1;
    }
    
    *out_len = (size_t)(end - s);
    return 0;
}

char *join_tuple(const char **tuple, size_t count, const char *delimiter)
{
    size_t total_length = 1;
    size_t delimiter_length = 0;
    size_t i;
    char *result;
    char *current;

    if (tuple == NULL || delimiter == NULL)
    {
        return NULL;
    }

    if (count > 0 && count <= SIZE_MAX / 2)
    {
        if (safe_strlen(delimiter, 4096, &delimiter_length) != 0)
        {
            return NULL;
        }
    }
    else if (count > 0)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        size_t element_length;
        
        if (tuple[i] == NULL)
        {
            return NULL;
        }
        
        if (safe_strlen(tuple[i], 4096, &element_length) != 0)
        {
            return NULL;
        }
        
        if (total_length > SIZE_MAX - element_length)
        {
            return NULL;
        }
        total_length += element_length;
        
        if (i < count - 1)
        {
            if (total_length > SIZE_MAX - delimiter_length)
            {
                return NULL;
            }
            total_length += delimiter_length;
        }
    }

    result = (char *)malloc(total_length);
    if (result == NULL)
    {
        return NULL;
    }

    current = result;
    for (i = 0; i < count; i++)
    {
        size_t element_length;
        size_t remaining = (size_t)(result + total_length - current);
        
        if (safe_strlen(tuple[i], remaining, &element_length) != 0)
        {
            free(result);
            return NULL;
        }
        
        if (element_length > 0)
        {
            if (element_length >= remaining)
            {
                free(result);
                return NULL;
            }
            if (element_length <= remaining - 1)
            {
                memcpy(current, tuple[i], element_length);
                current += element_length;
            }
            else
            {
                free(result);
                return NULL;
            }
        }

        if (i < count - 1)
        {
            remaining = (size_t)(result + total_length - current);
            
            if (delimiter_length >= remaining)
            {
                free(result);
                return NULL;
            }
            
            if (delimiter_length > 0)
            {
                if (delimiter_length <= remaining - 1)
                {
                    memcpy(current, delimiter, delimiter_length);
                    current += delimiter_length;
                }
                else
                {
                    free(result);
                    return NULL;
                }
            }
        }
    }
    *current = '\0';

    return result;
}

int main(void)
{
    const char *tuple[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(tuple) / sizeof(tuple[0]);
    const char *delimiter = ", ";
    char *joined;

    joined = join_tuple(tuple, count, delimiter);
    if (joined == NULL)
    {
        fprintf(stderr, "Error: failed to join tuple elements\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);

    free(joined);
    joined = NULL;

    return EXIT_SUCCESS;
}