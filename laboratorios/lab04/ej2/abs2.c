#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void absolute(int x, int *y) {
    if(x >= 0){
        *y = x;
    }else{
        *y = -x;
    }
}

int main(void) {
    int a=0, res=0;  // No modificar esta declaración
    // --- No se deben declarar variables nuevas ---
    a = -10;
    absolute(a, &res);
    printf("el valor absoluto de %d es %d\n", a, res);
    //
    // Completar aquí
    //
    assert(res >= 0 && (res == a || res == -a));
    return EXIT_SUCCESS;
}
/*el parametro int *y seria de tipo in ya que 
solo leemos la direccion de memoria a la q apunta *y
y nunca modificamos el valor del puntero en si, es decir,
nunca cambiamos la direccion a la que apunta. Para C yo veo que se
pueden poner parametros tambien de tipo out por ejemplo 
en una funcion q ingrese 2 punteros y modifique la direccion
de memoria a la que apunta el primero por la direccion a al
que apunta el segundo, no se leeria el primer puntero pero se le 
modificaria. Tambien se podria in/out si en una funcion 
se le ingresan dos punteros y se cambia la direccion a la que apunta el 
primer puntero en caso de que cumpla cierta condicion el valor de la direccion
en la que apunta.*/

