#include "main.h"
#include <fstream>

typedef typename ConnectedWeightedGraph::size_type size;

int main(int argc, char ** argv)
{
	//srand(time(0));
	std::cout << "Choose an action:" << std::endl;
	Graph * graph = 0;
	//	Generator new_generator;
	unsigned option;
	do
	{
		std::cout
			<< "1	: losowanie grafu spójnego z wagami\n"
			<< "2	: algorytmu Dijkstry dla wybranego wierzcholka\n"
			<< "3	: obliczanie macierzy odleglosci\n"
			<< "4	: obliczanie centrum grafu\n"
			<< "5	: obliczanie centrum minimax\n"
			<< "6	: minimalne drzewo rozpinajace\n"
			<< "0	: koniec programu\n" << std::endl;
		std::cin >> option;
		switch(option)
		{
		case 1:;
			{
				constexpr size nodes = 7;
				int ** adjacencyMatrix = new int *[nodes];
				//reading matrix from file
				std::ifstream fromFile("adjacencyMatrix.txt", std::ios_base::in);
				char comma;
				for(int i = 0; i < nodes; i++)
				{
					adjacencyMatrix[i] = new int[nodes];
					//reading file
					for (int j = 0; j < nodes; j++)
					{
						fromFile >> adjacencyMatrix[i][j] >> comma;
						std::cout << adjacencyMatrix[i][j] << " ";
					}
					std::cout << "\n";
				}
				for(int i = 0; i < nodes; i ++)
				{
					for(int j = i; j < nodes; j++)
					{
						adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
					}
				}
				ConnectedWeightedGraph(adjacencyMatrix, nodes);
				break;
			}
		case 2:;
			{
				break;
			}
		case 3:;
			{
				break;
			}
		case 4:;
			{
				break;
			}
		case 5:;
			{
				break;
			}
		case 6:;
			{
				break;
			}
			default: option = 0; break;
		}
		std::cout << std::endl;
	} while (option);
	delete graph;
	return 0;

}