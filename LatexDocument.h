#pragma once

#include <fstream>

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

	static void GenerateGraphBegin(
		std::ofstream &graph,
		int NumberOfVertices,
		std::string NameOfFile, 
		bool OverRead);

	/** \brief Metoda generuje koniec dokumentu LaTeX
	* \param graph - strumien wychodzacy do pliku
	*/
	static void GenerateGraphEnd(std::ofstream &graph);

};

