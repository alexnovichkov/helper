#ifndef RVALUES_C17_H
#define RVALUES_C17_H

/*
  lvalue - это выражение, которое обозначает невременный объект.
  rvalue - это выражение, которое обозначает временный объект или является литералом,
           не ассоциированным с объектом.
  Общее правило: если у вас есть имя для переменной, то это lvalue.
      vector<string> arr{3};
      const int x = 2;
      int y;
      int z = x+y;
      string str = "foo";
      vector<string> *ptr = &arr;
  Значение, возвращаемое функцией, или оператором, может быть как lvalue, так и rvalue.
  Это должно быть отражено в типе возвращаемого значения в объявлении функции.
  Функции, возвращающие value, возвращают rvalue.
  Функции, возвращающие reference или const reference, возвращают lvalue.

  Еще одно определение: lvalue - это то, что может стоять по любую сторону от оператора присваивания.
  rvalue - это то, что может стоять только справа от оператора присваивания.

  В C++ появилось понятие "rvalue reference", которое означает ссылку на rvalue,
  то есть на временный объект или на литерал.

  string str = "hello"; <- копирует литерал "hello" в переменную str
  string & rst = str;   <- создает ссылку (алиас) на переменную str
  rst += 'o';           <- теперь str и rst равны "helloo"
  string &bad = "hello"; <- ошибка! запрещены ссылки на rvalue
  string &&good = "hello"; <- отлично, rvalue ссылка на rvalue

  string &bad1 = str+'o';  <- ошибка! str+'o' - временный объект, то есть rvalue
  string &&good1 = str+'o'; <- отлично, сохраняет временный результат конкатенации
                             в новой переменной типа rvalue reference

  string &sub = str.substr(0,4); - ошибка! lvalue reference на временный объект
  string &&sub1 = str.substr(0,4); - отлично.

  Для чего используются lvalue reference:
  --------------------------------------

  1. Для упрощения сложных имен типов

  vector<double> vec;
  auto & tempVar = vec[2*i+1];
  //дальше работаем с tempVar, изменения в ней отражаются в векторе.

  Просто написать auto tempVar = vec[2*i+1] не достаточно, так как при этом просто
  будет скопировано значение из vec[2*i+1] в tempVar, и при изменении значения tempVar
  значение элемента вектора vec[2*i+1] меняться не будет.

  2. Для итерации в for (для изменения значений коллекций)

  for (auto &x: vec) {++x;} -  увеличиваем каждое значение на 1
  for (auto x: vec) {++x;} - исходный вектор не меняется, мы изменяем только
                             локальную переменную x

  3. Чтобы избежать лишнего копирования возвращаемых значений

  int findMax(vector<int> &vec) {
      int max = vec[0];
      ...
      return max;
  } <- из функции возвращается копия максимального элемента

  int &findMax(vector<int> &vec) {
      int &max = vec[0];
      ...
      return max;
  } <- из функции возвращается ссылка на максимальный элемент

  4. Чтобы изменения значений аргументов функции были видны снаружи функции.
        void swap(T & a, T & b);

  Для чего используют rvalue reference:
  ------------------------------------

  1. Чтобы избежать лишнего копирования при инициализации переменной

  string randomItem(vector<string> vec);
  string randomItem(const vector<string> & vec);
  string randomItem(const vector<string> && vec);


  vector<string> vec = {"hello", "world"};
  cout << randomItem(v); <- будет вызвана вторая функция, копирования вектора нет
  cout << randomItem({"hello", "world"}); <- будет вызвана третья функция, копирования
       вектора нет. Если бы функция string randomItem(const vector<string> && vec);
       не была объявлена, то вызывалась бы функция string randomItem(vector<string> vec);,
       что повлекло бы копирование вектора {"hello", "world"}

  2. Чтобы избежать лишнего копирования возвращаемых из функций
     локальных переменных

  vector<int> partialSum(const vector<int> &arr) {
      vector<int> result (arr.size());
      result[0] = arr[0];
      for (int i=1; i<arr.size(); ++i)
          result[i] = result[i-1] + arr[i];
      return result;
  }
    ...
  vector<int> sums = partialSum(vec);

  В функции создается локальная переменная result. Return-by-reference здесь невозможен,
  так как переменная result будет уничтожена при выходе из функции. Поэтому ее данные
  копируются в переменную sums, о чем нам говорит сигнатура функции.
  Если класс vector имеет эффективно реализованный оператор =, который возвращает
  rvalue reference (а он имеет - можно посмотреть заголовочный файл),
  то этого копирования можно избежать, то есть компилятор не будет
  создавать переменную result, а сразу будет заполнять вектор sums.

  3. Чтобы избежать лишнего присваивания при создании переменной из литерала

  Правила выбора типов аргументов функции:
  ---------------------------------------

  1. Если передаем маленькие объекты, не планируя их менять в функции - call-by-value
     int sum(int a, int b);
  2. Если передаем большие объекты, не планируя их менять - call-by-const-reference
     Matrix join(const Matrix &a, const Matrix &b);
  3. Если требуется изменять переданные в функцию параметры - call-by-reference
     void factorVector(vector<double> &vec, double factor);
  4. Если планируется передавать в функцию временные объекты, и мы хотим
     избежать лишнего копирования - call-by-rvalue-reference
     string toUpper(const string &&s);
     string result = toUpper("hello");


  Превращение lvalue в rvalue - функция std::move()
  Используется, чтобы в тех случаях, где мы ожидаем rvalue, а стоит lvalue, превратить
  lvalue в rvalue.

  Пример:
  void swap(vector<string> &x, vector<string> &y) {
      vector<string> tmp = x;
      x = y;
      y = tmp;
  } <- здесь выполняются три операции копирования векторов, что может быть дорого

  void swap(vector<string> &x, vector<string> &y) {
      vector<string> tmp = std::move(x);
      x = std::move(y);
      y = std::move(tmp);
  } <- здесь все копируемые векторы помечаются как movable, то есть мы просим компилятор
       не осуществлять реальное копирование, а использовать более дешевый operator &&=,
       то есть использовать call-by-rvalue-reference

  Если класс не поддерживает call-by-rvalue-reference, то компилятор просто сгенерирует
  стандартное копирование объектов класса. Таким образом, std::move - это просто просьба
  компилятору сгенерировать более быстрый код.


  */

#endif // RVALUES_C17_H
