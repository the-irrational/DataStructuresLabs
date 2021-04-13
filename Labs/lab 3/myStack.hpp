#include <utility>
template <typename Object>
class myStack
{
	private:
		int size;
		Object *objects;
		int current;
		
	public:
		myStack()
		{
			size = 10;
			objects = new Object[size];
			current = 0;
		}
		
		~myStack()
		{
			delete[] objects;
		}
		
		myStack(myStack && rhs)
		{
			size = rhs.size;
			objects = rhs.objects;
			current = rhs.current;
		}
		
		myStack & operator= (myStack && rhs)
		{
			delete[] objects;
			size = rhs.size;
			objects = rhs.objects;
			current = rhs.current;
			return *this;
		}
		
		myStack(const myStack<Object> & rhs)
		{
			size = 10;
			objects = new Object[size];
			current = 0;
			for (int i = rhs.current-1; i >= 0; i--)
			{
				push(rhs.objects[0]);
			}
		}
		
		myStack & operator= (const myStack & rhs)
		{
			myStack copy = rhs;
			std::swap(*this, copy);
			return *this;
		}
		
		void resize()
		{
			Object *newObjects = new Object[size*2];
			for (int i = 0; i < size; i++)
			{
				newObjects[i] = objects[i];
			}
			delete[] objects;
			objects = newObjects;
			size = size*2;
		}
		
		void push(Object o)
		{
			if (current == size-1) 
			{
				resize();
			}
			objects[current] = o;
			current++;
		}
		
		Object pop()
		{
			current--;
			Object retVal = objects[current];
			
			return retVal;
		}
		
		Object top()
		{
			if (!empty())
			{
				return objects[current-1];
			}
			else 
			{
				return objects[current];
			}
		}
		
		bool empty()
		{
			return (current == 0);
		}
		
		void clear()
		{
			delete[] objects;
			size = 10;
			objects = new Object[size];
			current = 0;
		}
};
				
