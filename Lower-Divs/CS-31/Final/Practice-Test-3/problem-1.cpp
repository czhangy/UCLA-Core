#include <iostream>
using namespace std;

//What is the problem with this function?





//Dynamically allocates a new integer and sets its value to 10.
//Changes set input ptr to point to that 10.
void ptr_function(int* ptr) 
{
	int *ptr2 = new int;
	*ptr2 = 10;
	ptr = ptr2;
}


/**************************************************************************/

void ptr_function2(int* ptr, int &a)
{
	int *ptr2 = &a;
	*ptr2 = 50;
	ptr = ptr2;
	a=1000;
}

//What is the output of the function below?





void call_ptr_function2()
{
	int *ptr = new int;
	*ptr = 10;
	int a = 25;
	ptr_function2(ptr, a);
	cout << "Pointer value is: " << *ptr << endl << "a's value is: " << a << endl;
}


/**************************************************************************/

//Why will this function cause a compile error?





void createBoard(char board[][], int rows, int cols)
{
	for (int i=0; i < rows; i++)
		for (int j=0; j < cols; j++)
		{
			if (i%2==0)
				if (j%2==0)
					board[i][j]='X';
				else
					board[i][j]='O';
			else
				if (j%2==0)
					board[i][j]='O';
				else
					board[i][j]='X';
		}
}

//What does this function output, assuming that the above function is corrected?





void printBoard()
{
	char board[10][10];
	createBoard(board, 10, 10);
	for (int i=0; i < 10; i++)
	{
		for (int j=0; j < 10; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}