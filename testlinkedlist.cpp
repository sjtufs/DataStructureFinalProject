#include <iostream>
#include <cstdio>
#include <string>
#include "LinkedList.h"
using namespace std;

void print(LinkedList<string> a)
{
	cout << "Get & Size:           ";
	for (int i=0; i<a.size(); ++i)
	 cout << ' ' << a.get(i);
	cout << endl;

	cout << "Iterator:             ";
	LinkedList<string>::Iterator itr=a.iterator();
	while (itr.hasNext()) cout << ' ' << itr.next();
	cout << "   empty = " ;
	if (a.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;

	cout << "Operator= <G&S>       ";
	LinkedList<string> b=a;
	for (int i=0; i<b.size(); ++i)
	 cout << ' ' << b.get(i);
	cout << endl;

	cout << "Operator= <ITR>       ";
	itr=b.iterator();
	while (itr.hasNext()) cout << ' ' << itr.next();
	cout << "   empty = " ;
	if (b.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;

	cout << "Operator= <G&S>       ";
	LinkedList<string> c(a);
	for (int i=0; i<c.size(); ++i)
	 cout << ' ' << c.get(i);
	cout << endl;

	cout << "Copy-constructor <ITR>";
	itr=c.iterator();
	while (itr.hasNext()) cout << ' ' << itr.next();
	cout << "   empty = " ;
	if (c.isEmpty())
	 cout << "yes" << endl;
	else
	 cout << "no" << endl;

	cout << "Get First:  " << a.getFirst() << "\nGet Last:   " << a.getLast() << endl;
}

int main()
{
	string command;
	char ch;
	string x;
	long y,z;
	LinkedList<string> a,b;
	LinkedList<string>::Iterator itr ;//= a.iterator();
	while (1)
	{
	try
	 {
	 	cout << endl;
	 	cin >> command;
	 	if (command == "add")
	 	 {
	 	 	cin >> x;
	 	 	a.add(x);

	 	 }
	 	else if (command=="addfirst")
	 	 {
	 	 	cin >> x;
	 	 	a.addFirst(x);
	 	 }
	 	else if (command=="addlast")
	 	 {
	 	 	cin >> x;
	 	 	a.addLast(x);
	 	 }
	 	else if (command=="addindex")
	 	 {
	 	 	cin >> y >> x;
	 	 	a.add(y,x);
	 	 }
	 	else if (command=="clear")
	 	 a.clear();
	 	else if (command=="contains")
	 	 {
	 	 	cin >> x;
	 	 	if (a.contains(x))
	 	 	 cout << "yes" << endl;
	 	 	else
	 	 	 cout << "no" << endl;
	 	 }
	 	else if (command=="removeindex")
	 	 {
	 	 	cin >> y ;
	 	 	a.removeIndex(y);
	 	 }
	 	else if (command=="removefirst")
	 	 a.removeFirst();
	 	else if (command=="removelast")
	 	 a.removeLast();
	 	else if (command=="remove")
	 	 {
	 	 	cin >> x ;
	 	 	if (a.remove(x)) cout << "success" << endl;
	 	 	else cout << "failed" << endl;
	 	 }
	 	else if (command=="set")
	 	 {
	 	 	cin >> y >> x;
	 	 	a.set(y,x);
	 	 }
	 	else if (command=="new")
	 	 itr = a.iterator();
	 	else if (command=="hasnext")
	 	 cout << ((itr.hasNext())?"yes":"no") << endl;
	 	else if (command=="next")
	 	 cout << (itr.next()) << endl;
	 	else if (command=="removeitr")
	 	 itr.remove();
	 	 else if (command=="get")
	 	 {
	 	 	cin >> y;
	 	 	try
	 	 	 {
	 	 	 	cout << a.get(y) << endl;
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else
	 	 cout << "Illegal command!!" << endl;

	 	//print(a);

	 	//cout << "itr:  " << (*itr) << endl;
	  }
	 catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	}

	return 0;
}

