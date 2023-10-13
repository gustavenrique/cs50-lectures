#include <cs50.h>
#include <ctype.h> // isspace(), isalpha()
#include <stdio.h>
#include <string.h>
#include <math.h> // round()

int count_letters(string txt);
int count_words(string txt);
int count_sent(string txt);
int display_result(float index);

int main(void)
{
    // asking the user for the text
    string txt = get_string("Text: ");
    
    // calculating the number of letters
    int letters = count_letters(txt);
    
    // calculating the number of words
    int words = count_words(txt);
    
    // calculating the number of sentences
    int sent = count_sent(txt);
    
    // calculating the indices
    float L = (letters * 100) / (float) words;
    float S = (sent * 100) / (float) words;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    // displaying the result to the user
    display_result(index);
    
}

int count_letters(string txt)
{
    int letters = 0;
    for (int i = 0, len = strlen(txt); i < len; i++)
    {
        if (isalpha(txt[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string txt)
{
    int words = 0;
    for (int i = 0, len = strlen(txt); i < len; i++)
    {
        if (isspace(txt[i]))
        {
            words++;
        }
    }
    return words + 1;
}

int count_sent(string txt)
{
    int sent = 0;
    for (int i = 0, len = strlen(txt); i < len; i++)
    {
        if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            sent++;
        }
    }
    return sent;
}

int display_result(float index)
{
    if (index > 16)
    {
        printf("Grade 16+\n");
    } else if (index < 1)
    {
        printf("Before Grade 1\n");
    } else
    {
        printf("Grade %i\n", (int) round(index));
    }
    return 0;
}