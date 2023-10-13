#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string word = get_string("Type something: ");

    printf("Capitalized version: ");    
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        printf("%c", toupper(word[i]));
    }
    printf("\n");
}