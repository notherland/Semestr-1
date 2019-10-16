#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

const char* TXTINPUT = "/home/bibi/CLionProjects/NewOnegin/onegin.txt";
const char* TXTOUTPUT = "result.txt";

int SortString(const void *ptr1, const void *ptr2);


int main()
{
    FILE *onegin = fopen( TXTINPUT, "rb");

    assert( onegin );

    int sizetxt = TxtLong(onegin);
    char* txt = (char*)calloc(sizetxt + 1,sizeof(char));

    assert( txt );

    int num = fread(txt, sizeof(char) , sizetxt, onegin);
    if (num == 0 )
        perror("NUM");
    int n_lines = CounterOfLines(txt, sizetxt);
    char** str_ptrs = (char**)calloc(n_lines + 5, sizeof(char*));
    CreateStrPtrs(str_ptrs, txt, sizetxt);
    //output(str_ptrs, txt, n_lines);
    qsort(str_ptrs, n_lines, sizeof(char*), SortString);

    FILE *result = fopen (TXTOUTPUT, "w");
    output(str_ptrs, n_lines, result);

    free(txt);
    free(str_ptrs);

    return 0;
}

//Определяет размер файла

int TxtLong (FILE* onegin)
{
    fseek(onegin, 0 , SEEK_END);
    int length = ftell(onegin);
    fseek(onegin, 0, SEEK_SET);

    return length;
}

//Ищет /n

int CounterOfLines(char *txt, int size){

    assert( txt );

    int Lines = 0;
    for (int letter = 0; letter < size; letter++)
    {
        if (txt[letter] == '\n')
        {
            if (txt[letter + 1] == '\n')
                txt[letter + 1] =' ';
                Lines++;
                txt[letter] == '\0';
        }
    }

    return Lines;
}

//Создает массив указателей

int CreateStrPtrs (char **str_ptrs, char *txt, int sizetxt)
{
    assert( str_ptrs );
    assert( txt );

    str_ptrs[0] = txt;
    int flug = 1;
    for (int i = 1; i < sizetxt; i++)
    {
        if (txt[i] == '\n')
        {
            str_ptrs[flug] = txt + i + 1;
            flug ++;
            txt[i] = '\0';
        }
    }
}

//Функция вывода первой сортировки

int output(char **str_ptrs, int n_lines, FILE *result)
{
    for (int i = 0; i < n_lines; i++)
        fprintf(result, "%s\n", str_ptrs[i]);
}


//Сортировка строк

int SortString(const void *ptr1, const void *ptr2)
{

    assert( ptr1 );
    assert( ptr2 );

    const char* x = *(const char**)ptr1;
    const char* y = *(const char**)ptr2;

    int i = 0;
    int j = 0;
    int diff = 0;
    while (diff == 0 && *(x + i))
    {

        while (!isalpha(*(x + i)))
            i++;

        while (!isalpha(*(y + j)))
            j++;

        diff = *(x + i) - *(y + j);

        if (diff == 0)
        {
            i++;
            j++;
        }
    }

    return diff;
}

/*int SortStringFlip (void *ptr1, void *ptr2)
{
    assert( ptr1 );
    assert( ptr2 );

    const char* x = *(const char**)ptr1;
    const char* y = *(const char**)ptr2;

    
}*/
