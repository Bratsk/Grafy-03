#include "main.h"
#include <iostream>

typedef GraphConnectedWeighted::size_type size;

int main(int argc, char ** argv)
{
	//srand(time(0));
	std::cout << "Choose an action:" << std::endl;
	GraphConnectedWeighted * graph = 0;
	//	Generator new_generator;
	unsigned option;
	do
	{
		std::cout
			<< "1	: losowanie grafu spojnego z wagami\n"
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
				constexpr size numberNodes = 7;
				int ** adjacencyMatrix = new int *[numberNodes];
				//reading matrix from file
				std::ifstream fromFile("adjacencyMatrix.txt", std::ios_base::in);
				char comma; //comma only reads the separating character
				for(int i = 0; i < numberNodes; i++)
				{
					adjacencyMatrix[i] = new int[numberNodes];
					//reading file
					for (int j = 0; j < numberNodes; j++)
					{
						fromFile >> adjacencyMatrix[i][j] >> comma;
					}
				}
				std::cout << "sucessfully read matrix from file" << std::endl;
				//read matrixs
				for(int i = 0; i < numberNodes; i++)
				{
					for(int j = i; j < numberNodes; j++)
					{
						adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
					}
				}
				graph = new GraphConnectedWeighted(adjacencyMatrix, numberNodes);
				std::cout << *graph << std::endl;
				break;
			}
		case 2:;
			{
				graph->dijkstra(0);
				break;
			}
		case 3:;
			{
				graph->distanceMatrix();
				graph->printDistanceMatrix();
				break;
			}
		case 4:;
			{
				graph->printDistanceMatrix();
				int center = graph->GraphCenter();
				std::cout << "center = " << center << std::endl;
				break;
			}
		case 5:;
			{
				graph->printDistanceMatrix();
				int minmax = graph->GraphCenterMinMax();
				std::cout << "minmax = " << minmax << std::endl;
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