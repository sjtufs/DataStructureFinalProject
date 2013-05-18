#include <iostream>
#include <cstdio>
#include <string>
#include "HashMap.h"
using namespace std;

class Hashint
{
public:
	static int hashCode(string obj) { return obj.size(); }
};

typedef HashMap<string,string,Hashint> hashmap;

/*
void print(hashmap a)
{
	hashmap::Iterator itr = a.iterator();
	hashmap::Entry e;
	cout << "Itr:    ";
	try
	{
	for (int i=0; i<a.size();++i)
	 {
		e = itr.next();
		cout << "key: " << e.getKey() << " value: " << e.getValue() << " ";
	 }
	}
	catch (ElementNotExist error) { cout<< "wrong size!!!"<< endl;}
	cout << "   empty = " ;
	if (a.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;

	hashmap b(a);
	itr = b.iterator();
	cout << "copy:   ";
	try
	{
	 while (1)
	  {
		e = itr.next();
		cout << "key: " << e.getKey() << " value: " << e.getValue() << " ";
	  }
	}
	catch (ElementNotExist error) {}
	cout << "   empty = " ;
	if (b.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;

	hashmap c=a;
	itr = c.iterator();
	cout << "opr=:   ";
	try
	{
	 while (1)
	  {
		e = itr.next();
		cout << "key: " << e.getKey() << " value: " << e.getValue() << " ";
	  }
	}
	catch (ElementNotExist error) {}
	cout << "   empty = " ;
	if (c.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;

}
*/
int main()
{
	string command;
	char ch;
	string x,y,z;
	hashmap a;
	hashmap::Iterator itr ;//= a.iterator();
	while (1)
	{
	try
	 {
	 	cout << endl;
	 	cin >> command;
	 	if (command == "add")
	 	 {
	 	 	cin >> x >> y;
	 	 	a.put(x,y);
	 	 }
	 	else if (command=="clear")
	 	 a.clear();
	 	else if (command=="get")
	 	 {
	 	 	cin >> x;
	 	 	cout << "value= " << a.get(x) << endl;
	 	 }
	 	else if (command=="containskey")
	 	 {
	 	 	cin >> x;
	 	 	if (a.containsKey(x))
	 	 	 cout << "yes" << endl;
	 	 	else
	 	 	 cout << "no" << endl;
	 	 }
	 	else if (command=="containsvalue")
	 	 {
	 	 	cin >> x;
	 	 	if (a.containsValue(x))
	 	 	 cout << "yes" << endl;
	 	 	else
	 	 	 cout << "no" << endl;
	 	 }
	 	else if (command=="remove")
	 	 {
	 	 	cin >> x ;
	 	 	a.remove(x);
	 	 }

	 	//print(a);

	  }
	 //catch (AllocationFailure error) { cout << error.getMessage() << endl; }
	 catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	}

	return 0;
}

