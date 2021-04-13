#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
template <typename Comparable>
class myBinaryMinHeap
{
	public:
		explicit myBinaryMinHeap(int capacity = 100) : array(capacity), currentSize{0} 
		{
			buildHeap();
		}
		explicit myBinaryMinHeap(const vector<Comparable> & items) : array(items.size() + 10), currentSize{items.size()}
		{
			for(int i = 0; i < items.size(); ++i)
				array[i + 1] = items[i];
			buildHeap();
		}
		
		bool isEmpty() const
		{
			return (currentSize == 0);
		}
		const Comparable & findMin() const
		{
			//find min
			return array[1];
		}
		
		void insert(const Comparable & x)
		{
			if(currentSize == array.size() - 1)
				array.resize(array.size() * 2);
				
				//Percolate up
			int hole = ++currentSize;
			Comparable copy = x;
			
			array[0] = move(copy);
			for( ; x < array[hole / 2]; hole /= 2)
				array[hole] = move(array[hole / 2]);
			array[hole] = move(array[0]);
		}
		void insert(Comparable && x)
		{
			if(currentSize == array.size() - 1)
				array.resize(array.size() * 2);
			Comparable copy = x;
			int hole = ++currentSize;
			array[0] = move(x);
			for( ; copy < array[hole / 2]; hole /= 2)
				array[hole] = move(array[hole / 2]);
			array[hole] = move(array[0]);
		}
		void deleteMin()
		{
			if(isEmpty())
				cerr << "Heap is Empty";
			
			array[1] = move(array[currentSize--]);
			percolateDown(1);
		}
		void deleteMin(Comparable & minItem)
		{
			if(isEmpty())
				cerr << "Heap is Empty";
				
			minItem = move(array[1]);
			array[1] = move(array[currentSize--]);
			percolateDown(1);
		}
		void makeEmpty()
		{
			currentSize = 0;
			array.clear();
		}
		void levelOrder(ofstream & out)
		{
			for (int i = 1; i <= currentSize; i++)
			{
				out << array[i];
				out << endl;
			}
			
		}
		
	private:
		int currentSize;
		vector<Comparable> array;
		
		void buildHeap()
		{
			for(int i = currentSize / 2; i > 0; --i)
				percolateDown(i);
		}
		void percolateDown(int hole)
		{
			int child;
			Comparable tmp = move(array[hole]);
			
			for( ; hole * 2 <= currentSize; hole = child)
			{
				child = hole * 2;
				if(child != currentSize && array[child + 1] < array[child])
					++child;
				if(array[child] < tmp)
					array[hole] = move(array[child]);
				else
					break;
			}
			array[hole] = move(tmp);
		}
};
