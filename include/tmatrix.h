// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;

public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if ((sz == 0) || (sz > MAX_VECTOR_SIZE))
			throw out_of_range("Vector size should be greater than zero and less than MAX_VECTOR_SIZE");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[v.sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		swap(*this, v);
	}
	~TDynamicVector()
	{
		delete[] pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v)
			return *this;
		if (sz != v.sz) {
			T* p = new T[v.sz];
			sz = v.sz;
			pMem = p;
		}
		std::copy(v.pMem, v.pMem + sz, pMem);
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind >= sz)
			throw std::out_of_range("Index out of range");
		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind >= sz)
			throw std::out_of_range("Index out of range");
		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)
			return 0;
		return memcmp(pMem, v.pMem, sizeof(T) * sz) == 0;
	}
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)
			return 1;
		return memcmp(pMem, v.pMem, sizeof(T) * sz) != 0;
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			res.pMem[i] = pMem[i] + val;
		}
		return res;
	}

	TDynamicVector operator-(T val)
	{
		TDynamicVector res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			res.pMem[i] = pMem[i] - val;
		}
		return res;
	}
	TDynamicVector operator*(T val)
	{
		TDynamicVector res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			res.pMem[i] = pMem[i] * val;
		}
		return res;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw "Vector operation on vectors of different sizes";
		TDynamicVector res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			res.pMem[i] = pMem[i] + v.pMem[i];
		}
		return res;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw "Vector operation on vectors of different sizes";
		TDynamicVector res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			res.pMem[i] = pMem[i] - v.pMem[i];
		}
		return res;
	}

	T operator*(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw "Vector operation on vectors of different sizes";

		T result = T{};
		for (size_t i = 0; i < sz; i++)
		{
			result = result + (pMem[i] * (v.pMem[i]));
		}
		return result;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (sz == 0)
		{
			throw out_of_range("Zero matrix size");
		}
		if (sz > MAX_MATRIX_SIZE)
		{
			throw out_of_range("Matrix size greater than MAX_MATRIX_SIZE");
		}
		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	size_t size() const { return sz; }

	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		if (sz != m.sz)
			return 0;
		for (size_t i = 0; i < sz;i++) {
			if (pMem[i] != m.pMem[i])
				return 0;
		}
		return 1;
	}

	bool operator!=(const TDynamicMatrix& m) const noexcept
	{
		return !(*this == m);
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix res(*this);
		for (size_t i = 0; i < sz; i++)
		{
			for (size_t j = 0; j < sz; j++)
			{
				res[i][j] *= val;
			}
		}

		return res;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		if (sz != v.sz)
		{
			throw "Operation on different sized matrix and vector";
		}
		TDynamicVector<T> res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			for (size_t j = 0; j < sz; j++)
			{
				res[i] += pMem[i][j] * v[j];
			}
		}
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
		{
			throw "Operation on different sized matrices";
		}
		TDynamicMatrix res(*this);
		for (size_t i = 0; i < sz; i++)
		{
			for (size_t j = 0; j < sz; j++)
			{
				res[i][j] += m[i][j];
			}
		}

		return res;
	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
		{
			throw "Operation on different sized matrices";
		}
		TDynamicMatrix res(*this);
		for (size_t i = 0; i < sz; i++)
		{
			for (size_t j = 0; j < sz; j++)
			{
				res[i][j] -= m[i][j];
			}
		}

		return res;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
		{
			throw logic_error("Operation on different sized matrices");
		}
		TDynamicMatrix res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			for (size_t k = 0; k < sz; k++)
			{
				for (size_t j = 0; j < sz; j++)
				{
					res[i][j] += pMem[i][k] * m[k][j];
				}
			}
		}
		return res;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.size(); ++i)
		{
			istr >> v[i];
		}
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.size(); ++i)
		{
			ostr << v[i] << '\n';
		}
		return ostr;
	}

	T& at(size_t i, size_t j)
	{
		if ((i >= sz) || (j >= sz))
		{
			throw "Access index larger than matrix size";
		}
		return pMem[i][j];
	}

	const T& at(size_t i, size_t j) const
	{
		if ((i >= sz) || (j >= sz))
		{
			throw "Access index larger than matrix size";
		}
		return pMem[i][j];
	}

};

#endif
