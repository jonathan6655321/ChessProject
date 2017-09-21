//
// Created by Jonathan on 9/21/2017.
//

#include "ArrayUtils.h"
#include "constants.h"

/*
 * does the OR operation on two arrays,
 * 1 = any element that is not 0
 * 0 = zeros only
 *
 * changes arr1 in place
 */
void arrayOr(int *arr1, int *arr2, int size)
{
   for(int i=0; i<size; i++)
   {
       if(arr1[i] != 0 || arr2[i] != 0)
           arr1[i] = 1;
   }
}

/*
 * if all elements are 0 returns SUCCESS, else FAIL
 */
int isZeroArray(int *arr, int size)
{
    for(int i=0; i<size; i++)
    {
        if(arr[i] != 0)
            return FAIL;
    }
    return SUCCESS;
}