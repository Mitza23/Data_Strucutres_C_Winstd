#include "ccstack.h"
#include "common.h"

#define INITIAL_SIZE    100

int StCreate(CC_STACK **Stack)
{
    CC_STACK* stk = NULL;
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    stk = (CC_STACK*)malloc(sizeof(CC_STACK));
    if (NULL == stk)
    {
        return -1;
    }

    memset(stk, 0, sizeof(*stk));

    stk->Count = 0;
    stk->Size = INITIAL_SIZE;
    stk->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    if (NULL == stk->Array)
    {
        free(stk);
        return -1;
    }

    *Stack = stk;

    return 0;
}

int StDestroy(CC_STACK **Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    CC_STACK* stk = *Stack;

    if (NULL == stk)
    {
        return -1;
    }

    free(stk->Array);
    free(stk);

    *Stack = NULL;

    return 0;
}

int StResizeUp(CC_STACK* Stack)
{
    CC_STACK* aux = NULL;
    aux = (CC_STACK*)malloc(sizeof(CC_STACK));
    if (NULL == aux)
    {
        return -1;
    }
    aux->Count = Stack->Count;
    aux->Size = Stack->Size * 2;
    aux->Array = (int*)malloc(sizeof(int) * aux->Size);
    if (NULL == aux->Array)
    {
        return -1;
    }

    int i;
    for (i = 0; i < Stack->Count; i++)
    {
        aux->Array[i] = Stack->Array[i];
    }
    free(Stack->Array);
    free(Stack);
    *Stack = *aux;
    return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    if (Stack->Count >= Stack->Size)
    {
        if (0 != StResizeUp(Stack))
        {
            return -1;
        }
    }

    Stack->Array[Stack->Count] = Value;
    Stack->Count++;
    
    return 0;
}

int StPop(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    if (0 <= Stack->Count)
    {
        return -1;
    }

    Stack->Count--;
    *Value = Stack->Array[Stack->Count];

    return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Stack)
    {
        return -1;
    }

    if (0 <= Stack->Count)
    {
        return -1;
    }

    *Value = Stack->Array[Stack->Count];

    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    if (0 < Stack->Count)
    {
        return -1;
    }

    if (0 == Stack->Count)
    {
        return 0;
    }

    return 1;
}

int StGetCount(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    if (0 < Stack->Count)
    {
        return -1;
    }

    return Stack->Count;
}

int StClear(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);

    if (NULL == Stack)
    {
        return -1;
    }

    Stack->Count = 0;
    Stack->Size = INITIAL_SIZE;
    free(Stack->Array);
    Stack->Array = (int*)malloc(sizeof(int) * INITIAL_SIZE);
    if (NULL == Stack->Array)
    {
        free(Stack);
        return -1;
    }

    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(StackToPush);
    return -1;
}
