#include <iostream>
#include <queue>
 
typedef unsigned int UINT;
using namespace std;
 
template <typename T>
class circQueue : public queue<T> {
public:
    circQueue() {}
    void rotate() {
        this->push(this->front());
        this->pop();
    }
    void pushBin(UINT n, UINT digits) {
      for (UINT i=0; i < digits; i++) {
            this->push((n & 0x1) + '0');
            //printf("pushing %c\n", (n & 0x1) + '0');
            n = n >> 1;
        }
    }
    void display() {
        for(int i=0; i<this->size();i++){
            cout << this->front() << " ";
            this->push(this->front());
            this->pop();
        } 
        cout << endl;           
    }
 
};
 
template <typename T>
class RotMatrix {
private:
    vector < circQueue <T> > M;
    UINT dimX, dimY;
public:
    RotMatrix() {};
    void init(UINT x, UINT y) {
        for (UINT i=0; i < y; i++){
            circQueue <T> A;
            M.push_back(A);
        }
        dimX = x; dimY = y;
    }
 
    void read(T **A) {
        for (UINT i=0; i < dimY; i++){
            for (UINT j=0; j < dimX; j++){
                M[i].push(A[i][j]);
            }
        }       
    }
 
    void readBins(vector<UINT> V) {
        for (int i=0; i<V.size(); i++) {
            M[i].pushBin(V[i], dimX);
        }
    }
 
    void rotate_left(){
        for (UINT i=0; i < dimY; i++){
            M[i].rotate();
        }       
    }
 
    void readDiagonally(bool onlyHeader = false) {
        //printf("dimX:%u, dimY:%u", dimX, dimY);
        UINT minDim = min(dimX,dimY);
        UINT maxDim = max(dimX,dimY);
        for (UINT i = 0; i < dimX + dimY; i++) {

            UINT iBegin = (i < dimX) ? 0 : i - dimX + 1;
            UINT iEnd = (i < minDim) ? i + 1  : ((i < maxDim) ? minDim : dimY + dimX - i - 1);

            // this one to compute the actual x coordinate
            UINT x = (i<dimX) ? i : dimX-1;

            //printf("i:%u, begin: %u, end: %u\n",i, iBegin, iEnd);
            for (UINT j = iBegin ; j < iBegin + iEnd ; j++) {
                if (onlyHeader) printf("(%u,%u)\t", x-- ,j);
                else { 
                    cout << M[j].front() << "\t" ;
                    M[j].rotate();
                }
            }
        }
    }
 
    void display() {
        for (UINT i=0; i < dimY; i++){
            M[i].display();
        }
    }
};
 
 
const int dimX = 6;
const int dimY = 7;
 
typedef char * charptr;
int main() {
 
    // circQueue<char> Q;
    // Q.pushBin(0x5,4);
 
    // Q.display();
 
    UINT A[] = {0x30, 0x04, 0x3e, 0x0b, 0x05, 0x0a, 0x31};
    //UINT A[] = {0x3, 0x5, 0x2};
    vector <UINT> V(A, A+dimY);
    // V.push_back(0x7);
    // V.push_back(0x5);
    // V.push_back(0x9);
 
 
    // charptr *A = new charptr[dimY];
    // for (UINT i=0; i<dimY; i++) { 
    //  A[i] = new char[dimX];
    //  for (UINT j=0; j<dimX; j++) {
    //      A[i][j] = 'A' + i*3 + j;
    //  }
    // }
 
    RotMatrix<char> R;
    R.init(dimX,dimY);
    //R.read(A);
    R.readBins(V);
 
    R.display(); 
    cout << " ------- " << endl;
    R.readDiagonally(true); cout << endl;
    R.readDiagonally();
    cout << endl;
    cout << " ------- " << endl;
    R.rotate_left();    
    R.display();
    cout << " ------- " << endl;
    R.readDiagonally();

    cout << " ------- " << endl;
    R.rotate_left();    
    R.display();
    cout << " ------- " << endl;
    R.readDiagonally();

}