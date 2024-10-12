/*
Práctica 7: Iluminación 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture Dado10caras;


Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;

Model cuerpo_carro, cofre, llanta_der, llanta_izq; //modelos de carros 

Model lampara;
Model Aku;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//función de calculo de normales por promedio de vértices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}

void CrearDado10caras()
{
	unsigned int dado10_indices[] = {
		//1
		0,1,2,
		//2
		3,4,5,
		//3
		6,7,8,
		//4
		9,10,11,
		//5
		12,13,14,
		//6
		15,16,17,
		//7
		18,19,20,
		//8
		21,22,23,
		//9
		24,25,26,
		//10
		27,28,29,

	};

	GLfloat dado10_vertices[] = {

		// Numero 9
		//x		y		z		S		T			NX		NY		NZ
		0.0f, 1.0f,  0.0f,	    0.22f,  0.46f,		-1.0f,	-1.0f,	1.0f,	    //0
		1.0f, 0.0f,  0.0f,		0.020f,  0.26f,		-1.0f,	-1.0f,	1.0f,	    //1
		0.31f, 0.0f, -0.95f,	0.22f,	 0.04f,		-1.0f,	-1.0f,	1.0f,	    //2

		//0.0f, 1.0f,  0.0f,	    0.22f,  0.46f,		0.0f,	0.0f,	0.0f,	    //0
		//1.0f, 0.0f,  0.0f,		0.020f,  0.26f,		0.0f,	0.0f,	0.0f,	    //1
		//0.31f, 0.0f, -0.95f,	0.22f,	 0.04f,		0.0f,	0.0f,	0.0f,	    //2

		//Numero 1
		//x		y		z		S		T			NX		NY		NZ
		0.31f, 0.0f, -0.95f, 	0.020f,  0.720f,	1.0f,	-1.0f,	1.0f,	    //3
		-0.81f, 0.0f, -0.59f,	0.020f,  0.29f,		1.0f,	-1.0f,	1.0f,	    //4
		0.0f, 1.0f, 0.0f,       0.22f,  0.492f,		1.0f,	-1.0f,	1.0f,	    //5

		//Numero 7 
		//x		y		z		S		T			NX		NY		NZ
		0.0f, 1.0f, 0.0f,   	0.24f,  0.527f,		1.0f,	-1.0f,	0.0f,	    //6
		-0.81f, 0.0f, -0.59f,	0.24f,  0.972f,		1.0f,	-1.0f,	0.0f,	    //7 
		-0.809f, 0.0f, 0.59f,  	0.011f,	0.748f,	    1.0f,	-1.0f,	0.0f,	    //8

		//Numero 5
		//x		y		z		S		T			NX		NY		NZ
		-0.809f, 0.0f, 0.59f, 	0.476f,  0.751f,	1.0f,	-1.0f,	-1.0f,	    //9
		0.309f, 0.0f, 0.95f,	0.255f,	0.97f,		1.0f,	-1.0f,	-1.0f,	    //10
		0.0f, 1.0f, 0.0f, 	    0.257f,  0.527f,	1.0f,	-1.0f,	-1.0f,	    //11

		//Numero 3
		//x		y		z		S		T			NX		NY		NZ
		0.0f, 1.0f, 0.0f,    	0.257f,  0.496f,	-1.0f,	-1.0f,	-1.0f,	    //12
		0.309f, 0.0f, 0.95f, 	0.488f,	 0.277f,	-1.0f,	-1.0f,	-1.0f,	    //13
		1.0f, 0.0f,0.0f,  	    0.488f,  0.722f,	-1.0f,	-1.0f,	-1.0f,	    //14

		// Numero 4
		//x		y		z		S		T			NX		NY		NZ
		1.0f,  0.0f,   0.0f,	0.51f, 0.277f,		-1.0f,	1.0f,	1.0f,	    //15
		0.0f, -1.0f,   0.0f,	0.738f, 0.503f,		-1.0f,	1.0f,	1.0f,	    //16
		0.31f,  0.0f, -0.95f,	0.51f, 0.722f,		-1.0f,	1.0f,	1.0f,	    //17

		//Numero 6
		//x		y		z		S		T			NX		NY		NZ
		0.31f, 0.0f, -0.95f, 	0.517f,  0.746f,	1.0f,	1.0f,	1.0f,	    //18
		0.0f, -1.0f, 0.0f,  	0.742f,	0.521f,		1.0f,	1.0f,	1.0f,	    //19
		-0.81f, 0.0f, -0.59f,  	0.738f,  0.982f,	1.0f,	1.0f,	1.0f,	    //20

		//Numero 10 
		//x		y		z		S		T			NX		NY		NZ
		-0.81f, 0.0f, -0.59f,  	0.757f,  0.982f,	1.0f,	1.0f,	0.0f,	    //21
		0.0f, -1.0f, 0.0f,  	0.757f,	0.517f,		1.0f,	1.0f,	0.0f,	    //22
		-0.809f, 0.0f, 0.59f,   0.976f,  0.748f,	1.0f,	1.0f,	0.0f,	    //23

		//Numero 2
		//x		y		z		S		T			NX		NY		NZ
		-0.809f, 0.0f, 0.59f, 	0.984f,  0.722f,	1.0f,	1.0f,	-1.0f,	    //24
		0.309f, 0.0f, 0.95f,	0.984f,	0.277f,		1.0f,	1.0f,	-1.0f,	    //25
		0.0f, -1.0f, 0.0f,	    0.767f,  0.496f,	1.0f,	-1.0f,	-1.0f,	    //25

		//Numero 8
		//x		y		z		S		T			NX		NY		NZ
		0.0f, -1.0f, 0.0f,     	0.753f,  0.478f,	-1.0f,	1.0f,	-1.0f,	    //27
		0.309f, 0.0f, 0.95f,	0.976f,	0.248f,		-1.0f,	1.0f,	-1.0f,	    //28
		1.0f, 0.0f,0.0f,  	    0.751f,  0.023f,	-1.0f,	1.0f,	-1.0f,	    //29

	};

	Mesh* dado10 = new Mesh();
	dado10->CreateMesh(dado10_vertices, dado10_indices, 240, 30);
	meshList.push_back(dado10);
};

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearDado10caras();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	Dado10caras = Texture("Textures/dado10_caras.png");
	Dado10caras.LoadTextureA();


	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	cuerpo_carro = Model();
	cuerpo_carro.LoadModel("Models/basecarpop2.obj");
	cofre = Model();
	cofre.LoadModel("Models/cofre2.obj");
	llanta_der = Model();
	llanta_der.LoadModel("Models/llantaop2.obj");
	llanta_izq = Model();
	llanta_izq.LoadModel("Models/llantaizq.obj");

	lampara = Model();
	lampara.LoadModel("Models/Floor_Lamp_02.obj");
	
	Aku= Model();
	Aku.LoadModel("Models/aku_aku.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 1.0f, 1.0f, //color
		1.5f, 5.0f, 
		0.0f, 11.4f, -25.0f, //direccion 
		0.5f, 0.2f, 0.1f); // con lin exp
	pointLightCount++;

	//Luz puntual modelo Aku
	pointLights[1] = PointLight(1.0f, 0.0f, 1.0f, //color
		1.5f, 5.0f,
		0.0f, 2.0f, -30.0f, //direccion 
		0.5f, 0.2f, 0.1f); // con lin exp
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz COFRE
	spotLights[1] = SpotLight(1.0f, 0.0f, 0.0f,
		5.0f, 30.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.5f, 0.3f, 0.2f,
		30.0f);
	spotLightCount++;

	//Luz auto
	spotLights[2] = SpotLight(0.0f, 0.0f, 1.0f, // color
		2.0f, 15.0f,			
		10.0f, 0.0f, 0.0f,	//Posición inicial
		-1.0f,0.0f, 0.0f,	//Dirección en la que apunta
		0.8f, 0.01f, 0.01f,	
		15.0f);				//apertura
	spotLightCount++;

	////Luz helicoptero
	//spotLights[3] = SpotLight(1.0f, 1.0f, 0.0f, // color
	//	1.0f, 1.0f,
	//	0.0f, 0.0f, 0.0f,	//Posición inicial
	//	0.0f, -1.0f, 0.0f,	//Dirección en la que apunta
	//	0.0f, 0.0f, 0.1f,	// con lin exp
	//	15.0f);				//apertura
	//spotLightCount++;

	//Luz auto

	spotLights[3] = SpotLight(1.0f, 0.0f, 1.0f, // color
		0.8f, 15.0f,
		0.0f, 0.0f, 0.0f,	//Posición inicial
		-1.0f, 0.0f, 0.0f,	//Dirección en la que apunta
		0.5f, 0.01f, 0.01f,
		15.0f);				//apertura
	spotLightCount++;

	////COFRE LUZ
	//spotLights[4] = SpotLight(0.0f, 0.0f, 1.0f, // color
	//	5.0f, 30.0f,
	//	5.0f, 10.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f,
	//	0.5f, 0.3f, 0.2f,
	//	30.0f);			//apertura
	//spotLightCount++;

	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		/*if (mainWindow.getEnciende() == true)
		{
			shaderList[0].SetPointLights(pointLights, 1);
		}
		else {
			shaderList[0].SetPointLights(pointLights, 0);
		};

		if (mainWindow.getEnciende2() == true)
		{
			PointLight auxlight = pointLights[0];
			pointLights[0] = pointLights[1];
			shaderList[0].SetPointLights(pointLights, 1);
			pointLights[0] = auxlight;
		}
		else {
			PointLight auxlight = pointLights[0];
			pointLights[0] = pointLights[1];
			shaderList[0].SetPointLights(pointLights, 0);
			pointLights[0] = auxlight;
		};*/

		
		
		PointLight auxLights[2]; //Arreglo temporal de luces activas
		int numLights = 0; //Se inicia el contador de las luces activas

		// Control de la lámpara 
		if (mainWindow.getEnciende()==true) {
			// Si la lámpara está encendida, la agregamos al arreglo de luces activas
			auxLights[numLights] = pointLights[0]; //Se pasa al arreglo de luces activas la luz de la lampara
			numLights++;
		}

		// Control de Aku
		if (mainWindow.getEnciende2()==true) {
			// Si la segunda luz está encendida, la agregamos al arreglo de luces activas
			auxLights[numLights] = pointLights[1]; //Se pasa al arreglo de luces activas la luz de Aku
			numLights++;
		}

		shaderList[0].SetPointLights(auxLights, numLights);


		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelauxCOF(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		/*DADO DE 10 CARAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.5f, 20.5f, -2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Dado10caras.UseTexture();
		meshList[4]->RenderMesh();*/

		/*CUERPO CARRO*/
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.9f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 0.0f, 0.0f)); //se mueve el carro
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		spotLights[2].SetPos(glm::vec3(-3.0f + mainWindow.getmuevex(), 2.0f, 1.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpo_carro.RenderModel(); // se muestra el cuerpo del carro
		
		model = modelaux;

		//LUZ COCHE
		
		// Posición del coche
		glm::vec3 posicionCoche = glm::vec3(model[3]);
		glm::vec3 direccionCoche = glm::vec3(model[2]);

		// Desplazando la Luz
		glm::vec3 direccionCocheAdelante = direccionCoche;
		glm::vec3 direccionCocheAtras = -direccionCoche;
		/*glm::vec4 desplazamientoLuz = glm::vec4(-6.0f, -0.1f, 1.8f,1.0f);*/
		

		spotLights[2].SetFlash(posicionCoche, direccionCocheAdelante);
		spotLights[3].SetFlash(posicionCoche, direccionCocheAtras);

		if (mainWindow.getPosicion() == true)
		{
			spotLightCount = 3; //Desactiva la luz trasera al tener nuestro contador en 3 cuando son 4
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else {
			SpotLight tempLight = spotLights[2]; //variable auxiliar para guardar la luz azul
			spotLights[2] = spotLights[3];  // Mueve la luz del índice 3 al 2
			spotLightCount = 3; //Mostrara la luz trasera que ahora esta en el indice de la luz azul
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
			spotLights[2] = tempLight; //Se regresa su valor original de la luz azul mediante la luz auxiliar

		};


		

		
		//Cofre
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.0f, 0.7f, 4.4f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelauxCOF = model;
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cofre.RenderModel(); //Se muestra el cofre

		model = modelauxCOF; //jerarquia para la luz
	
		spotLights[1].SetFlash(glm::vec3(model[3]), glm::vec3(model[2]));







		//llanta trasera lado derecho 
		model = modelaux;
		model = glm::translate(model, glm::vec3(-4.1f, -1.6f, -4.6f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_der.RenderModel(); // se muestra llanta vista derecha

		//llanta trasera lado izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.0f, -1.6f, -4.6f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_izq.RenderModel(); // se muestra llanta vista izquierda

		//llanta delantera lado derecho
		model = modelaux;
		model = glm::translate(model, glm::vec3(-4.1f, -1.6f, 5.7f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_der.RenderModel();  // se muestra llanta vista derecha

		//llanta delantera lado izquierdo
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.0f, -1.6f, 5.7f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_izq.RenderModel(); // se muestra llanta vista izquierda

		////Helicoptero
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(20.0f, 5.0f, 6.0f));
		//model = glm::translate(model, glm::vec3(mainWindow.getavanzar(), 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Blackhawk_M.RenderModel();

		//spotLights[3].SetPos(glm::vec3(20.0f + mainWindow.getavanzar(), 5.0f, 6.0f));

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -30.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Aku.RenderModel();


		/*pointLights[1].SetFlash(glm::vec3(model[3]), glm::vec3(model[2]));*/
		////Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(10.0f, 1.0f, -40.0f));
		//model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		////blending: transparencia o traslucidez
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//AgaveTexture.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[3]->RenderMesh();
		//glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
