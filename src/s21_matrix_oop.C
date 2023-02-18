#include "s21_matrix_oop.h"
using namespace std;
S21Matrix::S21Matrix() {
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
}
S21Matrix::S21Matrix(int rows, int columns) {
  this->CreateMatrix(rows, columns);
}
S21Matrix::S21Matrix(const S21Matrix& other) { this->Copy(other); }
S21Matrix::S21Matrix(S21Matrix&& other) {
  this->Copy(other);
  other.RemoveMatrix();
}
S21Matrix::~S21Matrix() { this->RemoveMatrix(); }

void S21Matrix::CreateMatrix(int rows, int columns) {
  if (rows < 1 || columns < 1) {
    throw std::length_error(
        "Oh, no! Yure rows and columns less then 1! Try again man and without "
        "any tricks!");
  }
  this->rows_ = rows;
  this->cols_ = columns;
  this->matrix_ = new double*[rows_]();
  if (this->matrix_ == nullptr) {
    throw std::bad_alloc();
  }
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_]();
    if (this->matrix_[i] == nullptr) {
      for (int j = 0; j < i; j++) {
        delete[] this->matrix_[j];
      }
      delete[] this->matrix_;
      this->matrix_ = nullptr;
      this->rows_ = 0;
      this->cols_ = 0;
      throw std::bad_alloc();
    }
  }
}

void S21Matrix::RemoveMatrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
    this->rows_ = 0;
    this->cols_ = 0;
  }
}
void S21Matrix::Copy(const S21Matrix& other) {
  this->CreateMatrix(other.rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*(double num) {
  this->MulNumber(num);
  return *this;
}
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this->matrix_ != nullptr) {
    this->RemoveMatrix();
    this->Copy(other);
  } else {
    this->Copy(other);
  }
  return *this;
}
bool S21Matrix::operator==(const S21Matrix& other) {
  bool tmp = this->EqMatrix(other);
  return tmp;
}
double& S21Matrix::operator()(int i, int j) {
  if (i > this->rows_ || j > this->cols_ || i < 0 || j < 0) {
    throw std::length_error(
        "Oh, no! Your problem with rows and "
        "columns!"
        "Try again man and without any tricks!");
  }
  return this->matrix_[i][j];
}
/// @brief Сумма двух матриц, результат операции которой записывается в
/// базовый класс
/// @param other Матрица
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (other.matrix_ == nullptr && this->matrix_ == nullptr &&
      (this->rows_ < 1 || other.rows_ < 1)) {
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  if ((this->rows_ == other.rows_) && (this->cols_ == other.cols_)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
      }
    }
  } else {
    throw std::length_error("Error: matrix size is wrong");
  }
}
/// @brief Разница двух матриц, результат операции которой записывается в
/// базовый класс
/// @param other Матрица
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (other.matrix_ == nullptr && this->matrix_ == nullptr &&
      (this->rows_ < 1 || other.rows_ < 1)) {
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  if ((this->rows_ == other.rows_) && (this->cols_ == other.cols_)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
      }
    }
  } else {
    throw std::length_error("Error: matrix size is wrong");
  }
}
/// @brief Умножение матрицы на число, результат операции которой записывается
/// в базовый класс
/// @param other Матрица
void S21Matrix::MulNumber(const double num) {
  if ((this->matrix_ == nullptr) && (this->rows_ < 1)) {
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] * num;
    }
  }
}
/// @brief Умножение матрицы на матрицу, результат операции которой
/// записывается в базовый класс
/// @param other Матрица
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (other.matrix_ == nullptr && this->matrix_ == nullptr &&
      (this->rows_ < 1 || other.rows_ < 1)) {
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  if ((this->cols_ == other.rows_)) {
    S21Matrix result(this->rows_, other.cols_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < other.cols_; j++) {
        for (int k = 0; k < other.rows_; k++) {
          result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
        }
      }
    }
    this->Copy(result);
  } else {
    throw std::length_error("Error: matrix size is wrong");
  }
}
/// @brief Сравнение матриц
/// @param other Вторая матрица
/// @return bool
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = true;
  if (other.matrix_ == nullptr && this->matrix_ == nullptr &&
      (this->rows_ == other.rows_ && this->cols_ == other.cols_)) {
    res = false;
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  for (int i = 0; i < this->rows_ && res; i++) {
    for (int j = 0; j < this->cols_ && res; j++) {
      if (round(this->matrix_[i][j] * pow(10, 7)) !=
          round(other.matrix_[i][j] * pow(10, 7))) {
        res = false;
      }
    }
  }
  return res;
}
/// @brief Транспанирование матрицы, результат операции которой записывается
/// в базовый класс
/// @return
S21Matrix S21Matrix::Transpose() {
  if ((this->matrix_ == nullptr) && (this->rows_ < 1)) {
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  S21Matrix result(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return result;
}
/// @brief Определитель матрицы
/// @return Результат
double S21Matrix::Determinant() {
  double result = 0.0;
  if ((this->matrix_ == nullptr) && (this->rows_ < 1)) {
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  if (this->rows_ == this->cols_) {
    result = this->GetDeterminant();
  } else {
    throw std::length_error("Error: matrix size is wrong");
  }
  return result;
}
/// @brief Определитель матрицы
/// @return Результат
double S21Matrix::GetDeterminant() {
  double result = 0.0;
  // если матрица very small
  if (this->rows_ == 1) {
    result = this->matrix_[0][0];
  } else {
    S21Matrix tmp(this->rows_ - 1, this->cols_ - 1);
    for (int i = 0; i < this->cols_; i++) {
      this->GetMatrix(0, i, tmp);
      if (i % 2) {
        result -= this->matrix_[0][i] * tmp.GetDeterminant();
      } else {
        result += this->matrix_[0][i] * tmp.GetDeterminant();
      }
    }
  }
  return result;
}
void S21Matrix::GetMatrix(int row, int col, const S21Matrix& tmp) {
  int m_row = 0;
  int m_col = 0;
  for (int i = 0; i < this->rows_; i++) {
    if (i == row) {
      continue;
    }
    m_col = 0;
    for (int j = 0; j < this->cols_; j++) {
      if (j == col) {
        continue;
      }
      tmp.matrix_[m_row][m_col] = this->matrix_[i][j];
      m_col++;
    }
    m_row++;
  }
}
S21Matrix S21Matrix::CalcComplements() {
  if ((this->matrix_ == nullptr) && (this->rows_ < 1)) {
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  if (this->rows_ != this->cols_) {
    throw std::length_error("Error: matrix size is wrong");
  }
  S21Matrix result(this->rows_, this->cols_);
  S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
  double determinant = 0.0;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->GetMatrix(i, j, minor);
      determinant = minor.Determinant();
      result.matrix_[i][j] = pow(-1, i + j) * determinant;
    }
  }
  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  if ((this->matrix_ == nullptr) && (this->rows_ < 1)) {
    throw std::length_error(
        "Oh, no! Your matrix is empty or maybe problem with rows and "
        "columns! "
        "Try again man and without any tricks!");
  }
  if (this->rows_ != this->cols_) {
    throw std::length_error("Error: matrix size is wrong");
  }
  double determinant = this->Determinant();
  if (std::fabs(determinant) < 1e-7) {
    throw std::length_error(
        "Ooops!!! Determinant is 0, try again and please don't try to break "
        "my "
        "code");
  }
  S21Matrix result(this->rows_, this->cols_);
  if (this->rows_ == 1) {
    result.setElement(0, 0, 1.0 / determinant);
  } else {
    S21Matrix tmp = this->CalcComplements();
    result = tmp.Transpose();
    result.MulNumber(1 / determinant);
  }

  return result;
}