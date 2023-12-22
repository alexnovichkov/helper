#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

//template <typename Comparable>
//void merge(std::vector<Comparable> & a, std::vector<Comparable> & tmpArray,
//           int leftPos, int rightPos, int rightEnd )
//{
//    int leftEnd = rightPos - 1;
//    int tmpPos = leftPos;
//    int numElements = rightEnd - leftPos + 1;

//    while (leftPos <= leftEnd && rightPos <= rightEnd )
//        if( a[ leftPos ] <= a[ rightPos ] )
//            tmpArray[tmpPos++] = std::move(a[leftPos++]);
//        else
//            tmpArray[tmpPos++] = std::move(a[rightPos++]);

//    while(leftPos <= leftEnd) // копируем остаток первой половины
//        tmpArray[tmpPos++] = std::move(a[leftPos++]);

//    while(rightPos <= rightEnd) // копируем остаток правой половины
//        tmpArray[tmpPos++] = std::move(a[rightPos++]);

//    // копируем tmpArray обратно
//    for(int i = 0; i < numElements; ++i, --rightEnd)
//        a[rightEnd] = std::move(tmpArray[rightEnd]);
//}

uint32_t * RadixSort(uint32_t * a, uint32_t *b, size_t count)
{
    size_t mIndex[4][256] = {0};            // count / index matrix
    size_t i,j,m,n;
    uint32_t u;
    for(i = 0; i < count; i++){         // generate histograms
        u = a[i];
        for(j = 0; j < 4; j++){
            mIndex[j][(size_t)(u & 0xff)]++;
            u >>= 8;
        }
    }
    for(j = 0; j < 4; j++){             // convert to indices
        m = 0;
        for(i = 0; i < 256; i++){
            n = mIndex[j][i];
            mIndex[j][i] = m;
            m += n;
        }
    }
    for(j = 0; j < 4; j++){             // radix sort
        for(i = 0; i < count; i++){     //  sort by current lsb
            u = a[i];
            m = (size_t)(u>>(j<<3))&0xff;
            b[mIndex[j][m]++] = u;
        }
        std::swap(a, b);                //  swap ptrs
    }
    return(a);
}

void RadixSort(std::vector<uint32_t> & a, std::vector<uint32_t> &b, size_t count)
{
    size_t mIndex[4][256] = {0};            // count / index matrix
    size_t i,j,m,n;
    uint32_t u;
    for(i = 0; i < count; i++){         // generate histograms
        u = a[i];
        for(j = 0; j < 4; j++){
            mIndex[j][(size_t)(u & 0xff)]++;
            u >>= 8;
        }
    }
    for(j = 0; j < 4; j++){             // convert to indices
        m = 0;
        for(i = 0; i < 256; i++){
            n = mIndex[j][i];
            mIndex[j][i] = m;
            m += n;
        }
    }
    for(j = 0; j < 4; j++){             // radix sort
        for(i = 0; i < count; i++){     //  sort by current lsb
            u = a[i];
            m = (size_t)(u>>(j<<3))&0xff;
            b[mIndex[j][m]++] = u;
        }
        std::swap(a, b);                //  swap ptrs
    }
    //return std::move(a);
}

std::vector<uint32_t> sortCartesianProducts(std::vector<uint32_t> a, std::vector<uint32_t> b)
{
    const int n = a.size();
    const int m = b.size();

    //0. Простейшие проверки
    if (n==0 || m==0) return std::vector<uint32_t>();

    if (n==1) {
        std::sort(b.begin(), b.end());
        for (uint32_t &i: b) i*=a[0];
        return b;
    }
    if (m==1) {
        std::sort(a.begin(), a.end());
        for (uint32_t &i: a) i*=b[0];
        return a;
    }

    //сюда будем складывать результат
    std::vector<uint32_t> res(n*m);
    //временный вектор
    std::vector<uint32_t> temp(n*m);

    unsigned idx=0;
    for (auto i=0; i<n; ++i) {
        for (auto j=0; j<m; ++j)
            res[idx++]=a[i]*b[j];
    }

//    RadixSort(res,temp,res.size());
    RadixSort(res.data(),temp.data(),res.size());

//    //1. сортируем больший вектор, так как тогда понадобится меньше последовательных слияний
//    auto & firstVec = (n>m?a:b);
//    auto & secondVec = (n>m?b:a);
//    std::sort(firstVec.begin(), firstVec.end());
//    auto &firstVecSize = (n>m?n:m);
//    auto &secondVecSize = (n>m?m:n);

//    //Начальное смещение в векторе res равно 0. Оно будет увеличиваться с шагом firstVecSize
//    int offset = 0;

//    //2. Инициализируем вектор res попарными произведениями первого вектора на первый элемент второго
//    for (int i=0; i<firstVecSize; ++i)
//        res[i+offset] = firstVec[i]*secondVec[0];

//    offset += firstVecSize;

//    //3. в цикле добавляем в res вектор попарных произведений
//    for (int j = 1; j < secondVecSize; ++j) {

//        for (int i=0; i<firstVecSize; ++i)
//            res[i+offset] = firstVec[i]*secondVec[j];
//        //и сливаем два вектора
//        merge(res, temp, 0, j*firstVecSize, (j+1)*firstVecSize-1);
//        offset += firstVecSize;
//    }

    return res;
}

uint64_t getSum(std::vector<uint32_t> &v)
{
    uint64_t res=0;
    for (unsigned i=0;i<v.size(); i+=10) {
        res += v[i];
    }
    return res;
}



int main1()
{
    uint64_t sum = 0;
    int N, M;
    std::vector<uint32_t> a;
    std::vector<uint32_t> b;
    std::vector<uint32_t> res;

//#define FILL_FROM_FILE

#ifdef FILL_FROM_FILE
    // Заполнение из файла
    const std::string inputFileName = "input.txt";
    const std::string outputFileName = "output.txt";

    std::ifstream inputFile(inputFileName);
    inputFile >> N >> M;

    a.resize(N);
    for (int i=0; i<N && !inputFile.eof(); ++i) {
        inputFile >> a[i];
    }

    b.resize(M);
    for (int i=0; i<M && !inputFile.eof(); ++i) {
        inputFile >> b[i];
    }

    std::ofstream outputFile(outputFileName, std::ios_base::trunc);

#else
    // Заполнение случайными числами

    N=6000;
    M=6000;
    a.resize(N);
    b.resize(M);

    std::random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : std::time(nullptr);
    std::default_random_engine g(static_cast<std::default_random_engine::result_type>(seed));
    std::uniform_int_distribution intDistrib(0, 40000);

    for (auto &i: a) i=intDistrib(g);
    for (auto &i: b) i=intDistrib(g);
#endif
    // Основной алгоритм

    auto start = std::chrono::steady_clock::now();

    if (N>0 && M>0) {
        if (N==1) {
            std::sort(b.begin(), b.end());
            for (auto &i: b) i*=a[0];
            sum = getSum(b);
        }
        else if (M==1) {
            std::sort(a.begin(), a.end());
            for (auto &i: a) i*=b[0];
            sum = getSum(a);
        }
        else {
            res = sortCartesianProducts(a,b);
            sum = getSum(res);
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
#ifdef FILL_FROM_FILE
    outputFile << sum;
#else
    auto p = [](std::vector<uint32_t> &v){
        for (auto &i:v)std::cout<<i<<" ";
        std::cout << "\n";
    };
    //p(a);
    //p(b);
    //p(res);
    std::cout << sum << std::endl;
#endif
    return 0;
}
