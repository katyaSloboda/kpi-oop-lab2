// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "graph.h"
#include <iostream>

using namespace std;

int main()
{
	int parents1[] = { 1,2,3 };
	int parents2[] = { 1 };
	Node node1(5, parents1, sizeof(parents1) / sizeof(parents1[0]));
	Node node2(2, parents2, sizeof(parents2) / sizeof(parents2[0]));
	node1.Print();
	node2.Print();

	Graph graph;
	graph.Add(node1);
	graph.Add(node2);

	Graph path = graph.Path(node1, node2);
	path.Print();

	graph.Print();
	graph.Info();
	graph.IterateNodes(node2, Graph());

	graph.Remove(node1);
	graph.Print();
	graph.Info();
}

