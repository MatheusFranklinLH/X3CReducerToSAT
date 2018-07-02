#include "libraries.h";

vector< vector<int> > allCombs; //vetor-2d de todas as combinacoes de conjuntos candidatas a cobertura
vector<int> combination; // uma combinacao especifica
vector<int> index; // indice das colunas da matriz, que eh o vetor a partir do qual devem ser extraidas as combinacoes

/*
bool belongs(int v, int* s) {
    int n = sizeof(s)/sizeof(int);
    for(int i = 0; i < n; i++){
        if(v == s[i])
            return(true);
    }
    return(false);
}

int factorial(int p) {
    if(p == 0)
        return 1;
    return p*factorial(p-1);
}
*/

//funcao recursiva para gerar combinacoes
//baseado na seguinte observacao:
//combinacoes({ 1 2 3 4 5 }, 3 a 3) =
//{ 1, combinacoes({ 2 3 4 5 }, 2 a 2) } e
//{ 2, combinacoes({ 3 4 5 }, 2 a 2) } e
//{ 3, combinacoes({ 4 5 }, 2 a 2) }
//
void comb_gen_rec(int offset, int by) {
  if (by == 0) {
    allCombs.push_back(combination);
    return;
  }
  for (int i = offset; i <= index.size()-by; ++i) {
    combination.push_back(index[i]);
    comb_gen_rec(i+1, by-1);
    combination.pop_back();
  }
}

//wrapper para chamar a funcao recursiva e gerar as combinacoes:
void comb_gen(int nsets, int p) {

    for(int i = 0; i < nsets; i++){
        index.push_back(i); //preenche o vetor index dos indices correspondentes a subconjuntos de V que estao em S
    }
    comb_gen_rec(0, p);
}

bool matrix_x_cover(vector< vector<int> > A, int nrow, int ncol) {

    int numSetsInCover = ncol/N; //N = 3, no arquivo header.
                                 //Cada subconjunto tem 3 elementos, entao toda cobertura exata de um conjunto com 3p elementos deve ter p conjuntos.
                                 //Nesse caso, numSetsInCover eh p.
    comb_gen(nrow, numSetsInCover); //gera todas as combinacoes de indices p a p, correspondentes a combinacoes de subconjuntos que possivelmente formam uma cobertura exata.
    int ncombs = allCombs.size(); //Sera igual a numSetsInCover

    int colSum; //contador que verifica o numero de 1s em uma coluna da submatriz de A, formada por p linhas, correspondentes a subconjuntos condidatos a cobertura exata.
    int i, j, k; //indices

    for(i = 0; i < ncombs; i++){
    cout << "i = " << i << endl;
        for(j = 0; j < ncol; j++) {
            colSum = 0;
            for(k = 0; k < numSetsInCover; k++) {
                colSum += A[allCombs[i][k]][j];
                cout << "i = " << i << "; j = " << j << "; k = " << k << "; colSum = " << colSum << endl;
                if(colSum > 1){
                    cout << "break 1" << endl;
                    break;
                }
            }
            cout << "k = " << k << endl;
            if(k < numSetsInCover){
                cout << "break 2" << endl;
                break;
            }
        }
        cout << "j = " << j << endl;
        if(j >= ncol)
            return(true);
    }
    return(false);
}

bool exact_cover(int V[], int S[][N], int num_elem, int num_subsets) {
    //V eh o conjunto e S a sua cobertura <=> V esta contido na uniao dos subconjuntos pertencentes a S
    //Devemos achar uma cobertura exata S* contida em S
    //num_elem deve ser o tamanho de V
    // num_subsets deve ser o numero de colunas de S, ou seja o numero e subconjuntos de V pertencentes a S

    cout << "V = ";
    for(int i = 0; i < 6; i++){
        cout << V[i] << ' ';
    }
    cout << endl << endl;

    vector< vector<int> > A;

    bool belongs = false;

    //preenchendo a matriz binaria A, 1 se o elemento da coluna j pertence ao conjunto da linha i:
    for(int i = 0; i < num_subsets; i++) {
        for(int j = 0; j < num_elem; j++) {
            A.push_back(vector<int>());
            for(int k = 0; k < N; k++) {
                if(V[j] == S[i][k]) {
                    belongs = true;
                    break;
                }
            }
            if(belongs == true)
                A[i].push_back(1);
            else A[i].push_back(0);
            belongs = false;
        }
    }

    for(int i = 0; i < num_subsets; i++) {
        for(int j = 0; j < num_elem; j++) {
            cout << A[i][j] << ' ';
        }
        cout << endl << endl;
    }

    /*
    for(int i = 0; i < num_subsets; i++) {
        for(int j = 0; j < size_v; j++) {
            cout << A[i][j] << ' ';
        }
        cout << endl;;
    }
    */
    cout << "size_v = " << num_elem << endl << endl;


    //resolvendo a partir da matriz:
    return(matrix_x_cover(A, num_subsets, num_elem));
}



