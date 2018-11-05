/*

Copyright (c)2018，上海交通大学电子信息与电气工程学院
All rights reserved.
文件名称：Unary_sparse_polynomial_calculator
作者：Henry Lu
开始日期：2018年11月05日
完成日期：2018年11月05日
版本号：v1.0
【问题描述】
设计一个一元稀疏多项式简单计算器。
【基本要求】
（1）输入并建立多项式。输入格式：
n
c1 e1
c2 e2
…
cn en
其中 n 是多项式的项数，c i 和 e i 分别是第 i 项的系数和指数，c i 和 e i 之间用空格分开。
（2）多项式输出按照指数降序排列，输出形式为类数学表达式。例如：多项式
-3x 8 +6x 3 -18 的输出形式为-3x^8+6x^3-18；x 15 -8x 7 -14 的输出形式为 x^15-8x^7-14；注意：系数
为 1 的非零次项的输出形式中略去系数 1，如 1x 8 的输出形式为 x^8；-1x 8 的输出形式为-x^8；
指数为 1 的项略去指数 1，如 3x。

*/

#include <iostream>
#include "sLinkListCal.h"

using namespace std;

int main(){
    int n1, n2;
    double c1, e1, c2, e2;
    sLinkListCal cal1, cal2;
    // cout << "Please input number of terms of polynomial 1:" ;
    cin >> n1;
    for(int i = 0; i < n1; i++)
    {
        cin >> c1 >> e1;
        cal1.order_insert(c1, e1);
    }
    // cout << "Please input number of terms of polynomial 2:" ;
    
    cin >> n2;
    for(int i = 0; i < n2; i++)
    {
        cin >>  c2 >> e2;
        cal2.order_insert(c2, e2);
    }

    // cout << "cal1:";
    // cal1.traverse();
    // cout << "cal2:";
    // cal2.traverse();

    // cout << "cal1 + cal2:";
    cal1.add(cal2);
    // cout << "cal1 - cal2:";
    // cal1.sub(cal2);

    cal1.traverse();
    
    system("pause");
    return 0;
}