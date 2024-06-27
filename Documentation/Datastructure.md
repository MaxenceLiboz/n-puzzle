[<-- Back](../README.md)
## Data structure

The **open** list must be a list that allow to retrieve the lower **f score** as fast as possible. Therefore, a priority list is a good choice as the **top()** element is the highest priority.  

>**CPP Reference** : The priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.  
A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top(). 

The **closed** list must be a a list that allow the algorithm to check if a node is already in the list. For this purpose, we can use an unsorted list which will be fast for insert and fast for looksup as it use an hash for it.

>**CPP Reference** : Internally, the elements are not sorted in any particular order, but organized into buckets. Which bucket an element is placed into depends entirely on the hash of its value. This allows fast access to individual elements, since once a hash is computed, it refers to the exact bucket the element is placed into.  
Container elements may not be modified (even by non const iterators) since modification could change an element's hash and corrupt the container. 

The **node** must hold a **N*N 1D array**, the **g(x), h(x) and f(x) score**, an **ID** and the **ID of its parent** (in order to go backward, we might just need the close set but I am not sure, We might also be able to use the hash as the ID).  
The **open set** must hold the **node** above.  
The **close set** must hold the **node** above.  
The **structure / class itself** must hold the **open and close set**, a variable representing the maximum number of state at the same time in the **close set**, the **starting node** and the **goal node**


## Sources
[Priority queue](https://en.cppreference.com/w/cpp/container/priority_queue)  
[Unordered set](https://en.cppreference.com/w/cpp/container/unordered_set)  