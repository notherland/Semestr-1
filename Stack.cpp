#include <iostream>
#include <stdio.h>
#include <cmath>
#include <assert.h>

struct Stack_t
{
    char* data;
    size_t size;
    int error;
};

bool StackPush(Stack_t *stack, char new_elem);
char StackPop(Stack_t *stack);
void AddMem(Stack_t *stack);
void DellMem (Stack_t *stack);
bool StackOK (Stack_t *stack);
void Dump (Stack_t *stack);


const int MAXSIZE  = 10000;
const int MINSIZE = 1;
const int NULLPTR = 228;
const int BOTTOM_EXIT = 69;
const int TOP_EXIT = 1337;
const int FAIL = 1;
const int SUCCESS = 0;
const int SLOT = 1;

int main()
{
    Stack_t stack = {NULL, 0, 0};
    stack.data = (char*)calloc(MINSIZE, sizeof(char));//Тут я создаю calloc нулевого размера , может быть лажа

    StackPush (&stack, 28);
    StackPush (&stack, 123);
    StackPush (&stack, 13);
    int b = StackPop(&stack);
    StackPush (&stack, 21);
    printf("POP - %d\n", b);

    for (int i = 0; i < stack.size; i++)
        printf ("Elem[%d] = %d\n", i, stack.data[i]);
    return 0;
}

bool StackPush(Stack_t *stack, char new_elem)
{
    if (StackOK)
        Dump(stack);
    AddMem(stack);
    stack->data[stack->size++] = new_elem;
    if(StackOK)
        Dump(stack);
    return SUCCESS;
}

char StackPop(Stack_t *stack)
{
    if (StackOK(stack))
        Dump(stack);
    char top = stack->data[stack->size];
    printf ("%d", top);
    DellMem(stack);
    stack->size--;
    return top;
}

void AddMem(Stack_t *stack)
{
    stack->data = (char*)realloc(stack->data, stack->size + SLOT);
}

void DellMem (Stack_t *stack)
{
    stack->data = (char*)realloc(stack->data, stack->size - SLOT);
}

bool StackOK (Stack_t *stack)
{
    assert(stack);

    if (stack->data == NULL)
    {
        stack->error = NULLPTR;
        return FAIL;
    }

    if (stack->size < MINSIZE)
    {
        stack->error = BOTTOM_EXIT;
        return FAIL;
    }

    if (stack->size > MAXSIZE )
    {
        stack->error = TOP_EXIT;
        return FAIL;
    }

    return SUCCESS;
}

void Dump(Stack_t *stack)
{
    //printf("Size: %d", stack->size);
    switch (stack->error)
    {
        case 69:
        {
            printf("Going beyond the bottom of the array");
            break;
        }
        case 1337:
        {
            printf("Exceeding the upper bound of the array");
            break;
        }
        case 228:
        {
            printf("Array error");
            break;
        }

    }
}
