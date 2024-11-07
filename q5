#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 8

void get_poly(double **coeff, int* degreep); double eval_poly(double coeff[], int degree, double x);

int main() {

    double *coefficient;
    int degree;
    double x,result;


    get_poly(&coefficient,&degree);

    printf("Please enter a value for x: ");
    scanf("%lf",&x);

    result=eval_poly(coefficient,degree,x);
    printf("The result is %.1lf",result);

    free(coefficient);
    return 0;
}
void get_poly(double **coeff, int* degreep){

    printf("Please enter the degree of the polynomial.");
    scanf("%d",&(*degreep));
    if(*degreep<0 || *degreep>MAX_DEGREE){
        printf("Invalid degree, setting degree to 0.");
        *degreep=0;
    }

    *coeff= malloc(sizeof (double *)*(*degreep+1));
    if(*coeff==NULL){
        printf("error creating the coeff array!");
        exit(1);
    }
    for(int i=0;i<*degreep+1;i++){
        printf("a[%d]: ",i);
        scanf("%lf",&((*coeff)[i]));

    }
    printf("p(x)=");
    for(int i=0;i<=*degreep;i++){
        printf("%.0f*x^%d ",(*coeff)[i],i);
        if(i<*degreep){
            printf("+");
        }

    }
    printf("\n");

}

double eval_poly(double coeff[], int degree, double x){

    double result=0;

    for(int i=0;i<degree+1;i++){
        result+=(coeff)[i]*x;
    }

    return result;

}
