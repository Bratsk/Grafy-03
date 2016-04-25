#include "LatexDocument.h"
#include <fstream>

void LatexDocument::printDistanceVector(std::deque<node> distanceVector, int ** const adjacencyMatrix)
{
	std::ofstream tex_ofstream;
	tex_ofstream.open("distanceVector.tex");
	//begin document
	LatexDocumentBegin(tex_ofstream);

	int radius = 4;
	size_t numberNodes = distanceVector.size();
	double stepNode = 360.0 / numberNodes;
	for(size_t i = 0; i < numberNodes; i++)
	{
		tex_ofstream
			<< "\\node (" << distanceVector[i].name << ") "
			<< "at (" << i * stepNode << ":" << radius << ") "
			<< "[circle, draw=" 
			<< (distanceVector[i].distance ? "black" : "red") << "] "
			<< "{" << distanceVector[i].name << "};\n";
	}
	for(size_t i = 0; i < numberNodes; i++)
	{
		for(size_t j = i + 1; j < numberNodes; j++)
		{
			//if both nodes are connected - print
			if(adjacencyMatrix[i][j])
			{
				
				tex_ofstream
					<< "\t\\Edge[" << "label=" << adjacencyMatrix[i][j] << ", ";
				//if j is the sourceNode
				if(distanceVector[i].sourceNode == distanceVector[j].name || 
					distanceVector[j].sourceNode == distanceVector[i].name)
				{
					tex_ofstream
						<< "color=red";
				}
				else
				{
					tex_ofstream
						<< "color=black";
				}
				tex_ofstream
					<< "]"
					<< "(" << distanceVector[i].name << ")"
					<< "(" << distanceVector[j].name << ")\n";
			}
			
		}
		
	}
	//end document
	LatexDocumentEnd(tex_ofstream);
}

void LatexDocument::printSpanningTree(std::list<edge*> edgeList, 
	std::list<edge*> * set, 
	int ** const adjacencyMatrix, size_t numberNodes)
{
	std::ofstream tex_ofstream;
	tex_ofstream.open("spanningTree.tex");
	//begin document
	LatexDocumentBegin(tex_ofstream);
	int radius = 4;
	double stepNode = 360.0 / numberNodes;
	for (size_t i = 0; i < numberNodes; i++)
	{
		tex_ofstream
			<< "\\node (" << i << ") "
			<< "at (" << i * stepNode << ":" << radius << ") "
			<< "[circle, draw="
			<< "red" << "] "
			<< "{" << i << "};\n";
	}
	for(auto i = edgeList.begin(); i != edgeList.end(); ++i)
	{
		tex_ofstream
			<< "\t\\Edge[" << "label=" << adjacencyMatrix[(*i)->a][(*i)->b] << ", ";
		bool isInTree = false;
		for(auto j = set->begin(); j != set->end(); ++j)
		{
			if ((*i)->a == (*j)->a && (*i)->b == (*j)->b)
				isInTree = true;
		}
		//if j is the sourceNode
		
		if (isInTree)
		{
			tex_ofstream
				<< "color=red";
		}
		else
		{
			tex_ofstream
				<< "color=black";
		}
		tex_ofstream
			<< "]"
			<< "(" << (*i)->a << ")"
			<< "(" << (*i)->b << ")\n";
	}
	//end document
	LatexDocumentEnd(tex_ofstream);
}

inline void LatexDocument::LatexDocumentBegin(std::ofstream& tex_ofstream)
{
	tex_ofstream
		<< "\\documentclass{article}\n"
		<< "\\usepackage{color}\n"
		<< "\\usepackage{tkz-graph}\n"
		<< "\\usetikzlibrary{arrows}\n"
		<< "\\begin{document}\n"
		<< "\\begin{tikzpicture}[scale=1.5]\n"
		<< "\\SetGraphUnit{4}\n"
		<< "\\GraphInit[vstyle=Normal]\n"
		<< "\\tikzset{EdgeStyle/.style = {-}}"
		<< std::endl;
}

inline void LatexDocument::LatexDocumentEnd(std::ofstream& tex_ofstream)
{
	tex_ofstream
		<< "\\end{tikzpicture}\n"
		<< "\\end{document}"
		<< std::endl;
	return;
}
