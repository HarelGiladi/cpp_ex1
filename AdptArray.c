#include <stdio.h>
#include <assert.h>
#include "AdptArray.h"
#include "book.h"
#include "Person.h"
#include <string.h>
#include <stdlib.h>
 
// i worte this with help of past exams and gpt for some help

// define oue structre "class"
typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray;



// parm: arr, index
//return: cell value  of index or null
PElement GetAdptArrayAt(PAdptArray arr, int index){
    if (arr == NULL)
        return NULL;
    else if(index >= arr->ArrSize)
        return NULL;
    else if(index < 0)
        return NULL;
    if (arr->pElemArr[index] != NULL)    
        return arr->copyFunc(arr->pElemArr[index]);
    return NULL;
}

//parm: arr
//return : void
void PrintDB(PAdptArray arr){
    if (arr == NULL) 
        return;
    int i =0;
    while(i < arr->ArrSize){
        if (arr->pElemArr[i] != NULL)   
            arr->printFunc(arr->pElemArr[i]);
        i++;
    }
}
// parm : copy funcation, delete funaction, print funcation
//return: adapt array
PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete, PRINT_FUNC print)
{
	PAdptArray arr = (PAdptArray)malloc(sizeof(AdptArray));
	if (arr == NULL)
		return NULL;
	arr->ArrSize = 0;
	arr->pElemArr = (PElement*)calloc(0, sizeof(PElement));
	arr->delFunc = delete;
	arr->copyFunc = copy;
    arr->printFunc = print;
	return arr;
}

// parm: arr
//return: size
int GetAdptArraySize(PAdptArray arr){
    if (arr == NULL)
        return -1;
    return arr->ArrSize;
}


//parm: arr
//return: void
void DeleteAdptArray(PAdptArray arr){
	if (arr == NULL)   
		return;
    int i=0;
    while (i < arr->ArrSize){
        if (arr->pElemArr[i] != NULL)
            arr->delFunc(arr->pElemArr[i]);
       i++;
    }
    
}

//parm: arr , index, element
//return: success ot fail 
Result SetAdptArrayAt(PAdptArray arr, int index, PElement new_element)
{
    if (arr == NULL)
        return FAIL;
    else if( index < 0)
        return FAIL;
    if (arr->ArrSize <= index) {
        int bigger_size = index + 1;
        PElement* newElemArr = realloc(arr->pElemArr, bigger_size*sizeof(PElement));
        if (newElemArr == NULL)
            return FAIL;
        int i=arr->ArrSize;
        while (i < bigger_size){
            newElemArr[i] = NULL;
            i++;
        }
        arr->pElemArr = newElemArr;
        arr->ArrSize = bigger_size;
    }
    if (arr->pElemArr[index] != NULL)
        arr->delFunc(arr->pElemArr[index]);
    arr->pElemArr[index] = arr->copyFunc(new_element);
    
    return SUCCESS;
}