#include <iostream>
#include <cstdio>
#include <string>
#include "ArrayList.h"
using namespace std;
/*
void print(ArrayList<string> a)
{
	for (int i=0;i<a.size();++i)
	 cout << a[i] << ' ';
	cout << endl;
}
*/
int main()
{
	string command;
	char ch;
	string x;
	long y,z;
	ArrayList<string> a,b;
	ArrayList<string>::Iterator itr= a.iterator();
	while (1)
	 {
	 	cin >> command;
	 	if (command == "add")
	 	 {
	 	 	cin >> x;
	 	 	try
	 	 	 {
	 	 	 	a.add(x);
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else if (command=="addindex")
	 	 {
	 	 	cin >> y >> x;
	 	 	try
	 	 	 {
	 	 	 	a.add(y,x);
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
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
	 	else if (command=="empty")
	 	 {
	 	 	if (a.isEmpty())
	 	 	 cout << "yes" << endl;
	 	 	else
	 	 	 cout << "no" << endl;
	 	 }
	 	else if (command=="removeindex")
	 	 {
	 	 	cin >> y ;
	 	 	try
	 	 	 {
	 	 	 	a.removeIndex(y);
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else if (command=="remove")
	 	 {
	 	 	cin >> x ;
	 	 	try
	 	 	 {
	 	 	 	if (a.remove(x)) cout << "success" << endl;
	 	 	 	else cout << "failed" << endl;
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else if (command=="set")
	 	 {
	 	 	cin >> y >> x;
	 	 	try
	 	 	 {
	 	 	 	a.set(y,x);
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else if (command=="new")
	 	 {
	 	 	try
	 	 	 {
	 	 	 	itr = a.iterator();
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else if (command=="hasnext")
	 	 {
	 	 	try
	 	 	 {
	 	 	 	cout << ((itr.hasNext())?"yes":"no") << endl;
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else if (command=="next")
	 	 {
	 	 	try
	 	 	 {
	 	 	 	cout << (itr.next()) << endl;
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else if (command=="removeitr")
	 	 {
	 	 	try
	 	 	 {
	 	 	 	itr.remove();
	 	 	 }
	 	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	 }
	 	else
	 	 {
	 	 	cout << "Illegal command!!" << endl;
	 	 }
/*	 	print(a);
	 	try
	 	 {
	 	 	cout << "itr:  " << (*itr) << endl;
	 	 }
	 	catch (IndexOutOfBound error) { cout << error.getMessage() << endl; }
	 	catch (ElementNotExist error) { cout << error.getMessage() << endl; }
	 	*/
	 }

	return 0;
}

