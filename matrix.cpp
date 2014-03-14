#include "matrix.h"
#include "dot.h"

#include <iostream>
#include <iomanip>

const int WIDTH=3;

Matrix::Matrix(int n, int *first_row) : n(n),num_rows(1)
{
  rows = new int*[n];
  rows[0] = first_row;
  sum = new int[n];
  for(int i=0; i<n; i++)
    sum[i] = first_row[i];
}

Matrix::~Matrix()
{
  delete[] rows;
  delete[] sum;
}

bool Matrix::addRow(int *row)
{
  if (num_rows == 1)
  {
    // Check partial-canonical second row.
    // Within each section of "1"s (or 2s or 3s) in the first row,
    // make sure that the second row goes -3,-2,-1,1,2,3
    int i=2;
    for(int j=1;j<=3;j++)
    {
      while (rows[0][i] == 1 && (i<n))
      {
        if (row[i] < row[i-1])
        {
          return false;
        }
        i++;
      }
      i++;
    }
//    i++; // Should be on row[i] = 2 now, so move one more to check 2s
//    while (rows[0][i] == 2 && (i<n))
//    {
//      if (row[i] < row[i-1])
//      {
//        return false;
//      }
//      i++;
//    }
//    i++; // Should be on row[i] = 3 now, so move one more to check 3s
//    while (rows[0][i] == 3 && (i<n))
//    {
//      if (row[i] < row[i-1])
//      {
//        return false;
//      }
//      i++;
//    }
  }


  if (dot(n,row,sum) != 0)
  {
  //  print();
  //  std::cout << "Failed sum test" << std::endl;;
  //  for(int i=0; i<n; i++)
  //  {
  //    std::cout << std::setw(WIDTH) << sum[i];
  //  }
  //  std::cout << std::endl;
  //  for(int i=0; i<n; i++)
  //  {
  //    std::cout << std::setw(WIDTH) << row[i];
  //  }
  //  std::cout << std::endl;
    return false;
  }
  for(int i=0; i < num_rows; i++)
  {
    if (dot(n,row,rows[i]) != 0)
    {
      return false;
    }
  }
  rows[num_rows++] = row;
  for(int i=0; i < n; i++)
  {
    sum[i] += row[i];
  }
  return true;
}

void Matrix::deleteLastRow()
{
  num_rows--;
  for(int i=0; i < n; i++)
  {
    sum[i]-=rows[num_rows][i];
  }
}

void Matrix::print()
{
  for(int r=0; r < num_rows; r++)
  {
    for(int i=0; i < n; i++)
    {
      std::cout << std::setw(WIDTH) << rows[r][i];
    }
    std::cout << std::endl;
  }
}

bool Matrix::isDone()
{
  if (num_rows == n)
    return true;
  return false;
}
