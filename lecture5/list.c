#include <stdio.h>
#include <stdlib.h>

//  PUSH FUNCTION DOESN'T MODIFY THE PARAMETER

typedef struct node
{
    int number;
    struct node *next; 
}
node;

void free_list(node *list);
int memory_check(node *list, node *tmp);
int push_number(node *list, node *tmp, int num);

int main(void)
{
    node *list = NULL; // Array of nodes
    
    node *pn = NULL;
    push_number(list, pn, 1);
    
    push_number(list, pn, 2);
    
    push_number(list, pn, 3);
    
    printf("%i", list->number);
    
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    
    // Freeing the entire list
    free_list(list);
}

void free_list(node *list)
{
    while (list!=NULL)
    {
        node *nxtNode = list->next;
        free(list);
        list = nxtNode;
    }
}

int memory_check(node *list, node *tmp)
{
    if (list==NULL && tmp==NULL)
    {
        return 1;
    } 
    else if (tmp==NULL)
    { 
        free_list(list);
        return 1;
    }
    return 0;
}

int push_number(node *list, node *tmp, int num)
{
    node *last_seeker = NULL;
    
    tmp = malloc(sizeof(node));
    memory_check(list, tmp);
    
    tmp->number = num;
    tmp->next = NULL;

    if (list == NULL)
    {
        list = tmp;
        return 0;
    }
    for (last_seeker = list; 1; last_seeker = last_seeker->next)
    {
        if (last_seeker == NULL)
        {
            last_seeker = tmp;
            return 0;
        }
    }
}