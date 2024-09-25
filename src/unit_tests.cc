#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// Для дефолтного конструктора

TEST(MatrixTest, DefaultConstructorInitializesMatrix) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
  EXPECT_EQ(matrix.GetMatrixPointer(), nullptr);
}

TEST(MatrixTest, MatrixInitialization) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
  EXPECT_EQ(matrix.GetMatrixPointer(), nullptr);
}

TEST(MatrixTest, MemoryAllocation) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetMatrixPointer(), nullptr);
}

// Для матрицы заданных размеров

TEST(S21MatrixTest, ConstructorWithValidDimensions) {
  int rows = 3;
  int cols = 4;
  S21Matrix matrix(rows, cols);

  EXPECT_EQ(matrix.GetRows(), rows);
  EXPECT_EQ(matrix.GetCols(), cols);

  EXPECT_NE(matrix.GetMatrixPointer(), nullptr);
}

TEST(S21MatrixTest, ConstructorWithNegativeRows) {
  EXPECT_THROW(S21Matrix matrix(-1, 3), std::invalid_argument);
}

TEST(S21MatrixTest, ConstructorWithNegativeCols) {
  EXPECT_THROW(S21Matrix matrix(3, -1), std::invalid_argument);
}

TEST(S21MatrixTest, ConstructorWithNegativeRowsAndCols) {
  EXPECT_THROW(S21Matrix matrix(-1, -1), std::invalid_argument);
}

TEST(S21MatrixTest, MemoryAllocationWithValidDimensions) {
  int rows = 2;
  int cols = 2;
  S21Matrix matrix(rows, cols);

  EXPECT_NE(matrix.GetMatrixPointer(), nullptr);
}

// Для копирования матрицы с данными

TEST(S21MatrixTest, CopyConstructorWithData) {
  int rows = 3;
  int cols = 4;

  S21Matrix matrix(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix.SetElement(i, j, i + j);
    }
  }

  S21Matrix copy(matrix);

  EXPECT_EQ(copy.GetRows(), matrix.GetRows());
  EXPECT_EQ(copy.GetCols(), matrix.GetCols());
}

// Для перемещения матрицы с данными

TEST(S21MatrixTest, MoveConstructorWithData) {
  int rows = 3;
  int cols = 4;
  S21Matrix matrix(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix.SetElement(i, j, i + j);
    }
  }

  S21Matrix moved(std::move(matrix));

  EXPECT_EQ(moved.GetRows(), rows);
  EXPECT_EQ(moved.GetCols(), cols);
}

// Для оператора присваивания и перемещения
TEST(S21MatrixTest, MoveAssignmentOperatorWithData) {
  int rows = 3;
  int cols = 4;
  S21Matrix matrix(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix.SetElement(i, j, i + j);
    }
  }

  S21Matrix new_matrix;
  new_matrix = std::move(matrix);

  EXPECT_EQ(new_matrix.GetRows(), rows);
  EXPECT_EQ(new_matrix.GetCols(), cols);
}

// Для функции сравнения

TEST(S21MatrixTest, EqMatrix_true) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      matrix1.SetElement(i, j, 1.0 * (i + j));
      matrix2.SetElement(i, j, 1.0 * (i + j));
    }
  }

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

// Для функции сложения

TEST(S21Matrix, SumMatrixes_EqualSizes) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1.SetElement(0, 0, 1.0);
  matrix1.SetElement(0, 1, 2.0);
  matrix1.SetElement(1, 0, 3.0);
  matrix1.SetElement(1, 1, 4.0);

  matrix2.SetElement(0, 0, 5.0);
  matrix2.SetElement(0, 1, 6.0);
  matrix2.SetElement(1, 0, 7.0);
  matrix2.SetElement(1, 1, 8.0);

  matrix1.SumMatrix(matrix2);

  EXPECT_EQ(matrix1.GetElement(0, 0), 6.0);
  EXPECT_EQ(matrix1.GetElement(0, 1), 8.0);
  EXPECT_EQ(matrix1.GetElement(1, 0), 10.0);
  EXPECT_EQ(matrix1.GetElement(1, 1), 12.0);
}

TEST(S21MatrixTest, SumMatrix_DifferentSizedMatrices_ThrowsException) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

// Для функции вычитания

TEST(S21Matrix, SubMatrix_EqualSizes) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1.SetElement(0, 0, 5.0);
  matrix1.SetElement(0, 1, 6.0);
  matrix1.SetElement(1, 0, 7.0);
  matrix1.SetElement(1, 1, 8.0);

  matrix2.SetElement(0, 0, 1.0);
  matrix2.SetElement(0, 1, 2.0);
  matrix2.SetElement(1, 0, 3.0);
  matrix2.SetElement(1, 1, 4.0);

  matrix1.SubMatrix(matrix2);

  EXPECT_EQ(matrix1.GetElement(0, 0), 4.0);
  EXPECT_EQ(matrix1.GetElement(0, 1), 4.0);
  EXPECT_EQ(matrix1.GetElement(1, 0), 4.0);
  EXPECT_EQ(matrix1.GetElement(1, 1), 4.0);
}

TEST(S21Matrix, SubMatrix_EmptyMatrices) {
  S21Matrix matrix1(0, 0);
  S21Matrix matrix2(0, 0);

  EXPECT_NO_THROW(matrix1.SubMatrix(matrix2));
}

TEST(S21Matrix, SubMatrix_DifferentSizes_ThrowsException) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);

  matrix1.SetElement(0, 0, 5.0);
  matrix1.SetElement(0, 1, 6.0);
  matrix1.SetElement(1, 0, 7.0);
  matrix1.SetElement(1, 1, 8.0);

  matrix2.SetElement(0, 0, 1.0);
  matrix2.SetElement(0, 1, 2.0);
  matrix2.SetElement(0, 2, 3.0);
  matrix2.SetElement(1, 0, 4.0);
  matrix2.SetElement(1, 1, 5.0);
  matrix2.SetElement(1, 2, 6.0);
  matrix2.SetElement(2, 0, 7.0);
  matrix2.SetElement(2, 1, 8.0);
  matrix2.SetElement(2, 2, 9.0);

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

// Для функции умножения матрицы на число

TEST(S21MatrixTest, MultNumberPositive) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  matrix.MulNumber(2.0);

  EXPECT_DOUBLE_EQ(matrix(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(matrix(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix(1, 1), 8.0);
}

// Для функции умножения матрицы на матрицу

TEST(S21MatrixTest, MulMatrix_ValidMultiplication) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;

  matrix2(0, 0) = 7.0;
  matrix2(0, 1) = 8.0;
  matrix2(1, 0) = 9.0;
  matrix2(1, 1) = 10.0;
  matrix2(2, 0) = 11.0;
  matrix2(2, 1) = 12.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 58.0;
  expected_result(0, 1) = 64.0;
  expected_result(1, 0) = 139.0;
  expected_result(1, 1) = 154.0;

  matrix1.MulMatrix(matrix2);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), expected_result(i, j));
    }
  }
}

TEST(S21MatrixTest, MulMatrix_IncompatibleDimensions) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(4, 2);

  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

// Для функции транспортировании матрицы
TEST(S21MatrixTest, Transpose_SquareMatrix) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 1.0;
  expected_result(0, 1) = 3.0;
  expected_result(1, 0) = 2.0;
  expected_result(1, 1) = 4.0;

  S21Matrix result = matrix.Transpose();

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

// Для функции минора матрицы

TEST(S21MatrixTest, Minor_2x2Matrix) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix expected_result(1, 1);
  expected_result(0, 0) = 4.0;  // Minor of element (0,0)

  S21Matrix result = matrix.Minor(0, 0);

  for (int i = 0; i < 1; ++i) {
    for (int j = 0; j < 1; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

TEST(S21MatrixTest, Minor_3x3Matrix) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 5.0;
  expected_result(0, 1) = 6.0;
  expected_result(1, 0) = 8.0;
  expected_result(1, 1) = 9.0;

  S21Matrix result = matrix.Minor(0, 0);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

// Для функции Детермината

TEST(S21MatrixTest, Determinant_1x1Matrix) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  double expected_result = 5.0;

  double result = matrix.Determinant();
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(S21MatrixTest, Determinant_2x2Matrix) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double expected_result = (1.0 * 4.0) - (2.0 * 3.0);  // 4 - 6 = -2

  double result = matrix.Determinant();
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(S21MatrixTest, Determinant_3x3Matrix) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  double expected_result = 0.0;

  double result = matrix.Determinant();
  EXPECT_DOUBLE_EQ(result, expected_result);
}

TEST(S21MatrixTest, Determinant_NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.Determinant(), std::invalid_argument);
}

// Для функции математических дополнений

TEST(S21MatrixTest, CalcComplements_2x2Matrix) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 4.0;
  expected_result(0, 1) = -3.0;
  expected_result(1, 0) = -2.0;
  expected_result(1, 1) = 1.0;

  S21Matrix result = matrix.CalcComplements();

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

TEST(S21MatrixTest, CalcComplements_NonSquareMatrix) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.CalcComplements(), std::invalid_argument);
}

// Для функции инверсии матрицы

TEST(S21MatrixTest, InverseMatrix_2x2Matrix) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = -2.0;
  expected_result(0, 1) = 1.0;
  expected_result(1, 0) = 1.5;
  expected_result(1, 1) = -0.5;

  S21Matrix result = matrix.InverseMatrix();

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

TEST(S21MatrixTest, InverseMatrix_SingularMatrix) {
  S21Matrix matrix(3, 3);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

// Для операторов перегрузки

// Тест сложения матриц
TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 6.0;
  expected_result(0, 1) = 8.0;
  expected_result(1, 0) = 10.0;
  expected_result(1, 1) = 12.0;

  S21Matrix result = A + B;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

// Тест вычитания матриц
TEST(S21MatrixTest, OperatorMinus) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 5.0;
  A(0, 1) = 6.0;
  A(1, 0) = 7.0;
  A(1, 1) = 8.0;
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 4.0;
  expected_result(0, 1) = 4.0;
  expected_result(1, 0) = 4.0;
  expected_result(1, 1) = 4.0;

  S21Matrix result = A - B;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

// Тест умножения матриц
TEST(S21MatrixTest, OperatorMultiplyMatrix) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 19.0;
  expected_result(0, 1) = 22.0;
  expected_result(1, 0) = 43.0;
  expected_result(1, 1) = 50.0;

  S21Matrix result = A * B;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

// Тест умножения матрицы на скаляр
TEST(S21MatrixTest, OperatorMultiplyScalar) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 2.0;
  expected_result(0, 1) = 4.0;
  expected_result(1, 0) = 6.0;
  expected_result(1, 1) = 8.0;

  S21Matrix result = A * 2.0;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(result(i, j), expected_result(i, j));
    }
  }
}

// Тест оператора сложения и вычитания
TEST(S21MatrixTest, OperatorPlusEquals) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  A += B;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 6.0;
  expected_result(0, 1) = 8.0;
  expected_result(1, 0) = 10.0;
  expected_result(1, 1) = 12.0;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(A(i, j), expected_result(i, j));
    }
  }
}

TEST(S21MatrixTest, OperatorMinusEquals) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 5.0;
  A(0, 1) = 6.0;
  A(1, 0) = 7.0;
  A(1, 1) = 8.0;
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;

  A -= B;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 4.0;
  expected_result(0, 1) = 4.0;
  expected_result(1, 0) = 4.0;
  expected_result(1, 1) = 4.0;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(A(i, j), expected_result(i, j));
    }
  }
}

TEST(S21MatrixTest, OperatorMultiplyEquals) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  A *= B;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 19.0;
  expected_result(0, 1) = 22.0;
  expected_result(1, 0) = 43.0;
  expected_result(1, 1) = 50.0;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(A(i, j), expected_result(i, j));
    }
  }
}

TEST(S21MatrixTest, OperatorMultiplyEqualsScalar) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  A *= 2.0;

  S21Matrix expected_result(2, 2);
  expected_result(0, 0) = 2.0;
  expected_result(0, 1) = 4.0;
  expected_result(1, 0) = 6.0;
  expected_result(1, 1) = 8.0;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_DOUBLE_EQ(A(i, j), expected_result(i, j));
    }
  }
}

// Тест оператора доступа к элементу
TEST(S21MatrixTest, OperatorParentheses) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 4.0);
}

// Тест оператора == и !=
TEST(S21MatrixTest, OperatorEqual) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;

  EXPECT_TRUE(A == B);
  EXPECT_FALSE(A != B);

  B(0, 0) = 0.0;
  EXPECT_FALSE(A == B);
  EXPECT_TRUE(A != B);
}

TEST(S21MatrixTest, OperatorParentheses_ConstAccess) {
  S21Matrix matrix(2, 2);

  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  const S21Matrix& const_matrix = matrix;

  EXPECT_DOUBLE_EQ(const_matrix(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(const_matrix(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(const_matrix(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(const_matrix(1, 1), 4.0);
}

TEST(S21MatrixTest, OperatorParentheses_OutOfRange) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, -1), std::out_of_range);
  EXPECT_THROW(matrix(2, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 2), std::out_of_range);
}
TEST(S21MatrixTest, OperatorParentheses_OutOfRange2) {
  S21Matrix matrix(2, 2);

  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, -1), std::out_of_range);
  EXPECT_THROW(matrix(2, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 2), std::out_of_range);
}

TEST(S21MatrixTest, ThrowsOutOfRangeWhenAccessingInvalidIndex) {
  const S21Matrix matrix(3, 3);

  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(3, 0), std::out_of_range);

  EXPECT_THROW(matrix(0, -1), std::out_of_range);
  EXPECT_THROW(matrix(0, 3), std::out_of_range);

  EXPECT_THROW(matrix(-1, -1), std::out_of_range);
  EXPECT_THROW(matrix(3, 3), std::out_of_range);
}

TEST(S21MatrixTest, AccessValidIndex) {
  S21Matrix matrix(3, 3);
  matrix(1, 1) = 5.0;
  EXPECT_EQ(matrix(1, 1), 5.0);

  EXPECT_NO_THROW(matrix(0, 0));
  EXPECT_NO_THROW(matrix(2, 2));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
