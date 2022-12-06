
#include <algorithm>
#include <cstddef>
#include <exception>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <set>
#include <map>


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


template<typename T>
void printVector(vector<T> v){
	for(T t:v){
		cout << t << ", ";
	}
	cout << endl;
}


template<typename T>
set<T> vecToSet(vector<T> v){
	set<T> result;
	for(T t: v){
		result.insert(t);
	}
	return result;
}

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


