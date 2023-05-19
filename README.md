# limit-order-book

## Purpose
This project was a way for me to use what I learned in Data Structures during the
spring semester. Designing and implementing a fast limit order book is a prime example
of a problem where selecting the right data structures can give you great performance. This has
also served as an introduction to HFT and I hope to expand upon this project as I take
more classes.

## Description
A fast and accurate order book is essential for running an algorithmic trading
strategy. There are many different ways to implement an order book depending on
your requirements and the sparsity of the book. The structure that I decided to
implement can be found in a blog post [here](https://web.archive.org/web/20110219155647/http://howtohft.wordpress.com/author/howtohft/).
In this implementation we have Order objects and Limit objects. The Limit objects
are used to keep track of all the Orders at a price. We store the Limit objects in
two self-balancing BST, one for the buy side and one for the sell side. Each Limit
object stores a doubly linked list of Order objects (stored in order of time priority).
We also have two hash tables to store all the Limits and Orders for quick lookup.

From here I slightly diverged from the mentioned design. Ideally you would implement your own
self-balancing BST so you can store a pointer to the parent of each Limit object in the tree.
This allows you to still get O(1) time for getBestBid() and getBestOffer() when a Limit is deleted.
Because I am mainly doing this as an excersise I didn't want to fully reimplement an AVL tree
(something I have already done in class) so for now I will just search the BST to find a new min
or max when needed which can be done in O(*logn*) time. I may choose to come back and update 
this if I want better performance.

This implementation has the following performance:

| Operation        | Complexity (Average Case)                         | Complexity (Worst Case)                                   |
|------------------|---------------------------------------------------|-----------------------------------------------------------|
| addOrder         | O(1) if adding at an existing limit, insertion into a linked list and hash table. | O(*logn*) if adding at a new Limit, insertion into a BST and hash table. |
| cancelOrder      | O(1), search Limit using hash table, remove from linked list, remove from hash table. | O(*logn*) if we need to remove a Limit from BST. |
| executeOrder     | Same as cancelOrder. O(1)                         | O(*logn*)                                                    |
| getVolumeAtLimit | O(1), find Limit using hash table, volume is stored there. | O(1)                        |
| getBestBid       | O(1) when no Limits are deleted.                  | O(*logn*) when a Limit gets deleted.                         |
| getBestOffer     | O(1) when no Limits are deleted.                  | O(*logn*) when a Limit gets deleted.                         |

Note: the worst case situations should rarely happen in a dense order book.
*n* in this case is the number of Limits which should usually be much less than the number
of Orders. If you have a more sparse book, a different implementation might have better
performance.
## Instructions
To compile type `make`. To run tests type `./run`.