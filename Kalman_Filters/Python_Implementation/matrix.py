import math
from math import sqrt
import numbers

def zeroes(height, width):
        """
        Creates a matrix of zeroes.
        """
        g = [[0.0 for _ in range(width)] for __ in range(height)]
        return Matrix(g)

def identity(n):
        """
        Creates a n x n identity matrix.
        """
        I = zeroes(n, n)
        for i in range(n):
            I.g[i][i] = 1.0
        return I

class Matrix(object):

    # Constructor
    def __init__(self, grid):
        self.g = grid
        self.h = 0
        self.w = 0
        for row in grid:
            self.h += 1
        for c in grid[0]:
            self.w += 1

    #
    # Primary matrix math methods
    #############################
 
    def determinant(self):
        """
        Calculates the determinant of a 1x1 or 2x2 matrix.
        """
        if not self.is_square():
            raise(ValueError, "Cannot calculate determinant of non-square matrix.")
        if self.h > 2:
            raise(NotImplementedError, "Calculating determinant not implemented for matrices largerer than 2x2.")
        
        # TODO - your code here
        
        if self.h == 2:
            return self.g[0][0]*self[1][1] - self.g[1][0]*self.g[0][1]
        elif self.h == 1:
            return self.g[0][0]
        

    def trace(self):
        """
        Calculates the trace of a matrix (sum of diagonal entries).
        """
        if not self.is_square():
            raise(ValueError, "Cannot calculate the trace of a non-square matrix.")

        # TODO - your code here
        trace = 0
        for i in range(self.h):
            trace += self.g[i][i]
        return trace

    def inverse(self):
        """
        Calculates the inverse of a 1x1 or 2x2 Matrix.
        """
        if not self.is_square():
            raise(ValueError, "Non-square Matrix does not have an inverse.")
        if self.h > 2:
            raise(NotImplementedError, "inversion not implemented for matrices larger than 2x2.")

        # TODO - your code here
        det = self.determinant()
        if det == 0:
            raise(ValueError, "Matrix is not invertible.")
        
        inverse = zeroes(self.h, self.w)
        if inverse.h == 2:
            inverse[0][0], inverse[1][1] = self.g[1][1]/det, self.g[0][0]/det
            inverse[0][1] = self.g[0][1] * -1/det
            inverse[1][0] = self.g[1][0] * -1/det
        elif inverse.h == 1:
            inverse[0][0] = 1/det
            
        return Matrix(inverse)

    def _get_row(self, row):
        return self.g[row]
    
    def _get_column(self, column_number):
        column = []
        for row in self.g:
            column.append(row[column_number])
        return column
    
    def _dot_product(self, vector_one, vector_two):
        dotprod = 0
        vector_one = list(vector_one)
        vector_two = list(vector_two)
        if len(vector_one) != len(vector_two):
            print("Mismatch in vectors' length!")
            return
        for i in range(len(vector_one)):
            dotprod += vector_one[i]*vector_two[i]
        return dotprod
    
    
    def T(self):
        """
        Returns a transposed copy of this Matrix.
        """
        # TODO - your code here
        
        matrix_transpose = []
        for c in range(self.w):
            matrix_transpose.append(self._get_column(c))    
        return Matrix(matrix_transpose)

    def is_square(self):
        return self.h == self.w

    #
    # Begin Operator Overloading
    ############################
    def __getitem__(self,idx):
        """
        Defines the behavior of using square brackets [] on instances
        of this class.

        Example:

        > my_matrix = Matrix([ [1, 2], [3, 4] ])
        > my_matrix[0]
          [1, 2]

        > my_matrix[0][0]
          1
        """
        return self.g[idx]

    def __repr__(self):
        """
        Defines the behavior of calling print on an instance of this class.
        """
        s = ""
        for row in self.g:
            s += " ".join(["{} ".format(x) for x in row])
            s += "\n"
        return s

    def __add__(self,other):
        """
        Defines the behavior of the + operator
        """
        if self.h != other.h or self.w != other.w:
            raise(ValueError, "Matrices can only be added if the dimensions are the same") 
        #   
        # TODO - your code here
        #
        result = zeroes(self.h, self.w)
        for r in range(self.h):
            for c in range(self.w):
                result[r][c] = self.g[r][c] + other.g[r][c]
        return Matrix(result)

    def __neg__(self):
        """
        Defines the behavior of - operator (NOT subtraction)

        Example:

        > my_matrix = Matrix([ [1, 2], [3, 4] ])
        > negative  = -my_matrix
        > print(negative)
          -1.0  -2.0
          -3.0  -4.0
        """
        #   
        # TODO - your code here
        #
        
        result = zeroes(self.h, self.w)
        for r in range(self.h):
             for c in range(self.w):
                result[r][c] = -1*self.g[r][c]
        return Matrix(result)
            

    def __sub__(self, other):
        """
        Defines the behavior of - operator (as subtraction)
        """
        #   
        # TODO - your code here
        #
        if self.h != other.h or self.w != other.w:
            raise(ValueError, "Matrices can only be added if the dimensions are the same") 
        
        result = zeroes(self.h, self.w)
        for r in range(self.h):
            for c in range(self.w):
                result[r][c] = self.g[r][c] - other.g[r][c]
        return Matrix(result)
    
    def __mul__(self, other):
        """
        Defines the behavior of * operator (matrix multiplication)
        """

        rowsA,colsA = self.h, self.w
        rowsB,colsB = other.h, other.w
        
        if colsA != rowsB:
            raise(ValueError, "Number of columns in first matrix not equal to number of rows in second matrix; matrix multiplication failed!")
            
        
        product = []
        
        other_T = other.T()
        rowsB_T,colsB_T = other_T.h, other_T.w

        for rowA in self.g:
            rowprod = []
            for rowB_T in other_T.g:
                rowprod.append(self._dot_product(rowA,rowB_T))
            product.append(rowprod)
        

        return Matrix(product)
        

    def __rmul__(self, other):
        """
        Called when the thing on the left of the * is not a matrix.

        Example:

        > identity = Matrix([ [1,0], [0,1] ])
        > doubled  = 2 * identity
        > print(doubled)
          2.0  0.0
          0.0  2.0
        """
        if isinstance(other, numbers.Number):
            result = zeroes(self.h, self.w)
            for r in range(self.h):
                for c in range(self.w):
                    result[r][c] = self.g[r][c] * other
            return Matrix(result)
        
    def __len__(self):
        return self.h
            