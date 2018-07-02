#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int randNum(int min, int max)
{
   return rand() % max + min;
}

int main()
{
   srand(time(0));

   int numX = 3*randNum(1, 40); //Numero de elementos em X vai de 3*1 até 3*40
   int limite = randNum(50,500); //Numero de subcnjuntos em S, cada um vai ter 3 elementos apenas

   ofstream file;
   file.open("instancia.txt");

   file << numX << " " << limite <<endl;

   int i;
   int cont = 0;
   int j;
   int sorta, sortb, sortc;

   for(i=1; i<=limite; i++){
        sorta = randNum(1, numX);
        do{
            sortb = randNum(1, numX);
        }while(sortb == sorta);
        do{
            sortc = randNum(1, numX);
        }while(sortc==sorta || sortc==sortb);
        for(j=1;j<=numX;j++){
            if(j==sorta || j==sortb || j==sortc)
                file << "1 ";
            else
                file << "0 ";
        }
        file << endl;
   }



   file.close();
   return 0;
}
