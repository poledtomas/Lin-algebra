#include <stdio.h>
#include <stdbool.h>

void vypis( int n, float C[][n], int k)
{
	if (k==0) printf("\n Inverzní matice k matici A je:\n\n");
	if (k==1) printf("\n Matice A v HST je:\n\n");
	if (k==2) printf("\n Matice A je:\n\n");
	if (k==3) printf("\n Jednotková matice je:\n\n");
	
 for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f\t", C[i][j]);
        }
        printf("\n");
    }
}

void swap (int n, float a[][n], float b[][n] )
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
		float pom = a [i][k];
                float maf = b [i][k];
		a[i][k] = a[m][k];
		b[i][k] = b[m][k];
	        a[m][k] = pom;
		b[m][k] = maf;
	            }
              }
     }	  
}

void vydel (int n, float a[][n], float b[][n])
{
  for (int i = 0; i < n; i++){  
      double konst = a[i][i]; 
	for (int k = 0; k < n; k++){              
                    a[i][k] = a[i][k] / konst;
		    b[i][k] = b[i][k] / konst;	  
		}    
        }
}

void gauss (int n, float a[][n], float b[][n] )
{ 
   for (int i = 0; i < n; i++){  
        for (int j = 0; j < n; j++){
		if (a[i][i]==0){
			swap (n, a, b);
	}
            if (i != j) { 
               double pro = a[j][i] / a[i][i]; 
                  for (int k = 0; k < n; k++){                 
                    a[j][k] = a[j][k] - ((a[i][k]) * pro);
		    b[j][k] = b[j][k] - ((b[i][k]) * pro);	  
			}
	      } 
        }
   }
       vydel (n,a,b);
}

bool kontrola(int n, float a[][n],float c[][n])
{
    int pocet = 1;
    int maf = 0;
    double konst;

  for (int o=0; o<n; o++){
		if (a[o][0]==0){
			maf=maf+1;
			}
		}
	if (maf==n){
		return false;
	}

  	 for (int i=0; i<=n/2; i++){
   	     for (int j=0; j<n; j++){
		if (a[i][i]==0){
			swap (n, a, c);
	}
            if (i != j){ 
			konst = a[j][i]/ a[i][i];}
            for (int k=0; k<n; k++){
                a[j][k]=a[j][k] - ((a[i][k]*konst));
            }
           konst=0;
        }
   
  for (int l=0; l<n; l++){
		if (a[l][l]==0){
			pocet=pocet*a[l][l];
			}
		}
	if (pocet == 0){
	 vypis (n,a,1);
		return false;
		}
 	}
 vypis (n,a,1);
 return true; 
} 

int main()
{
    printf("Zadej rozněr regulární matice A: ");
    int n;
    scanf("%d", &n);

    float A[n][n];
    float B[n][n];
    float C[n][n]; 
    bool pro;

    printf("Zadej prvky matice A (po radcich):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
	    printf(" A[%d][%d]\t", i,j);
            scanf("%f", &A[i][j]);
	    C[i][j]=A[i][j];
   if (i==j){
		B[i][j]=1;
		}
   else {
	B[i][j]=0;
         }
    }
 }
  vypis(n,A,2);
  pro = kontrola (n,C,C);
 
  if( pro == true){
   	vypis(n,B,3);
   	gauss(n,A, B);
   	vypis(n,B,0);
  	}
		else {
		    printf ("\n Hmmmmm. Matice je singulární\n\n");
		}
   return 0;
}
