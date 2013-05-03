#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "Utility.h"
#include <memory.h>

/**
 * The ArrayList is just like vector in C++.
 * You should know that "capacity" here doesn't mean how many elements are now in this list,it means
 * the length of the host of your inner implemention
 * For example,even if the capacity is 10,the method "isTmpty()" may still return true.
 * The iterator iterates in the order of the elements being loaded into this list
 */
template <class T>
class ArrayList
    {
    private:
        int capacity,nowSize;
        T **data;

        class Iterator
            {
            private:
                ArrayList<T> *host;
                int position;
            public:
                /**
                *Returns true if the iteration has more elements.
                 */
                bool hasNext() {
                    return position<host->size()-1;
                }

				/**
				 * Returns the next element in the iteration.
				 * @throw ElementNotExist exception when hasNext() == false
				 */
                T& next() {
                    if (!hasNext()) throw ElementNotExist();
                    return host->get(++position);
                }

                /**
				 * Removes from the underlying collection the last element
			     * returned by the iterator
			     * The behavior of an iterator is unspecified if the underlying
			     * collection is modified while the iteration is in progress in
			     * any way other than by calling this method.
			     * @throw ElementNotExist
			     */
				void remove()
                    {
                    if (position==-1||position>=host->size()) throw ElementNotExist();
                    host->removeIndex(position);
                    position=-1;
                    }

                Iterator(ArrayList <T> *host,int position=-1)
                    : host(host),position(position) {}
            };
		
	public:
        /**
         * Constructs an empty array list with an initial capacity of 1000.
         */
        ArrayList()
            {
            capacity=1000;
            nowSize=0;
            data=new T*[capacity];
            }

        /**
         * Destructor
         */
        ~ArrayList()
            {
            clear();
            delete []data;
            }

        /**
         * Assignment operator
         */
        ArrayList& operator=(const ArrayList& x)
            {
            clear();
            for (int i=0;i<x.size();i++) add(x.get(i));
            return *this;
            }

        /**
         * Copy-constructor
         */
        ArrayList(const ArrayList& x)
            {
            capacity=x.size()*2;
            data=new T*[capacity];
            for (int i=0;i<x.size();i++)
                add(x.get(i));
            }

		/**
         * Appends the specified element to the end of this list.
		 * Always returns true.
         */
        bool add(const T &e)
            {
            if (nowSize==capacity)
                ensureCapacity(capacity*2);
            data[nowSize++]=new T(e);
            return true;
            }

		/**
		 * Inserts the specified element to the specified position in this list.
		 * The range of index parameter is [0, size], where index=0 means inserting to the head,
		 * and index=size means appending to the end.
		 * @throw IndexOutOfBound
		 */
		void add(int index,const T &element)
            {
            if (index<0||index>nowSize) throw IndexOutOfBound();
            if (nowSize==capacity) ensureCapacity(capacity*2);
            memmove(data+index+1,data+index,(nowSize-index)*sizeof(T));
            nowSize++;
            data[index]=new T(element);
            }

		/**
		 * Removes all of the elements from this list.
         */
        void clear()
            {
            while (nowSize) delete data[--nowSize];
            }

		/**
         * Returns true if this list contains the specified element.
         */
        bool contains(const T &e) const
            {
            for (int i=0;i<nowSize;i++)
                if (*data[i]==e) return true;
            return false;
            }

		/**
		 * Returns a const reference to the element at the specified position in this list.
		 * The index is zero-based, with range [0, size).
		 * @throw IndexOutOfBound
		 */
		const T& get(int index) const
            {
            if (index<0||index>=nowSize) throw IndexOutOfBound();
            return *data[index];
            }

		/**
         * Returns true if this list contains no elements.
         */
        bool isTmpty() const {return nowSize==0;}

		/**
		 * Removes the element at the specified position in this list.
		 * The index is zero-based, with range [0, size).
		 * @throw IndexOutOfBound
		 */
		T removeIndex(int index)
            {
            if (index<0||index>=nowSize) throw IndexOutOfBound();
            T r=*data[index];
            delete data[index];
            nowSize--;
            memmove(data+index,data+index+1,(nowSize-index)*sizeof(T));
            return r;
            }

		/**
		 * Removes the first occurrence of the specified element from this list, if it is present.
		 * Returns true if it was present in the list, otherwise false.
		 */
		bool remove(const T &e)
            {
            int index=indexOf(e);
            if (index==-1) return false;
            removeIndex(index);
            return true;
            }

		/**
		 * Replaces the element at the specified position in this list with the specified element.
		 * The index is zero-based, with range [0, size).
		 * @throw IndexOutOfBound
		 */
		T& set(int index,const T &e)
            {
            if (index<0||index>=nowSize) throw IndexOutOfBound();
            return *data[index]=e;
            }

		/**
         * Returns the number of elements in this list.
         */
        int size() const {return nowSize;}

		/**
         * Returns an iterator over the elements in this list in proper sequence.
         */
        Iterator iterator()
            {
            return Iterator(this,-1);
            }

        /**
         * Increases the capacity of this ArrayList instance,if necessary,to ensure that it can hold at least the number of elements specified by the minimum capacity argument.
         */
        void ensureCapacity(int newCapacity)
            {
            capacity=newCapacity;
            T **tmp=new T*[capacity];
            memcpy(tmp,data,nowSize*sizeof(T));
            delete []data;
            data=tmp;
            }

        /**
         * Returns the index of the first occurrence of the specified element in this list,or -1 if this list does not contain the element.
         */
        int indexOf(const T &e) const
            {
            for (int i=0;i<nowSize;i++)
                if (*data[i]==e) return i;
            return -1;
            }
    };
#endif

