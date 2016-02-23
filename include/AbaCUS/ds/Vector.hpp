#ifndef ABACUS_VECTOR_HPP
#define ABACUS_VECTOR_HPP

#include <cassert>
#include <cmath>

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
			VectorBase( T value ) {
				memset( elem, value, sizeof(T) * dim ); 
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
			T &operator[]( size_t index ) { assert( index >= 0 && index < dim ); return elem[index]; }
			T &operator()( size_t index ) { assert( index >= 0 && index < dim ); return elem[index]; }


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


			virtual VectorBase<T,dim> &operator+=( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] += rhs[i];
				return *this;
			}
			virtual VectorBase<T,dim> &operator-=( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] -= rhs[i];
				return *this;
			}
			virtual VectorBase<T,dim> &operator*=( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] *= rhs[i];
				return *this;
			}
			virtual VectorBase<T,dim> &operator/=( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] /= rhs[i];
				return *this;
			}


			virtual VectorBase<T, dim> operator+( T &rhs ) { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = elem[i] + rhs;
				return ret;
			}
			virtual VectorBase<T, dim> operator-( T &rhs ) { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = elem[i] - rhs;
				return ret;
			}
			virtual VectorBase<T, dim> operator*( T &rhs ) { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = elem[i] * rhs;
				return ret;
			}
			virtual VectorBase<T, dim> operator/( T &rhs ) { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = elem[i] / rhs;
				return ret;
			}

			virtual VectorBase<T, dim> &operator+=( T &rhs ) { 
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] += rhs;
				return *this;
			}
			virtual VectorBase<T, dim> &operator-=( T &rhs ) { 
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] -= rhs;
				return *this;
			}
			virtual VectorBase<T, dim> &operator*=( T &rhs ) { 
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] *= rhs;
				return *this;
			}
			virtual VectorBase<T, dim> &operator/=( T &rhs ) { 
				for( unsigned int i = 0 ; i < dim ; i++ ) elem[i] /= rhs;
				return *this;
			}

			// unary negation
			virtual VectorBase<T, dim> operator-() { 
				VectorBase<T,dim> ret;
				for( unsigned int i = 0 ; i < dim ; i++ ) ret[i] = -elem[i];
				return ret;
			}

			// boolean operator
			virtual bool operator==( VectorBase<T, dim> &rhs ) {
				for( unsigned int i = 0 ; i < dim ; i++ ) {
					if( elem[i] != rhs[i] ) return false;
				}
				return true;
			}

			// inequality cannot be overridden, it's suppose to be opposite of operator==
			bool operator!=( VectorBase<T, dim> &rhs ) {
				return !( *this == rhs );
			}

			// virtual function for faster implementation (without for loop)
			virtual T dot( VectorBase<T, dim> &rhs ) {
				T value = static_cast<T>(0.0);
				for( unsigned int i = 0 ; i < dim ; i++ ) {
					value += elem[i] * rhs[i];
				}
				return value;
			}

			// there will be no cross function in the class, since it cannot be generalized. 

			template <typename outputT>
			typename std::enable_if<std::is_floating_point<outputT>::value, outputT>::type normSquared() {
				outputT value = static_cast<outputT>(0.0);
				for( unsigned int i = 0 ; i < dim ; i++ ) {
					value += static_cast<outputT>( elem[i] * elem[i] );
				}
				return value;
			}

			// norm
			template <typename outputT>
			typename std::enable_if<std::is_floating_point<outputT>::value, outputT>::type norm() {
				outputT value = static_cast<outputT>( sqrt( normSquared<outputT>() ) );
				return value;
			}

			// warning, this will turn every parameter into typename T, just becareful with integer types... 
			void normalize() {
				T denom = static_cast<T>( norm() );
				for( unsigned int i = 0 ; i < dim ; i++ ) {
					elem[i] /= denom;
				}
			}

			template <typename returnT>
			VectorBase<returnT, dim> getNormalized() {
				returnT denom = static_cast<T>( norm() );
				if ( denom > 0 ) {
					VectorBase<returnT, dim> toReturn( elem );
					for( unsigned int i = 0 ; i < dim ; i++ ) {
						toReturn[i] /= denom;
					}
					return toReturn;
				} else {
					return 
				}
			}

			// you know what you're doing, don't be ridiculous putting something min > max in this function, it's just... stupid...  
			void clamp( T min, T max ) {
				assert( min <= max );
				for( unsigned int i = 0 ; i < dim ; i++ ) {
					if( elem[i] < min ) elem[i] = min;
					if( elem[i] > max ) elem[i] = max;
				}
			}

			// you know what you're doing, don't be ridiculous putting something min > max in this function, it's just... stupid...  
			void getClamped( T min, T max ) {
				assert( min <= max );
				VectorBase<T, dim> toReturn( elem ); 
				for( unsigned int i = 0 ; i < dim ; i++ ) {
					if( toReturn[i] < min ) toReturn[i] = min;
					if( toReturn[i] > max ) toReturn[i] = max;
				}
				return toReturn;
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

		//template <typename U>
		//class Vec2<U> : public VectorBase<U, 2> {
		//public :
		//	Vec2();
		//	Vec2( T x, T y );
		//	T x, y;
		//}; // end class Vec2<T>

	}; // end ds
	using namespace ds;
};

#endif