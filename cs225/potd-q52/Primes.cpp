#include <vector>
#include "Primes.h"

std::vector<int> *genPrimes(int M) {
    std::vector<int> *v = new std::vector<int>();
    std::vector<int> *t = new std::vector<int>(M);
    int i=0;
    int nextPrime = 2;

    for(i=0; i<M; i++)
        (*t)[i] = 1;

    (*t)[0]=0;
    (*t)[1]=0;

    v->push_back(2);

    while (nextPrime < M) {
        for(i=nextPrime*nextPrime;
                i < M;
                i+=nextPrime)
            (*t)[i] = 0;
        for(++nextPrime; nextPrime<M; nextPrime++)
            if ((*t)[nextPrime] == 1) {
                v->push_back(nextPrime);
                break;
            }
    }

    delete t;
    return v;
}


int numSequences(std::vector<int> *primes, int num) {
    int sequences = 0;
    int i =0;
    //iterate through each prime number in the list
    while((*primes)[i] <= num){
        int sum = 0;
        for(int j = i; j <= num; j++){
            sum+=(*primes)[j];
            if(sum==num){
                sequences++;
                break;
            }
        }
        i++;
    }
    return sequences;
}
