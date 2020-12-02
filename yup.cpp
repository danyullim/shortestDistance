#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Queue.h"

using namespace std;

// structure to represent position in 2D matrix
struct Position {
    int x; // row number
    int y; // column number
};

// function to update a position in output matrix for given position with shortest distance
void updateMatrix(int* output[], Position next, Position cur) {
    // update next's position in output matrix
    if (output[next.x][next.y] > (output[cur.x][cur.y] + 1)) { // add 1 for next distance
        output[next.x][next.y] = (output[cur.x][cur.y] + 1);
    }
}

// function to find shortest distance for each place in matrix for a patrolman
void findShortesdDistPatrolman(int* output[], int num_of_rows, int num_of_cols, Position p) {
    // find shortest path from patrolman's position to each place with BFS
    // create a queue to explore place in matrix for BFS algorithm
    queue<Position> q;
    // start exploring from patrolman's position
    // add patrolman's position to queue
    q.enqueue(p);
    // create a matrix to indicate explored positions
    bool** explored = new bool* [num_of_rows];
    for (int i = 0; i < num_of_rows; i++) {
        explored[i] = new bool[num_of_cols];
    }
    // initialize matrix with false as nno position is explored at start
    for (int i = 0; i < num_of_rows; i++) {
        for (int j = 0; j < num_of_cols; j++) {
            explored[i][j] = false;
        }
    }
    // look each position in queue
    while (!q.is_empty()) {
        // get current position for patrolman
        Position cur = q.front();
        // explore the current position if it is not already explored
        if (!explored[cur.x][cur.y] && output[cur.x][cur.y] != -1) { // patrolman cannot pass through the wall (-1 for wall)
            // add adjacent places to queue where patrolman can move
            // patrolman can move up, down, left and right
            // add up position if its not already explored
            if (cur.x > 0) {
                if (!explored[cur.x - 1][cur.y]) {
                    Position next = cur;
                    next.x -= 1;
                    q.enqueue(next);
                    // update next's position in output matrix
                    updateMatrix(output, next, cur);
                }
            }
            // add down position if its not already explored
            if (cur.x < (num_of_rows - 1)) {
                if (!explored[cur.x + 1][cur.y]) {
                    Position next = cur;
                    next.x += 1;
                    q.enqueue(next);
                    // update next's position in output matrix
                    updateMatrix(output, next, cur);
                }
            }
            // add left position if its not already explored
            if (cur.y > 0) {
                if (!explored[cur.x][cur.y - 1]) {
                    Position next = cur;
                    next.y -= 1;
                    q.enqueue(next);
                    // update next's position in output matrix
                    updateMatrix(output, next, cur);
                }
            }
            // add right position if its not already explored
            if (cur.y < (num_of_cols - 1)) {
                if (!explored[cur.x][cur.y + 1]) {
                    Position next = cur;
                    next.y += 1;
                    q.enqueue(next);
                    // update next's position in output matrix
                    updateMatrix(output, next, cur);
                }
            }
        }
        // remove current position from queue as it is explored
        q.dequeue();
        explored[cur.x][cur.y] = true;
    }
}


void findShortestDistance(char* input[], int* output[], int num_of_rows, int num_of_cols)
{
    // initialize output matrix with maximum possible distance for each open space
    // 0 for patrolman and -1 for wall;
    for (int i = 0; i < num_of_rows; i++) {
        for (int j = 0; j < num_of_cols; j++) {
            output[i][j] = INT_MAX;
            // if position is wall then output it as -1
            if (input[i][j] == 'W') {
                output[i][j] = -1;
            }
            if (input[i][j] == 'P') {
                output[i][j] = 0; // patrolman base location
            }
        }
    }
    // check input matrix for patrolman
    for (int i = 0; i < num_of_rows; i++) {
        for (int j = 0; j < num_of_cols; j++) {
            // calculate shortest distance for each open place in output matrix
            if (input[i][j] == 'P') {
                Position patrolman;
                patrolman.x = i;
                patrolman.y = j;
                findShortesdDistPatrolman(output, num_of_rows, num_of_cols, patrolman);
            }
        }
    }
}

