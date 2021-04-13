#include <utility>
template <typename Object>
class myQueue
{
	private:
		int size, back;
		Object *objects;
		
	public:
		myQueue()
		{
			size = 10;
			back = 0;
			objects = new Object[size];
		}
		
		~myQueue()
		{
			clear();
			delete[] objects;
		}
		
		myQueue(myQueue && rhs) : size{rhs.size}, back{rhs.back}
		{
			objects = rhs.objects;
		}
		
		myQueue & operator= (myQueue && rhs)
		{
			size = rhs.size;
			back = rhs.back;
			objects = rhs.objects;
			return *this;
		}
		
		myQueue(const myQueue<Object> & rhs) : size{rhs.size}, back{rhs.back}
		{
			objects = new Object[size];
			for (int i = 0; i < back; i++) 
			{
				objects[i] = rhs.objects[i];
			}
		}
		
		myQueue & operator= (const myQueue & rhs)
		{
			myQueue copy = rhs;
			std::swap(*this, copy);
			return *this;
		}
		
		void enqueue(Object o) 
		{
			if (back == size)
			{
				resize();
			}
			objects[back] = o;
			back++;
		}
		
		void resize()
		{
			size = size*2;
			Object *newObjects = new Object[size];
			for (int i = 0; i < back; i++)
			{
				newObjects[i] = objects[i];
			}
			delete[] objects;
			objects = newObjects;
		}
		
		Object dequeue()
		{
			Object retVal = front();
			if (!empty()) 
			{			
				for (int i = 1; i < back; i++)
				{
					objects[i-1] = objects[i];
				}
				back--;
			}
			return retVal;
		}
		
		Object front()
		{
			return objects[0];
		}
		
		bool empty()
		{
			return(back==0);
		}
		
		void clear()
		{
			delete[] objects;
			size = 10;
			back = 0;
			objects = new Object[size];
		}
};
