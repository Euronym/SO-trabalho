void bubble_sort(int numeros[], int amount) {
    int aux;
    for (int i = 0; i < amount-1; i++) {
       for (int j = 0; j < amount-1; j++) {
            if (numeros[j] > numeros[j+1]) {
               aux =  numeros[j];
               numeros[j] = numeros[j+1];
               numeros[j+1] = aux;
            }
        } 
    }
}
