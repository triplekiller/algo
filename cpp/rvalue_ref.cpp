/*
 * =====================================================================================
 *
 *       Filename:  rvalue_ref.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/17/2015 10:13:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;

class A {
public:
	A() {}
	explicit A(int i) : data(i) {
		cout << "normal ctor" << endl;
		ptr = &data;
	}

	A(const A &a) {
		data = a.data;
		cout << "copy ctor" << endl;
		ptr = &data;
	}

#if 1
	// typical declaration of a move ctor
	A(A &&a) {
		cout << "move ctor" << endl;
		ptr = a.ptr;
		data = a.data;
		a.ptr = nullptr;
		a.data = 0;
	}
#endif

	// avoiding implicit move constructor
//	A(A &&a) = delete;
	// forcing a move constructor to be generated by the compiler
//	A(A &&a) = default;

	A operator+(const A &a) {
		A tmp(data+a.data);
		cout << "operator+ called" << endl;
		tmp.show();
		cout << endl;
		return tmp;
	}

	void show() const{
		cout << "ptr=" << ptr << " data=" << data << endl;
	}

private:
	int data;
	int *ptr;
};

int main()
{
	int i = 99;

	cout << "####" << endl;
	A a(10);
	a.show();

	cout << "####" << endl;
	A b(i);
	b.show();

	cout << "####" << endl;
	A c(b);
	c.show();

	cout << "####" << endl;
	A d(b+c);
	cout << "show d" << endl;
	d.show();

	return 0;
}
