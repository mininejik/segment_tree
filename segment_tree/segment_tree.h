#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H
#include <iostream>
#include <vector>
using namespace std;


template <typename T>
class segment_tree {
protected:
    vector<bool> check;
    vector<T> vec;
    vector<T> O;
    int mSize;
    virtual void bld(T* A, int l, int r, int pos);
    void push(int pos);
    virtual void upd(int l, int r, int ml, int mr, int pos, T& val);
    T& get(int pos, int l, int r, int mpos);
public:
    int size();
    T& get(int pos);
    virtual void build(int sz, T* A);
    void update(int left, int right, T value);
    segment_tree(int size, T* A);
    segment_tree();
};



template <class T>
class segment_tree_summary_type1 : public segment_tree<T> // update() changes value
{
private:
    using segment_tree<T>::vec;
    using segment_tree<T>::O;
    using segment_tree<T>::mSize;
    using segment_tree<T>::check;
    T _get(int l, int r, int ml, int mr, int mpos);
protected:
    void bld(T* A, int l, int r, int pos);
    virtual void push(int pos, int l, int r);
    virtual void upd(int l, int r, int ml, int mr, int pos, T& val);
public:
    using segment_tree<T>::size;
    virtual void build(int size, T* A);
    void update(int l, int r, T value);
    segment_tree_summary_type1(int size, T* A);
    segment_tree_summary_type1();
    T get(int l, int r);


};



template <class T>
class segment_tree_summary_type2 : segment_tree_summary_type1<T> { // update() adds value to availible value
private:
    using segment_tree<T>::vec;
    using segment_tree<T>::O;
    using segment_tree<T>::mSize;
    using segment_tree_summary_type1<T>::bld;
    void push(int pos, int l, int r);
    void upd(int l, int r, int ml, int mr, int pos, T& val);
public:
    using segment_tree<T>::size;
    using segment_tree_summary_type1<T>::get;
    using segment_tree_summary_type1<T>::update;
    void build(int size, T* A);
    segment_tree_summary_type2(int size, T* A);
    segment_tree_summary_type2();

};
#include "segment_tree.inl"
#endif 
