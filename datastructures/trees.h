#ifndef TREES_H
#define TREES_H

#include <vector>
#include <iostream>
#include <string>

/*
Практически всегда, когда говорят о деревьях, подразумевают двоичные деревья поиска,
так как именно они являются основой для построения таких контейнеров, как set и map.

Дерево можно определить несколькими способами. Один из них - рекурсивный.
Дерево - это множество узлов, который может быть пустым. Один из этих узлов r называется
корнем дерева. Корень дерева соединен ветвями с нулем или более поддеревьев.

Корень каждого поддерева называется потомком корня r. Корень дерева r для корней
поддеревьев - предок.

Узлы без потомков называются листьями.

Путем от узла n_l до узла n_k называется последовательность узлов n_i, i=[l..k),
таких, что n_i+1 - предок узла n_i.

Реализация дерева
-----------------

Наиболее простой способ - напрямую выразить рекурсивное определение дерева.
Каждый узел - это структура, содержащая данные и список указателей на потомков.
*/
template <typename T>
struct TreeNodeSimple
{
    T data;
    std::vector<TreeNodeSimple*> children;
};
/*
Однако такая структура очевидно неэкономна и не универсальна. Вместо этого заметим,
что если мы расположим потомков одного узла по горизонтали, то между ними можно
создать связи. Тем самым мы обойдемся без использования стандартной библиотеки.
Узел будет содержать указатель на первого потомка и указатель на ближайший узел-сиблинг
*/
template <typename T>
struct TreeNode
{
    T data;
    TreeNode *firstChild;
    TreeNode *nextSibling;
};

//TODO: Добавить реализацию всего класса: добавление узлов, удаление, поиск в глубину, поиск в ширину

/*
================
Двоичные деревья
================

Двоичное дерево - это дерево, любой узел которого не может иметь больше двух потомков.
Любое (непустое) двоичное дерево состоит из корня, левого поддерева (м.б. пустого)
и правого поддерева (м.б. пустого).

Особенностью двоичного дерева является то, что глубина дерева с N узлами в среднем
равна O(√N). Такой вид деревьев, как двоичные деревья поиска, имеют глубину в среднем
равную O(log₂N).
*/
template <typename T>
struct BinaryTreeNode
{
    T data;
    BinaryTreeNode *leftChild;
    BinaryTreeNode *rightChild;
};

/*
Обход дерева
------------

1. Симметричный обход (inorder traversal): левая ветвь, узел, правая ветвь.
   В результате получается естественная запись операций, осуществляемых над узлами дерева.
2. Обход в глубину (postorder traversal): левая ветвь, правая ветвь, узел.
   Используется при поиске в глубину.
3. Обход в ширину (preorder traversal): узел, левая ветвь, правая ветвь.
   Используется при поиске в ширину.


Двоичное дерево поиска
----------------------

Если мы потребуем, чтобы для любого узла дерева потомки в левом дереве были меньше,
чем значение узла, а потомки в правом дереве были больше, чем значение узла, мы
получим двоичное дерево поиска.

Двоичные деревья поиска используются для быстрого поиска элемента в совокупности элементов.
Сложность поиска в среднем равна O(log N), благодаря сбалансированности дерева.
*/

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree( ) : root{nullptr} {}
    BinarySearchTree( const BinarySearchTree & rhs ) : root{nullptr}
    {
        root = clone( rhs.root );
    }
    BinarySearchTree( BinarySearchTree && rhs ) : root{rhs.root}
    {

    }
    ~BinarySearchTree( )
    {
        makeEmpty();
    }

    const Comparable & findMin( ) const
    {
        if (auto t = findMin(root)) return t->element;
        return Comparable();
    }
    const Comparable & findMax( ) const
    {
        if (auto t = findMax(root)) return t->element;
        return Comparable();
    }
    bool contains( const Comparable & x ) const
    {
        return contains(x, root);
    }
    bool isEmpty( ) const {return root==nullptr;}
    void printTree( std::ostream & out = std::cout ) const
    {
        if (isEmpty()) out << "Empty";
        else printTree(root, out);
    }
    void makeEmpty( )
    {
        makeEmpty(root);
        _count=0;
    }
    //duplicates are ignored
    void insert( const Comparable & x )
    {
        insert(x, root);
    }
    //duplicates are ignored
    void insert( Comparable && x )
    {
        insert(x, root);
    }
    void remove( const Comparable & x )
    {
        remove(x, root);
    }
    std::vector<std::vector<int>> asTable() const
    {
        std::vector<std::vector<int>> result(_count);
        asTable(root, result);
        return result;
    }

    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        makeEmpty();
        root=clone(rhs.root);
        return *this;
    }
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        makeEmpty();
        root = rhs.root;
        return *this;
    }
    size_t count() const
    {
        return _count;
    }

private:
    size_t _count=0;
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        size_t count;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
            : element{ theElement }, left{ lt }, right{ rt }, count{1} { }

        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
            : element{ std::move( theElement ) }, left{ lt }, right{ rt }, count{1} { }
    };

    BinaryNode *root;

    void insert( const Comparable & x, BinaryNode * &t)
    {
        if( t == nullptr ) {
            t = new BinaryNode{ x, nullptr, nullptr };
            _count++;
        }
        else if( x < t->element ) {
            insert( x, t->left );
        }
        else if( t->element < x ) {
            insert( x, t->right );
        }
        else
            t->count++; // Duplicate
    }
    void insert( Comparable && x, BinaryNode * &t)
    {
        if( t == nullptr ) {
            t = new BinaryNode{ std::move(x), nullptr, nullptr };
            _count++;
        }
        else if( x < t->element ) {
            insert( std::move(x), t->left );
        }
        else if( t->element < x ) {
            insert( std::move(x), t->right );
        }
        else
            t->count++; // Duplicate
    }
    void remove( const Comparable & x, BinaryNode * &t)
    {
        if( t == nullptr )
            return; // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if (t->count>1)
            t->count--;
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
            _count--;
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            _count--;
        }
    }
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->left != nullptr )
                t = t->left;
        return t;
    }
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true; // Match
    }
    void makeEmpty( BinaryNode * &t)
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    void printTree( BinaryNode *t, std::ostream & out , int level=0) const
    {
        //prints in preorder traversing
        if (t != nullptr) {
            out << std::string(level, ' ') << t->element;
            if (t->count>1) out << " " << t->count;
            out << std::endl;
            printTree(t->left, out, level+2);
            printTree(t->right, out, level+2);
        }
    }
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
    void asTable(BinaryNode *t, std::vector<std::vector<int>> &table, int index=0) const
    {
        int leftIndex = 2*(index+1);
        int rightIndex = 2*(index+1)+1;
        std::vector<int> row = {t->element, leftIndex, rightIndex};
        table[index] = row;
        if (t->left == nullptr) table[index][1]=0;
        else asTable(t->left, table, leftIndex);
        if (t->right == nullptr) table[index][2]=0;
        else asTable(t->right, table, rightIndex);
    }
};



#endif // TREES_H
