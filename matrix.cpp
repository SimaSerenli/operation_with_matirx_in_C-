#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <math.h>


using namespace std;
template <class Tmp>

class Mtrs
{
protected:
    Tmp str_M;
    Tmp stn_M;
    Tmp **mtrs;
    Tmp dgr_M;

public:
    Mtrs(Tmp _strM=10,Tmp _stnM=10,Tmp _dgrM=0 );
    void getSatirSutun(Tmp &,Tmp &,Tmp);
    void setSatirSutun(Tmp,Tmp,Tmp);
    void print(string);
    void print();
    Mtrs operator+=(int);
    Mtrs operator+=(const Mtrs& );
    Mtrs operator*=(int);
    Mtrs operator*(const Mtrs&);
    Mtrs operator-=(int);
    Mtrs operator-=(const Mtrs&);
    Mtrs operator^(int);
    Mtrs operator%(int);
    Mtrs operator/=(float);
    void reSizeMtrs(int,int);
    int detMtrs(const Mtrs&,int);
    void transpozMtrs();
    void emulMtrs(const Mtrs&);
    void inverseMtrs();


};

template <class Tmp>
Mtrs <Tmp>::Mtrs(Tmp _strM,Tmp _stnM,Tmp _dgrM){

    str_M = _strM;   //Mtrs class ina ait constructor tanimlamasi
    stn_M = _stnM;
    dgr_M=_dgrM;
    srand(time(NULL));   //her deger için farkli bir sayi atamasi
    int i,j;
    mtrs = new Tmp*[str_M];

    for(i=0; i<str_M; i++){

        mtrs[i] = new Tmp[stn_M];//Mtrs class ina ait iki bpyutsu pointer dizisinin olusturulmasi
    }

    if(dgr_M=='r')  //Matris içine 0-255 random sayi atamasi yapilmasi
    {
        for( i=0; i<str_M; i++)
        {
            for( j=0; j<stn_M; j++)
            {

                mtrs[i][j]=rand()%256;

            }
        }
    }

    else if(dgr_M=='e') //Matrisin birim matrise dönüstürülmesi
    {
        if(str_M==stn_M)
        {
            for(i=0; i<str_M; i++)
            {
                for(j=0; j<stn_M; j++)
                {
                    if(i==j)
                    {
                        mtrs[i][j]=1;

                    }
                    else
                    {
                        mtrs[i][j]=0;

                    }
                }

            }
        }
        else
            cout<<"Satir sütün sayisi esit olmadigi için birim matris olusturulamadi";

    }

    else{
        for(i=0; i<str_M; i++){

            for(j=0; j<stn_M; j++) {

                mtrs[i][j]=dgr_M;

            }
        }
    }
}

template <class Tmp>
void Mtrs<Tmp>::getSatirSutun(Tmp &_strM, Tmp &_stnM,Tmp _dgrM)  {
    _strM=str_M;
    _stnM=stn_M;

}
template <class Tmp>
void Mtrs<Tmp>::setSatirSutun(Tmp _strM,Tmp _stnM,Tmp _dgrM){
    str_M=_strM;
    stn_M=_stnM;
}
template <class Tmp>
void Mtrs<Tmp>::print(string _dosya){

//Alinan matrisi dosya üzerine yazdirilmasini saglayan fonksiyon

    ofstream dosya;
    dosya.open("_dosya");// .txt uzantili dosyanin mainden alinmasi.

    int i=0,j=0;

    for( i=0; i<str_M; i++){

        for( j=0; j<stn_M; j++){

            dosya<<mtrs[i][j]<<" ";
        }
        dosya<<endl;
    }
    dosya.close();
}

template <class Tmp>
void Mtrs<Tmp>::print()
{
   //Kosullari saglanarak olusturulan matris nesnesinin ekrana yazdirilmasi.
    int i=0,j=0;

    for( i=0; i<str_M; i++)
    {
        for( j=0; j<stn_M; j++)
        {

            cout<<mtrs[i][j]<<" ";
        }
        cout<<endl;
    }
}

template <class Tmp>
Mtrs<Tmp> Mtrs<Tmp>::operator+=(int _dgrM){ // Mainden alinan integer deger ile yine mainden aldigimiz matris nesnesinin toplanmasi.

    Mtrs mtrs_new(str_M,stn_M,0);

    for (int i=0; i<str_M; i++)
    {
        for (int j=0; j<stn_M; j++)
        {
            mtrs[i][j] += _dgrM;
        }
    }
    return mtrs_new;
}
template <class Tmp>
Mtrs<Tmp> Mtrs<Tmp>:: operator+=(const Mtrs<Tmp>& s1){

  //Yukarida olusturulan fonksitondan farkli olarak burada boyutlari esit olan iki matrisin toplanmasini saglar.

    if (str_M != s1.str_M || stn_M != s1.stn_M)
    {
        cout << "Matris boyutlari esit olmali.";
        return (*this);
    }
    Mtrs mtrs_new(str_M,stn_M,0);

 // iki fonksiyonda da tek matris nesnesinin olusturulmasinin sebebi ise;
 //ilkinde toplamin  alinan matrise yazilmasi ikincisinde ise alinan ilk matrisin üzerine toplamin yazilmasi

    for (int i=0; i<str_M; i++){

        for (int j=0; j<stn_M; j++){

            mtrs[i][j] += s1.mtrs[i][j];
        }
    }
    return mtrs_new;
}

template <class Tmp>
Mtrs<Tmp> Mtrs<Tmp> :: operator*=(int _dgrM)
{

    Mtrs mtrs_new(str_M,stn_M,0);//mainden tanimlanan nesnenin bir integer deger ile çarpilmasi
    for (int i=0; i<str_M; i++)
    {
        for (int j=0; j<stn_M; j++)
        {
            mtrs[i][j] *= _dgrM;
        }
    }
    return mtrs_new;
}
template <class Tmp>
Mtrs<Tmp> Mtrs <Tmp>:: operator*(const Mtrs<Tmp>& m1)
{
    int i=0,j=0,k=0; // iki matris nesnesini biribiri ile matris çarpm kurallarina göre çarpilmasi

    if (stn_M !=m1.str_M)
    {
        cout << "Ilk matrisin sütün sayisi ile ikinci matrisin satir sayisi esit olmalidir.";
        return (*this);
    }
    Mtrs mtrs_new(str_M,m1.stn_M,0);

    for (i=0; i<str_M; i++)
    {
        for (j=0; j<m1.stn_M; j++)
        {

            for(k = 0; k <stn_M; ++k)
            {
                mtrs_new.mtrs[i][j] += mtrs[i][k]*m1.mtrs[k][j];


            }
        }
    }
    return mtrs_new;
}
template <class Tmp>
Mtrs<Tmp> Mtrs<Tmp>:: operator-=(int _dgrM)
{
    Mtrs mtrs_new(str_M,stn_M,0);
    for (int i=0; i<str_M; i++)
    {
        for (int j=0; j<stn_M; j++)
        {
            mtrs[i][j] -= _dgrM;// Mainden aldigimiz integer deger matris nesnesinden çikarilarak tekrar ayni matris üzerine yazilir
        }
    }
    return mtrs_new;
}
template <class Tmp>
Mtrs<Tmp> Mtrs<Tmp>::operator-=(const Mtrs<Tmp>& m1)
{
    //Satir ve sütün degerleri esit olmayan matrisler üzerinde islem yapilamayacagi için önce bunun kontrolü yapilir.

    if (str_M != m1.str_M || stn_M != m1.stn_M)
    {
        cout << "Matris boyutlari esit olmali.";
        return (*this);
    }
    Mtrs mtrs_new(str_M,stn_M,0);
    for (int i=0; i<str_M; i++)
    {
        for (int j=0; j<stn_M; j++)
        {
            mtrs[i][j] -= m1.mtrs[i][j];
        }
    }
    return mtrs_new;
}
template <class Tmp>
Mtrs<Tmp> Mtrs<Tmp>:: operator^(int _dgrM)
{
    Mtrs mtrs_new(str_M,stn_M,0);
    for (int i=0; i<str_M; i++)
    {
        for (int j=0; j<stn_M; j++)
        {
            mtrs_new.mtrs[i][j]=	pow(mtrs[i][j], _dgrM);
        }
    }
    return mtrs_new;
}
template <class Tmp>
Mtrs<Tmp> Mtrs<Tmp>:: operator%(int _dgrM)
{
    Mtrs mtrs_new(str_M,stn_M,0);
    for (int i=0; i<str_M; i++)
    {
        for (int j=0; j<stn_M; j++)
        {
            mtrs_new.mtrs[i][j]=	mtrs[i][j]% _dgrM;
        }
    }
    return mtrs_new;
}
template <class Tmp>
Mtrs<Tmp> Mtrs<Tmp>:: operator/=(float _dgrM)
{
    Mtrs mtrs_new(str_M,stn_M,0);
    for (int i=0; i<str_M; i++)
    {
        for (int j=0; j<stn_M; j++)
        {
            mtrs[i][j] /= _dgrM;// sira ile tüm satir ve sütunlara ait degerleri istenilen integera böleriz.
        }
    }
    return mtrs_new;
}

template <class Tmp>
void Mtrs<Tmp>::reSizeMtrs(int _strM,int _stnM)
{
    Tmp* *newM;
    int i,j;
    newM = new Tmp*[_strM];
    for(i=0; i<_strM; i++)
    {
        newM[i] = new Tmp[_stnM];

    }
    for(i=0; i<_strM; i++)
    {
        for(j=0; j<_stnM; j++)
        {
            newM[i][j]=0;
        }

    }

    if (str_M>=_strM && stn_M>=_stnM)
    {   //Eger olusturulacak matrisin satir ve sütun degerleri önceki matristen küçükse
        int i=0,j=0;

        for(i=0; i<_strM; i++)
        {
            for(j=0; j<_stnM; j++)
            {

                cout<<mtrs[i][j]<<" ";
            }
            cout<<"\n";
        }

    }
    else if (str_M>=_strM && stn_M<=_stnM)
    {  //Eger yeni matrisimizde sadece sütun degeri büyütülecek ve satir degeri küçültülecekse yada esit olacaksa

        int i=0,j=0;

        for(i=0; i<_strM; i++)
        {
            for(j=0; j<stn_M; j++)
            {
                newM[i][j]=mtrs[i][j];

                cout<<newM[i][j]<<" ";
            }
            for(j=stn_M; j<_stnM; j++)
            {
                newM[i][j]=0;

                cout<<newM[i][j]<<" ";
            }
            cout<<"\n";
        }

    }

    else
    {  //eger yeni matrisim için hem satir hem de sütun degerim artiyorsa
        for(i=0; i<str_M; i++)
        {
            for(j=0; j<stn_M; j++)
            {
                newM[i][j]=mtrs[i][j];
            }
        }
        for(i=str_M; i<_strM; i++)
        {
            for(j=stn_M; j<_stnM; j++)
            {
                newM[i][j]=0;
            }
        }
        for(i=0; i<_strM; i++)
        {
            for(j=0; j<_stnM; j++)
            {
                cout<<newM[i][j]<<" ";
            }
            cout<<"\n";
        }

    }

}
template <class Tmp>

int Mtrs<Tmp>::detMtrs(const Mtrs<Tmp>& mtrs1,int boyut){ //n:matris boyutu
    if(mtrs1.str_M==mtrs1.stn_M){
        int detM=0;
        Mtrs<Tmp> matris(10,10,'r');
        if (boyut == 2){
          return (mtrs1.mtrs[0][0] * mtrs1.mtrs[1][1]) - (mtrs1.mtrs[1][0] * mtrs1.mtrs[0][1]);
        }
        else{
            for (int a = 0; a < boyut; a++) {
                int f = 0;
                for (int b = 1; b < boyut; b++) {
                   int h = 0;
                   for (int c = 0; c< boyut; c++) {
                      if (c == a)
                      continue;
                      matris.mtrs[f][h] = mtrs1.mtrs[b][c];
                      h++;
                   }
                   f++;
                }
                detM = detM + (pow(-1,a ) * mtrs1.mtrs[0][a] * detMtrs( matris, boyut - 1 ));
          }
            return detM;
        }
    }
    else{
        cout<<"Lutfen Kare Matris Giriniz!"<<endl;
        return 0;
    }
}
template <class Tmp>
void Mtrs<Tmp>::transpozMtrs()
{
    Mtrs t(stn_M,str_M,dgr_M);
    int i=0,j=0;

    for( i=0; i<stn_M; i++)
    {
        for( j=0; j<str_M; j++)
        {
            t.mtrs[i][j]=mtrs[j][i];
            cout<<t.mtrs[i][j]<<" ";
        }
        cout<<endl;
    }

}
template <class Tmp>
void Mtrs<Tmp> :: emulMtrs(const Mtrs<Tmp>& m1)
{
    int i,j;
    Mtrs new_mat(str_M,stn_M,0);
    if (str_M != m1.str_M && stn_M != m1.stn_M)
    {
        cout << "Matris boyutlari esit olmali.";

    }
    else
    {
        for (i=0; i<str_M; i++)
        {
            for (j=0; j<stn_M; j++)
            {
                new_mat.mtrs[i][j] = mtrs[i][j]*m1.mtrs[i][j];
                cout<<new_mat.mtrs[i][j];
                cout<<" ";
            }
            cout<<endl;
        }
    }

}
template<typename Tmp>
void Mtrs<Tmp>::inverseMtrs(){
    Mtrs<Tmp> matris_tmp(this->str_M,this->stn_M,'e');
    float d,k;
    for(int i=0;i<this->str_M;i++){
        d=this->mtrs[i][i];
        for(int j=0;j<this->stn_M;j++){
            this->mtrs[i][j]=this->mtrs[i][j]/d;
            matris_tmp.mtrs[i][j]=matris_tmp.mtrs[i][j]/d;
        }
        for(int x=0;x<this->str_M;x++){
            if(x!=i){
                k=this->mtrs[x][i];
                for(int j=0;j<this->stn_M;j++){
                    this->mtrs[x][j]=this->mtrs[x][j]-(this->mtrs[i][j]*k);
                    matris_tmp.mtrs[x][j]=matris_tmp.mtrs[x][j]-(matris_tmp.mtrs[i][j]*k);
                }
            }
        }
    }

    for(int i=0;i<this->str_M;i++){
        for(int j=0;j<this->stn_M;j++){
            this->mtrs[i][j]=matris_tmp.mtrs[i][j];
        }
    }
}
template<class Tp>
class Tablo :public Mtrs<int>
{
private:

    string *tablo_r;
    string *tablo_c;

public:
 Tablo(Tp _strM=10,Tp _stnM=10,Tp _dgrM=0);
 void disp();
 void itemAt(string);
 void itemAt(string,string);
 void itemAt(int,int);
 void setRowNames(string[],int );
 void setColNames(string[],int );
 void print();

};
template<class Tp>
Tablo<Tp>::Tablo(Tp _strM,Tp _stnM,Tp _dgrM):Mtrs<int>(_strM,_stnM,_dgrM)
    {
        int i,j;
        char sayac='A';
        tablo_c = new string[stn_M];
        tablo_r = new string[str_M];
        for(i=1; i<str_M; i++)
        {
            tablo_r[i]=i;
        }
    }
template<class Tp>
void Tablo<Tp>::disp(){

        int i,j;
        Tablo table(str_M+1,stn_M+1,dgr_M);

        char count='A';

        for(i=0; i<stn_M; i++){

            if(i == 0)
                cout<<"\t";

            tablo_c[i]=count++;
            cout<<tablo_c[i]<<"\t";
        }
        cout<<endl;
        for(i=0; i<str_M; i++){
            cout<<i<<"\t";
            for( j=0; j<stn_M; j++){
                cout<<table.mtrs[i][j]<<"\t";
            }
            cout<<endl;
        }
    }
template<class Tp>
void Tablo<Tp>::itemAt(string s){

        int i,j;
        Tablo table(str_M+1,stn_M+1,dgr_M);
        char count='A';
        table.mtrs[0][0]='#';



        for(i=1; i<stn_M+1; i++){
            table.mtrs[0][i]=count++;
        }

        for(i=1; i<str_M+1; i++)
        {
            table.mtrs[i][0]=i;
        }

        for(i=0; i<(str_M+1); i++)
        {
            for( j=0; j<stn_M+1; j++)
            {
                cout<<table.mtrs[i][j]<<" ";
            }
            cout<<endl;
        }
    }
template<class Tp>
void Tablo<Tp>::itemAt(int str_T,int stn_T){

        Tablo table(str_M+1,stn_M+1,dgr_M);

        cout<<table.mtrs[str_T-1][stn_T-1];
    }
template<class Tp>
void Tablo<Tp>::itemAt(string rs,string cs){

        Tablo table(str_M+1,stn_M+1,dgr_M);

        char cnt = '0';
        char cnt1='A';
        char cnt2 = '0';
        int d1 = 0;
        int d2 = 0;
        int d3 = 0;

    if(cs[1]!='\0')
      {
          for(int i=0;i<stn_M;i++)
             {
               if( cnt == cs[0] )
                 {
                   break;
                 }
                 cnt++;
                 d1++;
             }

     for(int i=0;i<stn_M;i++)
        {
         if( cnt2 == cs[1] )
            {
               break;
            }
             cnt2++;
              d3++;
        }

     d1=d1*10+d3;
     }
     else
     {
         {for(int i=0;i<stn_M;i++)
        {
          if( cnt == cs[0] )
            {
               break;
            }
             cnt++;
     d1++;
     }



     }
     }


    for(int i=0;i<stn_M;i++)
    {
      if(cnt1 == rs[0])
        {
        break;
        }
      d2++;
      cnt1++;
    }


     cout<<endl<<rs<<cs<<"="<<table.mtrs[d1][d2]<<endl<<endl;

      }
template<class Tp>
void  Tablo<Tp>::setRowNames(string s[],int n){
        Tablo table(str_M,stn_M,dgr_M);
        char count='A';
        int i,j,k=0;
        for(i=0; i<stn_M; i++)
        {
            if(i == 0)
                cout<<"\t\t\t ";

            tablo_c[i]=count++;
            cout<<tablo_c[i]<<"\t";
        }
        cout<<endl;
        for(i=0; i<str_M; i++)
        {
            if(k<n)
            {
                cout<<s[i]<<"\t";
            }
            else
            {
                cout<<i<<"\t\t\t";
            }
            k++;
            for( j=0; j<stn_M; j++)
            {
                cout<<table.mtrs[i][j]<<"\t";
            }
            cout<<endl;
        }

    }
template<class Tp>
void Tablo<Tp>::setColNames(string s[],int n){

        Tablo table(str_M,stn_M,dgr_M);
        char count='A';
        int i,j,k=0,cnt=0;
        for(i=0; i<stn_M; i++){

            if(i == 0)
                cout<<"\t";

            tablo_c[i]=count++;

            if(cnt<n)
                cout<<s[cnt]<<"\t";
            else
                cout<<tablo_c[i]<<"\t\t\t";
            cnt++;
        }
        cout<<endl;
        for(i=0; i<str_M; i++){

            cout<<i<<"\t";
            for( j=0; j<stn_M; j++)
            {

                cout<<table.mtrs[i][j]<<"\t\t\t";

                k++;
            }
            k=0;
            cout<<endl;
        }

    }
template<class Tp>
void Tablo<Tp>::print(){

        Tablo table(str_M,stn_M,dgr_M);
        char count='A';
        int i,j;
        string s[] = {"0. satir","1. satir","2. satir"};
        string s1[] = {"0.stn","1.stn","2.stn"};

        for(i=0; i<stn_M; i++){

            if(s1[i].length()>4)
                cout<<"Sutun["<<i<<"] boyutu 4ten buyuk"<<endl;
        }
        for(i=0; i<stn_M; i++)
        {
            if(i == 0)
                cout<<"\t\t\t";

            tablo_c[i]=count++;


            cout<<s1[i][0]<<s1[i][1]<<s1[i][2]<<s1[i][3]<<"\t\t";
        }
        cout<<endl;
        for(i=0; i<str_M; i++)
        {
            cout<<s[i]<<"\t";
            for( j=0; j<stn_M; j++)
            {

                cout<<table.mtrs[i][j]<<"\t\t\t";
            }
            cout<<endl;
        }

    }
int main()
{
    Mtrs<int> *m1 = new Mtrs<int>(4,5,8);
    Mtrs<int> *m2 = new Mtrs<int>(2,5,15);
    Mtrs<int> *m3 = new Mtrs<int>(5,5,'r');
    //Mtrs<float> *m4 = new Mtrs<float>(5,5,20);
    //Tablo<int> *t3 = new Tablo<int>(6,8,'r');
    //string s[] = {"0. satir","1. satir","2. satir"};
    //mod alma islemi
    //*m1=*m1%3;
    //m1->print();

    //sayi ile toplma islemi
    //*m2+=12;
    //m2->print();

    //kesirli bölme islemi(bu yüzden float)
    //*m3/=6;
    //m3->print();

    //Farkli matrisleri toplama islemi
    //*m1+=*m2;
    //m1->print();

    //iki matrisin çarpımı
    //*m1=*m1**m2;
    // m1->print();

    //kat sayi ile çarpma islemi
    //*m3*=3;
    //m3->print();

    // matrislerin elemansal çarpımları
    //m1->emulMtrs(*m2);
    //m3->print();

    //dosyaya yazdırma işlemi
    m1->print("deneme.txt");

    //matrislerin yeniden boyutlandırması
    //m1->reSizeMtrs(2,7);

     //matrisin determinant hesabı
    // m3->detMtrs(*m3,3);


    //tablonun sütun isimlerinin değiştirilmesi
    //t3->setColNames(s,3);

    //tablonun satır isimlerinin değiştirilmesi
    //t3->setRowNames(s,3);

    //tablonun kurallara göre oluşturulması
    // t3->disp();

    //t3->itemAt("1","H");

    delete m1;
    delete m2;
    delete m3;
}

