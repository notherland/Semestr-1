#include <iostream>
#include <stdio.h>
#include <cmath>
#include <assert.h>

struct Stack_t
{
    char* data;
    size_t size;
    int error;
    long long hash;
};

bool StackPush(Stack_t *stack, char new_elem);
char StackPop(Stack_t *stack);

void AddMem(Stack_t *stack);
void DellMem (Stack_t *stack);

bool StackOK (Stack_t *stack);
void Dump (Stack_t *stack);

void StackDestroy (Stack_t *stack);

void StackHashAdd(Stack_t *stack);
void StackHashDown(Stack_t *stack);
long long CheckHash (Stack_t *stack);
void StackAssert (Stack_t *stack);

int Degree (int a, int n);


const int MAXSIZE  = 100;
const int MINSIZE = 1;

const int NULLPTR = 228;
const int BOTTOM_EXIT = 69;
const int TOP_EXIT = 1337;
const int HACK_ERROR = 1001;

const int FAIL = 1;
const int SUCCESS = 0;

const int SLOT = 1;

const long long KEY = 2;

int main()
{
    Stack_t stack = {NULL, 0, 0, 0};
    stack.data = (char*)calloc(MINSIZE, sizeof(char));//Тут я создаю calloc нулевого размера , может быть лажа
    //НАЧАЛО ВВОДА
    StackPush (&stack, 28);
    StackPush (&stack, 123);
    StackPush (&stack, 13);
    StackPush (&stack, 21);
    StackPush (&stack, 1);
    int b = StackPop(&stack);
    //КОНЕЦ ВВОДА

        printf ("HASH - %lld\n", stack.hash);
        printf("TOP - %d\n", b);
        for (int i = 0; i < stack.size; i++)
            printf("Elem[%d] = %d\n", i, stack.data[i]);

    StackDestroy(&stack);
    return 0;
}

bool StackPush(Stack_t *stack, char new_elem)
{
    //if (StackOK)
    //    Dump(stack);
    StackAssert(stack);
    AddMem(stack);
    stack->data[stack->size - 1] = new_elem;
    StackHashAdd(stack);
    //if(StackOK)
    //    Dump(stack);
    StackAssert(stack);

    return SUCCESS;
}

char StackPop(Stack_t *stack)
{
    //if (StackOK(stack))
    //    Dump(stack);
    StackAssert (stack);
    char top = stack->data[stack->size - 1];
    DellMem(stack);
    StackHashDown(stack);
    //if (StackOK(stack))
    //    Dump(stack);
    StackAssert (stack);

    return top;
}

void AddMem(Stack_t *stack)
{
    stack->data = (char*)realloc(stack->data, stack->size + SLOT);
    stack->size++;
}

void DellMem (Stack_t *stack)
{
    stack->data = (char*)realloc(stack->data, stack->size - SLOT);
    stack->size--;
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

    if (stack->size >= MAXSIZE )
    {
        stack->error = TOP_EXIT;
        return FAIL;
    }
    if (stack->hash != CheckHash(stack))
    {
        //printf("CheckHash - %lld\n", CheckHash(stack));
        stack->error = HACK_ERROR;
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
            //StackDestroy(stack);
            //stack->error = -1;
            break;
        }
        case 1337:
        {
            printf("Exceeding the upper bound of the array");
            //StackDestroy(stack);
            //stack->error = -1;
            break;
        }
        case 228:
        {
            printf("Array error");
            //StackDestroy(stack);
            //stack->error = -1;
            break;
        }
        case HACK_ERROR:
        {
            printf( "HACK");
            break;
        }

    }
}

void StackDestroy (Stack_t *stack)
{
    //stack->data = (char*)realloc(stack->data, MINSIZE);
    //stack->size = MINSIZE;
    free(stack->data);
}

void StackHashAdd(Stack_t *stack)
{
    stack->hash = stack->hash + stack->data[stack->size - 1] * Degree(KEY, stack->size);
}

void StackHashDown(Stack_t *stack)
{
    stack->hash = stack->hash - stack->data[stack->size - 1] * Degree(KEY, stack->size);
}

int Degree (int a, int n)
{
    for (int i = 0; i < n ; i++)
        a = a * a;
    return a;
}

long long CheckHash (Stack_t *stack)
{
    int hash = 0;
    for (int i = 0; i < stack->size; i++)
        hash = hash + stack->data[i] * Degree(KEY, i);
    return hash;
}

void StackAssert (Stack_t *stack)
{
    if (StackOK(stack))
    {
        Dump(stack);
        abort();
    }
}
