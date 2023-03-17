#include <iostream>

using namespace std;

template<typename DT>
class Arbore;

template<typename DT>
class Nod;

template <class DT>
class  Nod
{
private:
    Nod<DT>* st;
    Nod<DT>* dr;
    DT data;

public:
    Nod()
    {
        st = NULL;
        dr = NULL;
    }
    Nod(DT x)
    {
        data = x;
        st = NULL;
        dr = NULL;
    }
    friend class Arbore<DT>;
};

template <class DT>
class Arbore
{
private:
    Nod<DT>* rad;
public:
    Arbore()
    {
        rad = NULL;
    }
    bool gol() {
        return(rad == NULL);
    }
    void insert(DT item)
    {
        Nod<DT>* nou_nod = new Nod<DT>(item);
        int poz[50], dim = 0, i;
        if (gol())
        {
            rad = nou_nod;
        }

        else
        {
            dim = numara_nod(rad) + 1;
            int i = 0;
            while (dim)
            {
                if (dim % 2 == 1)
                {
                    poz[i] = 1;

                }
                else
                {
                    poz[i] = 0;
                }
                dim = dim / 2;
                i++;
            }
            Nod<DT>* tmp = rad;
            for (int j = i - 2; j >= 1; j--)
            {
                if (poz[j] == 0)
                    tmp = tmp->st;
                else
                    tmp = tmp->dr;

            }
            if (poz[0] == 0)
                tmp->st = nou_nod;
            else
                tmp->dr = nou_nod;
        }
    }
    Nod<DT>* getrad() {   //returneaza radacina
        return rad;
    }
    void inorder(Nod<DT>* rad)
    {
        if (rad != NULL) {
            inorder(rad->st);
            cout << rad->data << " ";
            inorder(rad->dr);
        }
    }
    void postorder(Nod<DT>* rad)
    {
        if (rad != NULL) {
            postorder(rad->st);
            postorder(rad->dr);
            cout << rad->data << " ";
        }
    }
    void preorder(Nod<DT>* rad)
    {
        if (rad != NULL) {
            cout << rad->data << " ";
            preorder(rad->st);
            preorder(rad->dr);
        }
    }

    bool find(Nod<DT>* rad, DT d) {
        Nod<DT>* crt = rad;
        if (crt == NULL)
        {
            return 0;
        }
        else
        {
            if (d == crt->data) {
                return 1;
            }

            if (d > crt->data) {
                return find(crt->dr, d); //recursivitate tatii...ca sa intelegeti, faceti pe foaie!
            }
            else {
                return find(crt->st, d);
            }
        }
    }

    int Adancime(Nod<DT>* rad)
    {
        Nod<DT>* crt = rad;

        int ad_st = 0; //adancime la stanga
        int ad_dr = 0; //adancime la dreapta

        if (crt == NULL)
            return 0;
        else
        {
            ad_st = Adancime(crt->st);
            ad_dr = Adancime(crt->dr);


            if (ad_st > ad_dr)     //comparam adancimile...Alegem adancimea cea mai mare
                return(ad_st + 1);
            else return(ad_dr + 1);
        }
    }

    int numara_nod(Nod<DT>* rad)
    {
        Nod<DT>* crt = rad;

        int cnt = 0;

        if (crt == NULL)
            return 0;

        if (crt->st || crt->dr || crt->st == NULL || crt->dr == NULL) //probabil va intrebati de ce am mai pus conditia de NULL daca deja era pusa
            cnt++;

        cnt += numara_nod(crt->st) + numara_nod(crt->dr);
        return cnt;
    }

    int suma(Nod<DT>* rad)
    {
        if (!rad)
            return 0;
        int s = 0;
        s = rad->data + suma(rad->st) + suma(rad->dr);
        return s;
    }

    bool stramosi(Nod<DT>* rad, int x)
    {
        Nod<DT>* aux = rad;

        if (rad == NULL)
            return false;
        if (rad->data == x)
            return true;
        bool stanga = stramosi(aux->st, x);

        bool dreapta = false;
        if (!stanga)//daca nu mai avem nod pe stanga, cautam in dreapta
        {
            dreapta = stramosi(aux->dr, x);
        }
        if (stanga || dreapta)
            cout << rad->data << " ";

        return stanga || dreapta;
    }
    void afisare(int data)
    {
        int x;
        x = data;
        cout << x << " ";
    }
    bool stramosi(Nod<DT>* rad, int x,int v[100], int& dim)
    {
        Nod<DT>* aux = rad;
        

        if (rad == NULL)
            return false;
        if (rad->data == x)
            return true;
        bool stanga = stramosi(aux->st, x, v,dim);

        bool dreapta = false;
        if (!stanga)//daca nu mai avem nod pe stanga, cautam in dreapta
        {
            dreapta = stramosi(aux->dr, x,v,dim);
        }
        if (stanga || dreapta)
        {
            v[dim] = rad->data;
            dim++;
        }

        return stanga || dreapta;
    }

    DT cmmsc(int d1,int d2)
    {
        DT v1[100], v2[100],dim1=0,dim2=0,n=0;
        stramosi(getrad(), d1, v1, dim1);
        stramosi(getrad(), d2, v2, dim2);
        if (dim1 < dim2)
            n = dim1;
        else
            n = dim2;
        for (int i = n-1; i >=0; i--)
            if (v1[i] != v2[i])
            {
                return v1[i+ 1];
            }
    }
    
};


int main()
{
    Arbore<int> arbore;
    int n, x, d1, d2, v[100], nr = 0,min1=99999,min2=99999;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        arbore.insert(x);
        v[nr] = x;
        nr++;
    }
    cin >> d1>> d2;

    for (int i = 0; i < n; i++)
        arbore.afisare(v[i]);

    cout << endl<<arbore.suma(arbore.getrad())<<endl;

    cout<<arbore.cmmsc(d1,d2);

}
