#include <iostream>
#include <string>
#include <fstream>

using namespace std;
template <typename Object>
class bigV
{
  public:
    explicit bigV( int initSize = 0 ) : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }, depth { -1 }, visited { false }
      { objects = new Object[ theCapacity ]; }

    bigV( const bigV & rhs ) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {
      objects = new Object[ theCapacity ];
      for( int k = 0; k < theSize; ++k )
        objects[ k ] = rhs.objects[ k ];
    }

    bigV & operator= ( const bigV & rhs )
    {
      bigV copy = rhs;
      swap( *this, copy );
      return *this;
    }

    ~bigV( )
      { delete [ ] objects; }

    bigV(bigV && rhs) : theSize{rhs.theSize},
      theCapacity{rhs.theCapacity}, objects{rhs.objects}
    {
      rhs.objects = nullptr;
      rhs.theSize = 0;
      rhs.theCapacity = 0;
    }

    bigV & operator= ( bigV && rhs )
    {
      swap(theSize, rhs.theSize);
      swap(theCapacity, rhs.theCapacity);
      swap(objects, rhs.objects);
      return *this;
    }

    void resize(int newSize)
    {
      if(newSize>theCapacity)
        reserve(newSize*2);
      theSize = newSize;
    }

    void reserve(int newCapacity)
    {
      if(newCapacity < theSize)
        return;
      Object *newArray = new Object[ newCapacity ];
      for(int k = 0; k < theSize; ++k)
        newArray[k] = move(objects[k]);
      theCapacity = newCapacity;
      swap( objects, newArray);
      delete [] newArray;
    }

    Object & operator[](int index)
      {return objects[index]; }
    const Object & operator[](int index) const
      {return objects[index];}

    bool empty() const
      { return size() == 0; }
    int size() const
      { return theSize; }
    int capacity() const
      { return theCapacity; }

    void push_back( const Object & x)
    {
      if(theSize == theCapacity)
        reserve(2*theCapacity+1);
      objects[theSize++] = x;
    }

    void pop_back()
    {
      --theSize;
    }

    const Object & back() const
    {
      return objects[theSize - 1];
    }

    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin()
      { return &objects[0]; }
    const_iterator begin() const
      { return &objects[0]; }

    iterator end()
      {return &objects[size()];}
    const_iterator end() const
      {return &objects[size()]; }

    static const int SPARE_CAPACITY = 16;

    bigV<Object>& append(const bigV<Object>& data)
    {
      for (int k = 0; k < data.size(); ++k)
        push_back(data[k]);
      return *this;
    }

    bool known()
    {
      return visited;
    }
    void setKnown(bool known)
    {
      visited = known;
    }
    int getDepth()
    {
      return depth;
    }
    void setDepth(int d)
    {
      depth = d;
    }

  private:
    int theSize;
    int theCapacity;
    bool visited;
    int depth;
    Object * objects;
};
template <typename Object>
class queue
{
	private:
		int size, back;
		Object *objects;

	public:
		queue()
		{
			size = 10;
			back = 0;
			objects = new Object[size];
		}

		~queue()
		{
			clear();
			delete[] objects;
		}

		queue(queue && rhs) : size{rhs.size}, back{rhs.back}
		{
			objects = rhs.objects;
		}

		queue & operator= (queue && rhs)
		{
			size = rhs.size;
			back = rhs.back;
			objects = rhs.objects;
			return *this;
		}

		queue(const queue<Object> & rhs) : size{rhs.size}, back{rhs.back}
		{
			objects = new Object[size];
			for (int i = 0; i < back; i++)
			{
				objects[i] = rhs.objects[i];
			}
		}

		queue & operator= (const queue & rhs)
		{
			queue copy = rhs;
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

class myGraph
{
public:
  myGraph( char* filename )
  {
    size = initSize(filename);
    graph = new bigV<int>[size + 1];
    ifstream fin;
    fin.open(filename);
    if (fin.is_open())
    {
      string line;
      while (getline(fin, line, ','))
      {
        int index = stoi(line);
        getline(fin, line, ',');
        graph[index].push_back(stoi(line));
      }
    }
    else
    {
      cout<<"Invalid Filename!"<<endl;
    }
    //testWrite();
  }
  ~myGraph()
  {
    //delete anything
    delete[] graph;
  }
  void BFS( int source ) //using a queue
  {
    for (int i = 0; i <= size; i++)
    {
      graph[i].setDepth(-1);
      graph[i].setKnown(false);
    }
    queue<int> q = queue<int>();
    q.enqueue(source);
    graph[source].setDepth(0);
    cout<<source<<endl;
    for (int currentDepth = 0; currentDepth <= size; currentDepth++ )
    {
      for (int j = 0; j <= size; j++)
      {
        int i = q.front();
        if (!graph[i].known() && graph[i].getDepth() == currentDepth)
        {
          graph[i].setKnown(true);
          i = q.dequeue();
          for (auto& it : graph[i])
          {
            if (graph[it].getDepth() == -1)
            {
              graph[it].setDepth(currentDepth+1);
              q.enqueue(it);
              cout<<it<<endl;
            }
          }
        }
      }
    }
  }
  /*void BFS( int source )
  {
    for (int i = 0; i <= size; i++)
    {
      graph[i].setDepth(-1);
      graph[i].setKnown(false);
    }
    graph[source].setDepth(0);
    cout<<source<<endl;
    for (int currentDepth = 0; currentDepth <= size; currentDepth++ )
    {
      for (int i = 0; i <= size; i++) //counting up maybe?
      {
        if (!graph[i].known() && graph[i].getDepth() == currentDepth)
        {
          graph[i].setKnown(true);
          for (auto& it : graph[i])
          {
            if (graph[it].getDepth() == -1)
            {
              graph[it].setDepth(currentDepth+1);

              cout<<it<<endl;
            }
          }
        }
      }
    }
  }*/

  void DFS( int source )
  {
    for (int i = 0; i <= size; i++)
    {
      graph[i].setKnown(false);
    }
    recursiveDFS(source);
  }
  void recursiveDFS( int source )
  {
    cout<<source<<endl;
    graph[source].setKnown(true);
    for(auto& it : graph[source])
    {
      if (!graph[it].known())
      {
        recursiveDFS(it);
      }
    }
  }
  void print()
  {
    for (int i = 0; i <= size; i++)
    {
      cout<<i<<':';
      for (auto& it : graph[i])
      {
        cout<<' '<<it;
      }
      cout<<endl;
    }
  }
private:
  int size;
  bigV<int>* graph;

  //seems to work well
  int initSize(char* filename)
  {
    ifstream fin;
    fin.open(filename);
    if(fin.is_open())
    {
      //get the size first. minimize resizing
      fin.seekg(-1, ios_base::end);
      char ch;
      int loop = 0;
      while(loop<3)
      {
        fin.get(ch);

        if((int)fin.tellg() <= 1)
        {
          fin.seekg(0);
          loop = false;
        }
        else if (ch == ',')
        {
          loop++;
          if (loop < 3)
            fin.seekg(-2, ios_base::cur);
        }
        else
        {
          fin.seekg(-2, ios_base::cur);
        }
      }
      string line;
      getline(fin, line, ',');
      return stoi(line);
    }
    else
    {
      cout<<"Cannot open file!\n";
      return 0;
    }
  }

  void testWrite()
  {
    /*int overlord=0;
    for(int i = 0; i <= size; i++)
    {

      for (auto& it : graph[i])
      {
        overlord++;
      }
    }
    cout<<"Size: "<<size<<endl<<"Total Nodes: "<<overlord<<endl;
    cout<<"AVG Nodes: "<<overlord/size<<endl;
  }*/
  for (int i = 0; i <= size; i++)
  {
    for(auto&it : graph[i])
    {
      cout<<i<<','<<it<<',';
    }
  }
  }
};
