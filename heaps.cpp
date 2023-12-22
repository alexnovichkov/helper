#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

#include "datastructures/trees.h"

void heap1()
{
    using T = int;
    int N;
    std::vector<T> a;

#define FILL_FROM_FILE

#ifdef FILL_FROM_FILE
    // Заполнение из файла
    const std::string inputFileName = "input.txt";
    const std::string outputFileName = "output.txt";

    std::ifstream inputFile(inputFileName);
    inputFile >> N;

    a.resize(N);
    for (int i=0; i<N && !inputFile.eof(); ++i) {
        inputFile >> a[i];
    }

//    b.resize(M);
//    for (int i=0; i<M && !inputFile.eof(); ++i) {
//        inputFile >> b[i];
//    }

    std::ofstream outputFile(outputFileName, std::ios_base::trunc);

#else
    // Заполнение случайными числами

    N=6000;
//    M=6000;
//    a.resize(N);
//    b.resize(M);
    a={1,3,2,5,4};

    std::random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : std::time(nullptr);
    std::default_random_engine g(static_cast<std::default_random_engine::result_type>(seed));
    std::uniform_int_distribution intDistrib(0, 40000);

//    for (auto &i: a) i=intDistrib(g);
//    for (auto &i: b) i=intDistrib(g);
#endif
    // Основной алгоритм
    a.insert(a.begin(),0);

    auto start = std::chrono::steady_clock::now();
    bool isHeap = true;
    if (N>1) {
        for (int i=1; i<a.size(); ++i) {

            if (2*i<a.size() && a[i]>a[2*i]) {
                isHeap = false;
                break;
            }
            if ((2*i+1)<a.size() && a[i]>a[2*i+1]) {
                isHeap = false;
                break;
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
#ifdef FILL_FROM_FILE
    outputFile << (isHeap?"YES":"NO");
#else
    auto p = [](std::vector<uint32_t> &v){
        for (auto &i:v)std::cout<<i<<" ";
        std::cout << "\n";
    };
    //p(a);
    //p(b);
    //p(res);
    std::cout << isHeap << std::endl;
#endif
}

using T = int;
auto printVec = [](const std::vector<T> &v){
    for (const T&i : v) std::cout << i<<" ";
    std::cout << "\n";
};

class BinaryHeap
{
public:
    explicit BinaryHeap( int capacity = 100 );
    explicit BinaryHeap( const std::vector<T> & items );

    bool isEmpty( ) const {return currentSize==0;}
    T findMin( ) const;

    //возвращает индекс, в который помещен элемент x
    int insert(const T & x);
    void deleteMin( );
//    void deleteMin( T & minItem );
    void makeEmpty( );

    void replace(T x, T y);
    void print() const { for (int i=1; i<=currentSize; ++i) std::cout << array[i]<<" "; std::cout << "\n";}

private:
    struct S
    {
        S() {};
        T x = T();
        int line = 0;
    };
    size_t currentSize; // Number of elements in heap
    std::vector<T> array; // The heap array
    std::vector<S> indexes;

    void buildHeap( );
    void percolateDown( int hole );
    void percolateUp( int hole );
};

int BinaryHeap::insert( const T & x)
{
    //a[i] = {y, index}
    //Double the size of array of there is not enough space left
    if( currentSize == array.size( )-1) {
        array.resize( array.size( ) * 2 );
//        indexes.resize(array.size());
    }

    // Percolate up
    int hole = ++currentSize;
    T copy = x;

    array[ 0 ] = std::move( copy );
    for( ; x < array[ hole / 2 ]; hole /= 2 ) {
        array[ hole ] = std::move( array[ hole /2]);
//        indexes[hole].x = array[ hole ];
//        indexes[hole].line = indexes[hole/2].line;
    }
    array[ hole ] = std::move( array[ 0 ] );
//    indexes[hole].x = array[ hole ];
//    indexes[hole].line = line;

    return hole;
}

void BinaryHeap::deleteMin( )
{
    if(isEmpty( ) )
        return;

    array[ 1 ] = std::move( array[ currentSize-- ] );
//    indexes[1].x = array[1];
//    indexes[1].line = indexes[currentSize+1].line;
    percolateDown( 1 );
}

//void BinaryHeap::deleteMin( T & minItem )
//{
//    if( isEmpty( ) )
//        return;

//    minItem = std::move( array[ 1 ] );
//    array[ 1 ] = std::move( array[ currentSize-- ] );
//    percolateDown( 1 );
//}

void BinaryHeap::percolateDown( int hole )
{
    int child;
    T tmp = std::move( array[ hole ] );

    for( ; hole * 2 <= currentSize; hole = child )
    {
        child = hole * 2;
        if( child != currentSize && array[ child +1]<array[ child ] )
            ++child;
        if( array[ child ] < tmp )
            array[ hole ] = std::move( array[ child ] );
        else
            break;
    }
    array[ hole ] = std::move( tmp );
}

void BinaryHeap::percolateUp(int hole)
{
    // Percolate up
    T x = array[hole];

    array[ 0 ] = std::move( x );
    for( ; x < array[ hole / 2 ]; hole /= 2 )
        array[ hole ] = std::move( array[ hole /2]);
    array[ hole ] = std::move( array[ 0 ] );
}

BinaryHeap::BinaryHeap( const std::vector<T> & items )
    : array( items.size( ) + 10 ), currentSize{ items.size( ) }
{
    for( size_t i = 0; i < items.size( ); ++i )
        array[ i+1]=items[ i ];
    buildHeap( );
}

BinaryHeap::BinaryHeap( int capacity)
    : array(capacity), currentSize{0}
{

}

void BinaryHeap::buildHeap( )
{
    for( int i = currentSize / 2; i > 0; --i )
        percolateDown( i );
}

T BinaryHeap::findMin( ) const
{
    if( isEmpty( ) )
        return 0;
    return array[1];
}

void BinaryHeap::replace(T x, T y)
{
    auto index = std::find(array.begin()+1, array.end(), x);
    if (index == array.end()) {
        std::cout << x<<"not found\n";
        return;
    }
    auto pos = index-array.begin();
    array[pos] = y;
    percolateUp(pos);
}

void heap2()
{
    int N;
    BinaryHeap h;
    std::vector<T> a;

#define FILL_FROM_FILE

#ifdef FILL_FROM_FILE
    // Заполнение из файла
    const std::string inputFileName = "input.txt";
    const std::string outputFileName = "output.txt";

    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName, std::ios_base::trunc);

    inputFile >> N;
    a.resize(N);


    for (int i=0; i<N && !inputFile.eof(); ++i) {
        std::string op;
        T x, y;
        inputFile >> op;
        if (op=="A") {
            inputFile >> x;
            int pos = h.insert(x);
            a[i+1] = x;

            std::cout << "A:"<<x<<"\n";
            printVec(a);
            h.print();
        }
        if (op=="D") {
            inputFile >> x >> y;
            h.replace(a[x], y);
            std::cout << "D:"<<a[x]<<" "<<y<<"\n";
            h.print();
        }
        if (op=="X") {
            if (h.isEmpty()) outputFile << "*\n";
            else {
                outputFile << h.findMin() << "\n";
                h.deleteMin();
            }
            h.print();
        }
    }

#else
    N=8;
    a.resize(N);


    for (int i=0; i<N && !inputFile.eof(); ++i) {
        std::string op;
        T x, y;
        inputFile >> op;
        if (op=="A") {
            inputFile >> x;
            h.insert(x);
            a[i] = x;
        }
        if (op=="D") {
            inputFile >> x >> y;
            h.replace(a[x], y);
        }
        if (op=="X") {
            if (h.isEmpty()) outputFile << "*\n";
            else {
                outputFile << h.findMin() << "\n";
                h.deleteMin();
            }
        }
    }
#endif
}

void trees()
{
    BinarySearchTree<int> t;
    t.insert(4);
    t.insert(10);
    t.insert(3);
    t.insert(1);
    t.insert(6);
    t.printTree();
    std::cout << "\n";
    t.insert(2);
    //t.remove(6);
    //t.remove(10);
    std::cout << "min " <<t.findMin() << std::endl;
    std::cout << "max " <<t.findMax() << std::endl;
    t.printTree();
}

//int main()
//{
//    //heap2();
//    trees();
//    return 0;
//}
