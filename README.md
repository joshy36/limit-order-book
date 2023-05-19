# limit-order-book


## Description
A fast and accurate order book is essential for running an algorithmic trading
strategy. There are many different ways to implement an order book depending on
your requirements and the sparsity of the book. The structure that I decided to
implement can be found in a blog post [here](https://web.archive.org/web/20110219155647/http://howtohft.wordpress.com/author/howtohft/).
In this implementation we have Order objects and Limit objects. The Limit objects
are used to keep track of all the Orders at a price. We store the Limit objects in
two self-balancing BST, one for the buy side and one for the sell side. Each Limit
object stores a doubly linked list of Order objects (stored in order of time priority).
We also have a hash table 

This implementation allows for the following:
addOrder: O(1) if adding at an existing limit, insertion into a linked list and hash table.
O(logn) if adding at a new Limit, insertion into a BST and insertion into a hash table
cancelOrder: O(1), search Limit using hash table, remove from linked list, remove from hash table.
O(logn) if we need to remove a Limit from BST (should happen rarely)
executeOder: same as cancelOrder, O(1), O(logn) worst case
getVolumeAtLimit: O(1), find Limit using hash table, volume is stored there.
getBestBid: O(1), 
getBestOffer:(1)

n in this case is the number of Limits which should usually be much less than the number
of Orders. If you have a more sparse book, a different implementation might have better
performance.
## Instructions
To compile type `make`. To run type `./run`.