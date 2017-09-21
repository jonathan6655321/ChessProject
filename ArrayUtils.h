//
// Created by Jonathan on 9/21/2017.
//

#ifndef CHESSPROJECT_ARRAYUTILS_H
#define CHESSPROJECT_ARRAYUTILS_H


/*
 * does the OR operation on two arrays,
 * 1 = any element that is not 0
 * 0 = zeros only
 *
 * changes arr1 in place
 */
void arrayOr(int *arr1, int *arr2, int size);


/*
 * if all elements are 0 returns SUCCESS, else FAIL
 */
int isZeroArray(int *arr, int size);


#endif //CHESSPROJECT_ARRAYUTILS_H
