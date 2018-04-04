#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Node.hpp"

class Graph {
	private:
		int vertices;
		std::vector<Node*> *adjacencies;
		void DFSEngine(Node* startingVertex);
		void GenerateTopography(int totalVertices);
		void CreateVertices(int totalVertices);
		void CreateEdges(int totalVertices);
		void RandomizeAdjacencyOrders(int totalVertices);
	public:
		Graph(int vertices);
		void AddEdge(Node* first, Node* second);
		void DFS(Node* startingVertex);
		void DemolishWallBetweenNodes(Node* currentNode, Node* prevVisitedNode);
		void PrintGraph();
		Node* AccessRoom(int nodeNum);
};

#endif
