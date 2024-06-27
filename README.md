# Project reasearch

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



## Sources
[A* Algorithm | A* Algorithm Example](https://www.gatevidyalay.com/tag/a-star-search-algorithm-example/)  
[IDA-Star(IDA*) Algorithm in general](https://algorithmsinsight.wordpress.com/graph-theory-2/ida-star-algorithm-in-general/)  
[A-star(A*) in general](https://algorithmsinsight.wordpress.com/graph-theory-2/a-star-in-general/)  
[Implementing A-star(A*) to solve N-Puzzle](https://algorithmsinsight.wordpress.com/graph-theory-2/a-star-in-general/implementing-a-star-to-solve-n-puzzle/)  
