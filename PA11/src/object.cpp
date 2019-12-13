#include "object.h"


//The default constructor used to have the cube in it.
/*  Function: Object()
 *  Parameters: None
 *  Return: None
 *  Purpose: Initializes private/protected members
 */
Object::Object()
{
}
/*  Function: Object(nlohmann::json json_obj)
 *  Parameters: nlohmann::json json_obj
 *  Return: None
 *  Purpose: Loads object variables, models, and textures
 */
//The parameterized constructor uses the path in the parameter to call loadObject()
Object::Object(nlohmann::json json_obj, string name)
{
  m_config = json_obj;
  filePath = json_obj[name]["Path"];

  loadObject();//objTriMesh);
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
}

/*
 *  Function: ~Object()
 *  Parameters: None
 *  Return: None
 *  Purpose: rclears arrays and vectors used by the object
 */
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

/*
 *  Function: Update(unsigned int dt, int keyboardButton)
 *  Parameters: unsigned int dt, int keyboardButton
 *  Return: void
 *  Purpose: rotates, scales, and translates the planet to simulate rotation and orbit about the sun
 */
void Object::Update(unsigned int dt, int keyboardButton)
{
  btTransform trans;
  btScalar m[16];
  world->dynamicsWorld->stepSimulation(1 / 120.f, 10);
  rigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  model = glm::make_mat4(m);
}

/*
 *  Function: GetModel()
 *  Parameters: None
 *  Return: glm::mat4
 *  Purpose: Gets the 4x4 matrix representation of the model
 */
glm::mat4 Object::GetModel()
{
  return model;
}

/*
 *  Function: Render()
 *  Parameters: None
 *  Return: void
 *  Purpose: passes the textures, colors, and position of each vertex to the shaders.
 */
void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);

	for(int i = 0; i < meshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, meshes[i].VB);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture));
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,normal));

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
  glDisableVertexAttribArray(3);
}


/*
 *  Function: loadObject()
 *  Parameters: None
 *  Return: void
 *  Purpose: loads the vertices and faces into their respective vertices and indices vectors
 */
//
//Each scene has a mesh, each mesh has a face, each face has aiVector3D of mVertices
//Goal: load vertices and indices vertex.
//PA5: Uses the assimp library
void Object::loadObject()//btTriangleMesh*& t)
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

      /*btVector3 triArray[3];
      aiVector3D position = tmpvertices;
      triArray[j]*/
      glm::vec3 tmpnorm = glm::vec3(myScene->mMeshes[i]->mNormals[j].x, myScene->mMeshes[i]->mNormals[j].y, myScene->mMeshes[i]->mNormals[j].z);
      glm::vec2 tmptexture = glm::vec2(0);

      if(myScene->mMeshes[i]->HasTextureCoords(0))
      {
        tmptexture = glm::vec2(float(myScene->mMeshes[i]->mTextureCoords[0][j].x), float(myScene->mMeshes[i]->mTextureCoords[0][j].y));
      }
      meshes[i].Vertices.push_back(
        Vertex(
          tmpvertices,
          tmptexture,
          tmpvertices,
          tmpnorm
        )
      );
			vertexes.push_back(tmpvertices);
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

    if(filePath == "../blender_object/Lane2.obj" )
    {
      objTriMesh = new btTriangleMesh();
      btVector3 triArray[3];
      for(int j = 0; j < myScene->mMeshes[i]->mNumFaces; j++)
      {
        //loads indices
        for(int k = 0; k < myScene->mMeshes[i]->mFaces[j].mNumIndices; k++)
        {
    			aiVector3D position = myScene->mMeshes[i]->mVertices[ myScene->mMeshes[i]->mFaces[j].mIndices[k] ];
          triArray[k] = btVector3(position.x, position.y, position.z);
        }
        objTriMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
      }
      collisionShape = new btBvhTriangleMeshShape(objTriMesh, true);
    }
		/*if(filePath == "../blender_object/SPin.obj" )
    {

			collisionShape = new btConvexHullShape(0,0, sizeof(btVector3));
			for(int i=0; i < sizeof(vertexes);i ++)
			{
				collisionShape->btConvexHullShape->addPoint(vertexes[i]);
			}
		}*/
  }
}

/*
 *  Function: loadTextures()
 *  Parameters: None
 *  Return: void
 *  Purpose: loads the textures from the aiScene and populates a texture array with texture objects.
 */
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
              if (!m_Textures[i]->Load()) {
                  printf("Error loading texture '%s'\n", FullPath.c_str());
                  delete m_Textures[i];
                  m_Textures[i] = NULL;
              }
          }
      }
  }
}
