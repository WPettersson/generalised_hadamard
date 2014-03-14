#ifndef MATRIX_H
#define MATRIX_H


class Matrix
{
  public:
    Matrix(int n, int *first_row);
    ~Matrix();
    bool addRow(int *row);
    void deleteLastRow();
    void print();
    bool isDone();
  private:
    int n;
    int num_rows;
    int *sum;
    int **rows;
};


#endif /* MATRIX_H */
