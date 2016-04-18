#pragma once

#include "Graph.h"
/** klasa reprezentująca spojny graf losowy, z przypisanymi wagami*/
class ConnectedWeightedGraph : public Graph
{
public:
	//zadanie 3.1

	ConnectedWeightedGraph(int ** adjacencyMatrix, const size_type nodes);
	/** konstruktor generuje graf w sposob losowy albo G(n,l) lub G(n,p)
		jak w zadaniu 1.3
		\param n ilosc wierzcholkow
		\param l ilosc krawedzi
		*/
	ConnectedWeightedGraph(const size_type n, const size_type l);
	/**
	\param n ilosc wierzcholkow
	\param p procentowa liczba krawedzi*/
	ConnectedWeightedGraph(const size_type n, const float p);
	/** Default destructor */
	virtual ~ConnectedWeightedGraph();

	/* funkcja tworzy dokument LaTeX z graficzna reprezentacja grafu */
	void toLatex() const override;



	//zadanie 3.3
	/** \brief obliczanie macierzy odleglosci dla wszystkich wierzcholkow przy pomocy
	*   algorytmu dijkstry
	*   \return macierz odleglosci
	*/
	int **  distanceMatrix() const;

protected:
	/** dwuwymiarowa symetryczna macierz przechowujaca polaczenia
	pomiedzy wierzcholkami
	przykladowa reprezentacja
	0 1 0 3
	1 0 2 0
	0 2 0 4
	3 0 4 0
	wartosc liczby oznacza wage krawedzi*/
	const size_type _numberNodes;
	int ** _adjacencyMatrix;

};
