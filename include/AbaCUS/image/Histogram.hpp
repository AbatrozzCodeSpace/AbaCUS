#ifndef ABACUS_HISTOGRAM_HPP
#define ABACUS_HISTOGRAM_HPP

#include <vector>

#ifdef LIBFLOATIMAGE
#include <libfloatimage.h>
#endif

namespace abacus {
	namespace image{
		
		class Histogram {

		};

#ifdef LIBFLOATIMAGE
		inline void findHistogram( floatimage &img, float range, std::vector<std::vector<int>> &histogram, bool makeGreyscale = false ) {
			int numChannel = makeGreyscale ? 1 : 3;
			int numBar = ceil( 1.0f / range ); 
			histogram.resize( numChannel, std::vector<int>(numBar) );
			
			for( unsigned int y = 0 ; y < img.sizey ; y++ ) {
				for( unsigned int x = 0 ; x < img.sizex ; x++ ) {
					fRGB color = img.line(y)[x];
					if( makeGreyscale ) {
						double colorValue = 0.3 * color.r + 0.59 * color.g + 0.11 * color.b;
						int idx = colorValue / range;
						histogram[0][idx]++;
					} else {
						vec3f colorV( color.r, color.g, color.b );
						colorV /= range;
						vec3i colorIdx = colorV;
						histogram[0][colorIdx.x]++;
						histogram[1][colorIdx.y]++;
						histogram[2][colorIdx.z]++;
					}
				}
			}
		}
#endif

	};
	using namespace image;
};

#endif