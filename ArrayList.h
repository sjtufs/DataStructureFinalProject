#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include<memory.h>
#include "Utility.h"

/*
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list, 
 * where it means the length of the array of your internal implemention.
 * The iterator iterates in the order of the elements being loaded into this list
 */

template<class T>
class ArrayList
	{
	private:
		int capacity,nowSize;
		T **data;
	public:
		class Iterator
			{
			private:
				ArrayList<T> *array;
				int pos;
			public:
				Iterator(ArrayList<T> *array,int pos=-1):array(array),pos(pos) {}
				
				/*
				 * Returns true if the iteration has more elements. 
				 */
				bool hasNext()
					{
					return pos<array->size()-1;
					}
				
				/*
				 * Returns the next element in the iteration. 
				 * Exception : ElementNotExist
				 */
				const T& next()
					{
					if(!hasNext()) throw ElementNotExist();
					pos++;
					return array->get(pos);
					}
				
				/*
				 * Removes from the underlying collection the last element returned by the iterator.
				 * Exception : ElementNotExist
				 */
				void remove()
					{
					if(pos>=array->size||pos==-1) throw ElementNotExist();
					array->remove(pos);
					pos=-1;
					}
			};

		class constIterator
			{
			private:
				const ArrayList<T> *array;
				int pos;
			public:
				constIterator(const ArrayList<T> *array,int pos=-1):array(array),pos(pos) {}
				
				/*
				 * Returns true if the iteration has more elements. 
				 */
				bool hasNext()
					{
					return pos<array->size()-1;
					}
				
				/*
				 * Returns the next element in the iteration. 
				 * Exception : ElementNotExist
				 */
				const T& next()
					{
					if(!hasNext()) throw ElementNotExist();
					pos++;
					return array->get(pos);
					}
				
			};
		
		/*
		 * Constructs an empty array list (with an initial capacity of 100).
		 */
		ArrayList()
			{
			capacity=100;
			nowSize=0;
			data=new T*[capacity];
			}
		
		/*
		 * Destructor
		 */
		~ArrayList()
			{
			clear();
			if(data) delete []data;
			}

		/*
		 *  Assignment operator 
		 */
		ArrayList& operator=(const ArrayList &array)
			{
			clear();
			for(int i=0;i<array.size();i++) add(array.get(i));
			return *this;
			}
		
		/*
		 * Copy-constructor 
		 */
		ArrayList(const ArrayList &array)
			{
			capacity=array.size()*2;
			if(capacity<100) capacity=100;
			data=new T*[capacity];
			for(int i=0;i<array.size();i++) add(array.get(i));
			}
		
		/*
		 * Appends the specified element to the end of this list.
		 */
		bool add(const T& element)
			{
			if(nowSize==capacity) makeSpace(capacity*2);
			data[nowSize++]=new T(element);
			return true;
			}
		
		/*
		 * Inserts the specified element to the specified position in this list.
		 * The range of index parameter is [0, size],
		 * where index=0 means inserting to the head,
		 * and index=size means appending to the end.
		 * Exception : IndexOutOfBound
		 */
		void add(int index,const T &element)
			{
			if(index>size||index<0) throw IndexOutOfBound();
			if(nowSize==capacity) makeSpace(capacity*2);
			memmove(data+index+1,data+index,(nowSize-index)*sizeof(T));
			nowSize++;
			data[index]=new T(element);
			}

		/*
		 * Removes all of the elements from this list.
		 */
		void clear()
			{
			while(nowSize) delete data[--nowSize];
			}
		
		/*
		 * Returns true if this list contains the specified element.
		 */
		bool contains(const T &element) const
			{
			for(int i=0;i<nowSize;i++)
				if(data[i]==element) return true;
			return false;
			}
		
		/*
		 * Returns a const reference to the element at the specified position in this list.
		 * The index is zero-based, with range [0, size). 
		 * Exception : IndexOutOfBound
		 */
		T& get(int index)
			{
			if(index>=nowSize||index<0) throw IndexOutOfBound();
			return *data[index];
			}

		/*
		 *Returns true if this list contains no elements.
		 */
		bool isEmpty() const {return nowSize==0;}
		
		/*
		 * Returns an iterator over the elements in this list. 
		 */
		Iterator iterator()
			{
			return Iterator(this,-1);
			}
		
		/*
		 * Returns a const iterator over the elements in this list.
		 */
		constIterator ConstIterator() const
			{
			return constIterator(this,-1);
			}

		/*
		 * Removes the element at the specified position in this list. The index is zero-based, 
		 * with range [0, size). 
		 * Exception : IndexOutOfBound
		 */
		void remove(int index)
			{
			if(index>=size||index<0) throw IndexOutOfBound();
			delete data[index];
			nowSize--;
			memmove(data+index,data+index+1,(nowSize-index)*sizeof(T));
			}
		
		/*
		 * Removes the first occurrence of the specified element from this list, if it is present.
		 * Returns true if it is present in the list, otherwise false. 
		 */
		bool remove(const T &element)
			{
			int index=getIndex(element);
			if(index==-1) return false;
			remove(index);
			return true;
			}
		
		/*
		 * Replaces the element at the specified position in this list with the specified element. 
		 * The index is zero-based, with range [0, size). 
		 * Exception : IndexOutOfBound
		 */
		void set(int index,const T &element)
			{
			if(index>=nowSize||index<0) throw IndexOutOfBound();
			*data[index]=element;
			}

		/*
		 * Returns the number of elements in this list. 
		 */
		int size() const {return nowSize;}

		/*
		 * Increases the capacity of this list to newCapacity.
		 */
		void makeSpace(int newCapacity)
			{
			if(capacity>=newCapacity) return;
			capacity=newCapacity;
			T **tmp=new T*[capacity];
			memcpy(tmp,data,nowSize*sizeof(T));
			delete []data;
			data=tmp;
			}

		/*
		 * Returns the index of the first appearence of the specified element.
		 */
		int getIndex(const T &element) const
			{
			for(int i=0;i<nowSize;i++)
				if(*data[i]==element) return i;
			return -1;
			}	
	};
#endif
