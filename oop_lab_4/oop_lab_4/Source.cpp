
//#include "stdafx.h"
#include "Fibonacci.h"
#include<algorithm>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
void main()
{
	
	//Fibonacci<string> one(10, "afr", "" );
		Fibonacci<int> f(10);
		for (Fibonacci<int>::const_iterator iter = f.cbegin(); iter != f.cend(); ++iter)
			cout << *iter << endl;
		/*for (int i = 0; i < one.size(); i++) 
			cout << one.at(i) << " ";*/
		
		system("pause");
		//cout << "Input x: " << endl;
	//int x = 0;
	//cin >> x;

	//Fibonacci<int> fib = Fibonacci<int>(5);
	//vector<string> vect = vector<string>();

	//for (Fibonacci<int>::const_iterator iter = fib.cend() - x; iter != fib.cbegin() + x; iter -= 1)
	//{
	//	cout<<(*iter);
	//}

	
}