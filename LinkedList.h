#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"
#include<memory.h>

/*
 * A  linked list.
 * The iterator iterates in the order of the elements being loaded into this list.
 */

template<class T1,class T2>
void appendAll(T1 &v1,const T2 &v2)
	{
	typename T2::Iterator tmp=v2.Iterator();
	while(tmp.hasNext) v1.add(tmp.next());
	}

template<class T>
class LinkedList
	{
	public:
		struct Node
			{
			Node *pre,*next;
			T *data;
			
			Node():pre(NULL),next(NULL) {}
			
			Node(const T &element):pre(NULL),next(NULL)
				{
				data=new T(element);
				}
			
			~Node()
				{
				if(data) delete []data;
				data=NULL;
				}

			void insert(const T &element)
				{
				Node *tmp=new Node(element);
				tmp->pre=this;
				tmp->next=this->next;
				if(tmp->next) tmp->next->pre=tmp;
				this->next=tmp;
				}
			};
	
	private:
		Node *head,*last;
		int nowSize;
	
	public:
		class Iterator
			{
			private:
				LinkedList<T> *list;
				Node *pos;
			public:
				Iterator():pos(NULL) {}
				Iterator(Node *pos,LinkedList<T> *list):pos(pos),list(list) {}

				/*
				 * Returns true if the iteration has more elements. 
				 */
				bool hasNext()
					{
					if(pos==NULL||pos->next==NULL) return false;
					return true;
					}

				/*
				 * Returns the next element in the iteration. 
				 */
				const T& next()
					{
					if(pos==NULL||pos->next==NULL) throw ElementNotExist();
					pos=pos->next;
					return *(pos->data);
					}

				/*
				 * Removes from the underlying collection the last element returned by the iterator
				 */
				void remove()
					{
					if(pos==NULL||pos->data==NULL) throw ElementNotExist();
					if(pos==list->last) list->last=pos->pre;
					Node *tmp=pos->pre;
					tmp->next=pos->next;
					if(tmp->next) tmp->next->pre=tmp;
					delete pos;
					pos=NULL;
					list->nowSize--;
					}
			};
		

		class constIterator
			{
			private:
				LinkedList<T> *list;
				Node *pos;
			public:
				constIterator():pos(NULL) {}
				constIterator(Node *pos,LinkedList<T> *list):pos(pos),list(list) {}

				/*
				 * Returns true if the iteration has more elements. 
				 */
				bool hasNext()
					{
					if(pos==NULL||pos->next==NULL) return false;
					return true;
					}

				/*
				 * Returns the next element in the iteration. 
				 */
				const T& next()
					{
					if(pos==NULL||pos->next==NULL) throw ElementNotExist();
					pos=pos->next;
					return *(pos->data);
					}
			};

		/*
		 * constructs an empty list
		 */
		LinkedList()
			{
			head=last=new Node();
			head->pre=head;
			nowSize=0;
			}
		/*
		 * Copy-constructor
		 */
		LinkedList(const LinkedList<T> &list)
			{
			head=last=new Node();
			nowSize=0;
			head->pre=head;
			appendAll(*this,list);
			}
		/*
		 * Destructor
		 */
		~LinkedList()
			{
			clear();
			delete head;
			}
		
		LinkedList<T>& operator=(const LinkedList<T> &list)
			{
			this->clear();
			appendAll(*this,c);
			return *this;
			}

		/*
		 * Appends the specified element to the end of this list. 
		 */
		bool add(const T &element)
			{
			last->insert(element);
			while(last->next) last=last->next;
			nowSize++;
			return true;
			}
		
		/*
		 * Inserts the specified element to the specified position in this list. 
		 * The range of index parameter is [0, size], 
		 * where index=0 means inserting to the head, and index=size means appending to the end. 
		 */
		void add(int index,const T &element)
			{
			Node *tmp=head;
			for(int i=0;i<index;i++) tmp=tmp->next;
			tmp->insert(element);
			while(last->next) last=last->next;
			nowSize++;
			}

		/*
		 * Inserts the specified element to the beginning of this list. 
		 */
		void addFirst(const T &element)
			{
			head->insert(element);
			while(last->next) last=last->next;
			nowSize++;
			}
		
		/*
		 * Insert the specified element to the end of this list.
		 * Equivalent to add. 
		 */
		void addLast(const T &element)
			{
			add(element);
			}
	
		/*
		 * Removes all of the elements from this list.
		 */
		void clear()
			{
			Node *tmp=head;
			while(tmp->next)
				{
				Iterator tmp(head,this);
				while(head->next)
					{
					tmp.next();
					tmp.remove();
					}
				last=head;
				nowSize=0;
				}
			}
		
		/*
		 * Returns true if this list contains the specified element. 
		 */
		bool contains(const T &element) const
			{
			Node *tmp=head;
			while(tmp->next)
				{
				tmp=tmp->next;
				if(*(tmp->data)==element) return true;
				}
			return false;
			}

		/*
		 * Returns a const reference to the element at the specified position in this list. 
		 * The index is zero-based, with range [0, size). 
		 */
		T& get(int index)
			{
			Node *tmp=head;
			for(int i=0;i<=index;i++)
				{
				tmp=tmp->next;
				if(!tmp) throw IndexOutOfBound();
				}
			return *(tmp->data);
			}

		/*
		 * Returns a const reference to the first element. 
		 */
		const T& getFirst() const
			{
			if(head->next==NULL) throw ElementNotExist();
			return *(head->next->data);
			}
		
		/*
		 * Returns a const reference to the last element. 
		 */
		const T& getLast() const
			{
			if(isEmpty()) throw ElementNotExist();
			return *(last->data);
			}

		/*
		 * Returns true if this list contains no elements. 
		 */
		bool isEmpty()
			{
			return (head==last);
			}

		/*
		 * Removes the element at the specified position in this list. 
		 * The index is zero-based, with range [0, size).
		 */
		void remove(int index)
			{
			if(index>=size||index<0) throw IndexOutOfBound();
			Node *tmp=head;
			for(int i=0;i<=index;i++) tmp=tmp->next;
			Iterator del(tmp,this);
			del.remove();
			}

		/*
		 * Removes the first occurrence of the specified element from this list,if it is present. 
		 * Returns true if it is present in the list, otherwise false. 
		 */
		bool remove(const T &element)
			{
			Node *tmp=head;
			while(tmp->head)
				{
				tmp=tmp->next;
				if(*(tmp->data)==element)
					{
					Iterator del(tmp,this);
					del.remove();
					return true;
					}
				}
			return false;
			}

		/*
		 * Removes the first element from this list. 
		 */
		void removeFirst()
			{
			if(isEmpty()) throw ElementNotExist();
			Iterator del(head,this);
			del.remove();
			}

		/*
		 * Removes the last element from this list. 
		 */
		void removeLast()
			{
			if(isEmpty()) throw ElementNotExist();
			Iterator del(last,this);
			del.remove();
			}
		
		/*
		 * Replaces the element at the specified position in this list with the specified element.
		 * The index is zero-based, with range [0, size). 
		 */
		void set(int index,const T &element)
			{
			Node *tmp=head;
			for(int i=0;i<=index;i++) 
				{
				tmp=tmp->next;
				if(!tmp) throw IndexOutOfBound();
				}
			*(tmp->data)=element;
			}

		/*
		 * Returns the number of elements in this list. 
		 */
		int size() const {return nowSize;}
	
		/*
		 * Returns an iterator over the elements in this list. 
		 */
		Iterator iterator()
			{
			return Iterator(head,this);
			}
	
	};

#endif
