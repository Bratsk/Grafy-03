#include "GraphConnectedWeighted.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <deque>
#include <utility>
#include <list>
#include "LatexDocument.h"


bool distanceLess(const node a, const node b)
{
	return a.distance < b.distance;
}

bool edgeWeight(const edge * e1, const edge * e2)
{
	return e1->weight < e2->weight;
}

GraphConnectedWeighted::GraphConnectedWeighted(int ** adjacencyMatrix, const size_type nodes) :
	_numberNodes(nodes), _numberEdges(0),
	_adjacencyMatrix(adjacencyMatrix),
	_distanceMatrix(nullptr), 
	_minimalSpanningTree(nullptr)
{
	for (size_type i = 0; i < _numberNodes; i++)
	{
		for (size_type j = i; j < _numberNodes; j++)
		{
			if (_adjacencyMatrix[i][j])
			{
				_numberEdges++;
			}
		}
	}
}

GraphConnectedWeighted::GraphConnectedWeighted(const size_type n, const size_type l): 
	_numberNodes(0), _numberEdges(0),
	_adjacencyMatrix(nullptr),
	_distanceMatrix(nullptr), 
	_minimalSpanningTree(nullptr)
{
	
}

GraphConnectedWeighted::GraphConnectedWeighted(const size_type n, const float p): 
	_numberNodes(0), _numberEdges(0),
	_adjacencyMatrix(nullptr),
	_distanceMatrix(nullptr), 
	_minimalSpanningTree(nullptr)
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
	LatexDocument::printDistanceVector(distanceVector, _adjacencyMatrix);
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
	//create list of all edges
	std::list<edge*> edgeList;

	for (size_type i = 0; i < _numberNodes; i++)
	{
		for (size_type j = i; j < _numberNodes; j++)
		{
			if (_adjacencyMatrix[i][j])
			{
				edge * newEdge = new edge;
				newEdge->a = i;
				newEdge->b = j;
				newEdge->weight = _adjacencyMatrix[i][j];
				
				edgeList.push_back(newEdge);
			}
		}
	}
	edgeList.sort(edgeWeight);
	
	edge::set_type setcounter = 0;
	for (std::list<edge*>::iterator i = edgeList.begin(); i != edgeList.end(); ++i)
		(*i)->set = setcounter++;
	std::cout << "print edgeList" << std::endl;
	std::cout
		<< std::setw(4) << "a"
		<< std::setw(4) << "b"
		<< std::setw(8) << "wght"
		<< std::setw(4) << "set" << std::endl;
	for (std::list<edge*>::iterator i = edgeList.begin(); i != edgeList.end(); ++i)
	{
		std::cout
			<< std::setw(4) << (*i)->a << " "
			<< std::setw(3) << (*i)->b << " "
			<< std::setw(6) << (*i)->weight << " "
			<< std::setw(4) << (*i)->set << std::endl;
	}
	//all edges are now added to list which is sorted by weight
	//set counter back to set 0
	setcounter = 0;
	//list for sets
	//maximal size is the number of edges
	std::list<edge*> ** sets = new std::list<edge *> *[_numberEdges];
	//MAIN LOOP - for every edge...0
	for(std::list<edge*>::iterator currentEdge = edgeList.begin(); currentEdge != edgeList.end(); ++currentEdge)
	{
		//edge is connected to set
		bool node_a_connected = false; //connected to set a
		bool node_b_connected = false; //connected to set b
		bool searchSecondSet = false; //second set of edge
		edge::set_type firstSet = 0; //first set value
		//look if the current edge can be added to a set
		for (edge::set_type currentSet = 0; currentSet < setcounter; currentSet++)
		{
			for (std::list<edge *>::iterator n = sets[currentSet]->begin();
				n != sets[currentSet]->end();
				++n)
			{
				//if any connection on a
				if ((*n)->a == (*currentEdge)->a || (*n)->b == (*currentEdge)->a)
				{
					node_a_connected = true;
				}
				//on b
				if ((*n)->a == (*currentEdge)->b || (*n)->b == (*currentEdge)->b)
				{
					node_b_connected = true;
				}
			}
		
			//if both nodes in edge are in set then there is a circle
			//skip this edge
			if (node_a_connected != node_b_connected)
			{
				if (!searchSecondSet) // only one node is connected
				{
					(*currentEdge)->set = currentSet; // set same set value
					sets[currentSet]->push_back(*currentEdge); //add to set m
					searchSecondSet = true; //from now on we will search for the second set
					firstSet = currentSet;
				}
			}
			//searched secend set but not found
			//found two different sets
			//if both belong to a set ...
			else if(node_a_connected == true && true == node_b_connected && 
				// ... but not to the same set ...
				firstSet != currentSet ||
				// ...or they belong only to one set
				node_a_connected != node_b_connected && searchSecondSet)
			{
				//migrate all elements from largerSet to smallerSet
				//larger/smaller refers to index of set
				edge::set_type smallerIndexSet, largerIndexSet;
				smallerIndexSet = firstSet > currentSet ? currentSet : firstSet;
				largerIndexSet = firstSet < currentSet ? currentSet : firstSet;
				while (sets[largerIndexSet]->size())
				{
					std::list<edge *>::iterator firstElement = sets[largerIndexSet]->begin();
					(*firstElement)->set = (*currentEdge)->set;
					sets[smallerIndexSet]->push_back(*firstElement);
					sets[largerIndexSet]->pop_front(); // remove the first element
				}
				//delete empty set
				delete sets[largerIndexSet];
				sets[largerIndexSet] = nullptr;
				//move all other sets one to the front
				for (edge::set_type m = largerIndexSet; m < setcounter - 1; m++)
				{
					sets[m] = sets[m + 1];
				}
				//decrement set counter 
				setcounter--;
			}
		}

		//if no set found
		if (node_a_connected == false && false == node_b_connected)
		{
			sets[setcounter] = new std::list<edge *>;
			(*currentEdge)->set = setcounter;
			sets[setcounter]->push_back(*currentEdge);
			setcounter++;
		}
	}
	
	for (edge::set_type i = 0; i < setcounter; i++)
	{
		std::cout << "set" << i << std::endl;
		for (auto j = sets[i]->begin(); j != sets[i]->end(); ++j)
		{
			std::cout
				<< (*j)->a << " "
				<< (*j)->b << " "
				<< (*j)->weight << " "
				<< (*j)->set << std::endl;
		}
	}
	LatexDocument::printSpanningTree(edgeList, sets[0], _adjacencyMatrix, _numberNodes);
	//delete memory
	for (std::list<edge*>::iterator i = edgeList.begin(); i != edgeList.end(); ++i)
	{
		delete *i;
	}
	for (edge::set_type i = 0; i < setcounter; i++)
	{
		delete sets[i];
		sets[i] = nullptr;
	}
	delete[] sets;

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
