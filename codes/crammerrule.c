#include <stdio.h>
#include <stdbool.h>

void vypis( int n, float C[][n], int k)
{
    if (k==1) printf("\n Matice A v HST je:\n\n"); // výpis matice 
    if (k==2) printf("\n Matice A je:\n\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f\t", C[i][j]);
        }
        printf("\n");
    }
}

void swap (int n, float a[][n]) //prohodí řádky když je potřeba 
{
 int m ;
  for (int i = 0; i < n; i++) {
        if (a[i][i]==0){
                for (int j = 0; j < n; j++) {
            if (a[j][i]!=0){
                  m = j;
            }
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

float det(int n, float a[][n]) // výpočet determinantu
{
    int pocet = 1;
    int maf = 0;
    double konst;
    double det_mat = 1;

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
            pocet=pocet*a[l][l]; //vynásobí diagonální členy mezi sebou
            }
  det_mat = det_mat * a[l][l]; 
        	}
    if (pocet == 0){
          return det_mat =0;
        }
  return det_mat;
}

double crammer(int n,float a[][n], float det_A, float b[n], int m )
{
    float c[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
       c[i][j]=a[i][j];
           }
 }
    for (int j = 0;j<n;j++){
        c[j][m]=b[j]; //nahrdí daný sloupec pravou stranou 
       }
     float det_C = det(n,c); //spočítá determinat nové matice
     float result = det_C/det_A;

      return result;
}

int main()
{
    printf("Zadej roznìr regulární matice A: ");
    int n;
    scanf("%d", &n);

    float A[n][n];
    float C[n][n];
    float b[n];

    printf("Zadej prvky matice A (po radcich):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        printf(" A[%d][%d]\t", i,j);
            scanf("%f", &A[i][j]);
 		C[i][j]=A[i][j];
		 }
 }
    printf("Zadej pravou stranu matice\n");
    for (int i = 0; i < n; i++) {
            printf(" b[%d]\t", i);
            scanf("%f", &b[i]);
             }
vypis(n,A,2);

	double det_A= det(n,C);

  if (det_A == 0)  
		{
          printf ("\n Hmmmmm. Matice je singulární \n\n");
    }
	 else{
		 printf("\n Determinat matice A bez pravé strany je: %f \n \n ",det_A );
		 printf ("\n Řešení soustavy je: \n");

 	for(int i=0; i<n;i++){
           float result = crammer(n,A,det_A,b,i);
           printf ("\n b[%d] = %f",i,result);
     			}
	  printf ("\n");
  		}
     return 0;
}
