#ifndef MY_MATRIX_HH
#define MY_MATRIX_HH


template <typename T>  //general type T because you can either have  matrix of floats or a matrix of doubles

class my_matrix {
  private:
  	int rows;   //each matrix has a certain number of rows, a certain number of columns, and a pointer of pointers to each element
  	int columns;
  	T **pt;

  public:

    //prototypes for my_matrix class 

    my_matrix();   //default constructor

    my_matrix(int rows, int columns); //user constructor

   	my_matrix(const my_matrix &old); //copy constructor

   	~my_matrix(); //desturctor

    //overloaded operators for matrix operations

   	T& operator()(int row, int col);
   
    my_matrix& operator=(const my_matrix& b); //sets one matrix equal to another
   		
   	my_matrix operator+(const my_matrix& b); //adds two matrices 

   	my_matrix operator*(const my_matrix& b); //multiplies two matrices
   		
   	my_matrix operator|(const my_matrix& b); //performes left division of two matrices


	
};


#endif


