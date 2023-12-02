
#include <iostream>
template <class T>
class DynamicArray
{
public:
	//creates an array of given size and initializes the first empty element
	DynamicArray(int size) : m_data(new T[size])
	{
		m_size = size;
		m_firstEmptyElement = 0;
	}
	//deletes the array
	~DynamicArray()
	{
		delete[] m_data;
	}
	//adds an object to the array
	void add(T data)
	{
		if (m_firstEmptyElement < m_size)
		{
			m_data[m_firstEmptyElement] = data;
			m_firstEmptyElement++;
			increaseArraySize();
		}
		else
		{
			std::cerr << "Error: Index " << m_firstEmptyElement << " is out of bounds." << std::endl;
		}
	}
	//deletes the object at a given index, checks to see if we should decrease the size
	void removeByElement(int index) {
		if (index < 0 || index >= m_firstEmptyElement) {
			std::cerr << "Error: Index " << index << " is out of bounds." << std::endl;
			return;
		}

		// Delete the element if T is a non-primitive type
		delete& m_data[index];

		// Shift elements after the removed element to fill the gap
		for (int i = index; i < m_firstEmptyElement - 1; ++i) {
			m_data[i] = m_data[i + 1];
		}

		// Decrease the size
		--m_firstEmptyElement;

		// Optionally, you may want to check if it's appropriate to decrease the array size here
		decreaseArraySize();
	}
	//retrieves the object at the given index
	T getByElement(int index)
	{
		try
		{
			if (index < m_size)
			{
				return m_data[index];
			}
			else
			{
				throw index;
			}
		}
		catch (int index)
		{
			std::cout << "Index " << index << " is out of bounds." <<
				std::endl;
		}
	}
	//double the array size
	void increaseArraySize() {
		if (m_firstEmptyElement == m_size) {
			int newCapacity = m_size * 2;
			T* newArray = new T[newCapacity];

			for (int i = 0; i < m_firstEmptyElement; ++i) {
				newArray[i] = m_data[i];
			}

			m_size = newCapacity;
			delete[] m_data;

			m_data = newArray;
		}
	}

	//halves the array size
	void decreaseArraySize() {
		if (m_firstEmptyElement < m_size / 2) {
			int newCapacity = m_size / 2;
			T* newArray = new T[newCapacity];

			for (int i = 0; i < m_firstEmptyElement; ++i) {
				newArray[i] = m_data[i];
			}

			m_size = newCapacity;
			delete[] m_data;

			m_data = newArray;
		}
	}


private:
	T* m_data;
	int m_size;
	int m_firstEmptyElement;
};
//I chose to double the size when the array was filled as i say online that that seemed to be the most common practice
//To avoid making the array too small too quickly for the user I chose to decrease it only when the first empty element was at half the size or less, at which point i would halve
//the size of the array. 