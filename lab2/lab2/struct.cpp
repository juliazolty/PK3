#include <iostream>
#include <vector>

struct RandFill {         
    void operator()(std::vector<int>& wiersz) {
        for (int& num : wiersz) {
            num = std::rand() % 20; 
        }
    }
};  // obiekt funkcyjny generuj�cy losowe liczby w przedziale [0;20] do wype�nienia macierzy

