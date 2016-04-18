#include "GraphConnectedWeighted.h"

ConnectedWeightedGraph::ConnectedWeightedGraph(int ** adjacencyMatrix, const size_type nodes) :
	_numberNodes(nodes),
	_adjacencyMatrix(adjacencyMatrix)
{

}


ConnectedWeightedGraph::ConnectedWeightedGraph(const size_type n, const size_type l): _numberNodes(0),
                                                                          _adjacencyMatrix(nullptr)
{
	
}


ConnectedWeightedGraph::ConnectedWeightedGraph(const size_type n, const float p): _numberNodes(0),
																		  _adjacencyMatrix(nullptr)
{
	
}

ConnectedWeightedGraph::~ConnectedWeightedGraph()
{
	
}

void ConnectedWeightedGraph::toLatex() const
{
	return;
}

 int ** ConnectedWeightedGraph::distanceMatrix() const
{
	return _adjacencyMatrix;
}



