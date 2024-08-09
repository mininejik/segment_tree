#ifndef SEGMENT_TREE_INL
#define SEGMENT_TREE_INL
#include "segment_tree.h"
using namespace std;
template<class T>
void segment_tree<T>::bld(T* A, int l, int r, int pos)
{
    if (l > r) return;
    if (l == r) {
        vec[pos] = A[l];
        return;
    }
    int mid = (l + r) / 2;
    bld(A, l, mid, pos * 2);
    bld(A, mid + 1, r, pos * 2 + 1);
}
template<class T>
void segment_tree<T>::push(int pos)
{
    if (!check[pos]) return;
    O[pos * 2] = O[pos * 2 + 1] = O[pos];
    check[pos * 2] = check[pos * 2 + 1] = 1;
    check[pos] = 0;
    vec[pos * 2] = vec[pos * 2 + 1] = O[pos];
}
template<class T>
void segment_tree<T>::upd(int l, int r, int ml, int mr, int pos, T& val)
{
    if (l > mr || r < ml) return;
    if (ml >= l && mr <= r) {
        O[pos] = val;
        check[pos] = 1;
        vec[pos] = val;
        push(pos);
        return;

    }
    push(pos);
    int mid = (ml + mr) / 2;
    upd(l, r, ml, mid, pos * 2, val);
    upd(l, r, mid + 1, mr, pos * 2 + 1, val);
}
template<class T>
T& segment_tree<T>::get(int pos, int l, int r, int mpos)
{
    if (pos == l && pos == r) return vec[mpos];
    int mid = (l + r) / 2;
    push(mpos);
    if (pos >= l && pos <= mid) return get(pos, l, mid, mpos * 2);
    else return get(pos, mid + 1, r, mpos * 2 + 1);
}
template<class T>
int segment_tree<T>::size()
{
    return mSize;
}
template<class T>
T& segment_tree<T>::get(int pos)
{
    return get(pos, 0, mSize - 1, 1);
}
template<class T>
void segment_tree<T>::build(int sz, T* A)
{
    mSize = sz;
    vec.clear();
    vec.resize(mSize * 4 + 4, 0);
    O.clear();
    O.resize(mSize * 4 + 4, 0);
    check.clear();
    check.resize(mSize * 4 + 4, 0);
    bld(A, 0, mSize - 1, 1);
}
template<class T>
void segment_tree<T>::update(int left, int right, T value)
{
    upd(left, right, 0, mSize - 1, 1, value);
}
template<class T>
segment_tree<T> :: segment_tree(int size, T* A)
{
    build(size, A);
}
template<class T>
segment_tree<T> ::segment_tree(){}


template<class T>
T segment_tree_summary_type1<T>::_get(int l, int r, int ml, int mr, int mpos)
{
    if (ml >= l && mr <= r)return vec[mpos];
    if (l > mr || r < ml) return 0;
    int mid = (ml + mr) / 2;
    push(mpos, ml, mr);
    return _get(l, r, ml, mid, mpos * 2) + _get(l, r, mid + 1, mr, mpos * 2 + 1);
}
template<class T>
void segment_tree_summary_type1<T>::bld(T* A, int l, int r, int pos) 
{
    if (l > r) return;
    if (l == r) { vec[pos] = A[l]; return; }
    int mid = (l + r) / 2;
    bld(A, l, mid, pos * 2);
    bld(A, mid + 1, r, pos * 2 + 1);
    vec[pos] = vec[pos * 2] + vec[pos * 2 + 1];
}
template<class T>
void segment_tree_summary_type1<T>::push(int pos, int l, int r)
{
    if (check[pos])
    {
        int mid = (l + r) / 2;
        vec[pos * 2] = (mid - l + 1) * O[pos];
        vec[pos * 2 + 1] = (r - mid) * O[pos];
        vec[pos] = vec[pos * 2] + vec[pos * 2 + 1];
        O[pos * 2] = O[pos * 2 + 1] = O[pos];
        check[pos * 2] = check[pos * 2 + 1] = 1;
        check[pos] = 0;
    }

}
template<class T>
void segment_tree_summary_type1<T>::upd(int l, int r, int ml, int mr, int pos, T& val) 
{
    if (l > mr || r < ml) return;
    if (ml >= l && mr <= r) {
        check[pos] = 1;
        O[pos] = val;
        push(pos, ml, mr);
        return;

    }
    push(pos, ml, mr);
    int mid = (ml + mr) / 2;
    upd(l, r, ml, mid, pos * 2, val);
    upd(l, r, mid + 1, mr, pos * 2 + 1, val);
    vec[pos] = vec[pos * 2] + vec[pos * 2 + 1];
}
template<class T>
void segment_tree_summary_type1<T>::build(int size, T* A) 
{
    mSize = size;
    vec.resize(size * 4 + 4, 0);
    O.resize(size * 4 + 4, 0);
    check.resize(size * 4 + 4, 0);
    bld(A, 0, size - 1, 1);
}
template<class T>
void segment_tree_summary_type1<T>::update(int l, int r, T value)
{
    upd(l, r, 0, mSize - 1, 1, value);
}
template<class T>
segment_tree_summary_type1<T>::segment_tree_summary_type1(int size, T* A) {
    build(size, A);
}
template<class T>
segment_tree_summary_type1<T>::segment_tree_summary_type1() {}
template<class T>
T segment_tree_summary_type1<T>::get(int l, int r)
{
    return _get(l, r, 0, mSize - 1, 1);
}


template<class T>    
void segment_tree_summary_type2<T>::push(int pos, int l, int r)
{
    int mid = (l + r) / 2;
    vec[pos * 2] += (mid - l + 1) * O[pos];
    vec[pos * 2 + 1] += (r - mid) * O[pos];
    vec[pos] = vec[pos * 2] + vec[pos * 2 + 1];
    O[pos * 2] += O[pos];
    O[pos * 2 + 1] += O[pos];
    O[pos] = 0;
}
template <class T>
void segment_tree_summary_type2<T>::upd(int l, int r, int ml, int mr, int pos, T& val)
{
    if (l > mr || r < ml) return;
    if (ml >= l && mr <= r) {
        O[pos] += val;
        push(pos, ml, mr);
        return;

    }
    push(pos, ml, mr);
    int mid = (ml + mr) / 2;
    upd(l, r, ml, mid, pos * 2, val);
    upd(l, r, mid + 1, mr, pos * 2 + 1, val);
    vec[pos] = vec[pos * 2] + vec[pos * 2 + 1];
}
template <class T>
void segment_tree_summary_type2<T>::build(int size, T* A)
{
    mSize = size;
    vec.resize(size * 4 + 4, 0);
    O.resize(size * 4 + 4, 0);
    bld(A, 0, size - 1, 1);
}
template <class T>
segment_tree_summary_type2<T>::segment_tree_summary_type2(int size, T* A) : segment_tree_summary_type1<T>::segment_tree_summary_type1(size, A) {}
template <class T>
segment_tree_summary_type2<T>::segment_tree_summary_type2() {}
#endif SEGMENT_TREE_INL
