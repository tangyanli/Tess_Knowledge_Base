#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* convert unsinged int into char* */
char* itoa(unsigned a)
{
    int tmp = a;
    char* str = NULL;
    char array[9] = {0};
    int index = 7;
    int count = 0;

    while((tmp / 10) > 1)
    {
        array[index--] = tmp % 10 + '0';
        tmp = tmp / 10;
    }

    array[index--] = tmp + '0';
    count = 7 - index;
    str = malloc((count + 1) * sizeof(char));
    memset(str, 0, sizeof(char) * (count + 1));
    strcpy(str, array + index + 1);
    
    return str;
}

int compareStr(char* strA, char* strB)
{
    int compare = 0;
    int sizeA = strlen(strA);
    int sizeB = strlen(strB);
    int maxSize = (sizeA > sizeB) ? sizeA : sizeB;

    for (int index = 0; index < maxSize; index++)
    {
        /* Get the index-th value, if index is more then the end position, than get the last one */
        char a = (index > sizeA - 1) ? strA[sizeA - 1] : strA[index];
        char b = (index > sizeB - 1) ? strB[sizeB - 1] : strB[index];

        if (a != b)
        {
            compare = ( a < b) ? -1 : 1;
            break;
        }                     
    }

    return compare;
}

/* Return the index, than left is big than index-th, the right is small than index-th*/
int divide(char** ptrTable, int start, int end)
{
    char* str = NULL;
    int low  = start;
    int high = end;

    str = ptrTable[low];

    while(high > low)
    {
        while((high > low) && (compareStr(ptrTable[high], str) < 0))
            high--;
        if (high > low)
            ptrTable[low++] = ptrTable[high];
        
        while((high > low) && (compareStr(ptrTable[low], str) > 0))
            low++;
        if (high > low)
            ptrTable[high--] = ptrTable[low];        
    }

    ptrTable[low] = str;
    return low;
}

void quickSort(char** ptrTable, int start, int end)
{
    int index = 0;
    
    if (end > start)
    {
        /* The left of index is big than index, the right of the index is small than index */
        index = divide(ptrTable, start, end);
        quickSort(ptrTable, start, index - 1);
        quickSort(ptrTable, index + 1, end);
    }
}

char* getMaxStr(unsigned* array, int size)
{
    int index = 0;
    int count = 0;
    char** ptrTable = malloc(sizeof(char*) * size);
    char* str = NULL;

    for (index = 0; index < size; index++)
    {
        ptrTable[index] = itoa(array[index]);
        count += strlen(ptrTable[index]);
    }

    quickSort(ptrTable, 0, size -1 );  

    str = malloc(sizeof(char) * (count + 1));
    str[count] = '\0';
    strcpy(str, ptrTable[0]);
    printf("%s,", ptrTable[0]);
    free(ptrTable[0]);
    ptrTable[0] = NULL;

    for (index = 1; index < size; index++)
    {
        strcat(str, ptrTable[index]);
        printf("%s,", ptrTable[index]);
        free(ptrTable[index]);
        ptrTable[index] = NULL;
    }

    printf("\n");
    free(ptrTable);
    return str;  
}

int main()
{
    int a[7] = {4, 5, 43, 404, 45, 442, 446};
    char *b = getMaxStr(a, 7);

    return 0;
}