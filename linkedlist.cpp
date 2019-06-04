#include "linkedlist.h"
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <exception>
#include <random>
#include <fstream>
#include <ctime>
#include <climits>

template<typename T> using Vec = std::vector<T>;
template<typename T> using It = typename std::vector<T>::iterator;


/// Insertion sort for vector of integers or strings
template<typename T>
void insertionSort(It<T> start, It<T> end)
{
    if (end - start <= 1)
        return;
    for (It<T> i = start + 1; i < end; ++i)
    {
        T pivot = *i;
        It<T> j = i - 1;
        while (j >= start && *j > pivot)
        {
            *(j + 1) = *j;
            j--;
        }
        *(j + 1) = pivot;
    }
}

/// Merge sort for vector of integers or strings
template<typename T>
void merge(It<T> start, It<T> middle, It<T> end)
{
    Vec<T> result;
    It<T> left(start), right(middle);
    while (left != middle && right != end)
    {
        if (*left <= *right)
            result.push_back(*left++);
        else
            result.push_back(*right++);
    }
    while (left != middle)
        result.push_back(*left++);
    while (right != end)
        result.push_back(*right++);
    for (const T& i : result)
        *start++ = i;
}

template<typename T>
void mergeSort(It<T> start, It<T> end)
{
    if (end - start <= 1)
        return;
    It<T> middle = start + (end - start) / 2;
    mergeSort<T>(start, middle);
    mergeSort<T>(middle, end);
    merge<T>(start, middle, end);
}

template<typename T>
It<T> partition(It<T> start, It<T> end)
{
    It<T> left(start), right(--end), pivot(start + (end - start) / 2);
    while (left < right)
    {
        while (*left < *pivot)
            ++left;
        while (*right > *pivot)
            --right;
        if (*left >= *right)
        {
            std::swap(*left, *right);
            ++left;
            --right;
        }
    }
    return left;
}


/// Quick sort for vector of integers or strings
template<typename T>
void quickSort(It<T> start, It<T> end)
{
    if (end - start <= 1)
        return;
    It<T> pivot = partition<T>(start, end);
    quickSort<T>(start, pivot);
    quickSort<T>(pivot, end);
}

/// Counting sort for vector of integers or strings
void countingSort(It<int> start, It<int> end)
{
    int minel = *std::min_element(start, end), maxel = *std::max_element(start, end);
    Vec<int> v(maxel - minel + 1, 0);
    for (It<int> i = start; i < end; ++i)
        v[*i - minel]++;
    It<int> g = start;
    int k = end - start;
    for (int i = 0; i < v.size(); ++i)
    {
        while (v[i]--)
            *(g++) = i + minel;
    }
}


void test1()
{
    std::vector<int> v{45, 3, 2, 5, 1, 0};
    std::vector<std::string> k{"b", "abba", "mama"};
    mergeSort<int>(v.begin(), v.end());
    mergeSort<std::string>(k.begin(), k.end());
    for (int i : v)
        std::cout << i << " ";
    for (std::string i : k)
        std::cout << i << " ";
}

void test2()
{
    std::vector<int> v{45, 3, 2, 5, 1, 0};
    std::vector<std::string> k{"b", "abba", "mama"};
    quickSort<int>(v.begin(), v.end());
    quickSort<std::string>(k.begin() + 1, k.end());
    for (int i : v)
        std::cout << i << " ";
    for (std::string i : k)
        std::cout << i << " ";
}

void test3()
{
    std::vector<int> v{45, 3, 2, 5, 1, 0};
    std::vector<std::string> k{"b", "abba", "mama"};
    insertionSort<int>(v.begin(), v.end());
    insertionSort<std::string>(k.begin() + 1, k.end());
    for (int i : v)
        std::cout << i << " ";
    for (std::string i : k)
        std::cout << i << " ";
}


/// Insertion sort for doubly Linked List
template<typename T>
void insertionSort(LinkedList<T>& l)
{
    typename LinkedList<T>::Node* p = l.getHead();
    /// The compared node
    typename LinkedList<T>::Node* current = l.getHead()->getNext();
    typename LinkedList<T>::Node* prev = p;
    if (!p || !p->getNext())
        return;
    while (current)
    {
        /// Useful for an already sorted list
        if (prev->getValue() <= current->getValue())
        {
            current = current->getNext();
            prev = prev->getNext();
        }
        else
        {
            /// If the value of the compared node is less than the value of the head
            if (l.getHead()->getValue() > current->getValue())
            {
                prev->setNext(current->getNext());
                current->setNext(l.getHead());
                l.setHead(current);
            }
            else
            {
                p = l.getHead();
                while (p->getNext() && p->getNext()->getValue() < current->getValue())
                    p = p->getNext();
                prev->setNext(current->getNext());
                current->setNext(p->getNext());
                p->setNext(current);
            }
        }
        current = prev->getNext();
    }
}

/// Function swapping values of two nodes
template<class T>
void swapNodes(typename LinkedList<T>::Node* a, typename LinkedList<T>::Node* b)
{
    if (a && b)
    {
        T temp = a->getValue();
        a->setValue(b->getValue());
        b->setValue(temp);
    }

}

/// Consider pivot as the last element
/// and place all smaller elements to the left
/// and greater ones to the right of pivot, respectively
template<class T>
typename LinkedList<T>::Node* partition(typename LinkedList<T>::Node* start, typename LinkedList<T>::Node* end)
{
    /// Set pivot
    T x = end->getValue();
    typename LinkedList<T>::Node* i = start->getPrev();

    /// Traversing a Linked List
    for (typename LinkedList<T>::Node* j = start; j != end; j = j->getNext())
    {
        if (j->getValue() <= x)
        {
            if (!i)
                i = start;
            else
                i = i->getNext();
            swapNodes<T>(i, j);
        }
    }
    if (!i)
        i = start;
    else
        i = i->getNext();
    swapNodes<T>(i, end);
    return i;
}

/// QuickSort implementation for doubly Linked List
template<class T>
void quickSort(typename LinkedList<T>::Node* start, typename LinkedList<T>::Node* end)
{
    if (!start || !end || start == end || start == end->getNext())
        return;
    typename LinkedList<T>::Node* p = partition<T>(start, end);
    quickSort<T>(start, p->getPrev());
    quickSort<T>(p->getNext(), end);
}

/// Output of Linked List
template<typename T>
std::ostream& operator<<(std::ostream& s, const LinkedList<T>& l)
{
    const typename LinkedList<T>::Node* cur = l.getHead();
    while (cur)
    {
        s << cur->getValue();
        cur = cur->getNext();
        if (cur)
            s << " -> ";
    }
    return s;
}


/// Convert vector of integers or strings to the doubly Linked List
template<typename T>
LinkedList<T> convertToList(const std::vector<T>& values)
{
    LinkedList<T> l;
    for (const T& i : values)
        l.appendValueAsTail(i);
    return l;
}

/// Create vector of random numbers
Vec<int> createVectorOfInts(size_t kol)
{
    Vec<int> v(kol);
    std::mt19937 gen(time(nullptr));
    for (int i = 0; i < kol; ++i)
    {
        size_t k = (rand() % INT_MAX) + 1;
        std::uniform_int_distribution<int> distr(0, k);
        v[i] = distr(gen);
    }
    return v;

}

/// Create a random string
std::string generateRandomString(uint maxOutputLength = 15,
                                 std::string allowedChars = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
{
    uint outputLength = rand() % maxOutputLength + 1;

    int randomIndex;
    std::string outputString = "";

    for (uint i = 0; i < outputLength; ++i)
    {
        randomIndex = rand() % allowedChars.length();
        outputString += allowedChars[randomIndex];
    }

    if (outputString.empty())
    {
        return generateRandomString(maxOutputLength, allowedChars);
    }
    else
    {
        return outputString;
    }
}

/// Create vector of random strings
Vec<std::string> createVectorOfStrings(size_t kol)
{
    Vec<std::string> v;
    for (size_t j = 0; j < kol; ++j)
        v.push_back(generateRandomString());
    return v;
}


void mainTest(size_t k, std::ofstream& quick, std::ofstream& merge,
              std::ofstream& insertion, std::ofstream& counting, std::ofstream& out)
{
    double timeinsec1 = 0, timeinsec2 = 0, timeinsec3 = 0,
            timeinsec4 = 0, timeinsec5 = 0, timeinsec6 = 0,
            timeinsec7 = 0, timeinsec8 = 0, timeinsec9 = 0,
            timeinsec10 = 0, timeinsec11 = 0;
    for (int j = 0; j < 3; ++j)
    {
        Vec<int> vec = createVectorOfInts(k);

        Vec<std::string> strvec = createVectorOfStrings(k);

        LinkedList<int> list = convertToList(vec);

        LinkedList<std::string> strlist = convertToList(strvec);

//-----Quick for vectors

        clock_t start1 = clock();
        quickSort<int>(vec.begin(), vec.end());
        clock_t end1 = clock();

        timeinsec1 += (double) (end1 - start1) / CLOCKS_PER_SEC;

//-----Quick

        clock_t start2 = clock();
        quickSort<std::string>(strvec.begin(), strvec.end());
        clock_t end2 = clock();

        timeinsec2 += (double) (end2 - start2) / CLOCKS_PER_SEC;

//-----Quick

        clock_t start3 = clock();
        quickSort<int>(list.getHead()->getNext(), list.getHead());
        clock_t end3 = clock();

        timeinsec3 += (double) (end3 - start3) / CLOCKS_PER_SEC;


//-----Quick
        clock_t start4 = clock();
        quickSort<std::string>(strlist.getHead()->getNext(), strlist.getHead());
        clock_t end4 = clock();

        timeinsec4 += (double) (end4 - start4) / CLOCKS_PER_SEC;

//-----Merge

        clock_t start5 = clock();
        mergeSort<int>(vec.begin(), vec.end());
        clock_t end5 = clock();

        timeinsec5 += (double) (end5 - start5) / CLOCKS_PER_SEC;

//-----Merge

        clock_t start6 = clock();
        mergeSort<std::string>(strvec.begin(), strvec.end());
        clock_t end6 = clock();

        timeinsec6 += (double) (end6 - start6) / CLOCKS_PER_SEC;

//-----Insertion
        clock_t start7 = clock();
        insertionSort<int>(vec.begin(), vec.end());
        clock_t end7 = clock();

        timeinsec7 += (double) (end7 - start7) / CLOCKS_PER_SEC;

//-----Insertion

        clock_t start8 = clock();
        insertionSort<std::string>(strvec.begin(), strvec.end());
        clock_t end8 = clock();

        timeinsec8 += (double) (end8 - start8) / CLOCKS_PER_SEC;

//-----Insertion

        clock_t start9 = clock();
        insertionSort<int>(list);
        clock_t end9 = clock();

        timeinsec9 += (double) (end9 - start9) / CLOCKS_PER_SEC;


//-----Insertion
        clock_t start10 = clock();
        insertionSort<std::string>(strlist);
        clock_t end10 = clock();

        timeinsec10 += (double) (end10 - start10) / CLOCKS_PER_SEC;

//-----Counting

        clock_t start11 = clock();
        countingSort(vec.begin(), vec.end());
        clock_t end11 = clock();

        timeinsec11 += (double) (end11 - start11) / CLOCKS_PER_SEC;
    }
    quick << k << ", " << timeinsec1 / 3;
    quick << ", " << timeinsec2 / 3;
    quick << ", " << timeinsec3 / 3;
    quick << ", " << timeinsec4 / 3 << "\n";

    merge << k << ", " << timeinsec5 / 3;
    merge << ", " << timeinsec6 / 3 << "\n";

    insertion << k << ", " << timeinsec7 / 3;
    insertion << ", " << timeinsec8 / 3;
    insertion << ", " << timeinsec9 / 3;
    insertion << ", " << timeinsec10 / 3 << "\n";

    counting << k << ", " << timeinsec11 / 3 << "\n";


    out << k << ", " << (timeinsec1 / 3 + timeinsec2 / 3 + timeinsec3 / 3 + timeinsec4 / 3) / 4;

    out << ", " << (timeinsec5 / 3 + timeinsec6 / 3) / 2;

    out << ", " << (timeinsec7 / 3 + timeinsec8 / 3 + timeinsec9 / 3 + timeinsec10 / 3) / 4;

    out << ", " << timeinsec11 / 3 << "\n";


}

int main()
{
    std::ofstream quick("/Users/macbook/Desktop/quick.csv"),
    merge("/Users/macbook/Desktop/merge.csv"), insertion("/Users/macbook/Desktop/insertion.csv"),
    counting("/Users/macbook/Desktop/quick.csv"), out("/Users/macbook/Desktop/quick.csv");
    for (int i = 1; i <= 5; ++i)
        mainTest(10 * i, quick, merge, insertion, counting, out);
    return 0;

}