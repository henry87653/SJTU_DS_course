#ifndef SLINKLISTCAL_H
#define SLINKLISTCAL_H

#include "sLinkList.h"
#include <iostream>
using namespace std;

class sLinkListCal : public list<double>
{
private:
	struct node{//单链计算器表中的结点类
		double coeff;
        double expo;
		node *next;

		node(const double &c, const double &e, node *n = NULL)
			{coeff = c; expo = e; next = n;}
		node():coeff(0), expo(0), next(NULL){}
		~node(){}
	};
    
    node *head;
	int currentLength;

    //返回第i个结点的地址(返回一个node指针)
    //注意head->next = move(0)；
    //第一个数据结点为 0；
    //move(0), move(1), ... , move(currentLength - 1)
	node *move(int i)const{
		node *p = head;
		while(i-- >= 0) p = p->next;
		return p;
	}
    

public:
    void simplify(){//化简，将相邻的同次项合并,删除系数0项
        if(currentLength >= 2){//将相邻的同次项合并,2项以上才需要化简
            int i = 0;
            // bool flag = false;
            while(i < currentLength-1){///????
                // flag = false;//
                if(move(i)->expo == move(i+1)->expo){//系数相等，合并
                    move(i)->coeff += move(i+1)->coeff;
                    remove(i+1);
                    // flag = true;
                }
                else i++;//不等，下一个i
            }
        }

        node *p = head->next, *q = head;
        int j = 1;
        //删除系数0项

        // while(p != NULL){
        //     if()
        //     q = p; p = p->next; j++;
        // }

        for(j = 0; j < currentLength; j++)
        {
            // cout << j << ':' << p->expo << endl;
            if(p->coeff == 0) {remove(j); j--; p = q->next;}
            else{p = p->next; q = q->next;}
        }
    }

    sLinkListCal(){
        head = new node;
        currentLength = 0;
    }
    ~sLinkListCal(){clear(); delete head; cout<<"sLinkListCal destructed" << endl;}

    void clear(){
        node *p = head->next, *q;
        head->next = NULL;
        while(p != NULL){  //删除表中所有的结点
            q = p->next;
            delete p;
            p = q;
        }
        currentLength = 0;
    }
    
    int length() const{return currentLength;}
    
    void insert(int i, const double &x){}
    int search(const double &x) const{}

    void remove(int i) override{//删除第i个数据结点 0 1 ... currentLength-1
        node *pos, *delp;
        if(i == 0) pos = head;
        else pos = move(i-1);
        delp = pos->next;
        // if(i == currentLength)
        //     {delete delp; pos->next = NULL;currentLength--; return;}
        pos->next = delp->next;//绕过delp
        delete delp;
        --currentLength;
    }

    double visit(int i) const{//只返回指数部分
		return move(i)->expo;
	}

    void traverse() const{
		node *p = head->next;
		cout << endl;
        int i;

        if( currentLength == 0) { cout << '0' << endl; return;}
        
        for( i = 1; i < currentLength; i++)
        {
            if(p->expo != 0){
                if(p->coeff != 1){
                    if(p->coeff == -1) cout << '-';
                    else cout << p->coeff;
                }
                cout << 'x';
                if(p->expo != 1){
                    if(p->expo > 0) cout << '^' << p->expo;
                    else {cout << "^(" << p->expo << ')';}
                }
            }
            else cout << p->coeff;
            p = p->next;
            if(p->coeff > 0) cout << '+';
        }
        if(p->expo != 0){
            if(p->coeff != 1){
                if(p->coeff == -1) cout << '-';
                else cout << p->coeff;
            }
            cout << 'x';
            if(p->expo != 1){
                if(p->expo > 0) cout << '^' << p->expo;
                else {cout << "^(" << p->expo << ')';}
            }
        }
        else cout << p->coeff;
		cout << endl;
	}

    //有序插入，插入后指数由大到小
    void order_insert(const double &c, const double &e){
        node *pos;
        node *p = head->next, *q = head;
        if (currentLength > 0){//已经有项
            for(int i = 1; i <= currentLength; i++)
            {
                if(p->expo > e){q = p; p = p->next;}
                else break;
            }
        }
        pos = new node(c, e, p);
        q->next = pos;
		++currentLength;
        // simplify();
	}

    void order_insert(node *t){order_insert(t->coeff, t->expo);}
    void n_order_insert(node *t){order_insert(0 - t->coeff, t->expo);}

    void add(const sLinkListCal &cal){
        //每一项插入
        node *p = cal.head->next;
        for(int i = 0; i < cal.currentLength; i++)
        {
            order_insert(p);
            p = p->next;
        }
        simplify();
    }

    void sub(const sLinkListCal &cal){
        //每一项插入
        node *p = cal.head->next;
        for(int i = 0; i < cal.currentLength; i++)
        {
            n_order_insert(p);
            p = p->next;
        }
        simplify();
    }
};

#endif //SLINKLISTCAL