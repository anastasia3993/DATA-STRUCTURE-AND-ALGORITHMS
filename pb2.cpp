#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename DT>
class ListaD2;

template<typename DT>
class Nod;

template<typename DT>
class Nod
{
	DT info;
	Nod* urm; // legatura la nodul urmator
	Nod* ant; // legatura la nodul anterior
public:
	Nod()
	{
		urm = ant = NULL;
	}
	Nod(int x)
	{
		info = x;
		urm = ant = NULL;
	}
	~Nod()
	{
		if (urm)
			delete urm; // APEL destructor clasa Nod

	}
	friend class ListaD2<DT>;

};

template<typename DT>
class ListaD2
{ //protected:
	Nod<DT>* inc, * crt, * sf;
public:
	ListaD2();
	int push_back(const DT&);
	int push_front(const DT&);
	void pop_back(int);
	int pop_front();

	int size();
	bool empty();
	
	void afis();
	void swap(int, int);
	int find(const DT&);
	

	~ListaD2()
	{
		delete inc; // distruge prima celula (santinela de inceput)
	} // apelare destructor clasa Nod

};

template<typename DT>
ListaD2<DT>::ListaD2()
{
	inc = crt = new Nod<DT>;
	sf = new Nod<DT>();
	inc->urm = sf;
	sf->ant = inc;
	//inc->ant = NULL;
	//sf->urm = NULL;
}

template<typename DT>
int ListaD2<DT>::push_back(const DT& d)
{
	if (!(sf->urm = new Nod<DT>())) // [2] creare nod nou
		return 1; // eroare alocare memorie

	sf->urm->ant = sf; // [3] legatura inversa nod nou -> sf
	sf->info = d; // [3] adaugare info nou in fosta santinela

	sf = sf->urm; // [4] actualizare sfarsit lista (santinela)
	sf->urm = NULL; // [4] anulare legatura nod urmator

	return 0; // succes
}

template<typename DT>
int ListaD2<DT>::push_front(const DT& d)
{
	if (!(inc->ant = new Nod<DT>())) // [2] creare nod nou
		return 1; // eroare alocare memorie

	inc->ant->urm = inc; // [3] leagare celula noua -> inc
	inc->info = d; // [3] copiere info nou in prima celula

	inc = inc->ant; // [4] actualizare inceput lista (santinela)
	inc->ant = NULL; // [4] anulare legatura ant pt sanitela

	return 0; // operatie terminata cu succes
}

template<typename DT>
void ListaD2<DT>::afis()
{
	Nod<DT>* crt = nullptr;
	if (inc)
	{
		crt = inc->urm;
		while (crt->urm)
		{
			cout << crt->info << " ";
			crt = crt->urm;
		}
	}
	cout << endl;
}
template<typename DT>
void ListaD2<DT>::swap(int k, int nr)
{
	int i = 0;
	Nod<DT>* st,*dr,*tmp2,*tmp1;
	st=dr = inc;
	while (st && i <k- nr)
	{
		st = st->urm;
		i++;
	}
	i = 0;
	while (dr && i < k + nr)
	{
		dr = dr->urm;
		i++;
	}
	tmp2 = dr->urm;
	tmp1 = dr->ant;

	st->ant->urm = dr;
	st->urm->ant = dr;
	dr->urm->ant = st;
	dr->ant->urm = st;

	dr->urm = st->urm;
	dr->ant = st->ant;
	st->urm = tmp2;
	st->ant = tmp1;
}

template<typename DT>
int ListaD2<DT>::pop_front()
{
	inc = inc->urm;
	return 0;
}
template<typename DT>
int ListaD2<DT>::size()
{
	Nod<DT>* crt;
	int lung = 0;
	if (inc)
	{
		crt = inc->urm;
		while (crt)
		{
			crt = crt->urm;
			lung++;
		}
	}
	return lung;
}
template<typename DT>
bool ListaD2<DT>::empty()
{
	if (size() == 0)
		return false;
	else
		return true;
}
template<typename DT>
void ListaD2<DT>::pop_back(int l)
{
	int c = 0;
	Nod<DT>* crt;
	if (inc)
	{
		crt = inc->urm;
		while (crt)
		{
			if (c == l - 2)//daca ne aflam la penultimul element
			{
				crt->urm = crt->urm->urm;
				break;
			}
			c++;
			crt = crt->urm;
		}
	}
}
template<typename DT>
int ListaD2<DT>::find(const DT& d)
{
	if (inc)
	{
		crt = inc->urm;
		while (crt != sf)
		{
			if (crt->info == d)
				return 0; //success s-a gasit d, in crt
			crt = crt->urm;
		}
		return 1; // success nu s-a gasit d in lista
	}
	return -1; //eroare initiere lista

}
int main()
{
	ListaD2<int> lst;
	int n, x, k, nr,addf,addi,cautat,l=0;
	cin >> n ;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		lst.push_back(x);
	}
	

	cin >> k >> nr>>addf>>addi>>cautat;
	lst.afis();//lista cu elementele sale
	lst.push_front(addi);//lista cu element adaugat la inceput
	lst.afis();
	

	lst.pop_front();//lista cu element de la inceput eliminat
	lst.afis();

	lst.push_back(addf);//lista cu element adaugat la final
	lst.afis();

	l = lst.size();
	lst.pop_back(l);
	lst.afis();

	if (lst.size() == 0)
		cout << 1<<endl;//goala
	else
		cout << 0<<endl;//lista nu e goala

	cout << lst.size()-1<<endl;//dimensiune
	
	if (lst.find(cautat) == 0)
		cout << 1<<endl;
	else
		cout << 0<<endl;
	lst.swap(k, nr);//swap
	lst.afis();
}