There are 3 segment tree clasess.


segment_tree<>:

int size() returns number of elements of array wich was used to create a segment tree
void build(int size, T* array) creates a segment tree
void update(int left, int right, T value) changes all elemenst from left to right to value
T& get(int position) returns current value
segment_tree(int size, T* array) - constructor


segment_tree_summary_type1<>:

int size() returns number of elements of array wich was used to create a segment tree
void build(int size, T* array) creates a segment tree
void update(int left, int right, T value) changes all elemenst from left to right to value
T get(int left, int right) returs summary of all elemets from left to right
segment_tree_summary_type1(int size, T* array) - constructor

segment_tree_summary_type2<>:

everething is the same as segment_tree_summary_type1<>, but update() adds value to availible elements (not changes them to value)
