#ifndef _RWAY_TRIE_H_
#define _RWAY_TRIE_H_
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using std::vector;
using std::shared_ptr;
using std::string;

// Specially designed for lower case alphabets [a-z] [0-26] 
template <class T>
class Node {
	T dValue;
	vector<shared_ptr<Node>> dNext;
public:
	Node(T xT) : dValue(xT), dNext(26) {
		std::fill_n(std::begin(dNext), 26, nullptr);
	}
	shared_ptr<Node> mGetNodePtr(char xT) const { return dNext.at(xT - 'a'); }
	void mSetNodePtr(char xT, shared_ptr<Node> xPtr) { dNext.at(xT - 'a') = xPtr; }
	T mGetValue() const { return dValue; }
	void mSetValue(T xT) { dValue = xT; }
	vector<shared_ptr<Node>> mGetArr() const { return dNext; }
};

template <class T>
class RWayTrie {
	shared_ptr<Node<T>> dRoot = nullptr;
	using root = shared_ptr<Node<T>>;
	root _mGetKey(root xPtr, string xKey, size_t xPos);
	root _mPutKey(root xPtr, string xKey, size_t xPos, T xVal);
	root _mDeleteKey(root xPtr, string xKey, size_t xPos);
	void _mPrint(shared_ptr<Node<T>> xPtr);
public:
	RWayTrie(T xT):dRoot(std::make_shared<Node<T>>(xT)) {}
	shared_ptr<Node<T>> mGetRootPtr() const { return dRoot; }
	T mGetKey(string xKey);
	void mPutKey(string xKey, T xVal);
	void mDeleteKey(string xKey);
	void mPrint();
};

#endif