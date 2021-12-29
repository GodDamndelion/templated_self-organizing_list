#pragma once
#include <fstream>
#include <iostream>

using std::cout;
using std::ifstream;

template<class TInfo>
struct NODE_L
{
	TInfo info;
	NODE_L* next;
	NODE_L* prev;
	NODE_L(TInfo info, NODE_L* next = nullptr, NODE_L* prev = nullptr) : info(info), next(next), prev(prev) {};
	~NODE_L() { next = nullptr; prev = nullptr; }
};

template<class TInfo>
using ptrNODE_L = NODE_L<TInfo>*;

template<class TInfo>
struct DoublyLinkedList
{
	ptrNODE_L<TInfo> begin, end;
	size_t size;
	DoublyLinkedList() { begin = nullptr; end = nullptr; size = 0; }
	DoublyLinkedList(ifstream& file);
	void First_node(const TInfo& product);
	bool Empty();
	void Add_after_node(ptrNODE_L<TInfo> pNode, const TInfo& product);
	void Add_before_node(ptrNODE_L<TInfo> pNode, const TInfo& product);
	void Add_into(const TInfo& product);
	TInfo Delete(ptrNODE_L<TInfo>& pNode);
	void Print();
	~DoublyLinkedList();
};

template<class TInfo>
ptrNODE_L<TInfo> Find_place(ptrNODE_L<TInfo> begin, const TInfo& product)
{
	ptrNODE_L<TInfo> p = begin;
	while (p && p->info < product)
		p = p->next;
	return p;
}

template<class TInfo>
DoublyLinkedList<TInfo>::DoublyLinkedList(ifstream& file)
{
	size = 0;
	TInfo product;
	file >> product;
	First_node(product);
	while (!file.eof())
	{
		file >> product;
		Add_into(product);
	}
}

template<class TInfo>
void DoublyLinkedList<TInfo>::Add_into(const TInfo& product)
{
	ptrNODE_L<TInfo> place;
	place = Find_place(begin, product);
	if (place)
		Add_before_node(place, product);
	else
		Add_after_node(end, product);
}

template<class TInfo>
void DoublyLinkedList<TInfo>::First_node(const TInfo& product)
{
	begin = new NODE_L<TInfo>(product);
	end = begin;
	size++;
}

template<class TInfo>
bool DoublyLinkedList<TInfo>::Empty()
{
	return begin == nullptr;//!begin
}

template<class TInfo>
void DoublyLinkedList<TInfo>::Add_after_node(ptrNODE_L<TInfo> pNode, const TInfo& product)
{
	ptrNODE_L<TInfo> p = new NODE_L<TInfo>(product, pNode->next, pNode);
	if (pNode == end)
		end = p;
	else
		pNode->next->prev = p;
	pNode->next = p;
	size++;
}

template<class TInfo>
void DoublyLinkedList<TInfo>::Add_before_node(ptrNODE_L<TInfo> pNode, const TInfo& product)
{
	ptrNODE_L<TInfo> p = new NODE_L<TInfo>(product, pNode, pNode->prev);
	if (pNode == begin)
		begin = p;
	else
		pNode->prev->next = p;
	pNode->prev = p;
	size++;
}

template<class TInfo>
TInfo DoublyLinkedList<TInfo>::Delete(ptrNODE_L<TInfo>& pNode)
{
	ptrNODE_L<TInfo> p = pNode;
	if (pNode == begin)//удаление в голове
	{
		begin = p->next;
		pNode = begin;
		if (p->next)
			p->next->prev = nullptr;
	}
	else
		if (pNode == end)//удаление в хвосте
		{
			end = p->prev;
			pNode = end;
			if (p->prev)
				p->prev->next = nullptr;
		}
		else//удаление в середине
		{
			pNode = pNode->next;
			p->next->prev = p->prev;
			p->prev->next = p->next;
		}
	TInfo product;
	product = p->info;
	delete p;
	size--;
	return product;
}

template<class TInfo>
void DoublyLinkedList<TInfo>::Print()
{
	cout << " оличество элементов: " << size << '\n';
	ptrNODE_L<TInfo> ptr = begin;
	while (ptr)
	{
		cout << ptr->info << ' ';
		ptr = ptr->next;
	}
}

template<class TInfo>
DoublyLinkedList<TInfo>::~DoublyLinkedList()
{
	while (!Empty())
		Delete(begin);
	_CrtDumpMemoryLeaks(); //////////////////////////////////////////////
}