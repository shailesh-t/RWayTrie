#include "RWayTrie.h"
#include <iostream>
using std::begin;
using std::end;
using std::all_of;

using std::cout;

template <class T>
shared_ptr<Node<T>> RWayTrie<T>::_mGetKey(root xPtr, string xKey, size_t xPos)
{
	if (xPtr == nullptr) return nullptr;
	if (xPos == xKey.length()) return xPtr;
	char lX = xKey.at(xPos);
	return _mGetKey(xPtr->mGetNodePtr(lX), xKey, xPos + 1);
}

template <class T>
shared_ptr<Node<T>> RWayTrie<T>::_mPutKey(root xPtr, string xKey, size_t xPos, T xVal)
{
	if (xPtr == nullptr) xPtr = std::make_shared<Node<T>>(mGetRootPtr()->mGetValue());

	if (xPos == xKey.length()) { xPtr->mSetValue(xVal); return xPtr;}
	char lX = xKey.at(xPos);
	 xPtr->mSetNodePtr(lX, _mPutKey(xPtr->mGetNodePtr(lX), xKey, xPos + 1, xVal));
	 return xPtr;
}

template <class T>
shared_ptr<Node<T>> RWayTrie<T>::_mDeleteKey(root xPtr, string xKey, size_t xPos)
{
	if (xPtr == nullptr) return nullptr;

	if (xPos == xKey.length()) 
	{
		xPtr->mSetValue(mGetRootPtr()->mGetValue()); 
		auto lPt = xPtr->mGetArr();
		if ((xPtr->mGetValue() == mGetRootPtr()->mGetValue())&&(all_of(begin(lPt), end(lPt), [](auto x) {return x == nullptr;})))
			return nullptr;
		else
			return xPtr;
	}
	char lX = xKey.at(xPos);
	xPtr->mSetNodePtr(lX, _mDeleteKey(xPtr->mGetNodePtr(lX), xKey, xPos + 1));
	auto lPt = xPtr->mGetArr();
	if ((xPtr->mGetValue() == mGetRootPtr()->mGetValue()) && (all_of(begin(lPt),end(lPt), [](auto x) {return x == nullptr;})))
		return nullptr;
	else
		return xPtr;
}

template <class T>
T RWayTrie<T>::mGetKey(string xKey)
{
	shared_ptr<Node<T>> xPtr = _mGetKey(mGetRootPtr(), xKey, 0);
	if (xPtr)
		return xPtr->mGetValue();
	else
		return mGetRootPtr()->mGetValue();
}

template <class T>
void RWayTrie<T>::mPutKey(string xKey, T xVal)
{
	_mPutKey(mGetRootPtr(), xKey, 0, xVal);
}

template <class T>
void RWayTrie<T>::mDeleteKey(string xKey)
{
	_mDeleteKey(mGetRootPtr(), xKey, 0);
}

template <class T>
void RWayTrie<T>::_mPrint(shared_ptr<Node<T>> xPtr)
{
	if (xPtr == nullptr) return;
	size_t lCnt = 0;
	for (auto x : xPtr->mGetArr()) {
		if (x) {
			cout << char(lCnt + 'a') << '\n';
			_mPrint(x);
		}
		lCnt++;
	}
}

template <class T>
void RWayTrie<T>::mPrint()
{
	auto lPtr = mGetRootPtr();
	size_t lCnt = 0;
	for (auto x : lPtr->mGetArr()) {
		if (x) {
			cout << char(lCnt + 'a') << "\n";
			_mPrint(x);
			cout << "\n\n";
		}
		lCnt++;
	}
}

int main()
{
	RWayTrie<int> lTrie(-1);
	lTrie.mPutKey("hello", 2);
	lTrie.mPutKey("helllo", 2);
	lTrie.mPutKey("heo", 2);
	lTrie.mPutKey("shello", 2);
	lTrie.mPutKey("nhelots", 12);
	lTrie.mPutKey("sheello", 2);
	lTrie.mPutKey("nheloots", 2);
	cout<<lTrie.mGetKey("nhelots")<<'\n';
	lTrie.mPrint();
	lTrie.mDeleteKey("nhelots");
	cout << lTrie.mGetKey("nhelots") << '\n';
	lTrie.mPrint();
}