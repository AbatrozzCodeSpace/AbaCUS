#ifndef OBJ_IO_HPP
#define OBJ_IO_HPP

#if defined (CINDER_CINDER)
	#include <cinder/TriMesh.h>
#endif

#include <AbaCUS/io/IoCore.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <AbaCUS/ds/Vector.hpp>
#include <AbaCUS/string/split.hpp>

namespace abacus {
namespace io {

	template <typename _T>
	inline ABACUS_IO_STATUS loadObj(std::string filename, std::vector<_T> &vertices, std::vector<unsigned int> &faces) {
		std::cout << "loading OBJ file..." << std::endl;
		std::string line;
		std::ifstream myfile(filename.data());
		if (myfile) {
			while (getline(myfile, line)) {
				char *cstr = new char[line.length() + 1];
				strcpy(cstr, line.c_str());

				char header[10];
				sscanf(cstr, "%s ", header);
				if (strcmp(header, "v") == 0) { // vertices
					_T x, y, z;
					x = y = z = 0.0;
					sscanf(cstr, "%*s %f %f %f", &x, &y, &z);
					vertices.push_back(x);
					vertices.push_back(y);
					vertices.push_back(z);
					
				}
				else if (strcmp(header, "f") == 0) { // faces
					std::vector<std::string> tokens;
					abacus::string::split(cstr, ' ', tokens);
					if (tokens.size() == 4) { // tris
						int f[3];
						for (int i = 1; i < tokens.size(); i++) {
							std::vector<std::string> tokens2;
							abacus::string::split(tokens[i], '/', tokens2);
							if (!tokens2.empty()) {
								f[i - 1] = atoi(tokens2[0].data());
							}
						}
						faces.push_back(f[0] - 1);
						faces.push_back(f[1] - 1);
						faces.push_back(f[2] - 1);
					}
					else if (tokens.size() == 5) { // quads
						int f[4];
						for (int i = 1; i < tokens.size(); i++) {
							std::vector<std::string> tokens2;
							abacus::string::split(tokens[i], '/', tokens2);
							if (!tokens2.empty()) {
								f[i - 1] = atoi(tokens2[0].data());
							}
						}
						faces.push_back(f[0] - 1);
						faces.push_back(f[1] - 1);
						faces.push_back(f[2] - 1);
						faces.push_back(f[1] - 1);
						faces.push_back(f[2] - 1);
						faces.push_back(f[3] - 1);
					}
				}

				delete[] cstr;

			}
			myfile.close();
		}
		else {
			return IO_LOAD_ERROR;
		}
		return IO_SUCCESS;
	}

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