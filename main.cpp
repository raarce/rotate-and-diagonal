#include <iostream>
#include <queue>
 
typedef unsigned int UINT;
using namespace std;

//
// A circular queue class for representing each of the
// rows of the matrix.
//
template <typename T>
class circQueue : public queue<T> {
public:
    circQueue() {}

    void rotateLeft() {
        this->push(this->front());
        this->pop();
    }
    
    //
    // Given a number and the number of bits, fills the 
    // matrix with 1 and 0's 
    // Example: pushBin(0x7,5) -->  [ 1 1 1 0 0]
    //
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
 
//
// A class to represent the 2-dimensional matrix
//

template <typename T>
class RotMatrix {
private:
    vector < circQueue <T> > M;
    UINT dimX, dimY;
public:
    RotMatrix() {};
    
    //
    // Init the matrix to x rows and y columns
    //
    void init(UINT x, UINT y) {
        for (UINT i=0; i < y; i++){
            circQueue <T> A;
            M.push_back(A);
        }
        dimX = x; dimY = y;
    }
 
    //
    // Deprecated  :-)
    //
    void read(T **A) {
        for (UINT i=0; i < dimY; i++){
            for (UINT j=0; j < dimX; j++){
                M[i].push(A[i][j]);
            }
        }       
    }
 
    //
    // Read an array of unsigned numbers and use each
    // to fill the 1 and 0's of a row matrix
    //
    void readBins(vector<UINT> V) {
        for (int i=0; i<V.size(); i++) {
            M[i].pushBin(V[i], dimX);
        }
    }
    
    //
    // Rotate left the matrix.
    // 
    void rotate_left(){
        for (UINT i=0; i < dimY; i++){
            M[i].rotateLeft();
        }       
    }
 
 
    //
    //  Starting from (0,0), read the matrix diagonally.
    //  (0,0), (1,0), (0,1), (2,0). (1,1), (0,2),.....
    //
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
 
 
    UINT A[] = {0x30, 0x04, 0x3e, 0x0b, 0x05, 0x0a, 0x31};
    vector <UINT> V(A, A+dimY);

 
    RotMatrix<char> R;
    R.init(dimX,dimY);

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
