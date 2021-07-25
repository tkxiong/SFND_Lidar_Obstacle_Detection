/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	~KdTree()
	{
		delete root;
	}

	void insertNode(Node **node, uint depth, std::vector<float> point, int id)
	{
		// Tree is empty
		if (*node == NULL)
		{
			*node = new Node(point, id);
		}
		else
		{
			// Calculate current dim
			uint cd = depth % 2;

			if (point[cd] < ((*node)->point[cd]))
			{
				insertNode(&((*node)->left), depth + 1, point, id);
			}
			else
			{
				insertNode(&((*node)->right), depth + 1, point, id);
			}
		}
	}


	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertNode(&root, 0, point, id);
	}

	void searchKDTreeNeighbors(std::vector<float> target, Node* node, int depth, float distanceTol, std::vector<int> &ids)
	{
		if (node != NULL)
		{
			if ((node->point[0] >= (target[0] - distanceTol) && node->point[0] <= (target[0] + distanceTol)) && 
				(node->point[1] >= (target[1] - distanceTol) && node->point[1] <= (target[1] + distanceTol)))
			{
				float deltaX = node->point[0] - target[0];
				float deltaY = node->point[1] - target[1];	
				float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
				if (distance <= distanceTol)
				{
					ids.push_back(node->id);
				}
			}

			int lr_id = depth % 2;
			if ((target[lr_id] - distanceTol) < node->point[lr_id])
			{
				searchKDTreeNeighbors(target, node->left, depth + 1, distanceTol, ids);
			}
			if ((target[lr_id] + distanceTol) > node->point[lr_id])
			{
				searchKDTreeNeighbors(target, node->right, depth + 1, distanceTol, ids);
			}

		}
	}


	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		searchKDTreeNeighbors(target, root, 0, distanceTol, ids);
		return ids;
	}
	

};




