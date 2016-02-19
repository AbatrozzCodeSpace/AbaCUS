#ifndef ABACUS_VECTOR_HPP
#define ABACUS_VECTOR_HPP

#include <cassert>

namespace abacus{
	namespace ds{
		template <typename T, int dim = 0>
		class VectorBase { 
			static const size_t size = dim;
		public : 
			// default constructor, warning! no initialization here!
			VectorBase() {}
			VectorBase( T* &data ) {
				memcpy( elem, data, sizeof(T) * dim );
			}

			void set( VectorBase<T, dim> &other ) {
				memcpy( elem, other.elem, sizeof(T) * dim );
			}

			template <typename U>
			void set( VectorBase< U, dim > &other ) {
				for ( unsigned int i = 0 ; i < dim ; i++ ) {
					elem[i] = static_cast<T>( other[i] );
				}
			}

			// accessor
			T &operator[]( size_t index ) { return elem[index]; }
			T &operator()( size_t index ) { return elem[index]; }

			// assignment 
			VectorBase<T, dim> &operator=( VectorBase<T, dim> &other ) { set(other); return *this; }
			template <typename U>
			VectorBase<T, dim> &operator=( VectorBase<U, dim> &other ) { set(other); return *this; }

			// arithmetic
			virtual VectorBase<T, dim> operator+( VectorBase<T, dim> &rhs ) { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = elem[i] + rhs[i];
				return ret;
			}
			virtual VectorBase<T, dim> operator-( VectorBase<T, dim> &rhs ) { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = elem[i] - rhs[i];
				return ret;
			}
			// same as Ptmult
			virtual VectorBase<T, dim> operator*( VectorBase<T, dim> &rhs ) { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = elem[i] * rhs[i];
				return ret;
			}
			// like Ptmult but divide
			virtual VectorBase<T, dim> operator/( VectorBase<T, dim> &rhs ) { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = elem[i] / rhs[i];
				return ret;
			}

			virtual VectorBase<T,dim> & operator+=( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] += rhs[i];
				return *this;
			}
			virtual VectorBase<T,dim> & operator-=( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] -= rhs[i];
				return *this;
			}
			virtual VectorBase<T,dim> & operator*=( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] *= rhs[i];
				return *this;
			}
			virtual VectorBase<T,dim> & operator/=( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] /= rhs[i];
				return *this;
			}

			// ostream
			friend std::ostream& operator<<( std::ostream &lhs, VectorBase<T, size> &rhs ) {
				lhs << "[";
				for( unsigned int i = 0 ; i < size ; i++ ) {
					if( i == size - 1 ) {
						lhs << rhs[i];
					} else {
						lhs << rhs[i] << ", ";
					}
				}
				lhs << "]";
				return lhs;
			}


		private :
			T elem[dim];
		}; // end class VectorBase

		

	}; // end ds
	using namespace ds;
};

#endif