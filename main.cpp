#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Queue.h"

using namespace std;

// use struct for 2-d matrix/array
struct twod_matrix 
{
	// declare rows
    int rows; 
	// declare columns
    int columns;
};

bool loadGraph(std::string file_name, char*** input, int& num_of_rows, int& num_of_cols)
{
	char ch;
	ifstream f(file_name);

	if (f.fail()) 
	{
		std::cout << "Couldn't open the file: " << file_name << std::endl;
		return false;
	}

	//Read file into input and update num_of_rows and num_of_cols
	// reading in the number of rows and columns
	// first rows, then columns
	f >> num_of_rows;
	f >> num_of_cols;

	// initializing input for parameter
	(*input) = new char*[num_of_rows];

	// use for loop to run through the rows
	for (int x = 0; x < num_of_rows ; x++) 
	{
		// initializing the input
		(*input)[x] = new char[num_of_cols];
		// use for loop for number of columns
		for(int i = 0; i < num_of_cols; i++) 
		{
			// reading the input rows and columns
			// with rows and columns
			f >> (*input)[x][i];
		}
	}
	// close file
	f.close();
	// update boolean value
	return true;

}

// update the position of matrix
// paramters are set as the output matrix,then 
void matrix_position(int* output[], twod_matrix after, twod_matrix now) 
{
	// condition to check output matrix after
	// check if the currently initialized matrix + 1 is less than the 
    if (1 + output[now.rows][now.columns] < output[after.rows][after.columns]) 
	{
		// reinitializing the position after
		// add one for the next position within the distance
		// update the matrix afterwards
        output[after.rows][after.columns] = 1 + output[now.rows][now.columns];
    }
}

// utilize breadth-first search in this function
// finding the shortest distance to the P
// keeping track of Os
// using struct variable as parameter
void patrolman_update(int* output[], int &num_of_rows, int &num_of_cols, twod_matrix patrol_man) 
{
	// initializing the queue of struct type 2-d matrix
    queue <twod_matrix> distance_queue;
	// start enqueuing the patrolman's position into matrix 
    distance_queue.enqueue(patrol_man);
    // initialize bool value to see if patrol man is crossed
	// running through the rows first 
    bool **found = new bool *[num_of_rows];
	// use for loop to run through the rows of the matrix
	// increment position
    for (int x = 0; x < num_of_rows; x++) 
	{
		// reinitialize
		// another matrix to keep track of the crossed positions of patrolman
		// boolean value of checking within the columns
        found[x] = new bool[num_of_cols];
    }

    // use for loop to set the matrix
	// setting matrix as no patrolman has been crossed
	// running through the number of rows
    for (int x = 0; x < num_of_rows; x++) 
	{
		// use nested for loop to also run through the columns
        for (int y = 0; y < num_of_cols; y++) 
		{
			// initialize the found matrix as the false
			// because none have been crossed yet
			// none have been fall
            found[x][y] = false;
        }
    }

    // while loop to only run if the queue is not empty
    while (distance_queue.is_empty() == false) 
	{
        // setting the current value from struct type
		// set the current variable to the front of the queue
        twod_matrix current_pos = distance_queue.front();

		// conditional to check if the current 
        // explore the nowrent matrix if it is not already explored
		// if not wall
        if (output[current_pos.rows][current_pos.columns] != -1 && found[current_pos.rows][current_pos.columns] == false) 
		{
			// allow the patrolman to move all 4 directions
			// conditional to check if the rows of the currentposition is greater than 0
			if (current_pos.rows > 0) 
			{
				// conditional to run if found matrix is false
				// the rows - 1 and the same columns
					// initialize the after value as the current position
                    twod_matrix after = current_pos;
					// reinitialize the rows after - 1 
                    after.rows = after.rows - 1;
					// enqueue to the distance queue of after value
                    distance_queue.enqueue(after);
                    // update after's matrix in the outputted matrix
					// call the matrix_position to reinitialize
                    matrix_position(output, after, current_pos);
            }

            // conditional to check if the number of rows
			// if it's still greater than the current position row, then execute 
            if (current_pos.rows < (num_of_rows - 1)) 
			{
				// conditional to check if the found matrix is not found
				// found matrix's rows increased by 1 and current columns
				twod_matrix after = current_pos;
				after.rows = after.rows + 1;
				// enqueue after value into the distance queue
				distance_queue.enqueue(after);
				// update after's matrix in outputted matrix
				// call the matrix_position to reinitialize the position matrix
				matrix_position(output, after, current_pos);
            }
            // conditional to check if the current position of columns is greater than 0
            if (current_pos.columns > 0) 
			{
					// set the after value to the current position
					twod_matrix after = current_pos;
					// reinitialize after columns by substracting 1
					after.columns = after.columns - 1;
					// enqueue after value into the distance queue
					distance_queue.enqueue(after);
					// update after's matrix in output matrix
					// call matrix_position function reinitialize the position matrix 
					matrix_position(output, after, current_pos);
			}

            // add right matrix if its not already explored
            if (current_pos.columns < (num_of_cols - 1)) 
			{	
					// set the matrix after postion to the current position
					twod_matrix after = current_pos;
					// reinitialize the after columns by adding 1 to the columns
					after.columns = after.columns + 1;
					// enqueue the after value into the distance queue
					distance_queue.enqueue(after);
					// update after's matrix in output matrix
					matrix_position(output, after, current_pos);
			}
        }
		// dequeue current matrix from the queue
		// as it is being run through
		// the Os
        distance_queue.dequeue();
		// reinitialize the found matrix to true after
		// running through the conditions to show that it is found 
        found[current_pos.rows][current_pos.columns] = true;
    }
}

void findShortestDistance(char* input[], int* output[], int num_of_rows, int num_of_cols)
{
	// use for loop to run through the number of rows first
    for (int x = 0; x < num_of_rows; x++) 
	{
		// while running inside the number of rows
		// use nested for loop to run through the number of columns
        for (int y = 0; y < num_of_cols; y++)
		{
			// set the output matrix to the max number of columns and rows added
            output[x][y] = num_of_rows + num_of_cols;
			
			// conditional to check if the character in the input matrix is a P
			if (input[x][y] == 'P') 
			{
				// if so, then the output should be 0
                output[x][y] = 0; 
            }
            // conditinoal to check if the character in the input matrix is a W
            if (input[x][y] == 'W') 
			{
				// if so, then the output should be -1
                output[x][y] = -1;
            }
        }
    }
    // check input matrix for patrolman
	// use for loop to run through the rows first
    for (int x = 0; x < num_of_rows; x++) 
	{
		// use nested for loop to run through the columns
        for (int y = 0; y < num_of_cols; y++) 
		{
			// if the input matrix has a character of P, execute the following
            if (input[x][y] == 'P') 
			{
				// initialize the partolman variable
                twod_matrix patrolman;
				// set the rows to the x
                patrolman.rows = x;
				// set the columns to the y
                patrolman.columns = y;
				// call patrolman_update function to find the shortest distance
                patrolman_update(output, num_of_rows, num_of_cols, patrolman);
            }
        }
    }
}
	
int main(int argc, char **argv)
{
	int num_of_rows, num_of_cols;
	string file_name = "input.txt";
	char** input_adj_matrix;

	loadGraph(file_name, &input_adj_matrix, num_of_rows, num_of_cols);

	std::cout << "The input adjacent matrix graph: " << std::endl;
	for (int i = 0; i < num_of_rows; i++) 
	{
		for (int j = 0; j < num_of_cols; j++) 
		{
			cout << std::setw(3) << input_adj_matrix[i][j];
		}
		cout << endl;
	}

	int** output_adj_matrix = new int* [num_of_rows];
	for (int i = 0; i < num_of_rows; i++) 
	{
		output_adj_matrix[i] = new int[num_of_cols];
	}

	findShortestDistance(input_adj_matrix, output_adj_matrix, num_of_rows, num_of_cols);

	std::cout << "\nThe shortest way from each patrolman: " << std::endl;
	for (int i = 0; i < num_of_rows; i++) 
	{
		for (int j = 0; j < num_of_cols; j++) 
		{
			cout << std::setw(3) << output_adj_matrix[i][j];
		}
		cout << endl;
	}

	return 0;
}