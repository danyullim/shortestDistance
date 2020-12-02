#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Queue.h"

using namespace std;

class Qitem
{
   public :
   int r,c;
   Qitem(int x,int y):r(x),c(y)
   {
      
   }
};

void find(int *arr[],int m,int n)
{
   int visit[m][n];
   queue <Qitem> q;
   // insert all the source node which is denoted as 0 into queue as row and pair column
   // for which i have bulit class called Qitem
   for(int i=0;i<m;i++)
   {
       for(int j=0;j<n;j++)
       {
           if(arr[i][j]==0)
           {
               Qitem s(i,j);
               q.enqueue( s);
           }
       }
   }
  
   // run while queue is not empty
   while(!q.is_empty())
   {
       Qitem s=q.front();
       q.dequeue();
       int r=s.r;
       int c=s.c;
  
           // up direction
           // we go in any direction if two condition is satisfied
           //1. it is valid row and column
           //2. when we move to next open space then distance should we minimum as prevoously calculated
           if(r-1>=0&&arr[r-1][c]>1+arr[r][c])
           {
               q.enqueue(Qitem(r-1,c));
               arr[r-1][c]=1+arr[r][c];
           }
          
           // down direction
           if(r+1<m&&arr[r+1][c]>1+arr[r][c])
           {
               q.enqueue(Qitem(r+1,c));
               arr[r+1][c]=1+arr[r][c];
           }
          
           // left direction
           if(c-1>=0&&arr[r][c-1]>1+arr[r][c])
           {
               q.enqueue(Qitem(r,c-1));
               arr[r][c-1]=1+arr[r][c];
       }
      
       // for right direction
           if(c+1<n&&arr[r][c+1]>1+arr[r][c])
           {
               q.enqueue(Qitem(r,c+1));
               arr[r][c+1]=1+arr[r][c];
           }
   }
      
  
}
void findShortestDistance(char *input[], int *output[], int num_of_rows, int num_of_cols)

{
   int sum=num_of_rows+num_of_cols;
for(int i=0;i<num_of_rows;i++)
       {
          for(int j=0;j<num_of_cols;j++)
          {
              // if it is open space then assign with maximum distance which is equal to
          // sum of row and column
          // if it is 'P' then assign it as 0
          // else when it is 'W' assign it as -1 which is considered to be invalid
              if(input[i][j]=='O')   
              output[i][j]=sum;
          else if(input[i][j]=='P')
          output[i][j]=0;
          else
          output[i][j]=-1;
           }
         
       }   
       find(output,num_of_rows,num_of_cols);
}