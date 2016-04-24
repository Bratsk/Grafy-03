#include "GraphConnectedWeighted.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <deque>
#include <utility>
#include <list>


bool distanceLess(const node a, const node b)
{
	return a.distance < b.distance;
}


GraphConnectedWeighted::GraphConnectedWeighted(int ** adjacencyMatrix, const size_type nodes) :
	_numberNodes(nodes),
	_adjacencyMatrix(adjacencyMatrix),
	_distanceMatrix(nullptr)
{

}


GraphConnectedWeighted::GraphConnectedWeighted(const size_type n, const size_type l): _numberNodes(0),
                                                                          _adjacencyMatrix(nullptr),
																		  _distanceMatrix(nullptr)
{
	
}


GraphConnectedWeighted::GraphConnectedWeighted(const size_type n, const float p): _numberNodes(0),
																		  _adjacencyMatrix(nullptr),
																		  _distanceMatrix(nullptr)
{
	
}

GraphConnectedWeighted::~GraphConnectedWeighted()
{
	if(_distanceMatrix)
	{
		//delete distancematrix
		for (size_type i = 0; i < _numberNodes; i++)
			delete[] _distanceMatrix[i];
		delete[] _distanceMatrix;
	}
	_distanceMatrix = nullptr;
}

void GraphConnectedWeighted::toLatex() const
{
	return;
}

void GraphConnectedWeighted::dijkstra(size_type sourceNode, int * resultArray) const
{
	typedef unsigned node_type;
	typedef size_type distance_type;
	try
	{
		if (sourceNode > _numberNodes)
			throw std::string("sourceNode do not exist in graph");
	}
	catch(const std::string errorMessage)
	{
		std::cout << errorMessage << std::endl;
	}
	std::deque<node> distanceVector(_numberNodes);
	//setting source node
	distanceVector[sourceNode].name = 'S';
	distanceVector[sourceNode].distance = 0;
	distanceVector[sourceNode].sourceNode = 'S';
	//setting inital values of distance vector
	char nextName = 'a';
	for(size_type i = 0; i < _numberNodes; i++)
	{
		if (distanceVector[i].name != 'S')
		{
			distanceVector[i].name = nextName++;
			distanceVector[i].distance = std::numeric_limits<distance_type>::max();
			distanceVector[i].sourceNode = 0; //value not set
		}
		distanceVector[i].id = i;
	}
	std::list<node::id_type> nodesList;
	for(size_type i = 0; i < _numberNodes; i++)
	{
		nodesList.push_back(distanceVector[i].id);
	}
	//while all nodes are passed
	while(!nodesList.empty())
	{
		node currentNode;
		currentNode.distance = std::numeric_limits<node::distance_type>::max();
		//find minimum node
		for(node::id_type i: nodesList)
		{
			if(distanceVector[i].distance < currentNode.distance)
			{
				currentNode = distanceVector[i];
			}
		}
		std::cout << "found minimum node " << currentNode.name << std::endl;
		//go threw all neighbours
		for (size_type j = 0; j < _numberNodes; j++)
			if(_adjacencyMatrix[currentNode.id][j]) //if neighbour exists
			{
				//check if path is smaller on this neighbour
				distance_type newDistance = currentNode.distance + _adjacencyMatrix[currentNode.id][j];
				distance_type oldDistance = distanceVector[j].distance;
				if (newDistance < oldDistance)
				{
					distanceVector[j].distance = newDistance;
					distanceVector[j].sourceNode = currentNode.name;
				}
			}
		//remove node from list
		nodesList.remove(currentNode.id);
	}
	//print result to screen
	for(size_type i = 0; i < _numberNodes; i++)
	{
		std::cout 
			<< std::setw(4) << distanceVector[i].name 
			<< std::setw(4) << distanceVector[i].id
			<< std::setw(4) << distanceVector[i].distance 
			<< std::setw(4) << distanceVector[i].sourceNode 
			<< std::endl;
	}
	//if resultArray provided as argument
	if(resultArray)
		for(auto i = 0; i < _numberNodes; i++)
			resultArray[i] = distanceVector[i].distance;
	return;
}

int GraphConnectedWeighted::GraphCenter() const
{
	int * sumColumns = new int[_numberNodes];
	std::cout << "sum";
	int min = std::numeric_limits<int>::max(); //infinity
	for (size_type i = 0; i < _numberNodes; i++)
	{
		sumColumns[i] = 0;
		for (size_type j = 0; j < _numberNodes; j++)
		{
			sumColumns[i] += _distanceMatrix[j][i];
		}
		std::cout << std::setw(3) << sumColumns[i];
		if (sumColumns[i] < min)
			min = sumColumns[i];
	}
	std::cout << std::endl;
	delete[] sumColumns;
	return min;
}

int GraphConnectedWeighted::GraphCenterMinMax() const
{
	int * maxColumns = new int[_numberNodes];
	std::cout << "max";
	int minmax = std::numeric_limits<int>::max(); //infinity
	for (size_type i = 0; i < _numberNodes; i++)
	{
		//initalising new max columns array
		maxColumns[i] = 0;
		//searching for maximum in each column
		for (size_type j = 0; j < _numberNodes; j++)
		{
			if (maxColumns[i] < _distanceMatrix[j][i])
				maxColumns[i] = _distanceMatrix[j][i];
		}
		//print max values to screen
		std::cout << std::setw(3) << maxColumns[i];
		if (maxColumns[i] < minmax)
			minmax = maxColumns[i];
	}
	std::cout << std::endl;
	delete[] maxColumns;
	return minmax;
}

void GraphConnectedWeighted::minimalSpanningTree() const
{
	return;
}

void GraphConnectedWeighted::distanceMatrix() const
{
	_distanceMatrix = new int *[_numberNodes];
	for(size_type i = 0; i < _numberNodes; i++)
	{
		int * dijkstra_i_vector = new int[_numberNodes];
		this->dijkstra(i, dijkstra_i_vector);
		_distanceMatrix[i] = dijkstra_i_vector;
	}
	return;
}

void GraphConnectedWeighted::printDistanceMatrix() const
{
	//print graph to screen
	char nodeName = 'A';
	std::cout << "   ";
	for (size_type i = 0; i < _numberNodes; i++)
		std::cout << std::setw(3) << nodeName++;
	std::cout << std::endl;
	nodeName = 'A';
	for (size_type i = 0; i < _numberNodes; i++)
	{
		std::cout << std::setw(3) << nodeName++;
		for (size_type j = 0; j < _numberNodes; j++)
		{
			std::cout << std::setw(3) << _distanceMatrix[i][j];
		}
		std::cout << std::endl;
	}
}

std::ostream & operator<<(std::ostream & o, const GraphConnectedWeighted & graph)
{
	char nodeName = 'A';
	o << "  ";
	for (Graph::size_type j = 0; j < graph.getNumberNodes(); j++)
	{
		o << std::setw(3) << nodeName++;
	}
	o << '\n'<< std::endl;
	nodeName = 'A';
	for(Graph::size_type i = 0; i < graph.getNumberNodes(); i++)
	{
		o << std::setw(2) << nodeName++;
		for(Graph::size_type j = 0; j < graph.getNumberNodes(); j++)
		{
			o << std::setw(3) << graph[i][j];
		}
		o << std::endl;
	}
	return o;
}
