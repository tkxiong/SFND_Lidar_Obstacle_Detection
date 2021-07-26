#include <vector>

// Structure to represent node of kd tree
template<typename PointT>
struct Node
{
	PointT point;
	int id;
	Node* left;
	Node* right;

	Node(PointT arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};

template<typename PointT>
struct KdTree
{
	Node<PointT>* root;

	KdTree()
	: root(NULL)
	{}

	~KdTree()
	{
		delete root;
	}

	void insertNode(Node<PointT> **node, uint depth, PointT point, int id)
	{
		// Tree is empty
		if (*node == NULL)
		{
			*node = new Node<PointT>(point, id);
		}
		else
		{
			// Calculate current dim
			uint cd = depth % 3;

            if (cd == 0)
            {
                if (point.x < ((*node)->point.x))
                {
                    insertNode(&((*node)->left), depth + 1, point, id);
                }
                else
                {
                    insertNode(&((*node)->right), depth + 1, point, id);
                }
            }
            else if (cd == 1)
            {
                if (point.y < ((*node)->point.y))
                {
                    insertNode(&((*node)->left), depth + 1, point, id);
                }
                else
                {
                    insertNode(&((*node)->right), depth + 1, point, id);
                }
            }
            else
            {
                if (point.z < ((*node)->point.z))
                {
                    insertNode(&((*node)->left), depth + 1, point, id);
                }
                else
                {
                    insertNode(&((*node)->right), depth + 1, point, id);
                }
            }
		}
	}


	void insert(PointT point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertNode(&root, 0, point, id);
	}

	void searchKDTreeNeighbors(PointT target, Node<PointT>* node, int depth, float distanceTol, std::vector<int> &ids)
	{
		if (node != NULL)
		{
			if ((node->point.x >= (target.x - distanceTol) && node->point.x <= (target.x + distanceTol)) && 
				(node->point.y >= (target.y - distanceTol) && node->point.y <= (target.y + distanceTol)) &&
                (node->point.z >= (target.z - distanceTol) && node->point.z <= (target.z + distanceTol)))
			{
				float deltaX = node->point.x - target.x;
				float deltaY = node->point.y - target.y;
                float deltaZ = node->point.z - target.z;
	
				float distance = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
				if (distance <= distanceTol)
				{
					ids.push_back(node->id);
				}
			}

			uint cd = depth % 3;

            if (cd == 0)
            {
                if ((target.x - distanceTol) < node->point.x)
                {
                    searchKDTreeNeighbors(target, node->left, depth + 1, distanceTol, ids);
                }
                if ((target.x + distanceTol) > node->point.x)
                {
                    searchKDTreeNeighbors(target, node->right, depth + 1, distanceTol, ids);
                }
            }
            else if (cd == 1)
            {
                if ((target.y - distanceTol) < node->point.y)
                {
                    searchKDTreeNeighbors(target, node->left, depth + 1, distanceTol, ids);
                }
                if ((target.y + distanceTol) > node->point.y)
                {
                    searchKDTreeNeighbors(target, node->right, depth + 1, distanceTol, ids);
                }
            }
            else
            {
                if ((target.z - distanceTol) < node->point.z)
                {
                    searchKDTreeNeighbors(target, node->left, depth + 1, distanceTol, ids);
                }
                if ((target.z + distanceTol) > node->point.z)
                {
                    searchKDTreeNeighbors(target, node->right, depth + 1, distanceTol, ids);
                }
            }
		}
	}


	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(PointT target, float distanceTol)
	{
		std::vector<int> ids;
		searchKDTreeNeighbors(target, root, 0, distanceTol, ids);
		return ids;
	}
	

};




