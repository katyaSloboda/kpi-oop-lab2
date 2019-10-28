#include "pch.h"
#include "graph.h"
#include <iostream>

using namespace std;

// Node constructors
Node::Node() : Num(0), parentsSize_(0), parentsData_(new int[parentsSize_]) {}
Node::Node(int num, int parents[], size_t parentsSize) 
	: Num(num), parentsSize_(parentsSize), parentsData_(new int[parentsSize_]) {
	for (size_t i = 0; i != parentsSize_; ++i)
		parentsData_[i] = parents[i];
}
Node::Node(const Node& node) 
	: Num(node.Num), parentsSize_(node.parentsSize_), parentsData_(new int[parentsSize_]) {
	for (size_t i = 0; i != parentsSize_; ++i)
		parentsData_[i] = node.parentsData_[i];
}

// Node operators
Node & Node::operator =(const Node &node) {
	if (this != &node)
		Node(node).Swap(*this);
	return *this;
}
bool Node::operator ==(const Node &node) {
	if (Num != node.Num ||
		!CheckParents(node.parentsData_, node.parentsSize_))
		return false;

	return true;
}

// Node methods
// Set parents nums
void Node::SetParents(int parents[], size_t parentsSize) {
	if (parentsSize_ != 0)
		delete[] parentsData_;
	parentsSize_ = parentsSize;
	parentsData_ = new int[parentsSize_];

	for (size_t i = 0; i != parentsSize_; ++i)
		parentsData_[i] = parents[i];
}
// Check parents nums
bool Node::CheckParents(int parents[], size_t parentsSize) {
	if (parentsSize_ != parentsSize)
		return false;

	for (size_t i = 0; i != parentsSize_; ++i)
		if (parentsData_[i] != parents[i])
			return false;

	return true;
}
// Swap two nodes
void Node::Swap(Node& node) {
	int const n = Num;
	Num = node.Num;
	node.Num = n;

	size_t const s = parentsSize_;
	parentsSize_ = node.parentsSize_;
	node.parentsSize_ = s;

	int * const d = parentsData_;
	parentsData_ = node.parentsData_;
	node.parentsData_ = d;
}
// Print info about node
void Node::Print() {
	cout << "Num: " << Num << "\n";
	cout << "parentsSize_: " << parentsSize_ << "\n";
	for (size_t i = 0; i != parentsSize_; ++i)
		cout << parentsData_[i] << "\t";
	cout << "\n";
}

// Graph constructors
Graph::Graph() : nodesSize_(0), nodesData_(new Node[nodesSize_]) {}
Graph::Graph(const Graph& graph) 
	: nodesSize_(graph.nodesSize_), nodesData_(new Node[nodesSize_]) {
	for (size_t i = 0; i != nodesSize_; ++i)
		nodesData_[i] = graph.nodesData_[i];
}

// Graph operators
Graph& Graph::operator =(const Graph& graph) {
	if (this != &graph)
		Graph(graph).Swap(*this);
	return *this;
}

// Graph methods
// Add node to the beginning of the array
void Graph::Shift(Node node) {
	if (Find(node.Num).Num != 0)
	{
		cout << "This node already exist\n";
		return;
	}

	Node * nodes = new Node[nodesSize_ + 1];
	nodes[0] = node;
	for (size_t i = 0; i != nodesSize_; ++i)
		nodes[i + 1] = nodesData_[i];

	if (nodesSize_ != 0)
		delete[] nodesData_;

	nodesData_ = nodes;
	++nodesSize_;
}
// Add node to the end of the array
void Graph::Add(Node node) {
	if (Find(node.Num).Num != 0)
	{
		cout << "This node already exist\n";
		return;
	}

	Node * nodes = new Node[nodesSize_ + 1];
	for (size_t i = 0; i != nodesSize_; ++i)
		nodes[i] = nodesData_[i];
	if (nodesSize_ != 0)
		delete[] nodesData_;

	nodes[nodesSize_] = node;
	nodesData_ = nodes;
	++nodesSize_;
}
// Remove existing node
void Graph::Remove(Node node) {
	if (nodesSize_ == 0)
	{
		cout << "Graph is empty\n";
		return;
	}

	int i = IndexOf(node.Num);
	if (i == -1)
	{
		cout << "This node not exist\n";
		return;
	}

	Node * nodes = new Node[nodesSize_ - 1];
	int count1 = 0, count2 = 0;
	while (count1 != nodesSize_ - 1 || count2 != nodesSize_)
	{
		if (i != count2)
		{
			nodes[count1] = nodesData_[count2];
			++count1;
		}
		++count2;
	}
		
	if (nodesSize_ != 0)
		delete[] nodesData_;

	nodesData_ = nodes;
	--nodesSize_;
}
// Clear graph
void Graph::Clear() {
	nodesSize_ = 0;
	delete[] nodesData_;
}
// Print graph structure
void Graph::Print() {
	cout << "\nGraph:\n";
	cout << "nodesSize_: " << nodesSize_ << "\n";
	for (size_t i = 0; i != nodesSize_; ++i)
	{
		Node node = nodesData_[i];
		cout << "Num: " << node.Num << ";\t";

		cout << "Parents: ";
		size_t parentsSize = node.GetParentsSize();
		int * parents = node.GetParentsData();
		for (size_t j = 0; j != parentsSize; ++j)
			cout << parents[j] << ",\t";

		cout << "\n";
	}
	cout << "\n";
}
// Print info about graph
void Graph::Info() {
	cout << "Number of graph nodes: " << nodesSize_ << "\n";
}
// Get index of node
int Graph::IndexOf(int num) {
	for (size_t i = 0; i != nodesSize_; ++i)
		if (nodesData_[i].Num == num)
			return i;

	return -1;
}
// Find a node in the graph
Node Graph::Find(int num) {
	for (size_t i = 0; i != nodesSize_; ++i)
		if (nodesData_[i].Num == num)
			return nodesData_[i];

	return Node();
}
// Swap graphs
void Graph::Swap(Graph& graph) {
	size_t const s = nodesSize_;
	nodesSize_ = graph.nodesSize_;
	graph.nodesSize_ = s;

	Node * const d = nodesData_;
	nodesData_ = graph.nodesData_;
	graph.nodesData_ = d;
}
// Get parent nodes
Graph Graph::FindParentNodes(int num) {
	Graph newGraph;
	if (nodesSize_ == 0)
		return newGraph;

	Node node = Find(num);
	if (node.Num == 0)
		return newGraph;

	size_t parentsSize = node.GetParentsSize();
	int * parents = node.GetParentsData();

	for (size_t j = 0; j != parentsSize; ++j)
	{
		int parentNum = parents[j];
		Node parentNode = Find(parentNum);
		if (node.Num != 0)
			newGraph.Add(parentNode);
	}

	return newGraph;
}
// Get children nodes
Graph Graph::FindChildNodes(int num) {
	Graph newGraph;
	if (nodesSize_ == 0)
		return newGraph;

	Node node = Find(num);
	if (node.Num == 0)
		return newGraph;

	for (size_t i = 0; i != nodesSize_; ++i)
	{
		Node chieldNode = nodesData_[i];
		if (chieldNode.CheckParents(new int[1]{ node.Num }, 1))
			newGraph.Add(chieldNode);
	}

	return newGraph;
}
// Get path between two nodes
Graph Graph::Path(Node node1, Node node2, bool inverseChild) {
	Graph newGraph;
	newGraph.Add(node1);

	// search by children
	Graph children = FindChildNodes(node1.Num);
	for (size_t i = 0; i != children.nodesSize_; ++i)
		if (children.nodesData_[i].Num == node2.Num)
		{
			if (inverseChild)
				newGraph.Shift(node2);
			else
				newGraph.Add(node2);
			return newGraph;
		}
		else
		{
			Graph nchildren = Path(children.nodesData_[i], node2, inverseChild);
			if (nchildren.IndexOf(node2.Num) != -1)
			{
				if (inverseChild)
				{
					for (size_t j = 0; j != newGraph.nodesSize_; ++j)
						nchildren.Add(newGraph.nodesData_[j]);
					return nchildren;
				}
				else
				{
					for (size_t j = 0; j != nchildren.nodesSize_; ++j)
						newGraph.Add(nchildren.nodesData_[j]);
					return newGraph;
				}
			}
		}

	// search by parents
	Graph parents = FindParentNodes(node1.Num);
	for (size_t i = 0; i != parents.nodesSize_; ++i)
		if (parents.nodesData_[i].Num == node2.Num)
		{
			newGraph.Shift(node2);
			return newGraph;
		}
		else
		{
			Graph nparents = Path(parents.nodesData_[i], node2, true);
			if (nparents.IndexOf(node2.Num) != -1)
			{
				for (size_t j = 0; j != newGraph.nodesSize_; ++j)
					nparents.Add(newGraph.nodesData_[j]);
				return nparents;
			}
		}

	newGraph.Remove(node1);
	return newGraph;
}
void Graph::IterateNodes(Node startNode, Graph checkedNodes) {
	// by children
	Graph children = FindChildNodes(startNode.Num);
	for (size_t i = 0; i != children.nodesSize_; ++i)
		if (checkedNodes.IndexOf(children.nodesData_[i].Num) == -1)
		{
			IterateNodes(children.nodesData_[i], checkedNodes);
			checkedNodes.Add(children.nodesData_[i]);
		}

	// by parents
	Graph parents = FindParentNodes(startNode.Num);
	for (size_t i = 0; i != parents.nodesSize_; ++i)
		if (checkedNodes.IndexOf(parents.nodesData_[i].Num) == -1)
		{
			IterateNodes(parents.nodesData_[i], checkedNodes);
			checkedNodes.Add(parents.nodesData_[i]);
		}
}