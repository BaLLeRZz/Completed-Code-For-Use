#include<iostream>
#include<vector>

template<class T>
class max_heap
{
private:
	std::vector<T> values{};
	const int get_left_child_index(int index) const;
	const int get_right_child_index(int index) const;
	const int get_parent_index(int index) const;
	void heapify(int index);
public:
	max_heap() = default;

	void insert(const T& element);
	void extract();
	const T& max() const;
	const size_t size() const;
	const bool empty() const;
	void print() const;
};

template<class T>
const int max_heap<T>::get_left_child_index(int index) const
{
	return index * 2 + 1;
}

template<class T>
const int max_heap<T>::get_right_child_index(int index) const
{
	return index * 2 + 2;
}

template<class T>
const int max_heap<T>::get_parent_index(int index) const
{
	return (index - 1) / 2;
}

template<class T>
void max_heap<T>::heapify(int index)
{
	int left = this->get_left_child_index(index);
	int right = this->get_right_child_index(index);
	size_t size = this->size();
	int index_to_swap = index;

	if (left < size && this->values[left] > this->values[index_to_swap])
		index_to_swap = left;

	if (right < size && this->values[right] > this->values[index_to_swap])
		index_to_swap = right;

	if (index_to_swap == index)
		return;

	std::swap(this->values[index_to_swap], this->values[index]);
	this->heapify(index_to_swap);
}

template<class T>
void max_heap<T>::insert(const T& element)
{
	this->values.push_back(element);
	int current_index = this->values.size() - 1;
	int parent_index = this->get_parent_index(current_index);
	while (parent_index >= 0 && this->values[parent_index] < this->values[current_index])
	{
		std::swap(this->values[current_index], this->values[parent_index]);
		current_index = parent_index;
		parent_index = this->get_parent_index(parent_index);
	}
}

template<class T>
void max_heap<T>::extract()
{
	if (this->values.size() == 0)
		return;

	std::swap(this->values[0], this->values[this->values.size() - 1]);
	this->values.pop_back();
	heapify(0);
}

template<class T>
const T& max_heap<T>::max() const
{
	return this->values[0];
}

template<class T>
const size_t max_heap<T>::size() const
{
	return this->values.size();
}

template<class T>
const bool max_heap<T>::empty() const
{
	return this->values.empty();
}

template<class T>
void max_heap<T>::print() const
{
	for (T value : this->values)
		std::cout << value << " ";

	std::cout << std::endl;
}

int main()
{
	max_heap<int> h;
	h.insert(10);
	h.print();
	h.insert(1);
	h.print();
	h.insert(15);
	h.print();
	h.insert(7);
	h.print();
	h.insert(20);
	h.print();
	std::cout << std::endl;
	while (!h.empty())
	{
		std::cout << h.max() << std::endl;
		h.extract();
		h.print();
		std::cout << std::endl;
	}
	return 0;
}
