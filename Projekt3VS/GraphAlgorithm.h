#pragma once

//zadanie 3.2
/** \brief algorytm Dijstry znajdujacy najkrotsze sciezki
*
* \param graphMatrix - macierz reprezentujaca graf spojny z wagami
* \param numberVertice - numer wierzcholka, ktory jest zrodlem
* \return zwracana jest zaalokowana tablica z wagami
*/

int* dijkstry(int const** graphMatrix, int numberVertice);


//zadanie 3.4

/** \brief obliczanie centrum grafu
* \param distanceMatrix - macierz odleglisci
* \return zwraca numer wierzcholka, ktory jest w centrum
*/

int graphCenter(int const ** distanceMatrix);

