/*20. –еализовать шаблон самоорганизующегос€ списка. ќсновной операцией €в-
л€етс€ операци€ поиска. ѕри нахождении элемента он открепл€етс€ со сво-
его места и вставл€етс€ в начало списка.*/
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
class DoublyLinkedList
{
protected:
	ptrNODE_L<TInfo> begin, end;
	size_t size;
public:
	ptrNODE_L<TInfo> get_begin() { return begin; }
	void set_begin(ptrNODE_L<TInfo> inputed) { begin = inputed; }
	ptrNODE_L<TInfo> get_end() { return end; }
	void set_end(ptrNODE_L<TInfo> inputed) { end = inputed; }
	size_t get_size() { return size; }
	DoublyLinkedList() { begin = nullptr; end = nullptr; size = 0; }
	DoublyLinkedList(ifstream& file);
	void First_node(const TInfo& product);
	bool Empty();
	void Add(const TInfo& product);
	void Add_after_node(ptrNODE_L<TInfo> pNode, const TInfo& product);
	void Add_before_node(ptrNODE_L<TInfo> pNode, const TInfo& product);
	void switch_pointers(ptrNODE_L<TInfo> q, ptrNODE_L<TInfo> p);
	void switch_pointers_with_head(ptrNODE_L<TInfo> q, ptrNODE_L<TInfo> p);
	void sort();
	virtual ptrNODE_L<TInfo> Search(TInfo elem);
	void Add_into_sorted(const TInfo& product);
	TInfo Delete(ptrNODE_L<TInfo>& pNode);
	void Print();
	ptrNODE_L<TInfo> operator[](int i);
	~DoublyLinkedList();
};

template<class TInfo>
class self_organizing_list : public DoublyLinkedList<TInfo>
{
public:
	self_organizing_list() {}
	self_organizing_list(ifstream& file) : DoublyLinkedList<TInfo>(file) {}
	ptrNODE_L<TInfo> Search(TInfo elem);
	~self_organizing_list() {}
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
	ptrNODE_L<TInfo> tail = begin;
	while (!file.eof())
	{
		file >> product;
		Add_after_node(tail, product);
		tail = tail->next;
	}
}

template<class TInfo>
void DoublyLinkedList<TInfo>::Add_into_sorted(const TInfo& product)
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
void DoublyLinkedList<TInfo>::Add(const TInfo& product)
{
	ptrNODE_L<TInfo> p = new NODE_L<TInfo>(product, nullptr, end);
	end->next = p;
	end = p;
	size++;
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
void DoublyLinkedList<TInfo>::switch_pointers(ptrNODE_L<TInfo> q, ptrNODE_L<TInfo> p)
{
	ptrNODE_L<TInfo> tmp = p->next;
	p->next = tmp->next;
	if (tmp == end)
		end = p;
	else
		tmp->next->prev = tmp->prev;
	if (tmp->info >= q->info)
	{
		tmp->next = q->next;
		tmp->prev = q;
		q->next = tmp;
		tmp->next->prev = tmp;
	}
	else
	{
		tmp->next = q;
		tmp->prev = q->prev;
		if (q == begin)
			begin = tmp;
		else
			q->prev->next = tmp;
		q->prev = tmp;
	}
}

template<class TInfo>
ptrNODE_L<TInfo> find_place_before(ptrNODE_L<TInfo>& list, TInfo elem)
{
	ptrNODE_L<TInfo> ptr = list;
	while (ptr->next->info < elem)
		ptr = ptr->next;
	return ptr;
}

template<class TInfo>
void DoublyLinkedList<TInfo>::sort()
{
	ptrNODE_L<TInfo> ptr = begin, insert;
	while (ptr->next)
	{
		if (ptr->info > ptr->next->info)
		{
			insert = find_place_before(begin, ptr->next->info);
			switch_pointers(insert, ptr);
		}
		else
			ptr = ptr->next;
	}
}

template<class TInfo>
ptrNODE_L<TInfo> DoublyLinkedList<TInfo>::Search(TInfo elem)
{
	ptrNODE_L<TInfo> result = nullptr, ptr = begin;
	while (!result && ptr)
		if (ptr->info == elem)
			result = ptr;
		else
			ptr = ptr->next;
	return result;
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
ptrNODE_L<TInfo> DoublyLinkedList<TInfo>::operator[](int i)
{
	ptrNODE_L<TInfo> result = nullptr;
	if (begin && i >= 0 && i < size)
		result = begin;
	if (i < size)
		while (i > 0)
		{
			if (result)
				result = result->next;
			else
				result = nullptr;
			--i;
		}
	return result;
}

template<class TInfo>
DoublyLinkedList<TInfo>::~DoublyLinkedList()
{
	while (!Empty())
		Delete(begin);
	_CrtDumpMemoryLeaks(); //////////////////////////////////////////////
}

template<class TInfo>
void DoublyLinkedList<TInfo>::switch_pointers_with_head(ptrNODE_L<TInfo> q, ptrNODE_L<TInfo> p)
{
	ptrNODE_L<TInfo> tmp = p->next;
	p->next = tmp->next;
	if (tmp == end)
		end = p;
	else
		tmp->next->prev = tmp->prev;
	tmp->next = q;
	tmp->prev = q->prev;
	if (q == begin)
		begin = tmp;
	else
		q->prev->next = tmp;
	q->prev = tmp;
}

template<class TInfo>
ptrNODE_L<TInfo> self_organizing_list<TInfo>::Search(TInfo elem)
{
	ptrNODE_L<TInfo> result = nullptr, ptr = DoublyLinkedList<TInfo>::begin;
	while (!result && ptr)
		if (ptr->info == elem)
		{
			result = ptr;
			if (ptr != DoublyLinkedList<TInfo>::begin)
				DoublyLinkedList<TInfo>::switch_pointers_with_head(DoublyLinkedList<TInfo>::begin, ptr->prev);
		}
		else
			ptr = ptr->next;
	return result;
}