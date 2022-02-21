#include "ccvector.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE    100

int VecCreate(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = NULL;

    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }

    free(vec->Array);
    free(vec);

    *Vector = NULL;

    return 0;
}

int VecResizeUp(CC_VECTOR *Vector)
{
    CC_VECTOR* aux = NULL;
    aux = (CC_VECTOR*) malloc(sizeof(CC_VECTOR));
    if(NULL == aux)
    {
        return -1;
    }
    aux->Count = Vector->Count;
    aux->Size = Vector->Size * 2;
    aux->Array = (int*) malloc(sizeof(int) * aux->Size);
    if(NULL == aux->Array)
    {
        return -1;
    }

    int i;
    for(i = 0 ; i < Vector->Count ; i++)
    {
         aux->Array[i] = Vector->Array[i];
    }
    free(Vector->Array);
    free(Vector);
    *Vector = *aux;
    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        if(0 != VecResizeUp(Vector))
        {
            return -1;
        }
    }

    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        if(0 != VecResizeUp(Vector))
        {
            return -1;
        }
    }

    for (int i = Vector->Count-1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        if(0 != VecResizeUp(Vector))
        {
            return -1;
        }
    }

    for (int i = Vector->Count - 1; i >= Index; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[Index] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index) {
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    if (Index >= Vector->Count || Index < 0)
    {
        return -1;
    }
    int i;
    for(i = Index ; i < Vector->Count - 1 ; i++)
    {
        Vector->Array[i] = Vector->Array[i + 1];
    }
    Vector->Count--;
    return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    if(Index >= Vector->Count || Index < 0)
    {
        return -1;
    }
    *Value = Vector->Array[Index];
    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (NULL == Vector)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (NULL == Vector)
    {
        return -1;
    }
    Vector->Count = 0;
    Vector->Size = INITIAL_SIZE;
    free(Vector->Array);
    Vector->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == Vector->Array)
    {
        free(Vector);
        return -1;
    }
    return 0;
}

int PlacePivot(CC_VECTOR* Vector, int left, int right, int* Index)
{
    if(NULL == Vector)
    {
        return -1;
    }
    int pivot = Vector->Array[right];
    int st = left - 1;
    int i, aux;
    for(i = left ; i < right ; i++)
    {
        if(Vector->Array[i] > pivot)
        {
            st++;
            aux = Vector->Array[st];
            Vector->Array[st] = Vector->Array[i];
            Vector->Array[i] = aux;
        }
    }
    aux = Vector->Array[st + 1];
    Vector->Array[st + 1] = Vector->Array[right];
    Vector->Array[right] = aux;
    *Index = st + 1;
    return 0;

}

int QuickSort(CC_VECTOR* Vector, int left, int right){
    if(left < right)
    {
        int pivot;
        int res = PlacePivot(Vector, left, right, &pivot);
        if(0 != res)
        {
            return -1;
        }
        res = QuickSort(Vector, left, pivot - 1);
        if(0 != res)
        {
            return -1;
        }
        res = QuickSort(Vector, pivot + 1, right);
        if(0 != res)
        {
            return -1;
        }
        return 0;
    }
    return 0;
}

int VecSort(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (NULL == Vector)
    {
        return -1;
    }
    int res = QuickSort(Vector, 0, Vector->Count - 1);
    return res;
}

int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector)
{
    CC_UNREFERENCED_PARAMETER(DestVector);
    CC_UNREFERENCED_PARAMETER(SrcVector);
    if (NULL == DestVector || NULL == SrcVector)
    {
        return -1;
    }
    int i, res;
    for(i = 0 ; i < SrcVector->Count ; i++)
    {
        res = VecInsertTail(DestVector, SrcVector->Array[i]);
        if(0 != res)
        {
            return res;
        }
    }
    return 0;
}
