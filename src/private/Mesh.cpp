#include "Mesh.h"

template class Triangle<vec3_f>;
template class Triangle<vec2_f>;

void Mesh::loadObjFileDate(const char* filePath)
{
    std::fstream file(filePath, std::fstream::in);
    if (!file.is_open())
    {
        std::cout << "failed to open File : " << filePath;
        return;
    }
    
    std::string line;
    
    while (std::getline(file, line))
    {
        //std::cout << line << "\n";
        
        std::stringstream ss(line);
        char ch;

        if (line[0] == '#')
            continue;

        ss >> ch;
        

        if (ch == 'v')
        {
            ss >> std::noskipws >> ch;
            if (ch == 't')
            {
                // texture values
            }
            else if (ch == 'n')
            {
                // normal values
            }
            else if (ch == ' ')
            {
                float v1, v2, v3;
                char space;

                ss >> v1 >> space >> v2 >> space >> v3;
        
                vertices.push_back({ v1,v2,v3 });
            }
        }
        else if (ch == 'f')
        {
            int v1, c1, n1, v2, c2, n2, v3, c3, n3;

            char slash;
        
            // Now, attempt to extract the values correctly
            if (!(ss >> v1 >> slash >> c1 >> slash >> n1)) {
                std::cerr << "Error parsing first vertex group!" << std::endl;
                continue;
            }

            if (!(ss >> v2 >> slash >> c2 >> slash >> n2)) {
                std::cerr << "Error parsing second vertex group!" << std::endl;
                continue;
            }

            if (!(ss >> v3 >> slash >> c3 >> slash >> n3)) {
                std::cerr << "Error parsing third vertex group!" << std::endl;
                continue;
            }
            faces.push_back({ v1, v2, v3 });
            texture.push_back({ c1,c2, c3 });
            normal.push_back({ n1, n2, n3 });
        }
    }

    file.close();
}
