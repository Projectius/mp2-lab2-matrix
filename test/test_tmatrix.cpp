#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(3));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-1));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(3);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(3);

	std::istringstream iss("1 2 3 4 5 6 7 8 9");
	iss >> m1;

	TDynamicMatrix<int> m2(m1);
	for (size_t i = 0; i < m1.size(); i++)
	{

		EXPECT_EQ(m1[i], m2[i]);
		
	}
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(3), m2(3);
	m1[1][0] = 1;
	EXPECT_NE(m1[1][0], m2[1][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(3);
	EXPECT_EQ(m.size(), 3);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	EXPECT_NO_THROW(m[1][1] = 1);
	EXPECT_TRUE(m[1][1] == 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);
	EXPECT_ANY_THROW(m.at(3, 0) = 1);
	EXPECT_ANY_THROW(m.at(0, 3) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m1(3);
	std::istringstream iss("1 2 3 4 5 6 7 8 9");
	iss >> m1;
	TDynamicMatrix<int> m2(m1);
	EXPECT_NO_THROW(m1 = m1);
	for (size_t i = 0; i < m1.size(); i++)
	{

		EXPECT_EQ(m1[i], m2[i]);

	}
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(3);
	std::istringstream iss("1 2 3 4 5 6 7 8 9");
	iss >> m1;
	TDynamicMatrix<int> m2(3);
	EXPECT_NO_THROW(m2 = m1);
	for (size_t i = 0; i < m1.size(); i++)
	{

		EXPECT_EQ(m1[i], m2[i]);

	}
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(2);
	EXPECT_NO_THROW(m2 = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(2);
	m2 = m1;
	EXPECT_EQ(m2.size(), m1.size());
	for (size_t i = 0; i < m1.size(); i++)
	{

		EXPECT_EQ(m1[i], m2[i]);

	}
}


TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(3), m2(m);
	EXPECT_EQ(m, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(3), m2(2);
	EXPECT_NE(m, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), e(2);
	istringstream("1 2 3 4") >> m1;
	istringstream("2 1 2 1") >> m2;
	istringstream("3 3 5 5") >> e;
	EXPECT_NO_THROW(m1=m1+m2);
	for (size_t i = 0; i < m1.size(); i++)
	{
		EXPECT_EQ(m1[i], e[i]);
	}
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2), m1(3);
	EXPECT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), e(2);
	istringstream("3 3 5 5") >> m1;
	istringstream("2 1 2 1") >> m2;
	istringstream("1 2 3 4") >> e;
	EXPECT_NO_THROW(m1 = m1 - m2);
	for (size_t i = 0; i < m1.size(); i++)
	{
		EXPECT_EQ(m1[i], e[i]);
	}
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2), m1(3);
	EXPECT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), e(2);
	istringstream("3 4 9 5") >> m1;
	istringstream("7 65 2 43") >> m2;
	istringstream("29 367 73 800") >> e;
	EXPECT_NO_THROW(m1 = m1 * m2);
	for (size_t i = 0; i < m1.size(); i++)
	{
		EXPECT_EQ(m1[i], e[i]);
	}
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2), m1(3);
	EXPECT_ANY_THROW(m * m1);
}