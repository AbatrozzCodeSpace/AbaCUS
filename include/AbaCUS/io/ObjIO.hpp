#ifndef OBJ_IO_HPP
#define OBJ_IO_HPP

#if defined (CINDER_CINDER)
	#include <cinder/TriMesh.h>
#endif

#include <iostream>
#include <string>
#include <vector>

namespace abacus {
namespace io {

#if defined (CINDER_CINDER)
inline 
void saveObj( std::string filename, 
				ci::TriMesh &mesh ) {
					std::cout << "saving OBJ to " << filename; 
					std::vector<ci::Vec3f> v = mesh.getVertices();
					std::vector<uint32_t> idx = mesh.getIndices();


					FILE* f = fopen( filename.data(), "w" );
					for (int i = 0 ; i < v.size(); i++) {
						fprintf( f, "v %f %f %f\n", v[i].x, v[i].y, v[i].z );
					}
					for ( int i = 0 ; i < idx.size(); i+=3 ) {
						fprintf( f, "f %d %d %d\n", idx[i]+1, idx[i+1]+1, idx[i+2]+1 );
					}

					fclose( f );
					std::cout << filename << " ..DONE!" << std::endl;
}
#endif

}
using namespace io;
}
#endif