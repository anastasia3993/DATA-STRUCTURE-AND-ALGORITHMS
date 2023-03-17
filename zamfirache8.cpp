#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
class festival {
public:
    int tickets;
    string name;
    festival()
    {
        tickets = 0;
        name = "";
    }
    festival(string sir,int x )
    {
        name = sir;
        tickets= x;
    }
};
void afis(vector<string>sir)
{
    for (int i = 0; i < sir.size(); i++)
    {
        cout << sir[i] << endl;
    }
}
int main()
{
    
    char x;
    cin >> x;
    cin.ignore();
    if (x == 'a')
    {
        vector<festival> persons;
        string text, call;
        int nr, number, position;
        cin >> nr;//nr de tranzactii

        for (int i = 0; i < nr; i++)
        {
            cin >> text;

            position = text.find(',');//caut pozitia virgulei in sir

            //creez un subsir care contine numarul de bilete cumparate si il transform in data de tip int
            number = stoi(text.substr(position + 1));

            //salvez in 'name' numele fiecarei persoane
            call= text.substr(0, position);

            bool found = false;
            if (persons.empty() == false)//verific daca vectorul ce pastreaza numele persoanelor este gol 
            {
                for (int j = 0; j < persons.size(); j++)
                    //verificam daca persoana curenta s-a mai repetat
                    if (persons[j].name == call)
                    {
                        persons[j].tickets += number;//adun nr de bilete cumparate de acceasi persona in zile diferite
                        found = true;
                    }
            }

            //daca nu se repeta o adaugam in vector
            if (!found)
            { 
                festival ob(call,number);
                persons.push_back(ob);
            }
        }
        
        for (int i = 0; i < persons.size(); i++)
            if (persons[i].tickets >= 5)
                cout << persons[i].name << ", " << persons[i].tickets << endl;
    }
    
    else
        if (x == 'b')
        {
            string trupa;
            int days, nr,position;
            queue<string> lst1, lst2, lst3;//pastrez fiecare trupa in lista corespunzatoare in functie de popularitate
            cin >> days;//nr de zile de festival
            cin.ignore();//pt folosirea corecta a lui getline

            int pop;
            //deoarece popularitatea fiecarei trupe poate 1,2,3 =>ultimul caracter din sir este intotdeauna un nr si penultimul caracter este virgula
            while (getline(cin, trupa, ',')) 
            {
                cin >> nr;//popularitea trupei curente

                if (nr== 1) 
                {
                    lst1.push(trupa);
                }
                else
                if (nr == 2) 
                {
                    lst2.push(trupa);
                }
                else
                if (nr == 3)
                {
                    lst3.push(trupa);
                }
            }

            for (int i = 0; i < days; i++) //pt fiecare zi afisez cate o formatie corespunzatoare popularitatii aferente
            {
                if (lst1.empty()==false) 
                {
                    cout << lst1.front() << " ";
                    lst1.pop();
                }
                
                if (lst2.empty()==false) 
                {
                    cout << lst2.front() << " ";
                    lst2.pop();
                }
            
                if (lst3.empty()==false) 
                {
                    cout << lst3.front() << " ";
                    lst3.pop();
                }
                cout << endl;
            }

        }
        else
            if (x == 'c')
            {
                vector<string>bands;
                int nr;
                string text;
                cin >> nr;//numarul de formatii ce trebuiesc ordonate
                cin.ignore();//golesc bufferul

                for (int i = 0; i < nr; i++)
                {
                    getline(cin, text);
                    bands.push_back(text);
                }
                //afis(bands);
                sort(bands.begin(), bands.end());

                for (auto elem : bands)
                    cout << elem << " ";
                cout << endl;
            }
    return 0;
}

