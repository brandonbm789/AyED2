#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) {
    if(x >= 0){
        y = x;
    }else{
        y = -x;
    }
}

int main(void) {
    int a=0, res=0;
    a = -10;
    absolute(a, res);
    printf("el valor absoluto de %d es %d\n", a, res);
    return EXIT_SUCCESS;
}

/*se termina mostrando por pantalla un 0, ya que la funcion absolute solo 
trabaja con una copia de res y no con res en si. no coincide con el 
programa visto en clase ya que res deberia haber terminado con el valor 10*/
