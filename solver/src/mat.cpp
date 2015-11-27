#include "../inc/mat.hh"

Matrix::Matrix(){size = 0; row = NULL;}

Matrix::Matrix(int rows, int cols, double init)
{
	size = rows;
	row = new Vector[rows];
	for(int i=0; i<rows; i++)
		row[i].Resize(cols, init);
}

Matrix::Matrix(const Matrix& mat)
{

	size = mat.Rows();
	row = new Vector[size];
	for(int i=0; i<size; i++)
	{
		row[i].Resize(mat.Cols());
		row[i]=mat[i];
	}
	
}
//Matrix::Matrix()
	
/*Matrix::Matrix(Vector *rows, int quant)
{
	size = quant;
	row = new Vector[size];
	for(int i=0; i<size; i++)
		row[i]=rows[i];

		}*/

void Matrix::Set(Vector vec, int ind)
{
	// ASSERT ROZMIAR WEKTORA!
	// ASSERT INDEKS!
	row[ind]=vec;
}

int Matrix::Rows() const{ return size; }

int Matrix::Cols() const{if(size==0) return 0; else return row[0].Size();}

Vector Matrix::operator[] (int ind) const{ return row[ind]; }

Vector& Matrix::operator[] (int ind){ return row[ind]; }

void Matrix::Print() const
{
	for(int i=0; i<size; i++)
		row[i].Print();
	std::cout << std::endl;
}

void Matrix::Resize(int rows, int cols)
{
	if((rows < 1) || (cols<  1)) return;
	if(size==0)
	{
		size = rows;
		row = new Vector[rows];
	}
	if(rows!=size)
	{
		Vector *nrow = new Vector[rows];
		for(int i=0; i<((rows<size)?rows:size); i++)
			nrow[i]=row[i];
		size=rows;
		delete[] row;
		row=nrow;
	}
	for(int i=0; i<size; i++)
		row[i].Resize(cols);
	
}

Matrix Matrix::Transpose() const
{
	Matrix temp(Cols(), Rows());
	temp.Print();
	for(int r=0; r<Rows(); r++)
		for(int c=0; c<Cols(); c++)	
			temp[c][r]=row[r][c];
	
	return temp;
}

double Matrix::Det(bool part_piv) const
{
	if((Rows()!=Cols()) || (size == 0) )
	{
		std::cerr << "Nie da rady" << std::endl;
		return 0;
	}

	Matrix mat(*this);

	int zam=0;
	for(int i=0; i<size; i++)
	{
		if(part_piv || (mat[i][i]==0))
		{
			int imax=i;
			for(int j=i+1; j<size; j++)
				if(abs(mat[j][i]) > abs(mat[imax][i])) imax=j;
			if(mat[imax][i]==0){return 0;}
			//std::cout << "DEBUG_b:\n" << "i=" << i << " imax=" << imax << std::endl;
			//std::cout << "[i]: "; mat[i].Print(); std::cout << "[imax]: "; mat[imax].Print();
			if(i!=imax)
			{
			Vector temp2(mat[i]);
			mat[i]=mat[imax];
			mat[imax]=temp2;
			zam++;
			}
            //std::cout << "DEBUG_a:\n" << "i=" << i << " imax=" << imax << std::endl;
			//std::cout << "[i]: "; mat[i].Print(); std::cout << "[imax]: "; mat[imax].Print();
		}

		//mat[i]=mat[i]/mat[i][i];
		for(int j=i+1; j<size; j++)
		{
			mat[j]=mat[j]+((mat[i]*(-1))*(mat[j][i]/mat[i][i]));
		}
			
	}

	double det=1;
	for(int i=0; i<size; i++) det*=mat[i][i];
	if(zam%2) det=-1*det;

	return det;
}
