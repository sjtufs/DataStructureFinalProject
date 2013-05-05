/** @file */
#ifndef __HASHMAP_H
#define __HASHMAP_H

#include "Utility.h"
#include "LinkedList.h"

/**
 * HashMap is a map implemented by hashing. Also, the 'capacity' here means the
 * number of buckets in your internal implemention, not the current number of the
 * elements.
 *
 * Template argument H are used to specify the hash function.
 * H should be a class with a static function named ``hashCode'',
 * which takes a parameter of type K and returns a value of type int.
 * For example, the following class
 * @code
 *      class Hashint {
 *      public:
 *          static int hashCode(int obj) {
 *              return obj;
 *          }
 *      };
 * @endcode
 * specifies an hash function for integers. Then we can define:
 * @code
 *      HashMap<int, int, Hashint> hash;
 * @endcode
 *
 * Hash function passed to this class should observe the following rule: if two keys
 * are equal (which means key1 == key2), then the hash code of them should be the
 * same. However, it is not generally required that the hash function should work in
 * the other direction: if the hash code of two keys are equal, the two keys could be
 * different.
 *
 * Note that the correctness of HashMap should not rely on the choice of hash function.
 * This is to say that, even the given hash function always returns the same hash code
 * for all keys (thus causing a serious collision), methods of HashMap should still
 * function correctly, though the performance will be poor in this case.
 *
 * The order of iteration could be arbitary in HashMap. But it should be guaranteed
 * that each (key, value) pair be iterated exactly once.
 */
template<class K,class V,class H>
class HashMap
	{
	private:
		LinkedList<Entry<K,V> > *list;
		int capacity,nowSize;
	
	public:
		class ConstIterator
			{
			private:
				HashMap<K,V,H> *host;
				const LinkedList<Entry<K,V> > *list;
				typename LinkedList<Entry<K,V> >::ConstIterator it;
				int capacity,position;

			public:
				bool hasNext()
					{
					if(host==NULL||host->size()==0) return false;
					if(position==-1||it.hasNext()) return true;
					for(int i=position+1;i<capacity;i++)
						if(!list[i].isEmpty()) return true;
					return false;
					}

				const Entry<K,V>& next()
					{
					if(host==NULL||host->size()==0) throw ElementNotExist();
					if(it.hasNext()) return it.next();
					if(position==-1)
						{
						while(list[++position].isEmpty());
						it=list[position].constIterator();
						return it.next();
						}
					throw ElementNotExist();
					}
				ConstIterator(int capacity=0,const LinkedList<Entry<K,V> > *list=NULL,const HashMap<K,V,H> *host=NULL)
					:capacity(capacity),position(-1),list(list),it(list[0].constIterator(),host(host)) {}
				
			};

		class Iterator
			{
			private:
				HashMap<K,V,H> *host;
				const LinkedList<Entry<K,V> > *list;
				typename LinkedList<Entry<K,V> >::Iterator it;
				int capacity,position;

			public:
				/**
				 * Returns true ifthe iteration has more elements
				 */
				bool hasNext()
					{
					if(host==NULL||host->size()==0) return false;
					if(position==-1||it.hasNext()) return true;
					for(int i=position+1;i<capacity;i++)
						if(!list[i].isEmpty()) return true;
					return false;
					}
				
				/**
				 * Returns the next element in the iteration.
				 * @throw ElementNotExist
				 */
				const Entry<K,V> next()
					{
					if(host==NULL||host->size()==0) throw ElementNotExist();
					if(it.hasNext()) return it.next();
					if(position==-1)
						{
						while(list[++position].isEmpty());
						it=list[position].constIterator();
						return it.next();
						}
					throw ElementNotExist();
					}
	
				ConstIterator(int capacity=0,const LinkedList<Entry<K,V> > *list=NULL,const HashMap<K,V,H> *host=NULL)
					:capacity(capacity),position(-1),list(list),it(list[0].constIterator(),host(host)) {}
				
			};


	};

#endif

