# Project research

## The goal
The goal of this projet is to create an algorithm that can solve the game [n-puzzle (taquin in french)](https://en.wikipedia.org/wiki/15_puzzle). It must be able to solve 3x3, 4x4 etc. However, the correction is going to be specific to solving the 3x3 as fast as possible.  
For a puzzle NxN the bigger the N is the higher the resolution time is goig to be.  


## Algorithms

**A-star (A\*)** can be used to solve the n-puzzle. You can find **[here](https://algorithmsinsight.wordpress.com/graph-theory-2/a-star-in-general/implementing-a-star-to-solve-n-puzzle/)** a realy good explaination of it.  
If I have to summurize it:  
- First I would say that each node represent a state of the puzzle. Therefore, each node has a maxium of 4 new children (the blank part going up, down, right or left). It will then expend until the n-puzzle is solve.
- Second each node is going to be given a score depending on the **heuristic** which is named **f**. The node with the lower **f score** is going to be chosen to continue the loop.  

This algorithm is storing in an **open** list the nodes that are not visited and in a **closed** list the nodes that are visisted, if there are no more **open** nodes the n-puzzle is not solvable.  

**Iterative Deepening (IDA\*)** is going to be the same as the **A-start** algorithm but it will use less memory. Indeed, it does not use the **open** and **closed** list, instead it use a threshold that is going to be set arbritrary at first. Once the threshold is reach, the smalest **f score** node is going to be the new threshold. Then, the algorithm restart from the begining.  

Therefore, we have here a choice to make, either take a more time efficient algorithm, or take a more space efficient algroithm.
It will need to be chose by the team, but we need to keep in mind that the correction is going to be more focus on the 3x3.

## Solvability
In order to optimize the algorithm, it is possible to check if a puzzle is solvable or not. This will help us detect node that we don't want to check further, but also check if a puzzle is solvable or not.  

#### The checks
In general, for a given grid of width N, we can find out check if a N*N – 1 puzzle is solvable or not by following below simple rules :  
- If N is odd, then puzzle instance is solvable if number of inversions is even in the input state.
- If N is even, puzzle instance is solvable if :  
  - the blank is on an even row counting from the bottom (second-last, fourth-last, etc.) and number of inversions is odd.
  - the blank is on an odd row counting from the bottom (last, third-last, fifth-last, etc.) and number of inversions is even.  

For all other cases, the puzzle instance is not solvable

#### The inversion  
If we assume the tiles written out in a single row (1D Array) instead of being spread in N-rows (2D Array), a pair of tiles (a, b) form an inversion if a appears before b but a > b. 
If we concider a taquin like this :  
**1 2 4**  
**3 5 6**  
**7 8 x**  
And we put it in a 1D array: **1 2 4 3 5 6 7 8**, we can see that:  
- **4-3** is an inversion.  

Another more complex example:  
**1 8 3**  
**2 6 5**  
**7 4 X**  
We put it in a 1D array: **1 8 3 2 6 5 7 4**, we can see that :
- **8-3, 8-2, 8-6, 8-5, 8-7, 8-4** (6 inversions)  
- **3-2** (1 inversion)  
- **6-5, 6-4** (2 inversions)  
- **5-4** (1 inversion)  
- **7-4** (1 inversion)  

Which mean we have **6 + 1 + 2 + 1 + 1 = 11 inversions**. Here the n-puzzle is **not solvable**.

Now you must understand that the algroithm can be optimize with this.

## Data structure
The **open** list must be a list that allow to retrieve the lower **f score** as fast as possible. Therefore, a priority list is a good choice as the **top()** element is the highest priority.  

>**CPP Reference** : The priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.  
A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top(). 

The **closed** list must be a a list that allow the algorithm to check if a node is already in the list. For this purpose, we can use an unsorted list which will be fast for insert and fast for looksup as it use an hash for it.

>**CPP Reference** : Internally, the elements are not sorted in any particular order, but organized into buckets. Which bucket an element is placed into depends entirely on the hash of its value. This allows fast access to individual elements, since once a hash is computed, it refers to the exact bucket the element is placed into.  
Container elements may not be modified (even by non const iterators) since modification could change an element's hash and corrupt the container. 

## Sources
[A* Algorithm | A* Algorithm Example](https://www.gatevidyalay.com/tag/a-star-search-algorithm-example/)  
[IDA-Star(IDA*) Algorithm in general](https://algorithmsinsight.wordpress.com/graph-theory-2/ida-star-algorithm-in-general/)  
[A-star(A*) in general](https://algorithmsinsight.wordpress.com/graph-theory-2/a-star-in-general/)  
[Implementing A-star(A*) to solve N-Puzzle](https://algorithmsinsight.wordpress.com/graph-theory-2/a-star-in-general/implementing-a-star-to-solve-n-puzzle/)  
[How to check if an instance of 15 puzzle is solvable?](https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/)  
[Priority queue](https://en.cppreference.com/w/cpp/container/priority_queue)  
[Unordered set](https://en.cppreference.com/w/cpp/container/unordered_set)  

