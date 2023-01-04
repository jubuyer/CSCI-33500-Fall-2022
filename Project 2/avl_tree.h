// Jubayer Ahmed
// AvlTree is a templated class implements a self-balancing Binary Search Tree (BST). The class takes
// the type Comparable, and implements methods that allow the height of the tree to remain balanced.
// Since the height never grows past log(N), where N is the number of nodes, the time complexity 
// of insertion, deletion, and searching is better than a regular BST. Has single rotation implemented
// for balancing the tree and two single rotations in place of a double rotation.

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// void remove( const Comparable & x, int & successful, int & total, int & current_path_) --> Remove x, iterate parameters
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMin( int & total, int & current_path_) --> Return smallest item, iterate parameters
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// int numTotalNodes( )   --> Return total number of nodes in tree
// float findInternalPathLen( float level ) --> Returns internal path length of tree.
// std::vector<string> find( const Comparable & x ) --> Returns vector<string> if x is found in the tree.
// std::vector<string> find( const Comparable & x, int & successful, int & total ) --> Returns vector<string> if x is found in the tree.
//
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
	AvlTree( ) : root{ nullptr }
	{ }

	AvlTree( const AvlTree & rhs ) : root{ nullptr }
	{
		root = clone( rhs.root );
	}

	AvlTree( AvlTree && rhs ) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	~AvlTree( )
	{
		makeEmpty( );
	}

	/**
	 * Deep copy.
	 */
	AvlTree & operator=( const AvlTree & rhs )
	{
		AvlTree copy = rhs;
		std::swap( *this, copy );
		return *this;
	}

	/**
	 * Move.
	 */
	AvlTree & operator=( AvlTree && rhs )
	{
		std::swap( root, rhs.root );

		return *this;
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMin( ) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMin( root )->element;
	}


	/**
	 * Overloaded findMin(): Find the smallest item in the tree. Iterates parameters to count 
	 * recursive calls. Throw UnderflowException if empty.
	 * 
	 * @param total counts the total number of recursive calls building previous deletion calls
	 * @param current_path_ counts the number of recursive calls during one deletion call
	 */
	const Comparable & findMin( int & total, int & current_path_) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMin( total, current_path_, root )->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable & findMax( ) const
	{
		if( isEmpty( ) )
			throw UnderflowException{ };
		return findMax( root )->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains( const Comparable & x ) const
	{
		return contains( x, root );
	}

	/**
	 * Returns total number of nodes in the tree.
	 */
	int numTotalNodes( ) const
	{
		return numTotalNodes( root );
	}

	/**
	 * Returns internal path length of tree.
	 */
	float findInternalPathLen( float level ) const
	{
		return findInternalPathLen( level, root );
	}

	/**
	 * Returns vector<string> if x is found in the tree.
	 * 
	 * @param x Comparable object that is to be found in the tree
	 * @param successful counts the number of find calls that successfully found the object
	 * @param total counts the total number of find calls building from all previous find calls
	 */
	std::vector<string> find( const Comparable & x, int & successful, int & total ) const
	{
		return find( x, successful, total, root );
	}

	/**
	 * Returns vector<string> if x is found in the tree.
	 * 
	 * @param x Comparable object that is to be found in the tree
	*/
	std::vector<string> find( const Comparable & x ) const
	{
		return find( x, root );
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	bool isEmpty( ) const
	{
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree( ) const
	{
		if( isEmpty( ) )
			cout << "Empty tree" << endl;
		else
			printTree( root );
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty( )
	{
		makeEmpty( root );
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert( const Comparable & x )
	{
		insert( x, root );
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert( Comparable && x )
	{
		insert( std::move( x ), root );
	}

	/**
	 * OVERLOADED: Remove x from the tree. Nothing is done if x is not found. Iterates reference
	 * parameters based on number of successful removes and total recursion calls.
	 * 
	 * @param x Comparable object that is to be found in the tree
	 * @param successful counts the number of find calls that successfully removes the object
	 * @param total counts the total number of recursive calls building from all previous deletion calls
	 * @param current_path_ counts the number of recursive calls during one (current) deletion call
	 */
	void remove( const Comparable & x, int & successful, int & total, int & current_path_)
	{
		remove( x, successful, total, current_path_, root );
	}

	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove( const Comparable & x )
	{
		remove( x, root );
	}

private:
	struct AvlNode
	{
		Comparable element;
		AvlNode   *left;
		AvlNode   *right;
		int       height;

		AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
			: element{ ele }, left{ lt }, right{ rt }, height{ h } { }

		AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
			: element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
	};

	AvlNode *root;


	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( const Comparable & x, AvlNode * & t )
	{
		if( t == nullptr )
			t = new AvlNode{ x, nullptr, nullptr };
		else if( x < t->element )
			insert( x, t->left );
		else if( t->element < x )
			insert( x, t->right );
		else
			t->element.Merge(x);

		balance( t );
	}

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert( Comparable && x, AvlNode * & t )
	{
		if( t == nullptr )
			t = new AvlNode{ std::move( x ), nullptr, nullptr };
		else if( x < t->element )
			insert( std::move( x ), t->left );
		else if( t->element < x )
			insert( std::move( x ), t->right );
		else
			t->element.Merge(x);

		balance( t );
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void remove( const Comparable & x, AvlNode * & t )
	{
		if( t == nullptr )
			return;   // Item not found; do nothing

		if( x < t->element )
			remove( x, t->left );
		else if( t->element < x )
			remove( x, t->right );
		else if( t->left != nullptr && t->right != nullptr ) // Two children
		{
			t->element = findMin( t->right )->element;
			remove( t->element, t->right );
		}
		else
		{
			AvlNode *oldNode = t;
			t = ( t->left != nullptr ) ? t->left : t->right;
			delete oldNode;
		}

		balance( t );
	}

	/**
	 * OVERLOADED: Remove x from the tree. Nothing is done if x is not found. Iterates reference
	 * parameters based on number of successful removes and total recursion calls.
	 * 
	 * @param x Comparable object that is to be found in the tree
	 * @param successful counts the number of find calls that successfully removes the object
	 * @param total counts the total number of recursive calls building from all previous deletion calls
	 * @param current_path_ counts the number of recursive calls during one (current) deletion call
	 */
	void remove( const Comparable & x, int & successful, int & total, int & current_path_, AvlNode * & t )
	{
		// if node is not found, remove the recursion calls that were called for finding 
		// the nonexistent node from the total. Set current path to 0. Return.
		if( t == nullptr ) {
			total -= current_path_;
			current_path_ = 0;
			return;   // Item not found; do nothing
		}

		if( x < t->element ) {
			total++;
			current_path_++;
			remove( x, successful, total, current_path_, t->left );
		}
		else if( t->element < x ) {
			total++;
			current_path_++;
			remove( x, successful, total, current_path_, t->right );
		}
		else if( t->left != nullptr && t->right != nullptr ) // Two children
		{
			total++;
			current_path_++;
			t->element = findMin( total, current_path_, t->right )->element;
			remove( t->element, successful, total, current_path_, t->right );
		}
		else
		{
			AvlNode *oldNode = t;
			t = ( t->left != nullptr ) ? t->left : t->right;
			delete oldNode;
			successful++;
			current_path_ = 0;
		}

		balance( t );
	}

	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance( AvlNode * & t )
	{
		if( t == nullptr )
			return;

		if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
			if( height( t->left->left ) >= height( t->left->right ) )
				rotateWithLeftChild( t );
			else
				doubleWithLeftChild( t );
		} else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
			if( height( t->right->right ) >= height( t->right->left ) )
				rotateWithRightChild( t );
			else
				doubleWithRightChild( t );
		}
		t->height = max( height( t->left ), height( t->right ) ) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	AvlNode * findMin( AvlNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		if( t->left == nullptr )
			return t;
		return findMin( t->left );
	}

	/**
	 * Overloaded findMin(): Find the smallest item in the tree. Iterates parameters to count 
	 * recursive calls. Throw UnderflowException if empty.
	 * 
	 * @param total counts the total number of recursive calls building previous deletion calls
	 * @param current_path_ counts the number of recursive calls during one deletion call
	 */
	AvlNode * findMin( int & total, int & current_path_, AvlNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		if( t->left == nullptr ) {
			total++;
			return t;
		} 
		else {
			total++;
			current_path_++;
			return findMin( total, current_path_, t->left );
		}
	}


	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	AvlNode * findMax( AvlNode *t ) const
	{
		if( t != nullptr )
			while( t->right != nullptr )
				t = t->right;
		return t;
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	float findInternalPathLen( float level, AvlNode *t ) const
	{
		if( t == nullptr )
			return 0;
		else { 
			return level + findInternalPathLen(level+1, t->right) + findInternalPathLen(level+1, t->left);
		}
	}


	/**
	 * Internal method to find number of nodes in a tree.
	 * t is the node that roots the tree.
	 */
	int numTotalNodes( AvlNode *t ) const
	{
		if( t == nullptr )
			return 0;
		else 
			return 1 + numTotalNodes(t->left) + numTotalNodes(t->right);
	}

	/**
	 * Internal method to find an item in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	std::vector<string> find( const Comparable & x, AvlNode *t ) const
	{
		if( t == nullptr ) {
			vector<string> finder_(1, "Not Found");
			return finder_;
		} else if( x < t->element )
			return find( x, t->left );
		else if( t->element < x )
			return find( x, t->right );
		else
			return t->element.getAcronyms();    // Match
	}

		/**
	 * Internal method to find an item in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	std::vector<string> find( const Comparable & x, int &successful, int &total, AvlNode *t ) const
	{
		if( t == nullptr ) {
			vector<string> finder_(1, "Not Found");
			return finder_;
		} else if( x < t->element ) {
			total++;
			return find( x, successful, total, t->left );
		}
		else if( t->element < x ) {
			total++;
			return find( x, successful, total, t->right );
		}
		else {
			successful++;
			return t->element.getAcronyms();    // Match
		}
	}

	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	bool contains( const Comparable & x, AvlNode *t ) const
	{
		if( t == nullptr )
			return false;
		else if( x < t->element )
			return contains( x, t->left );
		else if( t->element < x )
			return contains( x, t->right );
		else
			return true;    // Match
	}
	/****** NONRECURSIVE VERSION*************************
	    bool contains( const Comparable & x, AvlNode *t ) const
	    {
	        while( t != nullptr )
	            if( x < t->element )
	                t = t->left;
	            else if( t->element < x )
	                t = t->right;
	            else
	                return true;    // Match

	        return false;   // No match
	    }
	*****************************************************/

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty( AvlNode * & t )
	{
		if( t != nullptr )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = nullptr;
	}

	/**
	 * Internal method to print a subtree rooted at t in sorted order.
	 */
	void printTree( AvlNode *t ) const
	{
		if( t != nullptr )
		{
			printTree( t->left );
			cout << t->element << endl;
			printTree( t->right );
		}
	}

	/**
	 * Internal method to clone subtree.
	 */
	AvlNode * clone( AvlNode *t ) const
	{
		if( t == nullptr )
			return nullptr;
		else
			return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
	}
	// Avl manipulations
	/**
	 * Return the height of node t or -1 if nullptr.
	 */
	int height( AvlNode *t ) const
	{
		return t == nullptr ? -1 : t->height;
	}

	int max( int lhs, int rhs ) const
	{
		return lhs > rhs ? lhs : rhs;
	}

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */
	void rotateWithLeftChild( AvlNode * & k2 )
	{
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
		k1->height = max( height( k1->left ), k2->height ) + 1;
		k2 = k1;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild( AvlNode * & k1 )
	{
		AvlNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
		k2->height = max( height( k2->right ), k1->height ) + 1;
		k1 = k2;
	}

	/**
	 * Double rotate binary tree node: first left child.
	 * with its right child; then node k3 with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */
	void doubleWithLeftChild( AvlNode * & k3 )
	{
		rotateWithRightChild( k3->left );
		rotateWithLeftChild( k3 );
	}

	/**
	 * Double rotate binary tree node: first right child.
	 * with its left child; then node k1 with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void doubleWithRightChild( AvlNode * & k1 )
	{
		rotateWithLeftChild( k1->right );
		rotateWithRightChild( k1 );
	}
};

#endif
