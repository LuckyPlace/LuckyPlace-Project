#pragma once
#include <iostream>
using namespace std;

template <typename T1, typename T2>
class BinaryNode
{
private:
	T1 key;
	T2 data;
	BinaryNode* left;
	BinaryNode* right;
public:
	BinaryNode(T1 key = 0, T2 data = 0, BinaryNode* left = nullptr,BinaryNode* right = nullptr)
	{
		this->key = key;
		this->data = data;
		this->left = left;
		this->right = right;
	}
	void setKey(T1 key)
	{
		this->key = key;
	}
	T1 getKey()
	{
		return this->key;
	}
	void setData(T2 data)
	{
		this->data = data;
	}
	T2 getData()
	{
		return this->data;
	}
	void setLeft(BinaryNode* left)
	{
		this->left = left;
	}
	BinaryNode* getLeft()
	{
		return this->left;
	}
	void setRight(BinaryNode* right)
	{
		this->right = right;
	}
	BinaryNode* getRight()
	{
		return this->right;
	}
	bool isLeaf()
	{
		if (this->left == nullptr && this->right == nullptr)
			return true;
		else
			return false;
	}
	bool hasTwoChildren()
	{
		return
			this->left != nullptr && this->right != nullptr;
	}
	bool hasOneChild()
	{
		bool hasOnlyLeft = (this->left != nullptr && this->right == nullptr);

		bool hasOnlyRight = (this->left == nullptr && this->right != nullptr);

		return hasOnlyLeft || hasOnlyRight;
	}
};