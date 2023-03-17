#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <deque>
//#include <xutility>

using namespace std;

class Farmacie {
public:
	string nume, medicamente;
	int varsta, nr_medicamente, nr_ordine;
	float bani;
public:
	Farmacie()
	{
		nume = "";
		varsta = 0;
		bani = 0;
		nr_medicamente = 0;
		nr_ordine = 0;
		medicamente = "";
	}
	Farmacie(string m, int v, float b, int nr, string med)
	{
		nume = m;
		varsta = v;
		bani = b;
		nr_medicamente = nr;
		medicamente = med;
		if (varsta > 60)
			nr_ordine = 1;
		if (varsta >= 40 && varsta <= 59)
			nr_ordine = 2;
		if (varsta >= 20 && varsta <= 39)
			nr_ordine = 3;
		if (varsta < 20)
			nr_ordine = 4;
	}

};

//fctie afisare vector of object
void afis(vector<Farmacie>v)
{
	for (int i = 0; i < v.size(); i++)
		cout << v[i].nume << endl;// << v[i].varsta << " " << v[i].bani << " " << v[i].nr_medicamente << " " << v[i].medicamente << " " << v[i].nr_ordine << endl;
	cout << endl;
}


//fctie de comparare pt a
bool compare(Farmacie a, Farmacie b)
{
	if (a.nr_ordine != b.nr_ordine)
		return a.nr_ordine < b.nr_ordine;
	return a.nr_medicamente < b.nr_medicamente;
}

void afis_lista(list<string> s)
{
	list <string> ::iterator it;
	for (it = s.begin(); it != s.end(); ++it)
		cout << *it << " ";
}

//lista de afisare pt c
void afis_lista_endl(deque<string> s)
{
	if (s[0] != "")
		cout << s[0] << endl;
	for (int i = 1; i < s.size(); i++)
	{
		if (s[i] != s[i - 1])
			if (s[i] != " ")
				cout << s[i] << endl;
	}
}


//fctia care odoneaza crescator dupa nume(subp e)
bool compare_nume(Farmacie a, Farmacie b)
{
	return (a.nume < b.nume);
}

//fctie de comparare dupa al 2 lea elem din vector of pair(ex e)
bool sortbysec(const pair<string, float>& a, const pair<string, float>& b)
{
	return (a.second > b.second);
}
int main()
{
	vector<Farmacie>v;
	vector<pair<string, float>>pill;
	int nr_persoane, varsta1, nr_med1, poz = 0;
	float bani1, pret = 0;
	char subpunct;
	string med1, nume1, nume_medicament;
	cin >> subpunct >> nr_persoane;
	//citiri
	for (int i = 0; i < nr_persoane; i++)
	{
		cin >> nume1 >> varsta1 >> bani1 >> nr_med1;
		cin.ignore();
		getline(cin, med1);
		v.push_back(Farmacie(nume1, varsta1, bani1, nr_med1, med1));

	}
	while (getline(cin, med1))
	{
		poz = 0;
		while (med1[poz] != ' ')
		{
			poz++;
		}
		pret = stof(med1.substr(poz + 1));
		nume_medicament = med1.substr(0, poz);
		pill.push_back(make_pair(nume_medicament, pret));

	}

	if (subpunct == 'a')
	{
		sort(v.begin(), v.end(), compare);
		afis(v);

	}
	

	if (subpunct == 'b')
	{
		list<string>q1, q2, q3, q4;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i].nr_ordine == 1)
				q1.push_back(v[i].nume);
			if (v[i].nr_ordine == 2)
				q2.push_back(v[i].nume);
			if (v[i].nr_ordine == 3)
				q3.push_back(v[i].nume);
			if (v[i].nr_ordine == 4)
				q4.push_back(v[i].nume);
		}
		q1.sort();
		q2.sort();
		q3.sort();
		q4.sort();
		if (!q1.empty())
		{
			cout << "1: ";
			afis_lista(q1);
			cout << endl;
		}

		if (!q2.empty())
		{
			cout << "2: ";
			afis_lista(q2);
			cout << endl;
		}
		if (!q3.empty())
		{
			cout << "3: ";
			afis_lista(q3);
			cout << endl;
		}

		if (!q4.empty())
		{
			cout << "4: ";
			afis_lista(q4);
			cout << endl;
		}

	}

	if (subpunct == 'c')
	{
		deque<string> lst;
		for (int i = 0; i < v.size(); i++)//pt fiecare persoana
		{
			nume_medicament = "";
			for (auto x : v[i].medicamente)//pt fiecare lista de medicamente
			{
				bool gasit = false;
				if (x == ' ')//sparg lista in subsiruri ce reprezinta numele fiecarui medicament ce poate fi cumparat
				{
					for (int k = 0; k < pill.size(); k++)//medicamentul curent dorit de pers X il caut in lista de medicamente disponibile si daca nu l gasesc in adaug in lista lst
					{
						if (nume_medicament == pill[k].first)
							gasit = true;//medicamentul exista pe stoc
					}
					if (gasit == false)//medicamentul nu este pe stoc
						lst.push_back(nume_medicament);//creez o lista cu medicamente indisponibile (cu tot cu dubluri)
					nume_medicament = "";
				}
				else
				{
					nume_medicament += x;
				}
			}
			bool gasit = false;
			//caz separat pentru ultimul medicament din lista curenta
			for (int k = 0; k < pill.size(); k++)
			{
				if (nume_medicament == pill[k].first)
					gasit = true;
			}
			if (gasit == false)
				lst.push_back(nume_medicament);

		}
		sort(lst.begin(), lst.end());//ordonez alfabetic lista de medicamente indisponibile
		if (lst.size() > 1)//primul element din lista este mereu un spatiu 
			afis_lista_endl(lst);
		else
			cout << "Toate produsele sunt in stoc!";

	}

	if (subpunct == 'd')
	{
		for (int i = 0; i < v.size(); i++)//pt fiecare persoana
		{
			float suma_platit = 0;
			nume_medicament = "";
			for (auto x : v[i].medicamente)//pt fiecare lista de medicamente
			{
				if (x == ' ')//sparg lista in subsiruri ce reprezinta numele fiecarui medicament cumparat
				{
					for (int k = 0; k < pill.size(); k++)//medicamentul cumparat il caut in lista de med disponibila pt a suma
					{
						if (nume_medicament == pill[k].first)
							suma_platit += pill[k].second;
					}
					nume_medicament = "";
				}
				else
				{
					nume_medicament += x;
				}
			}
			//caz separat pentru ultimul medicament din lista curenta
			for (int k = 0; k < pill.size(); k++)
			{
				if (nume_medicament == pill[k].first)
					suma_platit += pill[k].second;
			}
			cout << v[i].nume << " -> ";
			cout << fixed << setprecision(2) << suma_platit << endl;
		}
	}

	if (subpunct == 'e')
	{
		sort(v.begin(), v.end(), compare_nume);
		sort(pill.begin(), pill.end(), sortbysec);//sortez dupa pret vectorul care contine toate medicamenetele disponibile in stoc
		vector<pair<string, float>> lst,lst1;
		bool gasit = false;
		for (int i = 0; i < v.size(); i++)//pt fiecare persoana
		{
			float suma_platit = 0;
			lst.clear();
			lst1.clear();
			nume_medicament = "";
			gasit = false;
			for (auto x : v[i].medicamente)//pt fiecare lista de medicamente
			{
				if (x == ' ')//sparg lista in subsiruri ce reprezinta numele fiecarui medicament cumparat
				{
					for (int k = 0; k < pill.size(); k++)//medicamentul cumparat il caut in lista de med disponibila pt a suma
					{
						if (nume_medicament == pill[k].first)
						{
							gasit = true;
							suma_platit += pill[k].second;//suma_platit pastreseaza suma pe care persoana X trebuie sa o plateasca
							lst.push_back(make_pair(pill[k].first, pill[k].second));//creez un vector in care bag toate medicamentele dorite de X
						}
					}
					if (gasit == false)
						lst1.push_back(make_pair(nume_medicament, 0));
					nume_medicament = "";
				}
				else
				{
					nume_medicament += x;
				}
			}
			gasit = false;
			//caz separat pentru ultimul medicament din lista curenta
			for (int k = 0; k < pill.size(); k++)
			{
				if (nume_medicament == pill[k].first)
				{ 
					gasit = true;
					suma_platit += pill[k].second;
					lst.push_back(make_pair(pill[k].first, pill[k].second));
				}
			}
			if (gasit == false)
				lst1.push_back(make_pair(nume_medicament, 0));
			sort(lst.begin(), lst.end(), sortbysec);//sortez lista de medicamente a fiecarei persoane dupa pretul produselor in ordine descrescatoare
			//for (int t = 0; t < lst.size(); t++)
				//	cout << lst[t].first << " "<<lst[t].second<<endl;
			if (suma_platit > v[i].bani)//cazul in care nu are destui bani sa cumpere toate medicamentele
			{
				int aux = 0;
				if (!lst.empty())
				{
					while ((suma_platit > v[i].bani) && (aux < lst.size()))
					{
						suma_platit = suma_platit - lst[aux].second;
						lst[aux].second = -1;
						aux++;
					}
				}

			}
			cout << v[i].nume << ": ";
			for (int t = 0; t < lst.size(); t++)
			   if (lst[t].second != -1)
					cout << lst[t].first << " ";
			for (int mon = 0; mon < lst1.size(); mon++)
				cout << lst1[mon].first << " ";
			cout << endl;

		}
	}
}

