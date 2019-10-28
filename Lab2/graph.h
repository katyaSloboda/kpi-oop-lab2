#ifndef GRAPH_H
#define GRAPH_H

class Node
{
	size_t parentsSize_;
	int * parentsData_;

public:
	int Num;

	Node();
	Node(int num, int parents[], size_t parentsSize);
	Node(const Node& node);
	~Node() {
		delete[] parentsData_;
	};

	Node& operator =(const Node& g);
	bool operator ==(const Node& g);

	size_t GetParentsSize() { return parentsSize_; };
	int * GetParentsData() { return parentsData_; };
	void SetParents(int parents[], size_t parentsSize);
	bool CheckParents(int parents[], size_t parentsSize);
	void Swap(Node& node);
	void Print();
};

class Graph
{
	size_t nodesSize_;
	Node * nodesData_;

public:
	Graph();
	Graph(const Graph& graph);
	~Graph() { 
		delete[] nodesData_;
	};

	Graph& operator =(const Graph& graph);

	void Shift(Node node);
	void Add(Node node);
	void Remove(Node node);
	void Clear();
	void Print();
	void Info();
	void Swap(Graph& graph);
	int IndexOf(int num);
	Node Find(int num);
	Graph FindParentNodes(int num);
	Graph FindChildNodes(int num);
	Graph Path(Node node1, Node node2, bool inverseChild = false);
	void IterateNodes(Node startNode, Graph checkedNodes);
};

#endif //GRAPH_H