
#include <algorithm>
#include <cstddef>
#include <exception>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <set>
#include <map>
#include <list>


using namespace std;


vector<string> getLineList(string path);


/**
 * Takes a base state and a string list and operates the given function over each string,
 * while storing the state. Returns the final state. A state can be any type.
 *
 * @param base: the base state
 * @param f: any function with the signature T (T, string)
 * @param slist: string vector
 *
 * @return T result: final state after iteration
 */
template<typename T>
T runStateFunction(T base, function<T(T, string)> f, vector<string> slist){
	for (string s : slist) {
		base = f(base, s);
	}
	return base;
}


/**
 * Takes two arguments any type that is capable of the modulo-operator (%) and 
 * gives back the mathematically complete Modulo result a mod b.
 * If the type is not capable of the %-operator, it will simply return a.
 *
 * @param T a
 * @param T b
 *
 * @return T result
 */
template<typename T>
T modulo(T a, T b) {
	try {
		const T result = a % b;
		return result >= 0 ? result : result + b;
	} catch (exception e) {
		cout << e.what();
		return a;
	}
}

/**
 * Takes two vectors with the common element type T, and returns
 * a vector with common elements. This method is not optimized and 
 * does not remove duplicate commons.
 *
 * @param vector<T> v1
 * @param vector<T> v2
 *
 * @result vector<T> result
 */
template<typename T>
vector<T> getIntersect(vector<T> v1, vector<T> v2){
	vector<T> result;
	for(size_t i=0; i<v1.size(); i++){
		if(find(v2.begin(), v2.end(), v1.at(i)) != v2.end()){
			result.push_back(v1.at(i));
		}
	}
	return result;	
}

/**
 * Takes a vector of the element type T and tries to print out 
 * its elements. If the element type does not support a cast to 
 * string, this method will fail.
 *
 * @param vector<T> v
 */
template<typename T>
void printVector(vector<T> v){
	for(T t:v){
		cout << static_cast<string>(t) << ", ";
	}
	cout << endl;
}

/**
 * Takes a vector of the element type T and converts it to 
 * a set of type T.
 *
 * @param vecto<T> v
 *
 * @return set<T> result
*/
template<typename T>
set<T> vecToSet(vector<T> v){
	set<T> result;
	for(T t: v){
		result.insert(t);
	}
	return result;
}

/*
 * Takes one iterable type V with element type E and returns 
 * if it has duplicate elements. Returns true if there is such
 * element, else false. Returns also true if the method fails for some 
 * reason.
 *
 * @param V<E> a 
 *
 * @return bool result
*/
template<typename V, typename E>
bool existsDupl(V v){
	try {
		map<E, int> m;	
		for(E e: v){
			if(m.find(e) == m.end()){
				m.insert({e,1});
			}
			else {
				return true;
			}
		}
		return false;
	} catch (exception e) {
		cout << e.what();
		return true;
	}
}


list<string> getLineListReally(string path);

void runLines(function<void(list<string>)> f, function<pair<list<string>, list<string>>(list<string>)> getNextLines, list<string> lines);


pair<list<string>, list<string>> getNextLine(list<string> lines);
