#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdbool.h>

#include "sudoku_solver.h"

#define GRID_SIZE 9
int grid[GRID_SIZE][GRID_SIZE];
int numberofcalls;
//The sudoku grid
/*
 * Function: initialise_array
 * ----------------------------
 *   Takes in the string representing the grid and initialises a 2D-array representing the grid
 *
 *    arg: string representing the grid
 *    .....
 *
 *   returns: Void
 */
void initialise_grid(const char* str)
{
    int row = 0, column = 0;
    // initialising every cell to 0
    for(int i = 0; i<GRID_SIZE ; i++)
    {
        for(int j = 0; j<GRID_SIZE ; j++)
        {
            grid[i][j] = 0;
        }
    }
    
    for(int i = 0; i < 110; i++)
    {
        if(str[i] != '.' && str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
        {
            grid[row][column] = (int)str[i] - 48;
        }
        if(str[i] != ' ' && str[i] != '\n')
            column = (column + 1) % 9;
        if(column == 0 && str[i] == '\n' && str[i - 1] != '\n')
            row = (row + 1) % 9;
    }
}

/*
 * Function: print
 * ----------------------------
 *      Print a 2D array in the grid format
 *
 *    arg: Void
 *
 *   returns: Void
 */
void print()
{
    for(int i = 0; i<GRID_SIZE ; i++)
    {
        for(int j = 0; j<GRID_SIZE; j++)
        {
            if(grid[i][j] == 0)
                printf(".");
            else
                printf("%d",grid[i][j]);
            if(j == 2|| j == 5)
                printf(" ");
        }
        if(i == 2 || i == 5)
            printf("\n");
        printf("\n");
    }
}


/*
 * Function: is_column_solved
 * ----------------------------
 *     Returns true if the given column is solved. False otherwise
 *
 *    arg: index of the column
 *
 *   returns: 1 if true, 0 otherwise
 */
int is_column_solved(int column)
{
    if(column >= GRID_SIZE || column < 0)
        errx(1,"ERROR-is_column_solved: index out of bounds");
    for(int i = 0; i < 9; i++)
    {
        int to_check = grid[i][column];
        for(int j = 0; j < 9; j++)
        {
            if (to_check == grid[j][column] && j != i)
                return false;
        }
    }
    return true;
}


/*
 * Function: is_row_solved
 * ----------------------------
 *     Returns true if the given row is solved. False otherwise
 *
 *    arg: index of the row
 *
 *   returns: 1 if true, 0 otherwise
 */
int is_row_solved(int row)
{
    if(row >= GRID_SIZE || row < 0)
        errx(1,"ERROR-is_column_solved: index out of bounds");
    for(int i = 0; i < 9 ; i++)
    {
        int to_check = grid[row][i];
        for(int j= 0; j < 9; j++)
        {
            if(to_check == grid[row][j] && j != i)
                return false;
        }
    }
    return true;
}


/*
 * Function: is_square_solved
 * ----------------------------
 *   Checks if the sqaure at position (x,y) is solved
 *
 *    arg1: x coordinate
 *    arg2: y coordinate
 *    .....
 *
 *   returns: 1 if ture, 0 otherwise
 */
int is_square_solved(int x, int y)
{
    int *square= square2array(x,y);
    for(int i = 0; i<GRID_SIZE; i++)
    {
        for(int j = 0; j< GRID_SIZE; j++)
        {
            if(square[i] == square[j] && i != j)
                return false;
        }
    }
    return true;
}

/*
 * Function: square2array
 * ----------------------------
 *   Returns an array representing the square at position x, y
 *
 *    arg1: x coordinate
 *    arg2: y coordinate
 *    .....
 *
 *   returns: returns the array
 */
int* square2array(int x, int y)
{
    static int array[GRID_SIZE];
    int index = 0;
    for(int i =x; i <x + 3;i++)
    {
        for(int j = y; j< y + 3 ; j++)
        {
            array[index] = grid[j][i];
            index++;
        }
    }
    return array;
}

/*
 * Function: already_in_column
 * ----------------------------
 *  Checks if val is in column col
 *
 *    arg1: the column of interest
 *    arg2: the value we want to check
 *    .....
 *
 *   returns: 1 if present. 0 otherwise
 */
int already_in_column(int col,int val)
{
    for(int i = 0; i< GRID_SIZE; i++)
    {
        if(grid[i][col] == val)
            return true;
    }
    
    return false;
}


/*
 * Function: already_in_row
 * ----------------------------
 *  Checks if val is in row row
 *
 *    arg1: the row of interest
 *    arg2: the value we want to check
 *    .....
 *
 *   returns: 1 if present. 0 otherwise
 */
int already_in_row(int row, int val)
{
    for(int i = 0;i < GRID_SIZE; i++)
    {
        if(grid[row][i] == val)
            return true;
    }
    return false;
}


/*
 * Function: already_in_square
 * ----------------------------
 *  Checks if val is in the square with top left corner at position (x,y)
 *
 *    arg1: the x coordinate
 *    arg2: the y coordinate
 *    arg3: teh value of interest
 *    .....
 *
 *   returns: 1 if present. 0 otherwise
 */
int already_in_square(int x,int y,int val)
{
    x /= 3;
    y /= 3;
    
    for(int Y = 0; Y < 3; Y++)
    {
        for(int X= 0; X < 3; X++)
        {
            if(grid[Y + y * 3][X + x * 3] == val)
                return true;
        }
    }
    
    return false;
}

void SetNextCoords(int *nextX, int *nextY)
{
    if (*nextX >= 9)
    {
        *nextX = 0;
        *nextY = *nextY + 1;
    }
}

int solve_rec(int x, int y)
{
    numberofcalls++;
    if (y >=9)
        return true;
    int a = 0, b = 0;
    int *nextX = &a;
    *nextX = x + 1;
    int *nextY = &b;
    *nextY = y;
    
    SetNextCoords(nextX,nextY);
    
    if(grid[y][x] != 0)
        return solve_rec(*nextX, *nextY);
    
    for(int i = 1; i <= 9; i++)
    {
        if(already_in_column(x, i) != true && already_in_row(y , i) != true && already_in_square(x, y, i) != true)
        {
            grid[y][x] = i;
            if(solve_rec(*nextX, *nextY))
                return true;
            grid[y][x] = 0;
        }
    }
    
    return false;
    
}

const char * grid_to_string(void)
{
    static char res[110] ="";
    int k = 0;
    for(int i = 0; i < GRID_SIZE; i++)
    {
        for(int j = 0; j < GRID_SIZE; j++)
        {
            res[k] = grid[i][j] + '0';
            if ( j == 2 || j == 5)
            {
                res[k + 1] = ' ';
                k+=2;
            }
            else
                k++;
        }
        res[k] = '\n';
        if( i == 2 || i == 5)
        {
            res[k + 1] = '\n';
            k += 2;
        }
        else
            k++;
    }
    return res;
}

int str_is_equal(const char *a, const char *b)
{
    unsigned long len = strlen(a);
    if(len != strlen(b))
        return false;
    for(unsigned long i = 0; i <len; i++)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}
void solve()
{
    solve_rec(0,0);
}
