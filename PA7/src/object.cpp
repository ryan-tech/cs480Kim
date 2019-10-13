#include "object.h"

//The default constructor used to have the cube in it.
Object::Object()
{
  angle = 0.0f;
  planet_translation_angle = 0.0f;
  planet_rotation_angle = 0.0f;
  moon_translation_angle = 0.0f;
  moon_rotation_angle = 0.0f;
  planet_clockwise_translation = true;
  planet_clockwise_rotation = true;
  moon_clockwise_translation = true;
  moon_clockwise_rotation = true;
}

//The parameterized constructor uses the path in the parameter to call loadObject()
Object::Object(string path)
{
  filePath = path;
  loadObject();
  loadTextures();
	for(int i = 0; i < meshes.size(); i++)
	{
		glGenBuffers(1, &meshes[i].VB);
		glBindBuffer(GL_ARRAY_BUFFER, meshes[i].VB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * meshes[i].Vertices.size(), &meshes[i].Vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &meshes[i].IB);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].IB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * meshes[i].Indices.size(), &meshes[i].Indices[0], GL_STATIC_DRAW);
	}
  angle = 0.0f;
  planet_translation_angle = 0.0f;
  planet_rotation_angle = 0.0f;
  moon_translation_angle = 0.0f;
  moon_rotation_angle = 0.0f;
  planet_clockwise_translation = true;
  planet_clockwise_rotation = true;
  moon_clockwise_translation = true;
  moon_clockwise_rotation = true;
}

Object::~Object()
{
	for(int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Vertices.clear();
		meshes[i].Indices.clear();
	}
  for (unsigned int i = 0 ; i < m_Textures.size() ; i++) {
      m_Textures[i] = NULL;
  }
}
void Object::Update(unsigned int dt, int keyboardButton)
{
  angle += dt * M_PI/10000;
  model = glm::translate(glm::mat4(1.0f), glm::vec3 (0.0f, 0.0f, 0.0f));
  model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

//A custom update function used by the planet -- PA6 deleted bc its in update moon. will make this into one update function in the next project (PA7)
void Object::Update_planet(unsigned int dt, int keyboardButton)
{
}


//A custom update function used by the moon
void Object::Update_moon(unsigned int dt, int keyboardButton)
{
  moon_translation_angle += dt * M_PI/800;
  moon_rotation_angle += dt * M_PI/800;
  //--------Below is same as update_planet----------//
  planet_rotation_angle += dt * M_PI/1000;
  planet_translation_angle += dt * M_PI/1000;
  //translation
  switch(keyboardButton)
  {
    case SDLK_LEFT:
      planet_clockwise_translation = true;
      break;
    case SDLK_RIGHT:
      planet_clockwise_translation = false;
      break;
    case SDLK_UP:
      planet_clockwise_rotation = true;
      break;
    case SDLK_DOWN:
      planet_clockwise_rotation = false;
      break;
    case SDLK_a:
      moon_clockwise_translation = true;
      break;
    case SDLK_s:
      moon_clockwise_translation = false;
      break;
    case SDLK_d:
      moon_clockwise_rotation = true;
      break;
    case SDLK_f:
      moon_clockwise_rotation = false;
      break;
  }

  if(planet_clockwise_translation)
  {
    planet_translation_angle += 0;
  }
  else
  {
    planet_translation_angle -= dt * M_PI/500;
  }

  if(planet_clockwise_rotation)
  {
    planet_rotation_angle += 0;
  }
  else
  {
    planet_rotation_angle -= dt * M_PI/500;
  }

  //translate first
  model = glm::translate(glm::mat4(1.0f), glm::vec3(cos(planet_translation_angle)*3, 0, sin(planet_translation_angle)*3));
  //rotate second
  model = glm::rotate(model, (planet_rotation_angle), glm::vec3(0.0, 1.0, 0.0));

  //--------Above is same as update_planet----------//

  if(moon_clockwise_translation)
  {
    moon_translation_angle += 0;
  }
  else
  {
    moon_translation_angle -= dt * M_PI/400;
  }

  if(moon_clockwise_rotation)
  {
    moon_rotation_angle += 0;
  }
  else
  {
    moon_rotation_angle -= dt * M_PI/400;
  }

  model = glm::translate(glm::mat4(1.0f), glm::vec3(cos(moon_translation_angle)*3+cos(planet_translation_angle)*3, 0, sin(moon_translation_angle)*3+sin(planet_translation_angle)*3));
  model = glm::rotate(model, (moon_rotation_angle), glm::vec3(0.0, 1.0, 0.0));

}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

	for(int i = 0; i < meshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, meshes[i].VB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].IB);

    const unsigned int MaterialIndex = meshes[i].MaterialIndex;

    if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
        m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
    }

		glDrawElements(GL_TRIANGLES, meshes[i].Indices.size(), GL_UNSIGNED_INT, 0);


	}
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}

//loads the vertices and faces into their respective vertices and indices vectors.
//Each scene has a mesh, each mesh has a face, each face has aiVector3D of mVertices
//Goal: load vertices and indices vertex.
//PA5: Uses the assimp library
void Object::loadObject()
{
  Assimp::Importer importer;
  //Define aiScene pointer
  const aiScene *myScene = importer.ReadFile(filePath, aiProcess_Triangulate);

  //
  //  Loading the meshes from the scene
  //
	for(int i = 0; i < myScene->mNumMeshes; i++)
  {
		meshes.push_back(Mesh());
	}


	//for each mesh in the scene
  for(int i = 0; i < myScene->mNumMeshes; i++)
  {
    meshes[i].MaterialIndex = myScene->mMeshes[i]->mMaterialIndex;
		//for each vertex in the mesh
    for(int j = 0; j < myScene->mMeshes[i]->mNumVertices; j++)
    {
      glm::vec3 tmpvertices = glm::vec3(myScene->mMeshes[i]->mVertices[j].x,myScene->mMeshes[i]->mVertices[j].y,myScene->mMeshes[i]->mVertices[j].z);
      glm::vec2 tmptexture = glm::vec2(0);
      if(myScene->mMeshes[i]->HasTextureCoords(0))
      {
        tmptexture = glm::vec2(float(myScene->mMeshes[i]->mTextureCoords[0][j].x), float(myScene->mMeshes[i]->mTextureCoords[0][j].y));
      }
      meshes[i].Vertices.push_back(
        Vertex(
          tmpvertices,
          tmptexture,
          tmpvertices
        )
      );
    }
    //for each face in the mesh
    for(int j = 0; j < myScene->mMeshes[i]->mNumFaces; j++)
    {
      //loads indices
      for(int k = 0; k < myScene->mMeshes[i]->mFaces[j].mNumIndices; k++)
      {
				meshes[i].Indices.push_back(myScene->mMeshes[i]->mFaces[j].mIndices[k]);
      }
    }
  }
}



void Object::loadTextures()
{
  Assimp::Importer importer;
  //Define aiScene pointer
  const aiScene *myScene = importer.ReadFile(filePath, aiProcess_Triangulate);
  m_Textures.resize(myScene->mNumMaterials);
  //
  //  loading the textures from the scene
  //
  std::string::size_type SlashIndex = filePath.find_last_of("/");
  std::string Dir;

  if (SlashIndex == std::string::npos) {
      Dir = ".";
  }
  else if (SlashIndex == 0) {
      Dir = "/";
  }
  else {
      Dir = filePath.substr(0, SlashIndex);
  }

  // Initialize the materials
  std::cout << myScene->mNumMaterials << std::endl;
  for (unsigned int i = 0 ; i < myScene->mNumMaterials ; i++) {
      const aiMaterial* pMaterial = myScene->mMaterials[i];

      m_Textures[i] = NULL;

      if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
          aiString Path;

          if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
              std::string FullPath = Dir + "/" + Path.data;
              m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());
              std::cout << FullPath.c_str() << std::endl;

              if (!m_Textures[i]->Load()) {
                  printf("Error loading texture '%s'\n", FullPath.c_str());
                  delete m_Textures[i];
                  m_Textures[i] = NULL;
              }
              else {
                  printf("Loaded texture '%s'\n", FullPath.c_str());
              }

          }
      }
  }
}
