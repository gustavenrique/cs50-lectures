#include <cs50.h>
#include <stdio.h>
#include <string.h> // strlen()
#include <stdlib.h> // atoi()
#include <ctype.h> // isupper, lower, alpha, digit

int main(int argc, string argv[])
{
    // verifying it was provided the right amount of args
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    } else
    {
        // verifying if the user provided a valid integer number key
        for (int i = 0, len = strlen(argv[1]); i < len; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // asking for the plaintext:
        const int key = atoi(argv[1]);
        
        string txt = get_string("plaintext: ");
        
        printf("ciphertext: ");
        
        // converting the plaintext into the ciphertext and displaying it
        for (int i = 0, len = strlen(txt); i < len; i++)
        {
            if (!isalpha(txt[i])) //
            {
                printf("%c", txt[i]);
            } else
            {
                // applying the formula: ci = (pi + k) % 26
                if (islower(txt[i]))
                {
                    char c = ((txt[i] - 'a') + key) % 26;
                    printf("%c", c + 'a');
                }
                if (isupper(txt[i]))
                {
                    char c = ((txt[i] - 'A') + key) % 26;
                    printf("%c", c + 'A');
                }
            }
        }
        printf("\n");
    }
    
}