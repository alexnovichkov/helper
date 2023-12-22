
class A
{
public:
    explicit A(int number) : n(number) 
    {}
    int operator() (int number) {
        std::cout << "adding "<<n<<" and "<<number<<std::endl;
        return number+n;
    }
private:
    int n = 0;
}

int main()
{
    A a {5};
    /* auto result = */a(6);
    a.operator()(6);

    A * b = new A(5);
    b->operator()(6);


    std::vector<int> vec(10);
    std::generate(vec.begin(), vec.end(), a);
}

auto it = vec.begin();