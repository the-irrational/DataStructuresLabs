#include <utility>
template <typename Object>
class myDlList
{
	private:
		struct Node
		{
			Object data;
			Node *prev;
			Node *next;
			
			Node (const Object & d = Object{ }, Node * p = nullptr, Node * n = nullptr) : data {d}, prev {p}, next {n} { }
			
			Node (Object && d, Node * p = nullptr, Node * n = nullptr) : data {std::move(d)}, prev {p}, next {n} { }
		};
		
	public:
		class const_iterator
		{
			public:
				const_iterator() : current {nullptr} 
					{ }
				
				const Object & operator* () const
					{ return retrieve(); }
				
				const_iterator & operator++ ()
				{
					current = current->next;
					return *this;
				}
				
				const_iterator operator++ (int)
				{
					const_iterator old = *this;
					++(*this);
					return old;
				}
				
				const_iterator operator-- ()
				{
					current = current->prev;
					return *this;
				}
				
				const_iterator operator-- (int)
				{
					const_iterator old = *this;
					--(*this);
					return old;
				}
				
				bool operator== (const const_iterator & rhs) const
					{ return current == rhs.current; }
				bool operator!= (const const_iterator & rhs) const
					{ return !(*this == rhs); }
					
				protected:
					Node *current;
					
					Object & retrieve() const
						{ return current->data; }
					
					const_iterator(Node *p) : current {p}
						{ }
					
					friend class myDlList<Object>;
		};
		
		class iterator : public const_iterator
		{
			public:
				iterator()
					{ }
				
				Object & operator* ()
					{ return const_iterator::retrieve(); }
				const Object & operator* () const
					{ return const_iterator::operator*(); }
				
				iterator & operator++ ()
				{
					this->current = this->current->next;
					return *this;
				}
				
				iterator operator++ (int)
				{
					iterator old = *this;
					++(*this);
					return old;
				}
				
				iterator operator-- ()
				{
					this->current=this->current->prev;
					return *this;
				}
				
				iterator operator-- (int)
				{
					iterator old = *this;
					--(*this);
					return old;
				}
				
			protected:
				iterator(Node *p) : const_iterator{ p }
					{ }
					
				friend class myDlList<Object>;
		};
		
	public:
		myDlList()
			{ init(); }
		
		myDlList(const myDlList & rhs)
		{
			init();
			for (auto & x : rhs)
			{
				push_back(x);
			}
		}
		
		~myDlList()
		{
			clear();
			delete head;
			delete tail;
		}
		
		myDlList & operator= (const myDlList & rhs)
		{
			myDlList copy = rhs;
			std::swap(*this, copy);
			return *this;
		}
		
		myDlList(myDlList && rhs) : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
		{
			rhs.theSize = 0;
			rhs.head = nullptr;
			rhs.tail = nullptr;
		}
			
		myDlList<Object> appendList(myDlList<Object> & data)
		{
			for ( auto i = data.begin(); i != data.end(); ++i)
			{
				push_back(*i);
			}
			
			/*for (auto & i : data)
			{
				push_back(i);
			}*/
			
			return *this;
		}
		
		myDlList & operator= (myDlList && rhs)
		{
			std::swap(theSize, rhs.theSize);
			std::swap(head, rhs.head);
			std::swap(tail, rhs.tail);
			
			return *this;
		}
		
		
		iterator begin()
			{ return { head->next }; }
		const_iterator begin() const
			{ return { head->next }; }	
		iterator end()
			{ return { tail }; }
		const_iterator end() const
			{ return { tail }; }
			
		int size() const
			{ return theSize; }
		bool empty() const
			{ return size() == 0; }
			
		void clear()
		{
			while(!empty())
				pop_front();
		}
		
		Object & front()
			{ return *begin(); }
		const Object & front() const
			{ return *begin(); }
		Object & back()
			{ return *--end(); }
		const Object & back() const
			{ return *--end(); }
		void push_front(const Object & x)
			{ insert(begin(), x); }
		void push_front(Object && x)
			{ insert(begin(), std::move(x)); }
		void push_back(const Object & x)
			{ insert(end(), x); }
		void push_back(Object && x)
			{ insert(end(), std::move(x)); }
		void pop_front()
			{ erase(begin()); }
		void pop_back()
			{ erase(--end()); }
			
		void reverselist()
		{
			Node *current = head;
			Node *prev = nullptr;
			Node *next = nullptr;
			tail = head;
			while (current != nullptr)
			{
				next = current->next;
				current->next = prev;
				current->prev = next;
				prev = current;
				current = next;
			}
			head = prev;
		}
			
		iterator insert( iterator itr, const Object & x )
		{
			Node *p = itr.current;
			Node *newNode = new Node{ x, p->prev, p };
			theSize++;
			//return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
			return ( p->prev = p->prev->next = newNode );
		}
		
		iterator insert(iterator itr, Object && x)
		{
			Node *p = itr.current;
			theSize++;
			return { p->prev = p->prev->next = new Node{ std::move(x), p->prev, p } };
		}
		
		iterator erase(iterator itr)
		{
			Node *p = itr.current;
			iterator retVal{ p->next };
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;
			theSize--;
			
			return retVal;
		}
		
		iterator erase(iterator from, iterator to)
		{
			for(iterator itr = from; itr != to; )
				itr - erase(itr);
				
			return to;
		}
		
	private:
		int theSize;
		Node *head;
		Node *tail;
		
		void init()
		{
			theSize = 0;
			head = new Node;
			tail = new Node;
			head->next = tail;
			tail->prev = head;
		}
};

