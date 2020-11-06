#pragma once

#include <stdexcept>

namespace vec 
{
	template<typename vec_t>
	class vector
	{
	private:
		int v_size;
		int v_cap;

	public:
		vec_t* vec;

	private:
		void vec_resize(const int new_size)
		{
			v_size = new_size;
			while (v_size > v_cap)
				v_cap *= 1.5f;

			vec_t* tmp = new vec_t[v_cap];

			for (int i = 0; i < v_size; i++)
			{
				if (vec[i] == NULL)
					break;
				tmp[i] = vec[i];
			}

			delete[] vec;
			vec = tmp;
		}

		void vec_resize_to_push_back()
		{
			v_cap *= 1.5f;
			vec_t* tmp = new vec_t[v_cap];

			for (int i = 0; i < v_size; i++)
				tmp[i] = vec[i];

			delete[] vec;
			vec = tmp;
		}

		void vec_resize_with_fill_val(const int size, vec_t val)
		{
			if (size > v_cap)
				v_cap = size;

			vec_t* tmp = new vec_t[v_cap];

			for (int i = 0; i < v_size; i++) 
			{
				if (vec[i] == NULL)
					break;
				tmp[i] = vec[i];
			}

			if (size > v_size)
				for (int i = v_size; i < v_cap; i++)
					tmp[i] = val;

			v_size = size;

			delete[] vec;
			vec = tmp;
		}

		void check_in_range(int index)
		{
			if (index >= v_size || index < 0)
				throw std::out_of_range("Out of range");
		}

	public:
		//Constructors
		vector()
		{
			v_size = 0;
			v_cap = 2;
			vec = new vec_t[v_cap];
		}

		//Destructor
		~vector() 
		{ 
			v_size = 0;
			v_cap = 1;
			delete[] vec; 
		}

		//Access to elements
		vec_t& operator[](const int index)
		{
			check_in_range(index);
			return vec[index];
		}

		vec_t at(int index)
		{
			check_in_range(index);
			return vec[index];
		}

		inline vec_t front()
		{
			return vec[0];
		}

		inline vec_t back()
		{
			return vec[v_size - 1];
		}

		//Work with vector size
		inline int size()
		{
			return v_size;
		}

		inline int capacity()
		{
			return v_cap;
		}

		void resize(int size)
		{
			vec_resize(size);
		}

		void resize(int size, vec_t data)
		{
			vec_resize_with_fill_val(size, data);
		}

		inline bool empty()
		{
			return v_size == 0 ? true : false;
		}

		inline void shrink_to_fit()
		{
			v_cap = v_size;
		}

		//Modifiers
		void push_back(vec_t data)
		{
			if (v_size == v_cap)
				vec_resize_to_push_back();
			vec[v_size] = data;
			v_size++;
		}

		void pop_back()
		{
			vec[v_size] = NULL;
			v_size--;
		}
	};

}
