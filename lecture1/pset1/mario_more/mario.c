#include <cs50.h> 
#include <stdio.h>

int main(void) 
{
    int h;
    
    do 
    {
        h = get_int("Height: ");
        
        if (h < 1 || h > 8) 
        {
            printf("It must be some number between 1 and 8.");
        }
    } while (h < 1 || h > 8);
    
    for (int i = 1; i <= h; i++) //i: layer of the tower
    {
        for (int s = h - i; s > 0; s--) //s: space
        {
            printf(" ");
        }
        
        for (int j = 1; j <= i; j++) //j: brick
        {
            printf("#");
        }
        
        printf("  ");
        
        for (int j2 = 1; j2 <= i; j2++) //j: brick2
        {
            printf("#");
        }
        
        printf("\n");
    }
}