//191307012 BERK AKIN
#include "stdafx.h"
#include <iostream>
#include <locale>
using namespace std;
struct D���m  
{  
    int veri;
	int y�kseklik;
    struct D���m *sol;  
    struct D���m *sa�;  
};  
int y�kseklik(D���m *k�k)  
{  
    if (k�k == NULL) 
	{
		return 0;
	}
    return k�k->y�kseklik;  
}  
int EnY�ksek(int a, int b)  
{  
    return (a > b)? a : b;  
}  
D���m* YeniD���m(int de�er)  
{  
    D���m* ge�ici = new D���m(); 
    ge�ici->veri = de�er;  
    ge�ici->sol = NULL;  
    ge�ici->sa� = NULL;  
    ge�ici->y�kseklik = 1;  
    return ge�ici;  
}  
D���m *Sa�a�evir(D���m *k�k)  
{  
    D���m *ge�ici = k�k->sol;  
    D���m *ge�ici2 = ge�ici->sa�;  
    ge�ici->sa� = k�k;  
    k�k->sol = ge�ici2;  
    k�k->y�kseklik = EnY�ksek(y�kseklik(k�k->sol),y�kseklik(k�k->sa�)) + 1;  
    ge�ici->y�kseklik = EnY�ksek(y�kseklik(ge�ici->sol),y�kseklik(ge�ici->sa�)) + 1;  
    return ge�ici;  
}   
D���m *Sola�evir(D���m *k�k)  
{  
    D���m *ge�ici = k�k->sa�;  
    D���m *ge�ici2 = ge�ici->sol;  
    ge�ici->sol = k�k;  
    k�k->sa� = ge�ici2;  
    k�k->y�kseklik = EnY�ksek(y�kseklik(k�k->sol),y�kseklik(k�k->sa�)) + 1;  
    ge�ici->y�kseklik = EnY�ksek(y�kseklik(ge�ici->sol),y�kseklik(ge�ici->sa�)) + 1;  
    return ge�ici;  
}  
int Denge(D���m *k�k)  
{  
    if (k�k == NULL)
	{
		return 0;
	} 
	else
	{
	 return y�kseklik(k�k->sol) - y�kseklik(k�k->sa�); 
	}    
}  
D���m* Ekle(D���m* k�k, int de�er)  
{  
    if (k�k == NULL)  
	{
		return(YeniD���m(de�er));
	}   

    if (de�er < k�k->veri)
	{
		k�k->sol = Ekle(k�k->sol, de�er);  
	}   

    else if (de�er > k�k->veri) 
	{
		k�k->sa� = Ekle(k�k->sa�, de�er);   
	}   

    else 
	{
		return k�k;
	}

    k�k->y�kseklik = 1 + EnY�ksek(y�kseklik(k�k->sol),y�kseklik(k�k->sa�));  
    int denge = Denge(k�k);  

    if (denge > 1 && de�er < k�k->sol->veri) 
	{
		return Sa�a�evir(k�k);  
	}

    if (denge < -1 && de�er > k�k->sa�->veri)  
	{
		return Sola�evir(k�k);   
	}

    if (denge > 1 && de�er > k�k->sol->veri)  
    {  
        k�k->sol = Sola�evir(k�k->sol);  
        return Sa�a�evir(k�k);  
    }  

    if (denge < -1 && de�er < k�k->sa�->veri)  
    {  
        k�k->sa� = Sa�a�evir(k�k->sa�);  
        return Sola�evir(k�k);  
    }  

    return k�k;  
}  
D���m * EnD���kde�er(D���m* k�k)  
{  
    D���m* ge�ici = k�k;  
    while (ge�ici->sol != NULL)  
    {
	   ge�ici = ge�ici->sol;  
	}
	   return ge�ici;  
}  
D���m* Sil(D���m* k�k, int de�er)  
{  
    if (k�k == NULL)  
        return k�k; 

    if ( de�er < k�k->veri )  
        k�k->sol = Sil(k�k->sol, de�er);  

    else if( de�er > k�k->veri )  
        k�k->sa� = Sil(k�k->sa�, de�er);   

    else
    {  
        if( (k�k->sol == NULL) || (k�k->sa� == NULL) )  
        {  
            D���m *ge�ici = k�k->sol ? k�k->sol:k�k->sa�;  

            if (ge�ici == NULL)  
            {  
                ge�ici = k�k;  
                k�k = NULL;  
            }  

            else 
            *k�k = *ge�ici;    

            free(ge�ici);  
        }  
        else
        {  
            D���m* ge�ici = EnD���kde�er(k�k->sa�);  
            k�k->veri = ge�ici->veri;  
            k�k->sa� = Sil(k�k->sa�,ge�ici->veri);  
        }  
    }

    if (k�k == NULL)  
    return k�k; 

    k�k->y�kseklik = 1 + EnY�ksek(y�kseklik(k�k->sol),y�kseklik(k�k->sa�));  
    int denge = Denge(k�k);   

    if (denge > 1 && Denge(k�k->sol) >= 0)  
        return Sa�a�evir(k�k); 

    if (denge > 1 && Denge(k�k->sol) < 0)  
    {  
        k�k->sol = Sola�evir(k�k->sol);  
        return Sa�a�evir(k�k);  
    }  

    if (denge < -1 && Denge(k�k->sa�) <= 0)  
        return Sola�evir(k�k);   

    if (denge < -1 && Denge(k�k->sa�) > 0)  
    {  
        k�k->sa� = Sa�a�evir(k�k->sa�);  
        return Sola�evir(k�k);  
    }  

    return k�k;  
}  
void preOrder(D���m *k�k)  
{  
    if(k�k != NULL)  
    {  
        cout << k�k->veri << " ";  
        preOrder(k�k->sol);  
        preOrder(k�k->sa�);  
    }  
}  
bool Ara(D���m* k�k, int de�er)
{
    if (k�k == NULL)
        return false;
 
    if (k�k->veri == de�er)
        return true;

    bool a = Ara(k�k->sol, de�er);
    if(a) return true; 
    bool a2 = Ara(k�k->sa�, de�er);
    return a2;
}

int main()  
{  
	setlocale(LC_ALL,"Turkish");
	D���m *k�k = NULL;  

    k�k = Ekle(k�k, 34); k�k = Ekle(k�k, 7);   k�k = Ekle(k�k, 12);  k�k = Ekle(k�k, 1);  
    k�k = Ekle(k�k, 6);  k�k = Ekle(k�k, 42);  k�k = Ekle(k�k, 23);  k�k = Ekle(k�k, 56);  
    k�k = Ekle(k�k, 8);  k�k = Ekle(k�k, 69);  k�k = Ekle(k�k, 1);   k�k = Ekle(k�k, 77);   

    cout << "PreOrder D�zeninde A�a�: ";  preOrder(k�k); 

    k�k = Sil(k�k, 42);  cout << endl<<"Silmeden Sonra PreOrder A�a�: ";  preOrder(k�k); cout<<endl;

	if (Ara(k�k, 8))
	{
        cout << "Aran�lan De�er Var";
	}
	else
	{
        cout << "Aran�lan De�er Yok";
	}

	cout<<endl<<endl;
    return 41;  
}  
