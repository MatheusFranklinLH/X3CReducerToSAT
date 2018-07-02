#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

int main()
{
    int j, i;

    /*int A[5][6];
    A[0][0] = 1;
    A[1][0] = 0;
    A[2][0] = 1;
    A[3][0] = 0;
    A[4][0] = 1;
    A[0][1] = 1;
    A[1][1] = 1;
    A[2][1] = 0;
    A[3][1] = 1;
    A[4][1] = 0;
    A[0][2] = 0;
    A[1][2] = 0;
    A[2][2] = 1;
    A[3][2] = 0;
    A[4][2] = 1;
    A[0][3] = 1;
    A[1][3] = 0;
    A[2][3] = 0;
    A[3][3] = 1;
    A[4][3] = 1;
    A[0][4] = 0;
    A[1][4] = 1;
    A[2][4] = 0;
    A[3][4] = 1;
    A[4][4] = 0;
    A[0][5] = 0;
    A[1][5] = 1;
    A[2][5] = 1;
    A[3][5] = 0;
    A[4][5] = 0;*/

    //leitura de instancia
    ifstream data;
    data.open("instancia1.txt");
    int lin =0, col=0;
    int **A;

    if(data.is_open()){
        data >> col;
        data >> lin;

        A = new int *[lin];
        for(i=0;i<lin;i++)
            A[i] = new int[col]; //alocando matriz

        for(i=0;i<lin;i++){
            for(j=0;j<col;j++){
                data >> A[i][j];
            }
        }
    }

    data.close();
    //termina leitura

    int cont;
    int x = 1;
    int numConj = lin;
    int numX = col;
    int contCL = 0;
    int contaux;

    for(i=0; i<numX;i++){
        contaux = 0;
        for(j=0; j<numConj; j++){
                if(A[j][i]){
                    contaux++;
                }
            }
        contCL += 1 + (contaux*(contaux-1))/2; //Conta numero de clausulas para colocar no arquivo do miniSAT
    }

    ofstream myfile;
    myfile.open("tmp.cnf");
    myfile << "p cnf " << numConj << " " << contCL << endl;

    while(x<numX+1){
        cont = 0;
        for (i = 0; i<numConj; i++){
            if(A[i][x-1]){
                cont ++; //Conta quantos subconjuntos tem o valor x
            }
        }
        int * aux = new int[cont];
        int s=cont;
        cont = 0;
        for(i=0; i<numConj; i++){
            if(A[i][x-1]){
                aux[cont++] = i+1; //Coloca os subconjuntos que tem o valor x no vetor auxiliar
            }
        }
        for(i=0; i<s;i++)
            myfile << aux[i] << " "; // imprime a primeira disjunção entre todos os subconjuntos que tem x
        myfile << "0" << endl;

        for(i=0; i<s-1; i++){
            for(int j=i+1; j<s; j++){
                myfile << "-" << aux[i] << " -" << aux[j];// garante o exactly one
                myfile << " 0" << endl;
            }
        }
        delete aux;
        x++;
    }

    myfile.close();

    system("minisat tmp.cnf tmp.sat");

    ifstream satsolution;
    satsolution.open("tmp.sat");
    string line;

    if(satsolution.is_open()){
      if(getline(satsolution, line))
            cout << line << endl;
    }
    if(!line.compare("SAT"))
        cout << "E possivel uma cobertura de conjuntos" << endl;
    else
        cout << "Nao e possivel uma cobertura de conjuntos" << endl;
    return 0;
}
