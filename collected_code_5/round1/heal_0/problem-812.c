#include <stdio.h>
#include <string.h>

char* abbreviate_road(char* str)
{
    char* occurrence = strstr(str, "road");
    while (occurrence != NULL)
    {
        memcpy(occurrence, "rd.", strlen("rd."));
        occurrence += strlen("rd.");
        occurrence = strstr(occurrence, "road");
    }
    return str;
}

int main()
{
    char str[100] = "This road is a broad road.";
    printf("%s\n", abbreviate_road(str));
    return 0;
}