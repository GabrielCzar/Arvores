#ifndef BNODE_H
#define BNODE_H

struct BNode{
	int value;
	BNode * left;
	BNode * right;

	BNode (int value = 0, BNode * left = nullptr, BNode * right = nullptr){
		this->value = value;
		this->left = left;
		this->right = right;
	}
};

#endif //BNODE_H