
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime> // do losowo wype³nionego wektora 
#include <cstdlib>
#include <iomanip> // zadanie 2
#include "struct.cpp"
#include <numeric> // Dodatkowy nag³ówek do u¿ycia std::accumulate

// Funkcja globalna zwieksza kazdy element matrixy o 1 //zadanie 4
void increment(int& element) 
{
	element += 1;
};

int main() {
	//zadanie 1 
	std::cout << "*************** zadanie 1 *****************" << std::endl;

	const int liczbaWierszy = 6;
	const int liczbaKolumn = 3;

	// wywo³anie wype³nienia macierzy liczbami losowymi
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//macierz jako wektora wektorów
	std::vector<std::vector<int>> matrix(liczbaWierszy, std::vector<int>(liczbaKolumn));

	// wype³nienie macierzy std::for_each
	std::for_each(matrix.begin(), matrix.end(), RandFill()); //RandFill to obiekt funkcyjny z struct.cpp

	// Wyœwietlenie macierzy
	for (const auto& wiersz : matrix)
	{
		for (const int& num : wiersz)
		{
			std::cout << num << " ";
		}
		std::cout << std::endl;
	};

	//zadanie 2 
	std::cout << '\n';
	std::cout << "*************** zadanie 2 *****************" << std::endl;

	// wypisanie matrixy za pomoc¹ wyra¿enia std::for_each przy u¿yciu std::left i std::setw(4)
	struct wyspisaniematrixy {
		void operator()(const std::vector<int>& rzad) {
			for (int element : rzad)
			{
				std::cout << std::left << std::setw(4) << element;
			}
			std::cout << '\n';
		}
	};
	std::cout << "matrix wypisana za pomoca funktora:" << std::endl;
	std::for_each(matrix.begin(), matrix.end(), wyspisaniematrixy());

	// wypisanie matrixy za pomoc¹ wyra¿enia lambda 

	std::cout << "\nUzycie wyrazenia lambda:" << std::endl;
	std::for_each(matrix.begin(), matrix.end(), [](const std::vector<int>& rz¹d) {
		for (const int& num : rz¹d) {
			std::cout << std::left << std::setw(4) << num;
		}
		std::cout << std::endl;
		});


	//zadanie 3 
	std::cout << '\n';
	std::cout << "*************** zadanie 3 *****************" << std::endl;
	// Transpozycja matrixy
	std::vector<std::vector<int>> matrixT(liczbaKolumn, std::vector<int>(liczbaWierszy));
	for (int i = 0; i < liczbaWierszy; ++i) {
		for (int j = 0; j < liczbaKolumn; ++j) {
			matrixT[j][i] = matrix[i][j];
		}
	};

	// macierze po transpozycji za pomoc¹ wyra¿enia lambda
	std::cout << "\nmacierz po transpozycji wyswietlona za pomoca wyrazenia lambda:\n";
	for (const std::vector<int>& rzad : matrixT) {
		for (int element : rzad) {
			std::cout << std::left << std::setw(4) << element;
		}
		std::cout << '\n';
	};

	//zadanie 4
	std::cout << '\n';
	std::cout << "*************** zadanie 4 *****************" << std::endl;


	//std::for_each do zwiêkszenia ka¿dego elementu matrixy o 1
	std::for_each(matrixT.begin(), matrixT.end(), [](std::vector<int>& row) {
		std::for_each(row.begin(), row.end(), increment);
		});

	std::cout << "\nMacierz po uzyciu funkcji 'increment' czyli zwiekszeniu kazdego elementu macierzy o 1:\n";
	for (const std::vector<int>& row : matrixT) {
		for (int element : row)
		{
			std::cout << std::left << std::setw(4) << element;
		}
		std::cout << '\n';
		
	};

	//zadanie 5 
	std::cout << '\n';
	std::cout << "*************** zadanie 5 *****************" << std::endl;

	// Sortowanie pierwszego wiersza macierzy transponowanej w kolejnosci malejacej
	std::vector<int> firstRowT = matrixT[0];  
	//Stwórz now¹ zmienn¹ firstRowT i przypisz do niej pierwszy rz¹d z wczeœniej transponowanej macierzy
	std::sort(firstRowT.begin(), firstRowT.end(), std::greater<int>());

	// Wypisanie posortowanego wektora za pomoc¹ std::for_each i lambdy
	std::cout << "Pierwszy rzad macierzy transponowanej w kolejnosci malejacej:\n";
	std::for_each(firstRowT.begin(), firstRowT.end(), [](int element) { //wypianie przy uzyciu metody std::for_each
		std::cout << std::left << std::setw(4) << element;
		});
	std::cout << '\n';

	//zadanie 6 
	std::cout << '\n';
	std::cout << "*************** zadanie 6 *****************" << std::endl;

	//algorytm std::transform do spotêgowania drugiego stopnia elementów wektora 
	std::vector<int>& firstRowT = matrixT[1];
	std::transform(firstRowT.begin(), firstRowT.end(), firstRowT.begin(),
		[](int element) { return element * element; }); //potegowanie

	// Wypisanie za pomoc¹ std::for_each 
	std::cout << "Spotegowane elementy drugiergo rzedu macierzy transponowanej :\n";
	std::for_each(firstRowT.begin(), firstRowT.end(), [](int element) {
		std::cout << std::left << std::setw(4) << element;
		});
	std::cout << '\n';
	  

	//zadanie 7
	std::cout << "*************** zadanie 7 *****************" << std::endl;
	// Zadanie 7: Usuwanie elementów nieparzystych za pomoc¹ std::remove_if i std::vector::erase
	std::vector<int>& thirdRowT = matrixT[2];
	thirdRowT.erase(std::remove_if(thirdRowT.begin(), thirdRowT.end(),
		[](int element) { return element % 2 != 0; }),
		thirdRowT.end());

	std::cout << "Trzeci wiersz macierzy po usuniêciu elementów nieparzystych:\n";
	std::for_each(thirdRowT.begin(), thirdRowT.end(), [](int element) {
		std::cout << std::left << std::setw(4) << element;
		});
	std::cout << '\n';

	//zadanie 8 zsumowanie calego wektora  
	std::cout << "*************** zadanie 8 *****************" << std::endl;
	std::cout << '\n';

	// Zadanie 8: Wypisanie sumy ca³ego wektora
	int sum = std::accumulate(thirdRowT.begin(), thirdRowT.end(), 0);
	std::cout << "\nSuma elementów trzeciego wiersza macierzy: " << sum << std::endl;
	system("pause");
	return 0;
}

	

	
	
