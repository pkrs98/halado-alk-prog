#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <list>
#define longlong 9223372036854775807

using namespace std;

//fuggveny az eredmenyek kiirasara
template<typename T>
void Eredmeny(T mini_vektor, T mini_lista)
{
    std::cout<<"\nSTD::VECTOR leggyorsabb lefutasi ido: "<<mini_vektor<<" microsec.";
    std::cout<<"\nSTD::LIST leggyorsabb lefutasi ido: "<<mini_lista<<" microsec.";
    T kul = abs(mini_lista-mini_vektor);
    if (mini_lista < mini_vektor)
    {
        std::cout<<"\nSTD::LIST "<<kul<<" microsec-mal gyorsabban fut le.\n\n";
    }
    else
    {
        std::cout<<"\nSTD::VECTOR "<<kul<<" microsec-mal gyorsabban fut le.\n\n";
    }
}

template<typename T>
void Eredmeny_nano(T mini_vektor, T mini_lista)
{
    std::cout<<"\nSTD::VECTOR leggyorsabb lefutasi ido: "<<mini_vektor<<" nanosec.";
    std::cout<<"\nSTD::LIST leggyorsabb lefutasi ido: "<<mini_lista<<" nanosec.";
    T kul = abs(mini_lista-mini_vektor);
    if (mini_lista < mini_vektor)
    {
        std::cout<<"\nSTD::LIST "<<kul<<" nanosec-mal gyorsabban fut le.\n\n";
    }
    else
    {
        std::cout<<"\nSTD::VECTOR "<<kul<<" nanosec-mal gyorsabban fut le.\n\n";
    }
}

//minimum ertekkel visszateres
template<typename T, typename R>
auto Legkisebb(T vektor, R min_ertek )
{
    unsigned n = vektor.size();
    for (unsigned i=0; i<n; i++)
    {
        if (vektor[i] < min_ertek && vektor[i] != 0)
        {
            min_ertek = vektor[i];
        }
    }
    return min_ertek;
}

//eltelt idovel ter vissza, microsec-ben
template<typename T>
auto kulonbseg(T t1, T t2)
{
    std::chrono::duration<double, std::micro> eltelt = t2-t1;
    return eltelt.count();
}

template<typename T>
auto kulonbseg_nano(T t1, T t2)
{
    std::chrono::duration<double, std::nano> eltelt = t2-t1;
    return eltelt.count();
}

int main()
{

    //elemek beszurasahoz egy n=1.000.000-as "elemek" tomb
    std::vector<int> elemek;
    for(int i=0; i<1000000; i++)
    {
        elemek.push_back(rand() % 100);
    }

    std::cout<<"std::vector VS std::list osszehasonlitasa";
    std::cout<<"\n1) Elemekbol megkonstrualas (N = 10.000)";
    {
        //futasi idoket tartalmazo vektorok
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;
        //vektor
        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            auto start = std::chrono::high_resolution_clock::now();     //Start
            for (int j=0; j<10000; j++)         //N=10.000 elemu vektor
            {
                vec.push_back(rand() %100);
            }
            auto stop = std::chrono::high_resolution_clock::now();      //Stop
            FutasiIdo_vektor.push_back(kulonbseg(start,stop));          //eltelt ido tarolasa
            vec.clear();
        }
        //lista
        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            auto start = std::chrono::high_resolution_clock::now();     //start
            for (int j=0; j<100000; j++)
            {
                lista.push_back(rand() %100);
            }
            auto stop = std::chrono::high_resolution_clock::now();      //stop
            FutasiIdo_lista.push_back(kulonbseg(start,stop));           //eltelt ido tarolasa
            lista.clear();
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n2) N = 1.000.000 elem beszurasa elore";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            for (int j=0; j<1000000; j++)
            {
                vec.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            vec.insert(vec.begin(), elemek.begin(), elemek.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg(start,stop));
            vec.clear();
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            for (int j=0; j<1000000; j++)
            {
                lista.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista.insert(lista.begin(), elemek.begin(), elemek.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg(start,stop));
            lista.clear();
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n3) N = 1.000.000 elem beszurasa vegere";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            for (int j=0; j<1000000; j++)
            {
                vec.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            vec.insert(vec.end(), elemek.begin(), elemek.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg(start,stop));
            vec.clear();
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            for (int j=0; j<1000000; j++)
            {
                lista.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista.insert(lista.end(), elemek.begin(), elemek.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg(start,stop));
            lista.clear();
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n4) N = 1.000.000 elem beszurasa kozepre";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            for (int j=0; j<1000000; j++)
            {
                vec.push_back(rand() %100);
            }
            auto index = vec.begin()+500000;
            auto start = std::chrono::high_resolution_clock::now();
            vec.insert(index, elemek.begin(), elemek.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg(start,stop));
            vec.clear();
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            for (int j=0; j<1000000; j++)
            {
                lista.push_back(rand() %100);
            }
            std::list<int>::iterator index = lista.begin();
            for (int i=0; i<500000; i++)
            {
                index++;
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista.insert(index, elemek.begin(), elemek.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg(start,stop));
            lista.clear();
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n5) N = 1.000.000 elem torlese elolrol, .erase()";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            for (int j=0; j<2000000; j++)
            {
                vec.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            vec.erase(vec.begin(),vec.begin()+999999);
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg(start,stop));
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            for (int j=0; j<2000000; j++)
            {
                lista.push_back(rand() %100);
            }
            std::list<int>::iterator index = lista.begin();
            for (int i=0; i<999999; i++)
            {
                index++;
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista.erase(lista.begin(), index);
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg(start,stop));
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n6) N = 1.000.000 elem torlese kozeprol, .erase()";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            for (int j=0; j<2000000; j++)
            {
                vec.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            vec.erase(vec.begin()+499999,vec.begin()+1499999);
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg(start,stop));
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            for (int j=0; j<2000000; j++)
            {
                lista.push_back(rand() %100);
            }
            std::list<int>::iterator index1 = lista.begin();
            for (int i=0; i<499999; i++)
            {
                index1++;
            }
            std::list<int>::iterator index2 = index1;
            for (int i=0; i<1000000; i++)
            {
                index2++;
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista.erase(index1, index2);
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg(start,stop));
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n7) N = 1.000.000 elem torlese vegerol";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            for (int j=0; j<2000000; j++)
            {
                vec.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            vec.erase(vec.end()-1000000,vec.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg_nano(start,stop));
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            for (int j=0; j<2000000; j++)
            {
                lista.push_back(rand() %100);
            }
            std::list<int>::iterator index = lista.end();
            for (int i=0; i<1000000; i++)
            {
                index--;
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista.erase(index, lista.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg_nano(start,stop));
        }
        auto NagySzam = longlong;
        Eredmeny_nano(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n8) Rendezes novekvo sorrendbe, N = 100.000 elem";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            for (int j=0; j<100000; j++)
            {
                vec.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            sort(vec.begin(),vec.end());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg(start,stop));
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            for (int j=0; j<100000; j++)
            {
                lista.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista.sort();
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg(start,stop));
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n9) Rendezes csokkeno sorrendbe, N = 100.000 elem";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec;
            for (int j=0; j<100000; j++)
            {
                vec.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            sort(vec.begin(),vec.end(),std::greater<int>());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg(start,stop));
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista;
            for (int j=0; j<100000; j++)
            {
                lista.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista.sort(greater<int>());
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg(start,stop));
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    std::cout<<"\n10) Elemek felcserelese (N = 1.000.000), .swap()";
    {
        std::vector<double> FutasiIdo_vektor;
        std::vector<double> FutasiIdo_lista;

        for (int i=0; i<100; i++)
        {
            std::vector<int> vec1;
            std::vector<int> vec2;
            for (int j=0; j<1000000; j++)
            {
                vec1.push_back(rand() %1000);
                vec2.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            vec1.swap(vec2);
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_vektor.push_back(kulonbseg_nano(start,stop));
        }

        for (int i=0; i<100; i++)
        {
            std::list<int> lista1;
            std::list<int> lista2;
            for (int j=0; j<1000000; j++)
            {
                lista1.push_back(rand() %1000);
                lista2.push_back(rand() %100);
            }
            auto start = std::chrono::high_resolution_clock::now();
            lista1.swap(lista2);
            auto stop = std::chrono::high_resolution_clock::now();
            FutasiIdo_lista.push_back(kulonbseg_nano(start,stop));
        }
        auto NagySzam = 1000000000.0f;
        Eredmeny_nano(Legkisebb(FutasiIdo_vektor,NagySzam), Legkisebb(FutasiIdo_lista,NagySzam));
    }

    return 0;
}
