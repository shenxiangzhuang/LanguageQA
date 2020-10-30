# CPP-QA

## Q1: 混用`>>`与`getline`造成输入流混乱

假设文件`test.txt`的内容如下, 这里的2表示后面有两行数据。

```
2
hello1 world1
hello2 world2

```

我们的读取程序如下

```cpp
#include <iostream>
#include <fstream>

int main(){
    std::ifstream stream("test.txt", std::ios::in);
    int n;
    stream >> n;
    std::cout << "n: " << n << std::endl;
    std::string line;
    for(int i=0; i<n; i++){
            getline(stream, line);
            std::cout << "Line: " << line << std::endl;
        }
    return 0;
}
```

得到的输出如下

```
n: 2
Line: 
Line: hello1 world1
```

下面我们来分析一下这段程序几个错误的地方。首先是语句`stream >> n;`，在此句执行之前，文件指针(通过`stream.tellg()`获取)指向的是`0`, 执行完之后指向的是`1`，也就是第一行的末尾,此时剩余的换行符是仍然在`stream`中的，所以后面第一次调用`getline`的时候就会出现第一行为空行的情况。进而，我们用`n`作为读取行数的条件也就不对了。

在[getline文档](https://en.cppreference.com/w/cpp/string/basic_string/getline)中也对这种情况进行了概括：

When consuming whitespace-delimited input (e.g. int n; [std::cin](http://en.cppreference.com/w/cpp/io/cin) >> n;) any whitespace that follows, including a newline character, will be  left on the input stream. Then when switching to line-oriented input,  the first line retrieved with `getline` will be just that whitespace. In the likely case that this is unwanted behaviour, possible solutions include:

-  An explicit extraneous initial call to `getline`
-  Removing consecutive whitespace with [std::cin](http://en.cppreference.com/w/cpp/io/cin) >> [std::ws](http://en.cppreference.com/w/cpp/io/manip/ws)
-  Ignoring all leftover characters on the line of input with cin.ignore([std::numeric_limits](http://en.cppreference.com/w/cpp/types/numeric_limits)\<[std::streamsize](http://en.cppreference.com/w/cpp/io/streamsize)\>::max(), '\n');

 这里我们采用第一种较为简单直观的方法

```cpp
#include <iostream>
#include <fstream>

int main(){
    std::ifstream stream("test.txt", std::ios::in);
    int n;
    stream >> n;
    std::cout << "n: " << n << std::endl;
    std::string line;
    // 仅仅读取到line, 不做任何操作
    getline(stream, line);
    for(int i=0; i<n; i++){
            getline(stream, line);
            std::cout << "Line: " << line << std::endl;
            // 对目标line做一些操作，func(line);
        }
    return 0;
}
```

针对这个情况，其实我们还可以换种方法，也就是开始的时候也直接用`getline`;此外，有时候文件中可能没有这样的一个`n`来告诉我们后面需要读取多少行，那就直接读取到文件末尾即可。我们将这两种改进融合得到下面的实现

```cpp
#include <iostream>
#include <fstream>

int main(){
    std::ifstream stream("test.txt", std::ios::in);
    std::string n_str;
    getline(stream, n_str);
    // 将字符串n_str直接转换为10进制的int
    int n = std::stoi(n_str);
    std::cout << "n: " << n << std::endl;
    std::string line;
    // 这里我们不需要n也可以读取全部数据
    while(getline(stream, line)){
        std::cout << "Line: " << line << std::endl;
        // 对目标line做一些操作，func(line);
        }
    return 0;
}
```



## Q2: `#ifndef`, `#define`与`#endif`

为了避免多次将同一文件的内容合并进来造成重复定义.

[Why use #ifndef CLASS_H and #define CLASS_H in .h file but not in .cpp?](https://stackoverflow.com/questions/3246803/why-use-ifndef-class-h-and-define-class-h-in-h-file-but-not-in-cpp)

## Q3: `explicit` keyword
文档[explicit specifier](https://en.cppreference.com/w/cpp/language/explicit)指出`Specifies that a constructor or conversion function (since C++11) or deduction guide (since C++17) is explicit, that is, it cannot be used for implicit conversions and copy-initialization.`

在[What does the explicit keyword mean?](https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean)中给出了几个具体的例子.

总之就是为了避免隐式转换带来隐藏的BUG.