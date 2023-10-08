#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

void copy (int n, float a[n][n], float b[n][n])
{
    for (int i =0; i<n; i++){
        for (int j =0; j<n; j++){
            b[i][j]=a[i][j];
        }
    }
}

void vypis( int n, float a[][n], int k)
{
    if (k==1) printf("\n Matice A je:\n\n");
    if (k==2) printf("\n Transponovaná matice k matici A je:\n\n");
    if (k==3) printf("\n Matice ortonormálních vektoru je:\n\n");

    for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
              printf("%f\t", a[i][j]);
          }
         printf("\n");
    }
}

void vypis_2( int n, int k, float a[][n], int pom) //funkce pro výpis ortogonálních vektorů
{
    if (pom==1) printf(" \n Matice ortogonálních vektorů je: \n \n");
    if (pom==2) printf(" \n Matice ortonormálních vektorů je: \n \n");

    for (int i = 0; i < n; i++) {
          for (int j = 0; j < k; j++) {
              printf("%f\t", a[i][j]);
          }
        printf("\n");
    }
}

void fillit (int n, float a[n][n])//naplní prázdné matice
{
    for (int i =0; i<n; i++){
        for (int j =0; j<n; j++){
           a[i][j]=0;
        }
    }
}

void swap (int n, float a[][n])
{
    int m ;
    for (int i = 0; i < n; i++) {
          if (a[i][i]==0){
                 for (int j = 0; j < n; j++) {
                     if (a[j][i]!=0) m = j;
                 }
        }
    if (m!=0){
        for (int k = 0; k < n; k++) {
              float pom = a[i][k];
               a[i][k] = -1*a[m][k]; // vynásobí řádek -1 aby se determinant nezměnil
               a[m][k] = pom;
             }
          }
     }
}

void make (int n, int num, float a[n][n], float b[][num])//vytvoří matice o rozměru num x num (výpočet subdeterminantu)
{
    for (int i =0; i<num; i++){
        for (int j =0; j<num; j++){
           b[i][j]=a[i][j];
        }
    }
}

float det(int n, float a[][n]) // výpočet determinantu
{
    int pocet = 1;
    int maf = 0;
    double konst;
    double det_mat = 1;

    //vypis(n,a,1);

    if (n==1) return det_mat = a[0][0];

    for (int o=0; o<n; o++){
        if (a[o][0]==0){
            maf=maf+1;
            }
        }
    if (maf==n){
        return det_mat=0;
    }
     for (int i=0; i<n/2; i++){
         for (int j=0; j<n; j++){
             if (a[i][i]==0){
            swap (n, a);
    }
            if (i != j){
            konst = a[j][i]/ a[i][i];
            for (int k=0; k<n; k++){
                a[j][k]=a[j][k] - ((a[i][k]*konst));
                    }
            konst=0;
            }
        }
    }
     if (a[n-1][n-2]!=0){
         float konst=a[n-1][n-2]/a[n-2][n-2];
              for (int j=n-2; j<n; j++){
                 a[n-1][j]=a[n-1][j]-konst*a[n-2][j];
             }
         }
  for (int l=0; l<n; l++){
        if (a[l][l]==0){
            pocet=pocet*a[l][l];
            }
  det_mat = det_mat * a[l][l];
            }
    if (pocet == 0){
          return det_mat =0;
        }

  return det_mat;
}

void tran(int n,float a[][n], float b[][n])
{
    for (int i =0; i<n; i++){
        for (int j =0; j<n; j++){
            b[j][i]=a[i][j];
        }
    }
}

bool hermi(int n, float a[][n]) //ověřovaná hermitovskosti, ověřuje se symetrie
{
    float b[n][n];

    copy(n,a,b);
    tran(n,a,b); //transpozice matice A

    for (int i =0;i<n;i++){
        for (int j =0;j<n;j++){
            if (a[i][j] != b[i][j]) return false; //pokud nejsou prvky shodné vrátí false
        }
     }
     return true;
}

bool sylvest_k(int n, float a[][n])
{
    float D; //pomocná proměnná na výpočet subdeterminantu

    for (int i=1;i<=n;i++){
        float b[i][i];
        make(n,i,a,b); //vytvoří menši matici
        D = det(i,b);  //spočítá subdeterminant pro vyhodnocení charakteru
        if (D<=0) return false;
    }
    return true;
}

float skal_s( int n, int col, int slo, float matX[][n], float matY[][n], float hermimat[][n])
{
    float c[n]; //pomocný vektor
    float skal=0;

    for (int i = 0; i < n; i++) {
        float s = 0;
        for (int j = 0; j < n; j++) {
            s = s + hermimat[i][j] * matY[j][slo];
            }
        c[i] = s;
        }

    for (int i =0;i<n;i++){
        skal = skal + matX[i][col]*c[i];
        }

    return skal;
}

float norma(int n, int slo,float matY[][n])
{
    float maf=0;

    for (int i= 0;i<n;i++){
        maf = maf + matY[i][slo]*matY[i][slo];
    }
    return maf;
}

void orto_normal(int n, int k, float matY[][n])
{
    float matH[n][n];
    float mat[n][n];
    float maf;
    float pom;

    copy(n,matY,mat);
    fillit(n,matH);

    for (int i =0;i<n;i++){
        maf = norma(n,i,mat);
        pom = 1/sqrt(maf);
        for (int j =0;j<n;j++){
            matH[j][i]=(matY[j][i])*pom;
        }
    }

    vypis_2(n,k,matH,2); //výpis ortonormální báze

}

void gramm_schmidt(int n, int k, float hermat[][n], float matX[][n])
{
    float matY[n][n]; //matice s vektory y0,y1,...,yn
    float matH[n][n]; //pomocná matice
    float vek[n];     //pomocný vektor
    float skal;
    float norm;
    float podil;

    fillit(n,matY);
    fillit(n,matH);

    for (int k = 0;k<n;k++) matY[k][0]=matX[k][0]; //y0 = x0

    for (int j=1;j<n;j++){  // j je pro xk vektory
         for (int i = 0;i<j;i++){

          skal = skal_s(n,j,i,matX,matY,hermat); //spočte skalární součin vektoru xj a yi
          norm = norma(n,i,matY); //spočte normu vektoru yi
          podil= skal/norm;

          for(int k=0;k<n;k++){
              matH[k][i] = podil*(matY[k][i]); //do pomocné matice se uloží podil * vektor yi
          }

          for(int r = 0;r<n;r++){
              vek[r]=0;
              for (int t =0;t<n;t++){
                   vek[r]=vek[r] + matH[r][t]; //sečte
              }
          }
          for (int m=0;m<n;m++){
              matY[m][j]=matX[m][j] - vek[m];
          }
        }
    }

    vypis_2(n,k,matY,1); //výpis ortogonálních vektorů
    orto_normal(n,k,matY); //převede ortogonální vektory na orotonormální
}

void dopln(int n, int col, float mat[][n]) //v případě, že uživatel zadá n != k, funkce dopní vektory na bázi daného prostoru
{
    for (int i =0;i<n;i++){
        mat[i][col] = 0;
        mat[i][col] =(rand()%10)/ 3.14159265359;
    }
}

void vektor(int n ,int k, float matH[][n])
{
    for (int i = n - 1; i >=k ;i--){
        dopln(n,i,matH);
    }
}

int main()
{
    srand(time(0));

    int n;
    int k;

    printf("Zadejte dimezi:\t ");
    scanf("%d", &n);

    printf(" \n Zadej matici kvadratické formy ve standartní bazi: \n\n ");

    float hermat[n][n];
    float matH[n][n];
    float B[n][n];
    float C[n][n];
    float X[n][n];

    fillit(n,matH);
    fillit(n,hermat);
    fillit(n,X);

    printf(" Zadej prvky matice (po řádcích):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
               printf(" A[%d][%d]\t", i,j);
               scanf("%f", &hermat[i][j]);
                  }
        }

    printf("\n Zadejte počet vektorů: \t");
    scanf("%d", &k);

    printf("\n Zadejte vektory do matice X po řádcích: \n");

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
               printf(" x[%d][%d] \t", j,i);
               scanf("%f", &X[j][i]); //matice vektorů
                  }
        }

     if (k!=n){ //doplnění na bázi
         copy(n,X,matH);
         vektor(n,k,matH);
    }

    else{
          copy(n,X,matH);
     }

    copy(n,hermat,B);
    copy(n,matH,C);

    if (hermi(n,hermat) == false) return printf ("\n Zadaná matice neni kvadratická forma \n");

    if (sylvest_k(n,B) == false) return printf ("\n Zadaná matice kvadratické formy není PD \n");

    if (det(n,C) == 0) return printf("\n Zadaný vektory jsou LZ \n");

        else {
          gramm_schmidt(n,k,hermat,matH);
    }
  return 0;
}

