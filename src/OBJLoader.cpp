#include "OBJLoader.h"

OBJLoader::OBJLoader()
{
    vertexCount = 0;
}

void OBJLoader:: load(string path)
{
//Deklaracje
//----------------------------------------------------------------------------------------------------------------------
    vector<float> not_nice_verts;
    vector<float> not_nice_normals;
    vector<float> not_nice_colors;
    vector<int> order_verts;
    vector<int> order_colors;
    vector<int> order_normals;

    int nv = 0;
    int nn = 0;

    char word[128];
    float fscaning_variable[3];
    unsigned int helping_variable[9];
    FILE * file = fopen(path.c_str(), "r");

//----------------------------------------------------------------------------------------------------------------------

    if( file == NULL )
    {
        cout<<"Couldn't load the file:" << path<<endl;
    }

    else
    {
        while(true)
        {
            int res = fscanf(file, "%s", word);
            if (res == EOF) break;

            if ( strcmp( word, "v" ) == 0 )
            {
                nv++;
                fscanf(file, "%f %f %f\n", &fscaning_variable[0], &fscaning_variable[1], &fscaning_variable[2] );
                not_nice_verts.push_back(fscaning_variable[0]);
                not_nice_verts.push_back(fscaning_variable[1]);
                not_nice_verts.push_back(fscaning_variable[2]);
                not_nice_verts.push_back(1.0f);
            } else if ( strcmp( word, "vt" ) == 0 )
            {
                fscanf(file, "%f %f \n", &fscaning_variable[0], &fscaning_variable[1] );
                not_nice_colors.push_back(fscaning_variable[0]);
                not_nice_colors.push_back(fscaning_variable[1]);
            } else if ( strcmp( word, "vn" ) == 0 )
            {
                nn++;
                fscanf(file, "%f %f %f\n", &fscaning_variable[0], &fscaning_variable[1], &fscaning_variable[2]  );

                not_nice_normals.push_back(fscaning_variable[0]);
                not_nice_normals.push_back(fscaning_variable[1]);
                not_nice_normals.push_back(fscaning_variable[2]);
                not_nice_normals.push_back(0.0f);
            } else if (strcmp( word, "f" ) == 0 )
            {
                vertexCount = vertexCount + 3;
                fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &helping_variable[0], &helping_variable[1], &helping_variable[2],
                                                             &helping_variable[3], &helping_variable[4], &helping_variable[5],
                                                             &helping_variable[6], &helping_variable[7], &helping_variable[8] );
               //  cout<<"f : "<<helping_variable[0] << "/" <<  helping_variable[1] << "/" << helping_variable[2] << " ";
               //  cout<<helping_variable[3] << "/" <<  helping_variable[4] << "/" << helping_variable[5] << " ";
               //  cout<<helping_variable[6] << "/" <<  helping_variable[7] << "/" << helping_variable[8] << endl;
                order_verts.push_back(helping_variable[0]);
                order_colors.push_back(helping_variable[1]);
                order_normals.push_back(helping_variable[2]);

                order_verts.push_back(helping_variable[3]);
                order_colors.push_back(helping_variable[4]);
                order_normals.push_back(helping_variable[5]);

                order_verts.push_back(helping_variable[6]);
                order_colors.push_back(helping_variable[7]);
                order_normals.push_back(helping_variable[8]);

            }
        }


        verts = new float[order_verts.size()*4];
        normals=new float[order_normals.size()*4];
        colors =new float[order_colors.size()*2];

        for( int i=0; i<order_verts.size(); i++ )
        {
             verts[i*4] = not_nice_verts[((order_verts[i]-1)*4)+0];

             verts[i*4+1] = not_nice_verts[((order_verts[i]-1)*4)+1];

             verts[i*4+2] = not_nice_verts[((order_verts[i]-1)*4)+2];

             verts[i*4+3] = not_nice_verts[((order_verts[i]-1)*4)+3];

        }
        for( int i=0; i<order_normals.size(); i++)
        {
             normals[i*4] = not_nice_normals[((order_normals[i]-1)*4)+0];
             normals[i*4+1] = not_nice_normals[((order_normals[i]-1)*4)+1];
             normals[i*4+2] = not_nice_normals[((order_normals[i]-1)*4)+2];
             normals[i*4+3] = not_nice_normals[((order_normals[i]-1)*4)+3];
        }

        for( int i=0; i<order_colors.size(); i++ )
        {
             colors[i*2] = not_nice_colors[((order_colors[i]-1)*2)+0];
             colors[i*2+1] = not_nice_colors[((order_colors[i]-1)*2)+1];
        }
    }
    fclose(file);
}





float * OBJLoader::getVerts()
{
    return verts;
}

float * OBJLoader::getNormals()
{
    return normals;
}

float * OBJLoader::getColors()
{
    return colors;
}
unsigned int OBJLoader::getVertexCount()
{
    return vertexCount;
}
