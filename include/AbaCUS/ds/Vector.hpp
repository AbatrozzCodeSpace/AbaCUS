#ifndef ABACUS_VECTOR_HPP
#define ABACUS_VECTOR_HPP

#include <cassert>
#include <cmath>
#include <algorithm>
#include <string>

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
				std::uninitialized_fill_n( &elem[0], dim, value );
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

			// casting
			operator std::string() const { 
				std::string str = "["; 
				for( unsigned int i = 0 ; i < size ; i++ ) {
					if( i == size - 1 ) {
						str += std::to_string( elem[i] );
					} else {
						str += std::to_string( elem[i] );
						str += ", ";
					}
				}
				str += "]";
				return str;
			}

			// static member functions
			static VectorBase<T, dim> zero() {
				return VectorBase<T, dim>(0);
			}

			static VectorBase<T, dim> one() {
				return VectorBase<T, dim>(1);
			}

		protected :
			T elem[dim];
		}; // end class VectorBase

		// vec2 class
		template <typename T>
		class Vec2 : public VectorBase<T, 2> {
		public :
			Vec2() { 
				elem[0] = 0;
				elem[1] = 0;
			}
			Vec2( T x_, T y_ ) {
				elem[0] = x_;
				elem[1] = y_;
			}
			Vec2( VectorBase<T,2> &base ) {
				elem[0] = base[0];
				elem[1] = base[1];
			}
			
			// setter, e.g. vec.x() = val;
			T &x() { return elem[0]; }
			T &y() { return elem[1]; }

			// getter
			T x() const { return elem[0]; }
			T y() const { return elem[1]; }
			
		}; // end class Vec2<T>

		// vec3 class
		template <typename T>
		class Vec3 : public VectorBase<T, 3> {
		public :
			Vec3() { 
				elem[0] = 0;
				elem[1] = 0;
				elem[2] = 0;
			}
			Vec3( T x_, T y_, T z_ ) {
				elem[0] = x_;
				elem[1] = y_;
				elem[2] = z_;
			}
			Vec3( VectorBase<T,3> &base ) {
				elem[0] = base[0];
				elem[1] = base[1];
				elem[2] = base[2];
			}
			// setter, e.g. vec.x() = val;
			T &x() { return elem[0]; }
			T &y() { return elem[1]; }
			T &z() { return elem[2]; }

			// getter
			T x() const { return elem[0]; }
			T y() const { return elem[1]; }
			T z() const { return elem[2]; }
		
		}; // end class Vec3<T>

		template <typename T, int dim> struct Vector { typedef VectorBase<T, dim> type; };
		template <typename T, int dim> struct Vec { typedef VectorBase<T, dim> type; };

		template <int dim> struct VecXi { typedef VectorBase<int, dim> type; };
		template <int dim> struct VecXf { typedef VectorBase<float, dim> type; };
		template <int dim> struct VecXd { typedef VectorBase<double, dim> type; };
		template <int dim> struct VecXl { typedef VectorBase<long, dim> type; };
		template <int dim> struct VecXui { typedef VectorBase<unsigned int, dim> type; };
		template <int dim> struct VecXb { typedef VectorBase<bool, dim> type; };

		//template <typename T, int dim> using Vector = VectorBase<T, dim>;
		//template <typename T, int dim> using Vec = VectorBase<T, dim>;

		//template <int dim> using VecXi = VectorBase<int, dim>;
		//template <int dim> using VecXf = VectorBase<float, dim>;
		//template <int dim> using VecXd = VectorBase<double, dim>;
		//template <int dim> using VecXl = VectorBase<long, dim>;
		//template <int dim> using VecXui = VectorBase<unsigned int, dim>;
		//template <int dim> using VecXb = VectorBase<bool, dim>;

		typedef Vec2<int>			Vec2i;
		typedef Vec2<float>			Vec2f;
		typedef Vec2<double>		Vec2d;
		typedef Vec2<long>			Vec2l;
		typedef Vec2<unsigned int>	Vec2ui;
		typedef Vec2<bool>			Vec2b;

		typedef Vec3<int>			Vec3i;
		typedef Vec3<float>			Vec3f;
		typedef Vec3<double>		Vec3d;
		typedef Vec3<long>			Vec3l;
		typedef Vec3<unsigned int>	Vec3ui;
		typedef Vec3<bool>			Vec3b;

	}; // end ds
	using namespace ds;
};

#endif