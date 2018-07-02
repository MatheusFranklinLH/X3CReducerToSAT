#include "libraries.h";

/*
vector< vector<int> > allCombs;
vector<int> combination;
vector<int> index;

/*
bool belongs(int v, int* s) {
    int n = sizeof(s)/sizeof(int);
    for(int i = 0; i < n; i++){
        if(v == s[i])
            return(true);
    }
    return(false);
}
*/
/*
int factorial(int p) {
    if(p == 0)
        return 1;
    return p*factorial(p-1);
}

void comb_gen_rec(int offset, int k) {
  if (k == 0) {
    allCombs.push_back(combination);
    return;
  }
  for (int i = offset; i <= index.size()-k; ++i) {
    combination.push_back(index[i]);
    comb_gen_rec(i+1, k-1);
    combination.pop_back();
  }
}

void comb_gen(int nsets, int p) {

    for(int i = 0; i < nsets; i++){
        index.push_back(i);
    }
    comb_gen_rec(0, p);
}
*/
int main()
{
    /***************************
    int V[] = {1, 2, 3, 4, 5, 6};

    int S[][N] = {
        {1, 2, 5},
        {2, 3, 4},
        {3, 4, 6},
        {2, 5, 6}
    };
    */
    int V[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int S[][N] = {
                  {1, 3, 6},
                  {3, 5, 6},
                  {1, 4, 7},
                  {7, 8, 9},
                  {2, 4, 7},
                  {3, 4, 6},
                  {5, 8, 9},
                  {1, 2, 9}
                 };
    int num_subsets = sizeof(S)/sizeof(S[0]);
    int num_elem = sizeof(V)/sizeof(int);

    bool e = exact_cover(V, S, num_elem, num_subsets);
    if(e){
        cout << endl << endl << "********************EH FIIIIIXA********************" << endl << endl;
    } else cout << endl << endl << "!!!!!!!!!!!!!!!!!!!!!QUE LOOOMBRA!!!!!!!!!!!!!!!!!!!!!" << endl << endl;
    cout << "ncol(A) = " << sizeof(S)/sizeof(S[0]) << endl << endl;


    cout << "/***********************************************************/" << endl << endl;



    /***********************************************************

    comb_gen(6, 2);
    int ncombs = allCombs.size();
    if(ncombs != factorial(6)/(factorial(2)*(factorial(6-(2)))))
        cout << "warning:" << " " << ncombs << endl;
    cout << "success:" << " " << ncombs << endl;

    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 2; j++) {
            cout << allCombs[i][j] << ' ';
        }
        cout << "-----------------" << endl << endl;
    }

    cout << A[allCombs[0][0]][0] << endl;
    */

    return 0;
}

