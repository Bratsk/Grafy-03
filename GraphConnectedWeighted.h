#pragma once

#include "Graph.h"
#include <iostream>
struct node
{
	typedef char name_type;
	typedef unsigned id_type;
	typedef unsigned distance_type;
	typedef char source_node_type;
	name_type name; //symbolic name of node
	id_type id; //position in deque
	distance_type distance; //distance source
	source_node_type sourceNode; //prevous node width shortest path
	
};

struct edge
{
	typedef unsigned node_type;
	typedef unsigned weight_type;
	typedef unsigned set_type;
	node_type a;
	node_type b;
	weight_type weight;
	set_type set;
};

bool distanceLess(const node a, const node b);
bool edgeWeight(const edge * e1, const edge * e2);


/** klasa reprezentująca spojny graf losowy, z przypisanymi wagami*/
class GraphConnectedWeighted : public Graph
{
	friend std::ostream & operator<<(std::ostream & o, const GraphConnectedWeighted & graph);
public:
	//zadanie 3.1

	GraphConnectedWeighted(int ** adjacencyMatrix, const size_type nodes);

	/** konstruktor generuje graf w sposob losowy albo G(n,l) lub G(n,p)
		jak w zadaniu 1.3
		\param n ilosc wierzcholkow
		\param l ilosc krawedzi
	*/
	GraphConnectedWeighted(const size_type n, const size_type l);

	/**
		\param n ilosc wierzcholkow
		\param p procentowa liczba krawedzi*/
	GraphConnectedWeighted(const size_type n, const float p);

	/** Default destructor */
	virtual ~GraphConnectedWeighted();


	size_type getNumberNodes() const
	{
		return _numberNodes;
	}

	const int * operator[](size_type i) const
	{
		return _adjacencyMatrix[i];
	}

	/* funkcja tworzy dokument LaTeX z graficzna reprezentacja grafu */
	void toLatex() const override;

	/**
	  * zadanie 3.2 algorytm Dijkstry
	  * @param source source node from which the Dijkstra algorithm is calculated
	  * @param resultArray array in wich the result is written
	  */
	void dijkstra(size_type source, int * resultArray = nullptr) const;

	//zadanie 3.3
	/** \brief obliczanie macierzy odleglosci dla wszystkich wierzcholkow przy pomocy
	*   algorytmu dijkstra
	*  \return macierz odleglosci
	*/
	void  distanceMatrix() const;

	void printDistanceMatrix() const;

	/**
	  * zadanie 3.4
	  */
	int GraphCenter(void) const;

	int GraphCenterMinMax(void) const;

	/**
	  *	zadanie 3.5 
	  */
	void minimalSpanningTree() const;
	

protected:
	/** dwuwymiarowa symetryczna macierz przechowujaca polaczenia
	  * pomiedzy wierzcholkami
	  * przykladowa reprezentacja
	  * 0 1 0 3
	  * 1 0 2 0
	  * 0 2 0 4
	  * 3 0 4 0
	  * wartosc liczby oznacza wage krawedzi
	  */
	const size_type _numberNodes;
	size_type _numberEdges;
	int ** _adjacencyMatrix;
	mutable int ** _distanceMatrix;
	mutable int ** _minimalSpanningTree;
};


std::ostream & operator<<(std::ostream & o, const GraphConnectedWeighted & graph);