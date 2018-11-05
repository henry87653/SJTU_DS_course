#ifndef SLINKLIST_H
#define SLINKLIST_H
#include "list.h"
#include <iostream>
using namespace std;


template <class elemType>
class sLinkList : public list<elemType>
{
private:
	struct node{//单链表中的结点类
		elemType data;
		node *next;

		node(const elemType &x, node *n = NULL)
			{data = x; next = n;}
		node():next(NULL){}
		~node(){}
	};

	node *head;
	int currentLength;

	//返回第i个结点的地址(返回一个node指针)
	node *move(int i)const{
		node *p = head;
		while(i-- >= 0) p = p->next;
		return p;
	}

public:
	sLinkList(){
		head = new node;
		currentLength = 0;
	}
	~sLinkList(){clear(); delete head; cout<< "sLInkList destructed" << endl;};
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
	void insert(int i, const elemType &x){
		node *pos;

		pos = move(i-1);
		pos->next = new node(x, pos->next);
		++currentLength;
	}
	void remove(int i){
		node *pos, *delp;

		pos = move(i-1);
		delp = pos->next;
		pos->next = delp->next;//绕过delp
		delete delp;
		--currentLength;
	}
	int search(const elemType &x) const{
		node *p = head->next;
		int i = 0;

		while(p != NULL && p->data != x){p = p->next; ++i;}
		if(p == NULL) return-1;else return i;
	}
	elemType visit(int i) const{
		return move(i)->data;
	}
	void traverse() const{
		node *p = head->next;
		cout << endl;
		while(p != NULL){
			cout << p->data << "  ";
			p = p->next;
		}
		cout << endl;
	}
	void erase(int i){//删除所有与第i个元素（含）相等的元素
		node *pre = move(i-1), *delp = pre->next; //
		elemType tmp = delp->data;
		int cnt = 1;

		pre->next = delp->next;//
		delete delp;

		for (pre = head; pre->next != NULL; pre = pre->next)
		{
			if (pre->next->data == tmp)
			{
				delp = pre->next;
				pre->next = delp->next;
				delete delp;
				++cnt;
			}
			currentLength -= cnt;
		}
	}
};

#endif // SLINKLIST_H
