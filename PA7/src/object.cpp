#include "object.h"

//The default constructor used to have the cube in it.
Object::Object()
{
  angle = 0.0f;
}

//The parameterized constructor uses the path in the parameter to call loadObject()
Object::Object(nlohmann::json json_obj, string object_name)
{
  m_config = json_obj;
  name = object_name;
  filePath = m_config["Planets"][name]["Filepath"];

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
  distanceFromOrigin = m_config["Planets"][name]["DistanceFromOrigin"];
  distanceFromOrigin *= 2;  //planets (if same size) are side by side. 2 is the perfect multiplier
  size = m_config["Planets"][name]["Size"];

  //size *= 100;
std::cout << size << std::endl;

  //distanceFromOrigin;
  //std::cout << distanceFromOrigin << std::endl;
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
  model = glm::translate(glm::mat4(1.0f), glm::vec3 (distanceFromOrigin, 0.0f, 0.0f));
  model = glm::scale(model, glm::vec3(size));
  model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
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
  fstream fileStream;
  fileStream.open(filePath);
  if (fileStream.fail()) {

    std::cout << "File: " << filePath << " could not be opened" << std::endl;
    return;
  }
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
  fstream fileStream;
  fileStream.open(filePath);
  if (fileStream.fail()) {

    std::cout << "File: " << filePath << " could not be opened" << std::endl;
    return;
  }
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
  //std::cout << myScene->mNumMaterials << std::endl;
  for (unsigned int i = 0 ; i < myScene->mNumMaterials ; i++) {
      const aiMaterial* pMaterial = myScene->mMaterials[i];

      m_Textures[i] = NULL;

      if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
          aiString Path;

          if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
              std::string FullPath = Dir + "/" + Path.data;
              m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());
              //std::cout << FullPath.c_str() << std::endl;

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
