//191307012 BERK AKIN
#include "stdafx.h"
#include <iostream>
#include <locale>
using namespace std;
struct Düðüm  
{  
    int veri;
	int yükseklik;
    struct Düðüm *sol;  
    struct Düðüm *sað;  
};  
int yükseklik(Düðüm *kök)  
{  
    if (kök == NULL) 
	{
		return 0;
	}
    return kök->yükseklik;  
}  
int EnYüksek(int a, int b)  
{  
    return (a > b)? a : b;  
}  
Düðüm* YeniDüðüm(int deðer)  
{  
    Düðüm* geçici = new Düðüm(); 
    geçici->veri = deðer;  
    geçici->sol = NULL;  
    geçici->sað = NULL;  
    geçici->yükseklik = 1;  
    return geçici;  
}  
Düðüm *SaðaÇevir(Düðüm *kök)  
{  
    Düðüm *geçici = kök->sol;  
    Düðüm *geçici2 = geçici->sað;  
    geçici->sað = kök;  
    kök->sol = geçici2;  
    kök->yükseklik = EnYüksek(yükseklik(kök->sol),yükseklik(kök->sað)) + 1;  
    geçici->yükseklik = EnYüksek(yükseklik(geçici->sol),yükseklik(geçici->sað)) + 1;  
    return geçici;  
}   
Düðüm *SolaÇevir(Düðüm *kök)  
{  
    Düðüm *geçici = kök->sað;  
    Düðüm *geçici2 = geçici->sol;  
    geçici->sol = kök;  
    kök->sað = geçici2;  
    kök->yükseklik = EnYüksek(yükseklik(kök->sol),yükseklik(kök->sað)) + 1;  
    geçici->yükseklik = EnYüksek(yükseklik(geçici->sol),yükseklik(geçici->sað)) + 1;  
    return geçici;  
}  
int Denge(Düðüm *kök)  
{  
    if (kök == NULL)
	{
		return 0;
	} 
	else
	{
	 return yükseklik(kök->sol) - yükseklik(kök->sað); 
	}    
}  
Düðüm* Ekle(Düðüm* kök, int deðer)  
{  
    if (kök == NULL)  
	{
		return(YeniDüðüm(deðer));
	}   

    if (deðer < kök->veri)
	{
		kök->sol = Ekle(kök->sol, deðer);  
	}   

    else if (deðer > kök->veri) 
	{
		kök->sað = Ekle(kök->sað, deðer);   
	}   

    else 
	{
		return kök;
	}

    kök->yükseklik = 1 + EnYüksek(yükseklik(kök->sol),yükseklik(kök->sað));  
    int denge = Denge(kök);  

    if (denge > 1 && deðer < kök->sol->veri) 
	{
		return SaðaÇevir(kök);  
	}

    if (denge < -1 && deðer > kök->sað->veri)  
	{
		return SolaÇevir(kök);   
	}

    if (denge > 1 && deðer > kök->sol->veri)  
    {  
        kök->sol = SolaÇevir(kök->sol);  
        return SaðaÇevir(kök);  
    }  

    if (denge < -1 && deðer < kök->sað->veri)  
    {  
        kök->sað = SaðaÇevir(kök->sað);  
        return SolaÇevir(kök);  
    }  

    return kök;  
}  
Düðüm * EnDüþükdeðer(Düðüm* kök)  
{  
    Düðüm* geçici = kök;  
    while (geçici->sol != NULL)  
    {
	   geçici = geçici->sol;  
	}
	   return geçici;  
}  
Düðüm* Sil(Düðüm* kök, int deðer)  
{  
    if (kök == NULL)  
        return kök; 

    if ( deðer < kök->veri )  
        kök->sol = Sil(kök->sol, deðer);  

    else if( deðer > kök->veri )  
        kök->sað = Sil(kök->sað, deðer);   

    else
    {  
        if( (kök->sol == NULL) || (kök->sað == NULL) )  
        {  
            Düðüm *geçici = kök->sol ? kök->sol:kök->sað;  

            if (geçici == NULL)  
            {  
                geçici = kök;  
                kök = NULL;  
            }  

            else 
            *kök = *geçici;    

            free(geçici);  
        }  
        else
        {  
            Düðüm* geçici = EnDüþükdeðer(kök->sað);  
            kök->veri = geçici->veri;  
            kök->sað = Sil(kök->sað,geçici->veri);  
        }  
    }

    if (kök == NULL)  
    return kök; 

    kök->yükseklik = 1 + EnYüksek(yükseklik(kök->sol),yükseklik(kök->sað));  
    int denge = Denge(kök);   

    if (denge > 1 && Denge(kök->sol) >= 0)  
        return SaðaÇevir(kök); 

    if (denge > 1 && Denge(kök->sol) < 0)  
    {  
        kök->sol = SolaÇevir(kök->sol);  
        return SaðaÇevir(kök);  
    }  

    if (denge < -1 && Denge(kök->sað) <= 0)  
        return SolaÇevir(kök);   

    if (denge < -1 && Denge(kök->sað) > 0)  
    {  
        kök->sað = SaðaÇevir(kök->sað);  
        return SolaÇevir(kök);  
    }  

    return kök;  
}  
void preOrder(Düðüm *kök)  
{  
    if(kök != NULL)  
    {  
        cout << kök->veri << " ";  
        preOrder(kök->sol);  
        preOrder(kök->sað);  
    }  
}  
bool Ara(Düðüm* kök, int deðer)
{
    if (kök == NULL)
        return false;
 
    if (kök->veri == deðer)
        return true;

    bool a = Ara(kök->sol, deðer);
    if(a) return true; 
    bool a2 = Ara(kök->sað, deðer);
    return a2;
}

int main()  
{  
	setlocale(LC_ALL,"Turkish");
	Düðüm *kök = NULL;  

    kök = Ekle(kök, 34); kök = Ekle(kök, 7);   kök = Ekle(kök, 12);  kök = Ekle(kök, 1);  
    kök = Ekle(kök, 6);  kök = Ekle(kök, 42);  kök = Ekle(kök, 23);  kök = Ekle(kök, 56);  
    kök = Ekle(kök, 8);  kök = Ekle(kök, 69);  kök = Ekle(kök, 1);   kök = Ekle(kök, 77);   

    cout << "PreOrder Düzeninde Aðaç: ";  preOrder(kök); 

    kök = Sil(kök, 42);  cout << endl<<"Silmeden Sonra PreOrder Aðaç: ";  preOrder(kök); cout<<endl;

	if (Ara(kök, 8))
	{
        cout << "Aranýlan Deðer Var";
	}
	else
	{
        cout << "Aranýlan Deðer Yok";
	}

	cout<<endl<<endl;
    return 41;  
}  
