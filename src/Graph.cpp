#include "../include/Graph.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>


Graph::Graph(int vertices){
	this->vertices = vertices;
	adjacencies = new std::vector<Node*>[vertices];
	GenerateTopography(vertices);
	DFS(adjacencies[0].front());
}

void Graph::GenerateTopography(int totalVertices){
	CreateVertices(vertices);
	CreateEdges(vertices);
	RandomizeAdjacencyOrders(vertices);
	
}

void Graph::CreateVertices(int totalVertices){
	for (int i=0; i<totalVertices; i++){
		adjacencies[i].push_back(new Node(i));
	}
}

void Graph::CreateEdges(int totalVertices){
	//connect nodes via edges(add to adjacency list)
	/* THIS SECTION IS CURRENTLY HARD-CODED FOR 25 VERTICES
	 * TODO:
	 * 	check that vertices is a sqrt'able number
	 * 	R is sqrt(vertices)
	 * 	add edge to any node s.t. addedOrder = +/-1, +/-R */
	for (int j=0; j<totalVertices; j++){
		if ((j-1) >= 0 && (j-1)!=4 && (j-1)!=9 && (j-1)!=14 && (j-1)!=19) {
			AddEdge(adjacencies[j].front(),adjacencies[j-1].front());
		}
		if ((j+1)<totalVertices && (j+1)!=5 && (j+1)!=10 && (j+1)!=15 && (j+1)!=20){
			AddEdge(adjacencies[j].front(),adjacencies[j+1].front());
		}
		if ((j-5) >= 0){
			AddEdge(adjacencies[j].front(),adjacencies[j-5].front());
		}
		if ((j+5)<totalVertices){
			AddEdge(adjacencies[j].front(),adjacencies[j+5].front());
		}
	}
}

void Graph::RandomizeAdjacencyOrders(int totalVertices){
	//done for purposes of randomizing DFS branch selection
	for (int k=0; k<totalVertices; k++){
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(adjacencies[k].begin()+1, adjacencies[k].end(), 
				std::default_random_engine(seed));
	}
}

void Graph::AddEdge(Node* first, Node* second){
	/* adding edge in directed fashion, relying on later calls of the AddEdge fn to
	 * implement the undirected behavior */
	adjacencies[first->GetCreatedOrder()].push_back(second);
}

void Graph::DFS(Node* startingVertex){

	for (Node* node : adjacencies[startingVertex->GetCreatedOrder()]){
		node->visited = false;
	}
	DFSEngine(startingVertex);
}

void Graph::DFSEngine(Node* startingVertex){
	for (Node* currentNode : adjacencies[startingVertex->GetCreatedOrder()]){
		//std::cout<<currentNode->GetCreatedOrder()<<std::endl;
		if (currentNode->visited == false){
			currentNode->visited = true;
			DemolishWallBetweenNodes(startingVertex, currentNode);
			DFSEngine(currentNode);
		}
	}
}

void Graph::DemolishWallBetweenNodes(Node* currentNode, Node* prevVisitedNode){
	int currentNodeOrderValue = currentNode->GetCreatedOrder();
	int prevNodeOrderValue = prevVisitedNode->GetCreatedOrder();
	int difference = currentNodeOrderValue - prevNodeOrderValue;
	switch(difference){
		case (-1):
			//std::cout<<"demo east wall at "<<currentNode->GetCreatedOrder()<<std::endl;
			//std::cout<<"erecting west wall at "<<prevVisitedNode->GetCreatedOrder()<<std::endl;
			currentNode->DemolishWall(false, false, true, false);
			prevVisitedNode->DemolishWall(false, false, false, true);
			break;
		case (1):
			currentNode->DemolishWall(false, false, false, true);
			//std::cout<<"demo west wall at "<<currentNode->GetCreatedOrder()<<std::endl;
			//std::cout<<"erecting east wall at "<<prevVisitedNode->GetCreatedOrder()<<std::endl;
			prevVisitedNode->DemolishWall(false, false, true, false);
			break;
		case (-5):
			//std::cout<<"demo north wall at "<<currentNode->GetCreatedOrder()<<std::endl;
			//std::cout<<"erecting south wall at "<<prevVisitedNode->GetCreatedOrder()<<std::endl;
			currentNode->DemolishWall(true, false, false, false);
			prevVisitedNode->DemolishWall(false, true, false, false);
			break;
		case (5):
			//std::cout<<"demo south wall at "<<currentNode->GetCreatedOrder()<<std::endl;
			//std::cout<<"erecting north wall at "<<prevVisitedNode->GetCreatedOrder()<<std::endl;
			currentNode->DemolishWall(false, true, false, false);
			prevVisitedNode->DemolishWall(true, false, false, false);
			break;
	}
}

void Graph::PrintGraph(){
	for (int i = 0; i<vertices; i++){
		Node* node = adjacencies[i].front();
		std::cout<<node->GetCreatedOrder()
			<<" walls: N "<<node->HasNorthWall()
			<<" S "<<node->HasSouthWall()
			<<" E "<<node->HasEastWall()
			<<" W "<<node->HasWestWall()<<std::endl;
		/*std::cout<<node->GetCreatedOrder()<<" adj to: ";
		for (Node* node : adjacencies[i]){
			std::cout<<node->GetCreatedOrder()<<" ";
		}*/
		std::cout<<std::endl;
	}
}

Node* Graph::AccessRoom(int nodeNum){
	return adjacencies[nodeNum].front();
}

