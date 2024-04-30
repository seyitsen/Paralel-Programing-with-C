#include <iostream>
#include <ctime>
#include <pthread.h>

using namespace std;

bool asalSayi(int sayi){
	if(sayi<2) return false;
	
	int i=2;
	int sinir=sayi/2;
	while(i<=sinir){
		if(sayi%i==0)
			return false;
		i++;
	}
	return true;
}

// Belirtilen sayiya kadar asal sayilari gösteren fonksiyon
void *aramaAralik(void *args){
	int *limit=(int*) args;
	
	for(int i=limit[0];i<=limit[1];i++){
		if(asalSayi(i)){
			//cout<<" "<<i<<" ";
		}
	}
}


struct Aralik {
    int baslangic;
    int bitis;
};

// 1-400000 arasindaki asal sayilari paralel programlama ile hesaplama
int main(){
	time_t startt,finish;
	
	startt=clock();
	
	
	int start=1;
	int end=400000;
	int kanalnum;
	int i,j;
	
	cout << "Lutfen kanal sayisi giriniz : ";
	cin >> kanalnum;
	
	// Kanal nesnesi dizisi olusturuluyor
	pthread_t *kanal_dizisi=new pthread_t[kanalnum];
	
	// Her bir kanalin hesaplayacagi deger miktari
	int kanalAralik=(end-start+1)/kanalnum;
	
	int kalan=(end-start+1) % kanalnum;
	int mevcutBaslangic=start;
	
	for(i=0;i<kanalnum;i++){
		int mevcutSon=mevcutBaslangic + kanalAralik -1;
		if(kalan>0){
			mevcutSon++;
			kalan--;
		}
		//int* aralik=new int[2]{mevcutBaslangic,mevcutSon};
		Aralik* aralik = new Aralik{mevcutBaslangic,mevcutSon};
		//int aralik[2]={mevcutBaslangic,mevcutSon};
		
		pthread_create(&kanal_dizisi[i],NULL,aramaAralik,aralik);
		
		mevcutBaslangic=mevcutSon + 1;
	}
	
	for(j=0;j<kanalnum;j++){
		pthread_join(kanal_dizisi[j],NULL);
	}
	
	finish=clock();
	cout << "\n\n Harcanan zaman= " << difftime(finish,startt) << " milisaniye";
	
	delete[] kanal_dizisi;
	
	
	getchar();
	return 0;
}
