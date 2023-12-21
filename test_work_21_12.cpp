#include <iostream>
#include <algorithm>

// Функция сортировки вставками
void insertionSort(double* elements, int* indices, int size) {
    for (int i = 1; i < size; ++i) {
        double currentElement = elements[i]; // Запоминаем текущий элемент
        int currentIndex = indices[i]; // Запоминаем текущий индекс
        int j = i - 1;

        // Сдвигаем элементы, которые больше текущего, вправо
        while (j >= 0 && elements[j] > currentElement) {
            elements[j + 1] = elements[j]; // Сдвигаем элемент
            indices[j + 1] = indices[j]; // Сдвигаем индекс
            --j;
        }

        // Вставляем текущий элемент на правильное место
        elements[j + 1] = currentElement;
        indices[j + 1] = currentIndex;
    }
}

// Функция сортировки Шелла
void shellSort(double* elements, int* indices, int size) {
    // Генерация последовательности длин шагов для сортировки Шелла
    for (int gap = size / 2; gap > 0; gap /= 2) {
        // Применение сортировки вставками с текущим шагом
        for (int i = gap; i < size; ++i) {
            double temp = elements[i]; // Запоминаем текущий элемент
            int tempIndex = indices[i]; // Запоминаем текущий индекс
            int j;

            // Сдвиг элементов, чтобы найти правильное место для вставки элемента
            for (j = i; j >= gap && elements[j - gap] > temp; j -= gap) {
                elements[j] = elements[j - gap]; // Сдвигаем элемент
                indices[j] = indices[j - gap]; // Сдвигаем индекс
            }

            // Вставка элемента на правильное место
            elements[j] = temp;
            indices[j] = tempIndex;
        }
    }
}

int main() {
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    /*
    Тут можно было использовать как структуру, например 
    struct Element {
        double value;
        int index;
    };
    в сочетании с 
    вектором std::vector<Element> elements(size);
    или
    Element* elements = new Element[size];
    */
    double* elements = new double[size]; // Создание массива элементов
    int* indices = new int[size]; // Создание массива индексов
    /*
    Для тестов можно было использовать
    // Заполнение массивов случайными значениями
    for (int i = 0; i < size; i++) {
        elements[i] = rand() % 1000 / 10.0; // Пример случайных значений от 0 до 100
        indices[i] = i;
    }
    */
    std::cout << "Enter the elements of the array separated by space:\n";
    for (int i = 0; i < size; ++i) {
        std::cin >> elements[i]; // Ввод элементов массива
        indices[i] = i; // Заполнение массива индексов
    }
    /*
    Тут можно было использовать функцию 
    bool compareElements(const Element& a, const Element& b) {
        return a.value < b.value || (a.value == b.value && a.index < b.index);
    }
    и сортировку 
    std::sort(elements, elements + size, compareElements);
    , но было принято решение реализовать свои функции сортировки. 
    По идее можно добавить для случаев, когда размер массива больше лио равен 10^8 поразрядую сортировку (LSD-версия), 
    так как она работает быстрее в больших массивах, но было принято решение, что данных двух сортировок достаточно.
    */
    // Выбор сортировки в зависимости от размера массива
    if (size < 100000) {
        insertionSort(elements, indices, size); // Вызов сортировки вставками
    } else  {
        shellSort(elements, indices, size); // Вызов сортировки Шелла
    }
    /*
    // Можно вывести отсортированный массив для проверки следующим образом:
    // Вывод отсортированных элементов массива
    for (int i = 0; i < size; i++)
        std::cout << elements[i] << " ";
    std::cout << "\n";
    */
    // Вывод двух наибольших элементов и их индексов
    std::cout << "Two largest elements of the array and their indices:\n";
    for (int i = size - 1; i >= std::max(0, size - 2); --i) {
        std::cout << "Element: " << elements[i] // Вывод элемента
                  << ", Index: " << indices[i] << std::endl; // Вывод индекса
    }

    delete[] elements; // Освобождение памяти от массива элементов
    delete[] indices; // Освобождение памяти от массива индексов

    return 0;
}
