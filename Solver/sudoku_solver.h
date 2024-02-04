#ifndef sudoku_solver_h
#define sudoku_solver_h

void initialise_grid(const char* str);
void print(void);
int is_column_solved(int column);
int is_row_solved(int row);
int is_square_solved(int x, int y);
int *square2array(int x, int y);
int already_in_column(int col,int val);
int already_in_row(int row, int val);
int already_in_square(int x,int y,int val);
void solve(void);
int solve_rec(int x, int y);
void SetNextCoords(int *nextX, int *nextY);
const char * grid_to_string(void);
int str_is_equal(const char *a, const char *b);


#endif /* sudoku_solver_h */
