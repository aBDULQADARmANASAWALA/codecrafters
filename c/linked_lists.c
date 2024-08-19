#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = NULL;
    node *ptr = NULL;
    node *n = NULL;
    for (int i = 1; i < argc; i++)
    {
        n = malloc(sizeof(node));
        // condition if no space left
        n -> number = atoi(argv[i]);
        n -> next = NULL;

        if (list == NULL)
        {
            list = n;
            ptr = list;
        }
        else
        {
            if (n -> number < list -> number)
            {
                n -> next = list;
                list = n;
                ptr = list;
            }
            else
            {
                while (ptr -> next != NULL && ptr -> next -> number < n -> number)
                {
                    ptr = ptr -> next;
                }
                if (ptr -> next == NULL)
                {
                    ptr -> next = n;
                    ptr = list;
                }
                else
                {
                    n -> next = ptr -> next;
                    ptr -> next = n;
                    ptr = list;
                }
            }
        }
    }

    while (ptr != NULL)
    {
        printf("%i\n", ptr -> number);
        ptr = ptr -> next;
    }
}
