#pragma once

#ifndef GRAPH_H
#define GRAPH_H

/** klasa Graph reprezentuje ogolny graf
dziedziczone sa po niej rozne typy grafow*/
class Graph
{
public:
	/** typ rozmiaru*/
	typedef int size_type;
	/** typ danych reprezentacji grafu*/
	typedef int value_type;

	/** Default constructor */
	Graph();
	/** Default destructor */
	virtual ~Graph();

	virtual void toLatex() const = 0;
};

#endif // GRAPH_H
