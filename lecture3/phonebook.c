#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string num;
}
person;

int main(void)
{
    person people[2];
    
    people[0].name = "Gugu";
    people[0].num = "+55 11 40028922";
    
    people[1].name = "Babu";
    people[1].num = "+42 15 37803672";
    
    string who = get_string("Who are you looking for? ");
    
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, who) == 0)
        {
            printf("Found: %s\n", people[i].num);
            return 0;
        }
    }
    printf("Not found :/\n");
    return 1;
}