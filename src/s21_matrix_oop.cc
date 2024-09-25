#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {
  // Дефолтный конструктор инициализирует матрицу нулевыми значениями
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 0 || cols < 0) {
    throw std::invalid_argument(
        "Строки и столбцы должны быть положительными числами");
  }
  AllocateMatrix(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(0), cols_(0), matrix_(nullptr) {
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    DeallocateMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

void S21Matrix::AllocateMatrix(int rows, int cols) {
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols]{0};  // Инициализация нулями
  }
  rows_ = rows;
  cols_ = cols;
}

void S21Matrix::DeallocateMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

S21Matrix::~S21Matrix() { DeallocateMatrix(); }

void S21Matrix::CopyMatrix(const S21Matrix& other) {
  AllocateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Инциализация функций
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Размеры матриц не подходят для сложения.");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  // Проверка на совпадение размеров матриц
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Размеры матриц не подходят для вычитания.");
  }

  // Выполнение поэлементного вычитания
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Количество столбцов в текущей матрице должно быть равно количеству "
        "строк в матрице other.");
  }

  // Создаем временную матрицу для хранения результата умножения
  S21Matrix result(rows_, other.cols_);

  // Выполняем умножение матриц
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  // Заменяем текущую матрицу результатом умножения
  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::Minor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0, mi = 0; i < rows_; ++i) {
    if (i == row) continue;
    for (int j = 0, mj = 0; j < cols_; ++j) {
      if (j == col) continue;
      minor.matrix_[mi][mj] = matrix_[i][j];
      ++mj;
    }
    ++mi;
  }
  return minor;
}

double S21Matrix::Determinant() const {
  if (cols_ != rows_) {
    throw std::invalid_argument("Матрица должна быть квадратной");
  }
  if (rows_ == 2) {
    return (matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1]);
  }
  if (rows_ == 1) {
    return matrix_[0][0];
  }
  double det = 0.0;
  for (int i = 0; i < rows_; ++i) {
    S21Matrix minor = Minor(0, i);
    det += (i % 2 == 0 ? 1 : -1) * matrix_[0][i] * minor.Determinant();
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (cols_ != rows_) {
    throw std::invalid_argument("Матрица должна быть квадратной");
  }
  S21Matrix complement(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = Minor(i, j);
      complement.matrix_[i][j] =
          ((i + j) % 2 == 0 ? 1 : -1) * minor.Determinant();
    }
  }
  return complement;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (det == 0) {
    throw std::invalid_argument("Матрица должна быть квадратной");
  }
  S21Matrix inverse = CalcComplements().Transpose();
  inverse.MulNumber(1.0 / det);
  return inverse;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& B) {
  SumMatrix(B);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& B) {
  SubMatrix(B);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double B) {
  MulNumber(B);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& B) {
  MulMatrix(B);
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& B) const {
  S21Matrix result(*this);
  result += B;
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& B) const {
  S21Matrix result(*this);
  result -= B;
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& B) const {
  S21Matrix result(*this);
  result *= B;
  return result;
}

S21Matrix S21Matrix::operator*(double B) const {
  S21Matrix result(*this);
  result *= B;
  return result;
}

bool S21Matrix::operator==(const S21Matrix& B) const { return EqMatrix(B); }

bool S21Matrix::operator!=(const S21Matrix& B) const { return !EqMatrix(B); }

double& S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Матрица вне диапазона");
  }
  return matrix_[i][j];
}

const double& S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Матрица вне диапазона");
  }
  return matrix_[i][j];
}

// Геттеры и Сеттеры

void S21Matrix::SetElement(int rows, int cols, double number) {
  matrix_[rows][cols] = number;
}

double S21Matrix::GetElement(int rows, int cols) const {
  return matrix_[rows][cols];
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

double** S21Matrix::GetMatrixPointer() const { return matrix_; }
