#include <iostream>
#include <cstdio> 
#include <string>
#include "TreeMap.h"
using namespace std;

void printEntry(TreeMap<string,string>::Entry e)
{
	cout << " k= " << e.getKey() << " v= " << e.getValue();
}

void print(TreeMap<string,string> &a)
{
	cout << "Iterator:         ";
	TreeMap<string,string>::Iterator itr=a.iterator();
	while (itr.hasNext()) printEntry(itr.next());//cout << ' ' << itr.next();
	cout << "   empty = " ;
	if (a.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;
	
	TreeMap<string,string> b=a;
	cout << "Operator=         ";
	itr=b.iterator();
	while (itr.hasNext()) printEntry(itr.next());//cout << ' ' << itr.next();
	cout << "   empty = " ;
	if (b.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;
	
	TreeMap<string,string> c(a);
	cout << "Copy-constructor  ";
	itr=c.iterator();
	while (itr.hasNext()) printEntry(itr.next());//cout << ' ' << itr.next();
	cout << "   empty = " ;
	if (c.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;
}

int main()
{
	string command;
	char ch;
	string x,y,z;
	TreeMap<string,string> a;
	TreeMap<string,string>::Iterator itr ;
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
	 	
	 	print(a);
	 	
	  }
	 catch (AllocationFailure error) { cout << error.getMessage() << endl; }
	 catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	}
	
	return 0;
}

