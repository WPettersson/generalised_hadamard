#include "matrix.h"
#include "dot.h"

#include <algorithm> // std::copy
#include <iostream>
#include <ios>
#include <fstream>
#include <iomanip>  // std::setw
#include <cstdlib> // atoi(), exit()
#include <ctime> // clock()
#include <cstring> // strcmp()
#include <list>

int orbit_count;

const int WIDTH = 3;

int n;
int count;
bool do_all;
bool print_orthogonal;
time_t last_progress;
const time_t progress_interval = 3*CLOCKS_PER_SEC; // Only print progress every "progress_interval"


bool canonical(int row[])
{
  int s = 1;
  for(int i=0; i<n; i++)
  {
    if (row[i] < s)
      return false;
    if (row[i] > s)
      s = row[i];
  }
  return true;
}

bool ok_second_row(int *first, int *second)
{
  int i=2;
  for(int j=1;j<=3;j++)
  {
    while (first[i] == j && (i<n))
    {
      if (second[i] < second[i-1])
        return false;
      i++;
    }
    i++;
  }
  return true;
}

bool next(int row[], int i)
{
  if (i == n)
    return false;
  row[i] *= -1;
  if (row[i] > 0)
  {
    row[i] += 1;
    if (row[i] == 4)
    {
      row[i] = 1;
      if (!next(row,i+1))
        return false;
    }
  }
  return true;
}

void recurse(Matrix* m,int pos,int **rows,int row_count) {
  if (!do_all && count > 0)
    return;
  if (m->isDone())
  {
    std::cout << "----------------------" << std::endl;
    m->print();
    std::cout << "----------------------" << std::endl;
    count+=1;
    return;
  }
  while (pos < row_count)
  {
    if (m->addRow(rows[pos]))
    {
      recurse(m,pos+1,rows,row_count);
      m->deleteLastRow();
    }
    pos++;
  }
}

int main(int argc, char **argv)
{
  int arg_counter = 2;
  if (argc < 2)
  {
    std::cout << "Usage: hadamard n [-o] [-a]" << std::endl;
    return 0;
  }
  n = atoi(argv[1]);
  count = 0;
  do_all = false;
  print_orthogonal = false;
  int num_first_row = -1;
  while ((arg_counter < argc) && (argv[arg_counter][0] == '-'))
  {
    if ( strcmp("-a", argv[arg_counter])==0)
    {
      do_all = true;
    }
    if ( strcmp("-o", argv[arg_counter])==0)
    {
      print_orthogonal = true;
    }
    if ( strcmp("-k", argv[arg_counter])==0)
    {
      arg_counter++;
      num_first_row = atoi(argv[arg_counter]);
    }
    arg_counter++;
  }


//  int r1[] = {1,1,1,1};
//  int r2[] = {1,-1,-1,1};
//  int r3[] = {-1,1,-1,1};
//  int r4[] = {1,1,-1,-1};
//  Matrix m(n,r1);
//  if (m.addRow(r2))
//  {
//    if (m.addRow(r3))
//    {
//      if (m.addRow(r4))
//        m.print();
//    }
//  }
//  return 0;

  int first_row[n];
  for(int i=0; i < n; i++)
    first_row[i] = 1;
  int row_num = 0;
  do
  {
    if (!canonical(first_row))
      continue;

    if (row_num >= 0 && row_num++ < num_first_row)
      continue;

    std::list<int *> orth_rows;
    int orth_count=0;
    int *next_row = new int[n];
    for(int i=0; i < n; i++)
      next_row[i] = 1;
    do
    {
      if (next_row[0] < 0)
        continue;

      // Check to see that first_row is always the most
      // canonical row.
      bool less = true;
      for(int i=0; i<n; i++)
      {
        if ((next_row[i] > first_row[i]) || (next_row[i] < 0))
        {
          less = false;
          break;
        }
      }
      if (less)
        continue;

      if (dot(n,first_row,next_row)==0)
      {
        int *new_row = new int[n];
        for( int i=0; i < n; i++)
          new_row[i] = next_row[i];
        orth_rows.push_back(new_row);
        orth_count+=1;
      }
    } while (next(next_row,0));
    delete[] next_row;
    //std::cout << "---------------------" << std::endl;
    //for(int i=0; i<n;i++)
    //  std::cout << std::setw(WIDTH) << first_row[i];
    //std::cout << std::endl;
    //std::cout << "---------------------" << std::endl;
    //for(int r=0; r< orth_count; r++)
    //{
    //  for(int i=0; i<n;i++)
    //    std::cout << std::setw(WIDTH) << rows[r][i];
    //  std::cout << std::endl;
    //}
    if (print_orthogonal)
    {
      int *r;
      std::cout << "First row" << std::endl;
      for(int i=0;i<n;i++)
        std::cout << std::setw(WIDTH) << first_row[i];
      std::cout << std::endl;
      std::cout << orth_count << " orthogonal rows"
                  " to check" << std::endl;
      for(std::list<int*>::iterator it=orth_rows.begin(); 
            it!=orth_rows.end(); it++)
      {
        r = *it;
        for(int i=0;i<n;i++)
          std::cout << std::setw(WIDTH) << r[i];
        if (ok_second_row(first_row,r))
          std::cout << "*";
        std::cout << std::endl;
      }
      break;
    }
    else
    {
      int **rows;
      rows = new int*[orth_count];
      int i=0;
      for(std::list<int*>::iterator it=orth_rows.begin(); 
            it!=orth_rows.end(); it++)
        rows[i++] = *it;
      orth_rows.clear();
      Matrix m(n,first_row);
      recurse(&m,0,rows,orth_count);
      for(int i=0; i< orth_count; i++)
        delete[] rows[i];
      delete[] rows;
    }
    if(!do_all && count > 0)
      break;
  } while (next(first_row,0));
  return count; // Did not find decomp.
}
