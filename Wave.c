/*****************************************************************************
*
* Lax-Wendroff
*
* Author: Dimitrios Loupas

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#define PI 3.14159265358979323846

int main(void){


    int i, 
        t=1,
        k=0,
        w=0,
      N=2000;               
                      

    double 
        T=5*PI,
        a=sqrt(2)/PI,
        c,
        x,
       **u,
         dx,
         dt,
         fTimeStart, 
         fTimeEnd;


    // grid spacings
  dx = (12.0-0.0)/(N-1);
  dt=0.5*(dx/a);

    c=a*(dt/dx);
   // printf("dx=%f \n",dx);
    //printf("dt=%f \n",dt);
    

    w=round((T/dt));
    //printf("T=%d \n",w);

// Allocate memory

  u = (double**) malloc(N*sizeof(double*));
  if(u==NULL){
      printf("No memory!");
      exit(1);
  }
  for (int i = 0; i < N; i++){
      u[i] = (double*) malloc(w*sizeof(double));
      if(u[i]==NULL){
      printf("No memory!");
      exit(1);
     }
  }
  // Record start time

  fTimeStart = omp_get_wtime();
  
  #pragma omp parallel private(i,k,x) shared(T,a,c,u,dx,w,N,t) default(none)
  {
      
    #pragma omp for
    for(i=0;i<N;i++){
      
      x=i*dx;


      if (x>=2 && x<=4)
      {
        u[i][0] = sin(PI*x);
        
      }
      else
      {
        u[i][0] = 0.0;
        
      }
      
    }
   
        
        do{
        #pragma omp for 
        for(i=1;i<N-1;i++){
            
            
            u[i][t]=u[i][t-1]-(c/2)*(u[i+1][t-1]-u[i-1][t-1])+((pow(c,2))/2)*(u[i+1][t-1] -2* u[i][t-1] + u[i-1][t-1]);

            
        }

        #pragma omp single
        t=t+1;

        }while(t<w+1);


}
for (int l = 0; l < N; l++)
  {
    printf("for x=%d :",l);
    
      printf("%g",u[l][w]);
    
    printf("\n");
    
  }

   // Record end time

  fTimeEnd = omp_get_wtime();

 // Free memory

  

  for (i = 0; i < N; i++){
        free(u[i] );
     }
  free(u);



// Print elapsed time

  printf("wall clock time     = %.20f\n", fTimeEnd - fTimeStart);

    //printf("%f",j);

}