#include "strcmp.h"

int strcmp(const char* a, const char * b) {
    while(*a && (*a == *b)){
        a++;
        b++;
    }
    return *(unsigned char*)a - *(unsigned char*)b;
}

int strncmp(const char* a, const char* b, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] != b[i] || a[i] == 0 || b[i] == 0)
            return (unsigned char)a[i] - (unsigned char)b[i];
    }
    return 0;
}

void memmove(char *str, int index, int length)
{
    int i = index;

    while(str[i + length] != '\0')
    {
        str[i] = str[i + length];
        i++;
    }

    str[i] = '\0';
}