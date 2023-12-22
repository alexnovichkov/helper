#include <iostream>
#include <vector>
#include <fstream>
#include "datastructures/trees.h"
#include <random>
#include <chrono>
#include <set>


using Row = std::vector<int>;

bool isBinaryTree(const std::vector<Row> & data)
{
    std::set<int> visited;
    for (size_t i=0; i<data.size(); ++i) {
        int value = data[i][0];
        size_t left = data[i][1];
        size_t right = data[i][2];
        if (i==0) visited.insert(value);

        if (left>0) {
            if (data[left-1][0] > value) return false;
            else visited.insert(data[left-1][0]);
        }
        if (right>0)  {
            if (data[right-1][0] < value) return false;
            else visited.insert(data[right-1][0]);
        }
    }
    return visited.size()==data.size();
}

int main()
{
    const std::string inputFileName = "input.txt";
    const std::string outputFileName = "output.txt";



    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName, std::ios_base::trunc);

    size_t N;
    inputFile >> N;
    std::vector<Row> data(N);
    for (size_t i=0;i<N; ++i) {
        int k,l,r;
        inputFile >> k >> l >> r;
        data[i] = {k,l,r};
    }


    outputFile << (isBinaryTree(data)?"YES":"NO");
    return 0;
}

int main11()
{
    const std::string inputFileName = "input.txt";
    const std::string outputFileName = "output.txt";

    //std::vector<Row> data;

    std::random_device seeder;
    const auto seed = seeder.entropy() ? seeder() : std::time(nullptr);
    std::default_random_engine g(static_cast<std::default_random_engine::result_type>(seed));
    std::uniform_int_distribution intDistrib(-1000000000, 1000000000);

    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName, std::ios_base::trunc);

    BinarySearchTree<int> tree;
    for (int i=0; i<10; ++i) tree.insert(intDistrib(g));
    tree.printTree();
    std::cout << tree.count();

    auto data = tree.asTable();
    for (auto row: data) {
        for (auto x:row) std::cout << x<<" ";
        std::cout << std::endl;
    }

    outputFile << (isBinaryTree(data)?"YES":"NO");
    return 0;
}
