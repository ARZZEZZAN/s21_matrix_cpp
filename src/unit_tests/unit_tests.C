#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix mat;
  ASSERT_EQ(mat.getRows(), 0);
  ASSERT_EQ(mat.getCols(), 0);
  ASSERT_EQ(mat.getMatrix(), nullptr);
}
TEST(S21MatrixTest, Constructor) {
  S21Matrix mat(3, 4);
  ASSERT_EQ(mat.getRows(), 3);
  ASSERT_EQ(mat.getCols(), 4);
  ASSERT_NE(mat.getMatrix(), nullptr);
  // Check that all elements are initialized to zero
  for (int i = 0; i < mat.getRows(); i++) {
    for (int j = 0; j < mat.getCols(); j++) {
      ASSERT_EQ(mat.getMatrix()[i][j], 0.0);
    }
  }

  // Check that an exception is thrown if rows or columns are less than 1
  ASSERT_THROW(S21Matrix mat2(0, 4), std::length_error);
  ASSERT_THROW(S21Matrix mat3(3, -1), std::length_error);
}
TEST(S21MatrixTest, constructor_move) {
  S21Matrix A(5, 5);
  S21Matrix B(std::move(A));
  EXPECT_EQ(5, B.getRows());
  EXPECT_EQ(5, B.getCols());
  EXPECT_EQ(0, A.getRows());
  EXPECT_EQ(0, A.getCols());
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix A(3, 4);
  S21Matrix B(A);
  EXPECT_EQ(3, B.getRows());
  EXPECT_EQ(4, B.getCols());
  EXPECT_EQ(1, A == B);
}
TEST(S21MatrixTest, SumMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a.setElement(0, 0, 1);
  a.setElement(0, 1, 2);
  a.setElement(1, 0, 3);
  a.setElement(1, 1, 4);

  b.setElement(0, 0, 5);
  b.setElement(0, 1, 6);
  b.setElement(1, 0, 7);
  b.setElement(1, 1, 8);

  expected.setElement(0, 0, 6);
  expected.setElement(0, 1, 8);
  expected.setElement(1, 0, 10);
  expected.setElement(1, 1, 12);

  a.SumMatrix(b);
  EXPECT_TRUE(a == expected);
}
TEST(S21MatrixTest, SubMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a.setElement(0, 0, 4);
  a.setElement(0, 1, 4);
  a.setElement(1, 0, 6);
  a.setElement(1, 1, 6);

  b.setElement(0, 0, 2);
  b.setElement(0, 1, 2);
  b.setElement(1, 0, 3);
  b.setElement(1, 1, 3);

  expected.setElement(0, 0, 2);
  expected.setElement(0, 1, 2);
  expected.setElement(1, 0, 3);
  expected.setElement(1, 1, 3);

  a.SubMatrix(b);
  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, MulMatrixTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a.setElement(0, 0, 1);
  a.setElement(0, 1, 2);
  a.setElement(1, 0, 3);
  a.setElement(1, 1, 4);

  b.setElement(0, 0, 5);
  b.setElement(0, 1, 6);
  b.setElement(1, 0, 7);
  b.setElement(1, 1, 8);

  expected.setElement(0, 0, 19);
  expected.setElement(0, 1, 22);
  expected.setElement(1, 0, 43);
  expected.setElement(1, 1, 50);

  a.MulMatrix(b);

  EXPECT_TRUE(a == expected);
}
TEST(S21MatrixTest, MulNumberTest) {
  S21Matrix a(2, 2);
  S21Matrix expected(2, 2);

  a.setElement(0, 0, 1);
  a.setElement(0, 1, 2);
  a.setElement(1, 0, 3);
  a.setElement(1, 1, 4);

  expected.setElement(0, 0, 2);
  expected.setElement(0, 1, 4);
  expected.setElement(1, 0, 6);
  expected.setElement(1, 1, 8);

  a.MulNumber(2);

  EXPECT_TRUE(a == expected);
}
TEST(S21MatrixTest, EqTest) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a.setElement(0, 0, 1);
  a.setElement(0, 1, 2);
  a.setElement(1, 0, 3);
  a.setElement(1, 1, 4);

  b.setElement(0, 0, 1);
  b.setElement(0, 1, 2);
  b.setElement(1, 0, 3);
  b.setElement(1, 1, 4);

  EXPECT_TRUE(a.EqMatrix(b));
}
TEST(Test, EQmatrix) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_THROW(A == B, std::length_error);
}
TEST(Test, operator_plus) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A = B + B;
  EXPECT_EQ(1, A == B);
}
TEST(Test, operator_minus) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A = B - B;
  EXPECT_EQ(1, A == B);
}
TEST(Test, inverst_test) {
  S21Matrix result(3, 3);
  result(0, 0) = 0;
  result(0, 1) = 1;
  result(0, 2) = -0.75;
  result(1, 0) = -0.5;
  result(1, 1) = 3;
  result(1, 2) = -2;
  result(2, 0) = 0.5;
  result(2, 1) = -3.5;
  result(2, 2) = 2.5;

  S21Matrix R(3, 3);
  R(0, 0) = 8;
  R(0, 1) = 2;
  R(0, 2) = 4;
  R(1, 0) = 4;
  R(1, 1) = 6;
  R(1, 2) = 6;
  R(2, 0) = 4;
  R(2, 1) = 8;
  R(2, 2) = 8;

  S21Matrix result_inverse(3, 3);
  result_inverse = R.InverseMatrix();
  EXPECT_EQ(1, result == result_inverse);
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}