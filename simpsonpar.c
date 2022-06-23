
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x){

    
    return 4.0/(1+x*x);
  
}

int main(void){

    int n,i,myid,nThreads,istart,iend;
    
    n=100000;
    double integral=0.0,a,b,h,x=0.0;
   
    a=0.0;
    b=1.0;
    h=(b-a)/n;
    
    
    #pragma omp parallel private(i,x,myid,nThreads,istart,iend) shared(a,n,h) reduction(+:integral) default(none)
  { myid=omp_get_thread_num();
        nThreads = omp_get_num_threads();
        istart=myid*n/nThreads+1;
       
        
        iend=(myid+1)*n/nThreads;
       
        
        if(myid == nThreads-1) iend = n+1;
    
    
    for ( i = istart; i < iend; i=i+2)
    {   x=a+i*h;
       
        integral=integral+((2*h)/6)*(f(x-h)+4*f(x)+f(x+h));

    }
  }
  
    printf("%.5f \n",integral);
    
    
    

}


