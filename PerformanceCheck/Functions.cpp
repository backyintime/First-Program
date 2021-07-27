#include"Functions.h"

int Leo(int n)
{
    PERF_CHECK;
    if (1 == n)//递归终止条件
    {
        return 1;
    }
    return n * Leo(n - 1);//返回阶乘的总和
}

void func()
{
    PERF_CHECK;
    func_2();
    func_2();
    for (long i = 0; i < 1; i++)
    {

    }
}

void func(QString str)
{
    PERF_CHECK;
    for (long i = 0; i < 10000000; i++)
    {

    }
}

void func_2()
{    
    PERF_CHECK;
    for (int i = 0; i < 10000000; i++)
    {

    }
}

void test()
{
    PERF_CHECK;
    func();
    func();
    //Leo(3);
    func("1");

    //func("Str");


}
