#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> c(v);
	EXPECT_EQ(v, c);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> c(v);
	c[3] = c[3] + 1;
	EXPECT_NE(v, c);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

//TEST(TDynamicVector, throws_when_set_element_with_negative_index) //негативного size_t не будет

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	EXPECT_ANY_THROW(v.at(6) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(2);
	v[0] = 10;
	EXPECT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	v1[4] = 5;
	EXPECT_NO_THROW(v2 = v1);
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(3), v2;
	v2 = v1;
	EXPECT_EQ(v2.size(), v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(3), v2(4);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	EXPECT_NO_THROW(v2 = v1);
	EXPECT_TRUE(v2 == v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int arr[] = { 2,3,4,5,6 };
	TDynamicVector<int> v1(arr,4), v2(v1);
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(2);
	v[0] = 10;
	v = v;
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3), v2(4);
	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int exarr[] = { 2,3,4,5,6 };
	int iarr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> ex(exarr, 5), v(iarr, 5);
	v = v + 1;
	EXPECT_EQ(ex, v);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int exarr[] = { 2,3,4,5,6 };
	int iarr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> ex(iarr, 5), v(exarr, 5);
	v = v - 1;
	EXPECT_EQ(ex, v);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int exarr[] = { 3,6,9,12,15 };
	int iarr[] = { 1, 2, 3, 4, 5 };
	TDynamicVector<int> ex(exarr, 5), v(iarr, 5);
	v = v*3;
	EXPECT_EQ(ex, v);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int exarr[] = { 2,2,4,6,8 };
	int iarr[] = {  1,2,3,4,5 };
	int iarr2[] = { 1,0,1,2,3 };
	TDynamicVector<int> ex(exarr, 5), v(iarr, 5), v2(iarr2,5);
	EXPECT_EQ(ex, v+v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2), v2(3);
	EXPECT_ANY_THROW(v1+v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int exarr[] = {0, 2, 2, 2, 2 };
	int iarr[] = { 1, 2, 3, 4, 5 };
	int iarr2[] = {1, 0, 1, 2, 3 };
	TDynamicVector<int> ex(exarr, 5), v(iarr, 5), v2(iarr2, 5);
	EXPECT_EQ(ex, v-v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2), v2(3);
	EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int iarr[] = {  1, 2, 3, 4, 5 };
	int iarr2[] = { 1, 0, 1, 2, 3 };
	TDynamicVector<int> v(iarr2, 5), v2(iarr, 5);
	EXPECT_EQ(v*v2, 27);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2), v2(3);
	EXPECT_ANY_THROW(v1 * v2);
}

