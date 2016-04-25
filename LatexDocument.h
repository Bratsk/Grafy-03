#pragma once

#include <fstream>
#include <deque>
#include <list>
#include "Graph.h"

/** \brief statyczna klasa LatexDokument generuje dokument w formacie LaTeX
*/

class LatexDocument
{
public:
	/** \brief Metoda generuje naglowek dokumentu LaTeX
	*
	* \param graph - strumien wychodzacy do pliku
	* \param NumberOfVertices - liczba wierzcholkow
	* \param NameOfFile - nazwa pliku, ktory jest generowany
	* \param OverRead - ???
	*
	*/
	static void printDistanceVector(std::deque<node> distanceVector, int ** const adjacencyMatrix);

	static void printSpanningTree(std::list<edge*> edgeList, 
		std::list<edge*> * set, 
		int ** const adjacencyMatrix, 
		size_t numberNodes);


	static void LatexDocumentBegin(std::ofstream &graph);

	/** \brief Metoda generuje koniec dokumentu LaTeX
	* \param graph - strumien wychodzacy do pliku
	*/
	static void LatexDocumentEnd(std::ofstream &graph);

};

