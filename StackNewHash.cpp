#include <stdio.h>
#include <cmath>
#include <assert.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_WHITE     "\x1b[37m"
#define ANSI_COLOR_YELLOW    "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

const char FAIL = 0;
const char SUCCESS = 1;
const char ST_FULL = 2;
const char ST_EMPTY = 3;
const char NULL_PTRS = 4;
const char DATANULLPTR = 5;
const char SIZENULLPTR = 6;
const int MAXSIZE = 3;
const int MINSIZE = 0;
struct stack {
    char *data; //указательн на начало памяти стека
    int size; //количество элементов в стеке
    //size_t maxsize;
    int Errorcode;
};

char Pop(struct stack *st_ptrs);

void Push(struct stack *st_ptrs, char x);

bool StackOK(struct stack *st_ptrs);

void Dump(struct stack *st_ptrs);

void Mem_increase(struct stack *st_ptrs);

void Mem_reduce(struct stack *st_ptrs);

void Stack_Init(struct stack *st_ptrs);

void Stack_Destraction(struct stack *st_ptrs);


int main() {


    struct stack st;
    Stack_Init(&st);
    char x = NAN, elem;
    //scanf("%c", &x);
    Stack_Init(&st);
    Push(&st, 'c');
    Push(&st, 'b');
    Push(&st, 'a');
    Push(&st, 'A');
    printf("Last element is:%c\n", Pop(&st));
    printf("Last element is:%c\n", Pop(&st));
    printf("Last element is:%c\n", Pop(&st));
    printf("Last element is:%c\n", Pop(&st));
    Stack_Destraction(&st);
    return 0;

}

void Stack_Init(struct stack *st_ptrs) {
    assert (st_ptrs);
    st_ptrs->size = 0;
    //st_ptrs->maxsize = MAXSIZE;
    st_ptrs->data = (char *) calloc(st_ptrs->size, sizeof(char));
    st_ptrs->Errorcode = -1;
    if (!StackOK(st_ptrs)) {
        Dump(st_ptrs);
        return;
    }

}

void Push(struct stack *st_ptrs, char x) {
    assert (st_ptrs);
    printf( ANSI_COLOR_YELLOW "Putting element %c into stack\n" ANSI_COLOR_WHITE, x);
    st_ptrs->size = st_ptrs->size + 1;
    if (!StackOK(st_ptrs)) {
        Dump(st_ptrs);
        return;
    }
    Mem_increase(st_ptrs);
    st_ptrs->data[st_ptrs->size] = x;
    if (!StackOK(st_ptrs)) {
        Dump(st_ptrs);

        return;
    }
    printf(ANSI_COLOR_GREEN"Elem %c has been put in Stack\n" ANSI_COLOR_WHITE, x);
}

char Pop(struct stack *st_ptrs) {
    assert(st_ptrs);
    printf(ANSI_COLOR_YELLOW"Taking last element out of stack\n" ANSI_COLOR_WHITE);
    st_ptrs->size = st_ptrs->size - 1;
    if (!StackOK(st_ptrs)) {
        Dump(st_ptrs);
        return '_';
    }
    Mem_reduce(st_ptrs);
    //printf("%d", st_ptrs->size);
    printf(ANSI_COLOR_GREEN "Element %c has been taken out of stack\n" ANSI_COLOR_WHITE, st_ptrs->data[st_ptrs->size + 1]);
    return st_ptrs->data[st_ptrs->size + 1];

}

bool StackOK(struct stack *st_ptrs) {
    assert(st_ptrs);
   // printf ("|!%d|\n", st_ptrs->size);
    if (st_ptrs->data == nullptr) {
        st_ptrs->Errorcode = DATANULLPTR;
        return FAIL;
    }
    /*if (st_ptrs->size == nullptr) {
        st_ptrs->Errorcode = SIZENULLPTR;
        return FAIL;}*/
    if (st_ptrs->size < MINSIZE) {
        st_ptrs->size += 1;
        st_ptrs->Errorcode = ST_EMPTY;
        return FAIL;
    }
    if (st_ptrs->size > MAXSIZE) {
        st_ptrs->size = st_ptrs->size - 1;
        st_ptrs->Errorcode = ST_FULL;
        return FAIL;
    }

    return SUCCESS;
}

void Dump(struct stack *st_ptrs) {
    printf(ANSI_COLOR_RED "There is an error:\n");
    printf(ANSI_COLOR_WHITE"Stack size %d\n", st_ptrs->size);
    switch (st_ptrs->Errorcode) {
        case 2: {
            printf("Stack is overflow\n");
            break;
        }
        case 3: {
            printf("Stack is empty\n");
            break;
        }
            //  case 4: {printf ("Stack is overflow"); break;};
        case 5: {
            printf("Null pointer to data\n");
            break;
        }
        case 6: {
            printf("Null pointer to size\n");
            break;
        }
    }
    return;

}

void Mem_increase(struct stack *st_ptrs) {
    st_ptrs->data = (char *) realloc(st_ptrs->data, st_ptrs->size + 1);
}

void Mem_reduce(struct stack *st_ptrs) {
    st_ptrs->data = (char *) realloc(st_ptrs->data, st_ptrs->size + 1);
}

void Stack_Destraction(struct stack *st_ptrs) {
    free(st_ptrs->data);
    st_ptrs->size = 0;
    st_ptrs->Errorcode = 0;
    //  st_ptrs->maxsize = 0;
}
