// Sudokuapplikaatio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

// UNASSIGNED is used for empty cells in sudoku grid
#define UNASSIGNED 0

// N is used for size of Sudoku grid. Size will be NxN
#define N 9

int NumOfCalls = 0;
// This function finds an entry in grid that is still unassigned
bool FindUnassignedLocation(int grid[N][N], int &row, int &col);

// Checks whether it will be legal to assign num to the given row,col
bool isSafe(int grid[N][N], int row, int col, int num);
/* Takes a partially filled-in grid and attempts to assign values to
all unassigned locations in such a way to meet the requirements
for Sudoku solution (non-duplication across rows, columns, and boxes) */
bool SolveSudoku(int grid[N][N])
{
	int row, col;

	// If there is no unassigned location, we are done
	if (!FindUnassignedLocation(grid, row, col))
		return true; // success!

					 // consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{
		// if looks promising
		if (isSafe(grid, row, col, num))
		{
			// make tentative assignment
			grid[row][col] = num;

			// return, if success, yay!
			NumOfCalls++;
			if (SolveSudoku(grid))
				return true;

			// failure, unmake & try again
			grid[row][col] = UNASSIGNED;
		}
	}
	return false; // this triggers backtracking
}

/* Searches the grid to find an entry that is still unassigned. If
found, the reference parameters row, col will be set the location
that is unassigned, and true is returned. If no unassigned entries
remain, false is returned. */
bool FindUnassignedLocation(int grid[N][N], int &row, int &col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
in the specified row matches the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (grid[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
in the specified column matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (grid[row][col] == num)
			return true;
	return false;
}

/* Returns a boolean which indicates whether any assigned entry
within the specified 3x3 box matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + boxStartRow][col + boxStartCol] == num)
				return true;
	return false;
}

/* Returns a boolean which indicates whether it will be legal to assign
num to the given row,col location. */
bool isSafe(int grid[N][N], int row, int col, int num)
{
	/* Check if 'num' is not already placed in current row,
	current column and current 3x3 box */
	return !UsedInRow(grid, row, num) &&
		!UsedInCol(grid, col, num) &&
		!UsedInBox(grid, row - row % 3, col - col % 3, num);
}

/* A utility function to print grid  */
void printGrid(int grid[N][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
			printf("%2d", grid[row][col]);
		printf("\n");
	}
}

void kaanna(string &mj)
{
/*	printf("pituus: %d", mj.length());
	printf("\n");*/
	unsigned int loppu=mj.length()-1;
	unsigned int pituus;
	char tmp;
	if ((loppu % 2) == 1) pituus = (loppu / 2) + 1; else pituus = loppu / 2;
/*	for (unsigned int i = 0;i < pituus;i++)
	{
		cout << "merkki: " << mj[i] << '\n';
	}
	for (unsigned int i = 0;i < pituus;i++)
	{
		cout << "merkki lopusta: " << mj[loppu - i] << '\n';
	}*/
	for (unsigned int i = 0;i < pituus;i++)
	{
		tmp = mj[i];
		mj[i] = mj[loppu - i];
		mj[loppu - i] = tmp;
	}
}

int main()
{
	// 0 means unassigned cells
	int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
	{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
	{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
	{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
	{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
	{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
	{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
	NumOfCalls++;
	if (SolveSudoku(grid) == true)
		printGrid(grid);
	else
		printf("No solution exists");
	//printf("kutsuja: %d \n", NumOfCalls);
	string mj;
/*	kaanna(mj);
	cout << mj << '\n';
	mj = "abradakabra";
	kaanna(mj);
	mj = "saippuakauppias";
	kaanna(mj);
	cout << mj << '\n';*/
	ifstream v("d:\\sudoku\\syote.txt");
	if (!v.fail())
	{
		while (getline(v, mj))
		{
			cout << mj << '\n';
			kaanna(mj);
			cout << mj << '\n';
		}
	}
	return 0;
}

