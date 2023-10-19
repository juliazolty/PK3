#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>


template <typename T>  //deklarujemy wzorzec kt�rego argumentem jest typ T
class Stack {
private:
    T* data;          // wskaznik na tablice dynamiczna
    int size;         // rozmiar stosu
    int top;          // indeks wierzcholka stosu

public:
    // Konstruktor przyjmuj�cy rozmiar tablicy
    Stack(int stackSize) {
        size = stackSize;
        data = new T[size];
        top = -1;
    }

    // destruktor
    ~Stack() {
        delete[] data;
    }

    // stos pusty -true
    bool isEmpty() const {
        return top == -1;
    }

    // stos pusty -true
    bool isFull() const {
        return top == size - 1;
    }

    // dodawanie elementu na stos 
    void push(const T& element) {
        if (isFull()) {
            throw std::overflow_error("Stack is full");
        }
        data[++top] = element;
    }

    // metoda usuwa element znajdujący się na podanej pozycji w liście, a następnie go zwraca
    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[top--];
    }

    // Metoda sum - sumuje wszystkie elementy stosu i zwraca wynik
    T sum() const {
        T result = T();  // 0 lub pusty string 
        for (int i = 0; i <= top; i++) {
            result += data[i];
        }
        return result;
    }
};

// Szablon char 
template <>
char Stack<char>::sum() const {
    int result = 0;
    for (int i = 0; i <= top; i++) {
        result += static_cast<int>(data[i]);
    }
    return static_cast<char>(result);
}

// Szablon string
template <>
std::string Stack<std::string>::sum() const {
    std::string result;
    for (int i = 0; i <= top; i++) {
        result += data[i];
    }
    return result;
}


int main() {
   
    Stack<int> intStack(10);
    intStack.push(1);
    intStack.push(6);
  
    std::cout << "Suma elementow na stosie int: " << intStack.sum() << std::endl;

    // Przyk�ad u�ycia stosu dla char
    Stack<char> charStack(15); 
    charStack.push('stos');
    std::cout << "Suma elementow na stosie char: " << charStack.sum() << std::endl;

    // Przyk�ad u�ycia stosu dla std::string
    Stack<std::string> stringStack(5);
    stringStack.push("Hello");
    stringStack.push(", ");
    stringStack.push("world!");
    std::string concatenatedString = stringStack.sum();

    std::cout << "Suma elementow na stosie string: " << concatenatedString << std::endl;
    system("pause");
    return 0;
    
    
}