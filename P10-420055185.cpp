
// PROYECTO DE LABORATORIO
// Miranda González José Francisco. Grupo teoría: 04. Grupo laboratorio: 03. 318222327
// Monter González Luis Enrique. Grupo teoría: 06. Grupo laboratorio: 03. 318276605
// Vázquez Gómez Carlos Iván. Grupo teoría: 04. Grupo laboratorio: 03. 420055185


//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <iomanip>
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

// PARA ELEGIR LOS GRADOS DE MANERA RANDOM EN LOS DADOS
#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

const float toRadians = 3.14159265f / 180.0f;

									// ##################################### VARIABLES PARA ANIMACION ##################################### \\
									// 
//variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

// CONTROL DE LUZ DIRECCIONAL
float totalDia = 30.0f;
float atardecer = 30.0f;
float totalnoche = 30.0f;
float ciclototal = 90.0;
float pi = 3.14159265f;
float angle;
float intensidad = 0.0f;
float FaseDia = 0.0f;
float oscuridad = 0.0f;
float adjustedIntensity = 0.0f;
bool esDia = true;
bool esNoche = false;

// VARIABLES PARA ANIMACION DEL DADO DE 8 CARAS
float subeBajaDado8 = 35.0f;
float subeBajaDadoOffset8 = 0.3f;
float rotaDadox8 = 0.0f;
float rotaDadoxOffset8 = 1.0f;
float rotaDadoy8 = 0.0f;
float rotaDadoyOffset8 = 1.0f;
float rotaDadoz8 = 0.0f;
float rotaDadozOffset8 = 1.0f;

// VARIABLES PARA ANIMACION DEL DADO DE 4 CARAS
float subeBajaDado4 = 35.0f;
float subeBajaDadoOffset4 = 0.3f;
float rotaDadox4 = 0.0f;
float rotaDadoxOffset4 = 1.0f;
float rotaDadoy4 = 0.0f;
float rotaDadoyOffset4 = 1.0f;

// RRESULTADO DEL DADO
int resultado4Caras = 0;
int resultado8Caras = 0;
int resultado = 0;

// VARIABLES PARA ANIAMCION DE RECORRIDO
float mueveAvatar01 = 0.0f;
float mueveAvatar01Offset = 0.1f;
float mueveAvatar01Base = 0.0f;
int resultadoAnterior01 = 0;

float mueveAvatar02 = 0.0f;
float mueveAvatar02Offset = 0.1f;
float mueveAvatar02Base = 0.0f;
int resultadoAnterior02 = 0;

float mueveAvatar03 = 0.0f;
float mueveAvatar03Offset = 0.1f;
float mueveAvatar03Base = 0.0f;
int resultadoAnterior03 = 0;

float mueveAvatar04 = 0.0f;
float mueveAvatar04Offset = 0.1f;
float mueveAvatar04Base = 0.0f;
int resultadoAnterior04 = 0;

float diferencia = 0.0f;
bool hayDiferencia = true;
int conta = 0;

float diferencia01 = 0.0f;
bool hayDiferencia01 = true;
int conta01 = 0;

float diferencia02 = 0.0f;
bool hayDiferencia02 = true;
int conta02 = 0; 

// VARIABLES PARA LA ANIMACION DE LA VUELTA 
float rotaAvatar01 = 0.0f;
float rotaAvatar01Offset = 1.0;
float rotaAvatar02 = 0.0f;
float rotaAvatar02Offset = 1.0;
float rotaAvatar03 = 0.0f;
float rotaAvatar03Offset = 1.0;
float rotaAvatar04 = 0.0f;
float rotaAvatar04Offset = 1.0;

// VARIABLES PARA ANIMACIÓN DE LOS BRAZOS Y PIERNAS
float rotaBrazoD = 0.0f;
float rotaBrazoDOffset = 0.8f;
float rotaBrazoI = 0.0f;
float rotaBrazoIOffset = 0.8f;
float rotaPiernaD = 0.0f;
float rotaPiernaDOffset = 0.8;
float rotaPiernaI = 0.0f;
float rotaPiernaIOffset = 0.8;
bool subebaja = true;

// ANIMACIONES DE CASILLAS

// CASILLA 02
float raidenSubeBaja = -8.0f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float raidenSubeBajaOffset = 0.1f;
float raidenRota = 0.0f;
float raidenRotaOffset = 2.0;
int raidenCont01 = 0;
int raidenCont02 = 0;
bool raiden = true;
float raidenTiempo = 0.0f;

// CASILLA 03
float scorpionSubeBaja = -9.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float scorpionSubeBajaOffset = 0.1f;
float scorpionRota = 0.0f;
float scorpionRotaOffset = 2.0;
int scorpionCont01 = 0;
int scorpionCont02 = 0;
bool scorpion = true;
float scorpionTiempo = 0.0f;

// CASILLA 04
float shaoSubeBaja = -9.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float shaoSubeBajaOffset = 0.1f;
float shaoRota = 0.0f;
float shaoRotaOffset = 2.0;
int shaoCont01 = 0;
int shaoCont02 = 0;
bool shao = true;
float shaoTiempo = 0.0f;

// CASILLA 05
float hellSubeBaja = -13.0f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float hellSubeBajaOffset = 0.1f;
float hellRota = 0.0f;
float hellRotaOffset = 2.0;
int hellCont01 = 0;
int hellCont02 = 0;
bool hell = true;
float hellTiempo = 0.0f;

// CASILLA 06
float viewerSubeBaja = -11.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float viewerSubeBajaOffset = 0.1f;
float viewerRota = 0.0f;
float viewerRotaOffset = 2.0;
int viewerCont01 = 0;
int viewerCont02 = 0;
bool viewer = true;
float viewerTiempo = 0.0f;

// CASILLA 07
float tree_stumpSubeBaja = -9.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float tree_stumpSubeBajaOffset = 0.1f;
float tree_stumpRota = 0.0f;
float tree_stumpRotaOffset = 2.0;
int tree_stumpCont01 = 0;
int tree_stumpCont02 = 0;
bool tree_stump = true;
float tree_stumpTiempo = 0.0f;

// CASILLA 08
float pine_treeSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float pine_treeSubeBajaOffset = 0.1f;
float pine_treeRota = 0.0f;
float pine_treeRotaOffset = 2.0;
int pine_treeCont01 = 0;
int pine_treeCont02 = 0;
bool pine_tree = true;
float pine_treeTiempo = 0.0f;

// CASILLA 09
float fire_dragonSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float fire_dragonSubeBajaOffset = 0.1f;
float fire_dragonRota = 0.0f;
float fire_dragonRotaOffset = 2.0;
int fire_dragonCont01 = 0;
int fire_dragonCont02 = 0;
bool fire_dragon = true;
float fire_dragonTiempo = 0.0f;

// CASILLA 10
float scorpion2SubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  scorpion2SubeBajaOffset = 0.1f;
float scorpion2Rota = 0.0f;
float  scorpion2RotaOffset = 2.0;
int  scorpion2Cont01 = 0;
int  scorpion2Cont02 = 0;
bool  scorpion2 = true;
float  scorpion2Tiempo = 0.0f;

// CASILLA 11
float wolfSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  wolfSubeBajaOffset = 0.1f;
float wolfRota = 0.0f;
float  wolfRotaOffset = 2.0;
int  wolfCont01 = 0;
int  wolfCont02 = 0;
bool  wolf = true;
float  wolfTiempo = 0.0f;

// CASILLA 12
float BarakaSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  BarakaSubeBajaOffset = 0.1f;
float BarakaRota = 0.0f;
float  BarakaRotaOffset = 2.0;
int  BarakaCont01 = 0;
int  BarakaCont02 = 0;
bool  Baraka = true;
float  BarakaTiempo = 0.0f;

// CASILLA 13
float boSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  boSubeBajaOffset = 0.1f;
float boRota = 0.0f;
float  boRotaOffset = 2.0;
int  boCont01 = 0;
int  boCont02 = 0;
bool  bo = true;
float  boTiempo = 0.0f;

// CASILLA 14
float cassieSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  cassieSubeBajaOffset = 0.1f;
float cassieRota = 0.0f;
float  cassieRotaOffset = 2.0;
int  cassieCont01 = 0;
int  cassieCont02 = 0;
bool  cassie = true;
float  cassieTiempo = 0.0f;

// CASILLA 15
float skullSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  skullSubeBajaOffset = 0.1f;
float skullRota = 0.0f;
float  skullRotaOffset = 2.0;
int  skullCont01 = 0;
int  skullCont02 = 0;
bool  skull = true;
float  skullTiempo = 0.0f;

// CASILLA 16
float rockySubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  rockySubeBajaOffset = 0.1f;
float rockyRota = 0.0f;
float  rockyRotaOffset = 2.0;
int  rockyCont01 = 0;
int  rockyCont02 = 0;
bool  rocky = true;
float  rockyTiempo = 0.0f;

// CASILLA 17
float drneoSubeBaja = -15.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  drneoSubeBajaOffset = 0.1f;
float drneoRota = 0.0f;
float  drneoRotaOffset = 2.0;
int  drneoCont01 = 0;
int  drneoCont02 = 0;
bool  drneo = true;
float  drneoTiempo = 0.0f;

// CASILLA 18
float frogSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  frogSubeBajaOffset = 0.1f;
float frogRota = 0.0f;
float  frogRotaOffset = 2.0;
int  frogCont01 = 0;
int  frogCont02 = 0;
bool  frog = true;
float  frogTiempo = 0.0f;

// CASILLA 19
float polarSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  polarSubeBajaOffset = 0.1f;
float polarRota = 0.0f;
float  polarRotaOffset = 2.0;
int  polarCont01 = 0;
int  polarCont02 = 0;
bool  polar = true;
float  polarTiempo = 0.0f;

// CASILLA 20
float wizardSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  wizardSubeBajaOffset = 0.1f;
float wizardRota = 0.0f;
float  wizardRotaOffset = 2.0;
int  wizardCont01 = 0;
int  wizardCont02 = 0;
bool  wizard = true;
float  wizardTiempo = 0.0f;

// CASILLA 21
float pinstripeSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  pinstripeSubeBajaOffset = 0.1f;
float pinstripeRota = 0.0f;
float  pinstripeRotaOffset = 2.0;
int  pinstripeCont01 = 0;
int  pinstripeCont02 = 0;
bool  pinstripe = true;
float  pinstripeTiempo = 0.0f;

// CASILLA 22
float lionSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  lionSubeBajaOffset = 0.1f;
float lionRota = 0.0f;
float  lionRotaOffset = 2.0;
int  lionCont01 = 0;
int  lionCont02 = 0;
bool  lion = true;
float  lionTiempo = 0.0f;

// CASILLA 23
float babytSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  babytSubeBajaOffset = 0.1f;
float babytRota = 0.0f;
float  babytRotaOffset = 2.0;
int  babytCont01 = 0;
int  babytCont02 = 0;
bool  babyt = true;
float  babytTiempo = 0.0f;

// CASILLA 24
float akuakuSubeBaja = -14.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  akuakuSubeBajaOffset = 0.1f;
float akuakuRota = 0.0f;
float  akuakuRotaOffset = 2.0;
int  akuakuCont01 = 0;
int  akuakuCont02 = 0;
bool  akuaku = true;
float  akuakuTiempo = 0.0f;

// CASILLA 25
float palm_treeSubeBaja = -15.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  palm_treeSubeBajaOffset = 0.1f;
float palm_treeRota = 0.0f;
float  palm_treeRotaOffset = 2.0;
int  palm_treeCont01 = 0;
int  palm_treeCont02 = 0;
bool  palm_tree = true;
float  palm_treeTiempo = 0.0f;

// CASILLA 26
float flowersSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  flowersSubeBajaOffset = 0.1f;
float flowersRota = 0.0f;
float  flowersRotaOffset = 2.0;
int  flowersCont01 = 0;
int  flowersCont02 = 0;
bool  flowers = true;
float  flowersTiempo = 0.0f;

// CASILLA 27
float basicSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  basicSubeBajaOffset = 0.1f;
float basicRota = 0.0f;
float  basicRotaOffset = 2.0;
int  basicCont01 = 0;
int  basicCont02 = 0;
bool  basic = true;
float  basicTiempo = 0.0f;

// CASILLA 28
float brianSubeBaja = -14.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  brianSubeBajaOffset = 0.1f;
float brianRota = 0.0f;
float  brianRotaOffset = 2.0;
int  brianCont01 = 0;
int  brianCont02 = 0;
bool  brian = true;
float  brianTiempo = 0.0f;

// CASILLA 29
float ernieSubeBaja = -13.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  ernieSubeBajaOffset = 0.1f;
float ernieRota = 0.0f;
float  ernieRotaOffset = 2.0;
int  ernieCont01 = 0;
int  ernieCont02 = 0;
bool  ernie = true;
float  ernieTiempo = 0.0f;

// CASILLA 30
float luisaSubeBaja = -13.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  luisaSubeBajaOffset = 0.1f;
float luisaRota = 0.0f;
float  luisaRotaOffset = 2.0;
int  luisaCont01 = 0;
int  luisaCont02 = 0;
bool  luisa = true;
float  luisaTiempo = 0.0f;

// CASILLA 31
float megSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  megSubeBajaOffset = 0.1f;
float megRota = 0.0f;
float  megRotaOffset = 2.0;
int  megCont01 = 0;
int  megCont02 = 0;
bool  meg = true;
float  megTiempo = 0.0f;

// CASILLA 32
float peterSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  peterSubeBajaOffset = 0.1f;
float peterRota = 0.0f;
float  peterRotaOffset = 2.0;
int  peterCont01 = 0;
int  peterCont02 = 0;
bool  peter = true;
float  peterTiempo = 0.0f;

// CASILLA 33
float joeSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  joeSubeBajaOffset = 0.1f;
float joeRota = 0.0f;
float  joeRotaOffset = 2.0;
int  joeCont01 = 0;
int  joeCont02 = 0;
bool  joe = true;
float  joeTiempo = 0.0f;

// CASILLA 34
float chrisSubeBaja = -20.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  chrisSubeBajaOffset = 0.1f;
float chrisRota = 0.0f;
float  chrisRotaOffset = 2.0;
int  chrisCont01 = 0;
int  chrisCont02 = 0;
bool  chris = true;
float  chrisTiempo = 0.0f;

// CASILLA 35
float casaSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  casaSubeBajaOffset = 0.1f;
float casaRota = 0.0f;
float  casaRotaOffset = 2.0;
int  casaCont01 = 0;
int  casaCont02 = 0;
bool  casa = true;
float  casaTiempo = 0.0f;

// CASILLA 36
float treeSubeBaja = -12.9f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  treeSubeBajaOffset = 0.1f;
float treeRota = 0.0f;
float  treeRotaOffset = 2.0;
int  treeCont01 = 0;
int  treeCont02 = 0;
bool  tree = true;
float  treeTiempo = 0.0f;

// CASILLA 37
float navidadSubeBaja = -14.0f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  navidadSubeBajaOffset = 0.1f;
float navidadRota = 0.0f;
float  navidadRotaOffset = 2.0;
int  navidadCont01 = 0;
int  navidadCont02 = 0;
bool  navidad = true;
float  navidadTiempo = 0.0f;

// CASILLA 38
float vinnySubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  vinnySubeBajaOffset = 0.1f;
float vinnyRota = 0.0f;
float  vinnyRotaOffset = 2.0;
int  vinnyCont01 = 0;
int  vinnyCont02 = 0;
bool  vinny = true;
float  vinnyTiempo = 0.0f;

// CASILLA 39
float flowers2SubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  flowers2SubeBajaOffset = 0.1f;
float flowers2Rota = 0.0f;
float  flowers2RotaOffset = 2.0;
int  flowers2Cont01 = 0;
int  flowers2Cont02 = 0;
bool  flowers2 = true;
float  flowers2Tiempo = 0.0f;

// CASILLA 40
float carterSubeBaja = -13.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
float  carterSubeBajaOffset = 0.1f;
float carterRota = 0.0f;
float  carterRotaOffset = 2.0;
int  carterCont01 = 0;
int  carterCont02 = 0;
bool  carter = true;
float  carterTiempo = 0.0f;

// CAMBIO DE DIA Y NOCHE
float dianocheTiempo;

// COCINADO EN LAS CASILLAS
int cocinado01 = 0;
int cocinado02 = 0;
int cocinado03 = 0;
int cocinado04 = 0;
int cocinado05 = 0;
int cocinado06 = 0;
int cocinado07 = 0;
int cocinado08 = 0;
int cocinado09 = 0;
int cocinado10 = 0;
int cocinado11 = 0;
int cocinado12 = 0;
int cocinado13 = 0;
int cocinado14 = 0;
int cocinado15 = 0;
int cocinado16 = 0;
int cocinado17 = 0;
int cocinado18 = 0;
int cocinado19 = 0;
int cocinado20 = 0;
int cocinado21 = 0;
int cocinado22 = 0;
int cocinado23 = 0;
int cocinado24 = 0;
int cocinado25 = 0;
int cocinado26 = 0;
int cocinado27 = 0;
int cocinado28 = 0;
int cocinado29 = 0;
int cocinado30 = 0;
int cocinado31 = 0;
int cocinado32 = 0;
int cocinado33 = 0;
int cocinado34 = 0;
int cocinado35 = 0;
int cocinado36 = 0;
int cocinado37 = 0;
int cocinado38 = 0;
int cocinado39 = 0;

////ANIMACION DEL CARRO COCO
float mueveCarro = 0.0f;              // Posición inicial del carro en el primer tramo
float giraCarro = 90.0f;               // Ángulo inicial de rotación (90 grados)
float mueveCarro2 = 0.0f;              // Posición en el segundo tramo
float mueveCarroOffset = 0.25f;        // Velocidad normal de desplazamiento del carro
float giraCarroTarget = 180.0f;        // Ángulo objetivo para el primer giro
float giraCarroTargetX = 270.0f; // Nueva rotación objetivo para movimiento en X negativo
float giraCarroTargetZ = 90.0f; // Rotación objetivo al mover hacia el eje Z negativo
float giraCarroVelocidad = 0.1f;      // Velocidad de rotación para una curva suave
float curvaCarroOffset = 0.1f;         // Velocidad reducida durante la curva
bool enCurva = false; // Bandera para saber si estamos en la curva
bool enMovimientoXNegativo = false; // Nueva bandera para el movimiento en X negativo
bool enMovimientoZ = false; // Bandera para saber si estamos en movimiento en el eje Z
bool enMovimientoX = false; // Bandera para saber si estamos en movimiento en el eje Z

//VARIABLES PARA ANIMACION MONOPOLY Y PASTO
float toffsetletrerou = 0.0f;
float toffsetletrerov = 0.0f;
float velocidadDesplazamiento = 0.01f;
float toffsetsuelou = 0.0f;
float toffsetsuelov = 0.0f;
bool texturaletrero = false;

// VARIABLES PARA ANIMACIÓN BRAZO DE SUBZERO
float rotaBrazoSubZero = 0.0f;
float rotaBrazoSubzeroOffset = 0.8f;
bool subebajaSubZeroBrazo = true;
float anguloVariaSubzero = 0.0f;

// VARIABLES PARA ANIMACION DE CRASH
float rotaCrash = 0.0f;
float rotaCrashOffset = 3.0;
float anguloVariaCrash = 0.0f;

// VARIABLES PARA TRANSFORMACION
float escala01 = 0.0f;
float escala01Offset = 0.1f;
float escala02 = 0.0f;
float escala02Offset = 0.1f;
float escala03 = 0.0f;
float escala03Offset = 0.1f;
float tiempoTransformacion = 0.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

//CAMARAS
Camera camera;
Camera CamaraAerea;
Camera currentCamara;
bool camaraAereaAc = false;
float posCamX = 2000.0f;
float posCamZ = 2000.0f;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture letrero;
Texture pasto;

									// ##################################### CREACION DE MODELOS ##################################### \\
//MODELO AVE
Model Cuerpo;
Model AlaIzq;
Model AlaDer;
// DADOS MODELOS
Model dado4CarasM;
Model dado8CarasM;

// CASILLAS DE COLOR AZUL (NOCHE)
Model casillaM;
Model casilla01M;
Model casilla02M;
Model casilla03M;
Model casilla04M;
Model casilla05M;
Model casilla06M;
Model casilla07M;
Model casilla08M;
Model casilla09M;
Model casilla10M;
Model casilla11M;
Model casilla12M;
Model casilla13M;
Model casilla14M;
Model casilla15M;
Model casilla16M;
Model casilla17M;
Model casilla18M;
Model casilla19M;
Model casilla20M;
Model casilla21M;
Model casilla22M;
Model casilla23M;
Model casilla24M;
Model casilla25M;
Model casilla26M;
Model casilla27M;
Model casilla28M;
Model casilla29M;
Model casilla30M;
Model casilla31M;
Model casilla32M;
Model casilla33M;
Model casilla34M;
Model casilla35M;
Model casilla36M;
Model casilla37M;
Model casilla38M;
Model casilla39M;
Model casilla40M;

//CASILLA DE COLOR AMARILLO (DIA)
Model casilla01A;
Model casilla02A;
Model casilla03A;
Model casilla04A;
Model casilla05A;
Model casilla06A;
Model casilla07A;
Model casilla08A;
Model casilla09A;
Model casilla10A;
Model casilla11A;
Model casilla12A;
Model casilla13A;
Model casilla14A;
Model casilla15A;
Model casilla16A;
Model casilla17A;
Model casilla18A;
Model casilla19A;
Model casilla20A;
Model casilla21A;
Model casilla22A;
Model casilla23A;
Model casilla24A;
Model casilla25A;
Model casilla26A;
Model casilla27A;
Model casilla28A;
Model casilla29A;
Model casilla30A;
Model casilla31A;
Model casilla32A;
Model casilla33A;
Model casilla34A;
Model casilla35A;
Model casilla36A;
Model casilla37A;
Model casilla38A;
Model casilla39A;
Model casilla40A;

//CASILLAS "ILUMINADA" (COCINADO AL PASAR POR LA CASILLA)
Model casilla01AR;
Model casilla02AR;
Model casilla03AR;
Model casilla04AR;
Model casilla05AR;
Model casilla06AR;
Model casilla07AR;
Model casilla08AR;
Model casilla09AR;
Model casilla10AR;
Model casilla11AR;
Model casilla12AR;
Model casilla13AR;
Model casilla14AR;
Model casilla15AR;
Model casilla16AR;
Model casilla17AR;
Model casilla18AR;
Model casilla19AR;
Model casilla20AR;
Model casilla21AR;
Model casilla22AR;
Model casilla23AR;
Model casilla24AR;
Model casilla25AR;
Model casilla26AR;
Model casilla27AR;
Model casilla28AR;
Model casilla29AR;
Model casilla30AR;
Model casilla31AR;
Model casilla32AR;
Model casilla33AR;
Model casilla34AR;
Model casilla35AR;
Model casilla36AR;
Model casilla37AR;
Model casilla38AR;
Model casilla39AR;
Model casilla40AR;

// MODELOS DE LAS CASILLAS
Model modeloCasilla01M;
Model modeloCasilla02M;
Model modeloCasilla03M;
Model modeloCasilla04M;
Model modeloCasilla05M;
Model modeloCasilla06M;
Model modeloCasilla07M;
Model modeloCasilla08M;
Model modeloCasilla09M;
Model modeloCasilla11M;
Model modeloCasilla12M;
Model modeloCasilla13M;
Model modeloCasilla14M;
Model modeloCasilla15M;
Model modeloCasilla16M;
Model modeloCasilla17M;
Model modeloCasilla18M;
Model modeloCasilla19M;
Model modeloCasilla20M;
Model modeloCasilla21M;
Model modeloCasilla22M;
Model modeloCasilla23M;
Model modeloCasilla24M;
Model modeloCasilla25M;
Model modeloCasilla26M;
Model modeloCasilla27M;
Model ModeloCasilla28;
Model ModeloCasilla29;
Model ModeloCasilla30;
Model ModeloCasilla31;
Model ModeloCasilla32;
Model ModeloCasilla33;
Model ModeloCasilla34;
Model ModeloCasilla35;
Model ModeloCasilla36;
Model ModeloCasilla37;
Model ModeloCasilla38;
Model ModeloCasilla39;
Model ModeloCasilla40;

//MODELOS DE CARRETERA
Model recta;
Model curva;
Model carroCortex;
Model carroCrunch;
Model carroCoco;

Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;

// MODELO DEL AVATAR PARA EL RECORRIDO (SUBZERO)
Model torsoSubZero;
Model cinturaSubZero;
Model brazoDerechoSubZero;
Model brazoIzquieroSubZero;
Model piernaDerechaSubZero;
Model piernaIzquierdaSubZero;

// MODELOS PARA ANIMACION 
// SUB ZERO
Model subZeroAnimacion;
Model scorpionCabeza;
Model scorpionCuerpo;
Model baseSubzero;
// CRASH
Model crashAnimacion;

// MODELOS DEL ENTORNO
Model globo;
Model casaCynthia;
Model arboltablero1;
Model palmeratablero;
Model arbolsinhojas;
Model arboltablero2;
Model flores1;
Model arbusto;
Model carro1;
Model mesa;
Model sombrero;
Model hacha;
Model estrella;
Model bazooka;
Model box1;
Model box2;
Model box3;
Model ermac;
Model goro;
Model cage;
Model kabal;
Model esqueleto;
Model Architect;
Model cleveland;
Model glenn_quagmire;
Model herbert;
Model Chicken_Nitro;
Model MK9_X360_STG_PROP_Statue_Goro;
Model lampara;

// MODELOS PARA LA TRASNFORMACION
Model scorpionOriginal;
Model scorpionTransformacion;
Model fireball;

// MODELOS AUXILIARES
Model esfera;

									// ##################################### SKYBOX ##################################### \\

// SKYBOX DIA 
Skybox skyboxDia;
// SKYBOX NOCHE
Skybox skyboxNoche;

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

//función para teclado de keyframes 
void inputKeyframes(bool* keys);

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
										// ##################################### PASTO ##################################### \\
	
	// PISO (PASTO)
	unsigned int pisoPastoIndices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLfloat pisoPastoVertices[] = {
		// LA TEXTURA SE VERA REPETIDA 10 VECES
		-10.0f, 0.0f, 10.0f,	0.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, -10.0f,	0.0f, 20.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	20.0f, 20.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		20.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	};

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

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		// Posiciones (x, y, z)    // Coords de textura (u, v)    // Normales (x, y, z)
		-1.0f, -1.0f, 0.0f,       0.25f, 0.83f,                 0.0f, 0.0f, 1.0f,     // Esquina inferior izquierda
		 1.0f, -1.0f, 0.0f,       0.83f, 0.83f,                 0.0f, 0.0f, 1.0f,     // Esquina inferior derecha
		 1.0f,  1.0f, 0.0f,       0.83f, 0.35f,                 0.0f, 0.0f, 1.0f,     // Esquina superior derecha
		-1.0f,  1.0f, 0.0f,       0.25f, 0.35f,                 0.0f, 0.0f, 1.0f      // Esquina superior izquierda
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

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj5);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

bool animacion = false;

//NEW// Keyframes
//variables para la animacion del ave
float movAve_x = 0;
float movAve_y = 0;
float movAve_z = 0;
float giroAve = 0;
float giroAla = 0;

#define MAX_FRAMES 100
int i_max_steps = 100;
int i_curr_steps = 0;

typedef struct _frame {
	float movAve_x;
	float movAve_z;
	float movAve_y;
	float movAve_xInc;
	float movAve_zInc;
	float movAve_yInc;
	float giroAve;
	float giroAveInc;
	float giroAla;
	float giroAlaInc;
} FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;
bool play = false;
int playIndex = 0;

void saveFrame(void) { // tecla L
	printf("Guardar nuevo keyframe en el índice %d\n", FrameIndex);

	printf("movAve_x es: %f\n", movAve_x);
	printf("movAve_y es: %f\n", movAve_y);
	printf("movAve_z es: %f\n", movAve_z);
	printf("giroAve es: %f\n", giroAve);
	printf("giroAla es: %f\n", giroAla);
	KeyFrame[FrameIndex].movAve_x = movAve_x;
	KeyFrame[FrameIndex].movAve_y = movAve_y;
	KeyFrame[FrameIndex].movAve_z = movAve_z;
	KeyFrame[FrameIndex].giroAve = giroAve;
	KeyFrame[FrameIndex].giroAla = giroAla;

	// Guardar en archivo con formato específico
	std::ofstream file("keyframes.txt", std::ios::app);
	if (file.is_open()) {
		file << std::fixed << std::setprecision(1); // Asegurarte de usar un decimal
		file << "KeyFrame[" << FrameIndex << "].movAve_x = " << KeyFrame[FrameIndex].movAve_x << "f;\n";
		file << "KeyFrame[" << FrameIndex << "].movAve_y = " << KeyFrame[FrameIndex].movAve_y << "f;\n";
		file << "KeyFrame[" << FrameIndex << "].movAve_z = " << KeyFrame[FrameIndex].movAve_z << "f;\n";
		file << "KeyFrame[" << FrameIndex << "].giroAve = " << KeyFrame[FrameIndex].giroAve << "f;\n";
		file << "KeyFrame[" << FrameIndex << "].giroAla = " << KeyFrame[FrameIndex].giroAla << "f;\n\n";
		file.close();
		printf("Keyframe guardado en keyframes.txt con exito\n");
	}
	else {
		printf("No se pudo abrir el archivo para guardar los keyframes.\n");
	}

	FrameIndex++;
}


void resetElements(void) { // tecla 0
	movAve_x = KeyFrame[0].movAve_x;
	movAve_x = KeyFrame[0].movAve_y;
	movAve_z = KeyFrame[0].movAve_z;
	giroAve = KeyFrame[0].giroAve;
	giroAla = KeyFrame[0].giroAla;
}

void interpolation(void) {
	KeyFrame[playIndex].movAve_xInc = (KeyFrame[playIndex + 1].movAve_x - KeyFrame[playIndex].movAve_x) / i_max_steps;
	KeyFrame[playIndex].movAve_yInc = (KeyFrame[playIndex + 1].movAve_y - KeyFrame[playIndex].movAve_y) / i_max_steps;
	KeyFrame[playIndex].movAve_zInc = (KeyFrame[playIndex + 1].movAve_z - KeyFrame[playIndex].movAve_z) / i_max_steps;
	KeyFrame[playIndex].giroAveInc = (KeyFrame[playIndex + 1].giroAve - KeyFrame[playIndex].giroAve) / i_max_steps;
	KeyFrame[playIndex].giroAlaInc = (KeyFrame[playIndex + 1].giroAla - KeyFrame[playIndex].giroAla) / i_max_steps;

}

void animate(void) {
	if (play) {
		if (i_curr_steps >= i_max_steps) {
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2) {
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				play = false;
			}
			else {
				i_curr_steps = 0;
				interpolation();
			}
		}
		else {
			movAve_x += KeyFrame[playIndex].movAve_xInc;
			movAve_y += KeyFrame[playIndex].movAve_yInc;
			movAve_z += KeyFrame[playIndex].movAve_zInc;
			giroAve += KeyFrame[playIndex].giroAveInc;
			giroAla += KeyFrame[playIndex].giroAlaInc;
			i_curr_steps++;
		}
	}
}

///////////////* FIN KEYFRAMES*////////////////////////////

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);
	//Variable auxiliar para realizar el cambio de camara
	Camera* currentCamera = &camera;
	//Camara que solo se mueve de forma ortogonal
	CamaraAerea = Camera(glm::vec3(posCamX, 150.0f, posCamZ), glm::vec3(0.0f, 1.0f, 0.0f), 75.0f, -90.0f, 0.3f, 0.5f);

	// camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/suelo2.png");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	letrero = Texture("Textures/letrero2.png");
	letrero.LoadTextureA();
	pasto = Texture("Textures/pasto1.png");
	pasto.LoadTextureA();

										// ##################################### CARGA DE MODELOS ##################################### \\
	

	//AVE PRACTICA10
	Cuerpo = Model();
	Cuerpo.LoadModel("Models/Cuerpo.obj");
	AlaDer = Model();
	AlaDer.LoadModel("Models/AlaDer.obj");
	AlaIzq = Model();
	AlaIzq.LoadModel("Models/AlaIzq.obj");

	// DADOS 
	dado4CarasM = Model();
	dado4CarasM.LoadModel("Models/dado4Caras.obj");
	dado8CarasM = Model();
	dado8CarasM.LoadModel("Models/dado8Caras.obj");

	// CASILLAS AZULES 
	casillaM = Model();
	casillaM.LoadModel("Models/casilla.obj");
	casilla01M = Model();
	casilla01M.LoadModel("Models/casilla01.obj");
	casilla02M = Model();
	casilla02M.LoadModel("Models/casilla02.obj");
	casilla03M = Model();
	casilla03M.LoadModel("Models/casilla03.obj");
	casilla04M = Model();
	casilla04M.LoadModel("Models/casilla04.obj");
	casilla05M = Model();
	casilla05M.LoadModel("Models/casilla05.obj");
	casilla06M = Model();
	casilla06M.LoadModel("Models/casilla06.obj");
	casilla07M = Model();
	casilla07M.LoadModel("Models/casilla07.obj");
	casilla08M = Model();
	casilla08M.LoadModel("Models/casilla08.obj");
	casilla09M = Model();
	casilla09M.LoadModel("Models/casilla09.obj");
	casilla10M = Model();
	casilla10M.LoadModel("Models/casilla10.obj");
	casilla11M = Model();
	casilla11M.LoadModel("Models/casilla11.obj");
	casilla12M = Model();
	casilla12M.LoadModel("Models/casilla12.obj");
	casilla13M = Model();
	casilla13M.LoadModel("Models/casilla13.obj");
	casilla14M = Model();
	casilla14M.LoadModel("Models/casilla14.obj");
	casilla15M = Model();
	casilla15M.LoadModel("Models/casilla15.obj");
	casilla16M = Model();
	casilla16M.LoadModel("Models/casilla16.obj");
	casilla17M = Model();
	casilla17M.LoadModel("Models/casilla17.obj");
	casilla18M = Model();
	casilla18M.LoadModel("Models/casilla18.obj");
	casilla19M = Model();
	casilla19M.LoadModel("Models/casilla19.obj");
	casilla20M = Model();
	casilla20M.LoadModel("Models/casilla20.obj");
	casilla21M = Model();
	casilla21M.LoadModel("Models/casilla21.obj");
	casilla22M = Model();
	casilla22M.LoadModel("Models/casilla22.obj");
	casilla23M = Model();
	casilla23M.LoadModel("Models/casilla23.obj");
	casilla24M = Model();
	casilla24M.LoadModel("Models/casilla24.obj");
	casilla25M = Model();
	casilla25M.LoadModel("Models/casilla25.obj");
	casilla26M = Model();
	casilla26M.LoadModel("Models/casilla26.obj");
	casilla27M = Model();
	casilla27M.LoadModel("Models/casilla27.obj");
	casilla28M = Model();
	casilla28M.LoadModel("Models/casilla28.obj");
	casilla29M = Model();
	casilla29M.LoadModel("Models/casilla29.obj");
	casilla30M = Model();
	casilla30M.LoadModel("Models/casilla30.obj");
	casilla31M = Model();
	casilla31M.LoadModel("Models/casilla31.obj");
	casilla32M = Model();
	casilla32M.LoadModel("Models/casilla32.obj");
	casilla33M = Model();
	casilla33M.LoadModel("Models/casilla33.obj");
	casilla34M = Model();
	casilla34M.LoadModel("Models/casilla34.obj");
	casilla35M = Model();
	casilla35M.LoadModel("Models/casilla35.obj");
	casilla36M = Model();
	casilla36M.LoadModel("Models/casilla36.obj");
	casilla37M = Model();
	casilla37M.LoadModel("Models/casilla37.obj");
	casilla38M = Model();
	casilla38M.LoadModel("Models/casilla38.obj");
	casilla39M = Model();
	casilla39M.LoadModel("Models/casilla39.obj");
	casilla40M = Model();
	casilla40M.LoadModel("Models/casilla40.obj");

	//CASILLAS AMARILLAS
	casilla01A = Model();
	casilla01A.LoadModel("Models/casilla01A.obj");
	casilla02A = Model();
	casilla02A.LoadModel("Models/casilla02A.obj");
	casilla03A = Model();
	casilla03A.LoadModel("Models/casilla03A.obj");
	casilla04A = Model();
	casilla04A.LoadModel("Models/casilla04A.obj");
	casilla05A = Model();
	casilla05A.LoadModel("Models/casilla05A.obj");
	casilla06A = Model();
	casilla06A.LoadModel("Models/casilla06A.obj");
	casilla07A = Model();
	casilla07A.LoadModel("Models/casilla07A.obj");
	casilla08A = Model();
	casilla08A.LoadModel("Models/casilla08A.obj");
	casilla09A = Model();
	casilla09A.LoadModel("Models/casilla09A.obj");
	casilla10A = Model();
	casilla10A.LoadModel("Models/casilla10A.obj");
	casilla11A = Model();
	casilla11A.LoadModel("Models/casilla11A.obj");
	casilla12A = Model();
	casilla12A.LoadModel("Models/casilla12A.obj");
	casilla13A = Model();
	casilla13A.LoadModel("Models/casilla13A.obj");
	casilla14A = Model();
	casilla14A.LoadModel("Models/casilla14A.obj");
	casilla15A = Model();
	casilla15A.LoadModel("Models/casilla15A.obj");
	casilla16A = Model();
	casilla16A.LoadModel("Models/casilla16A.obj");
	casilla17A = Model();
	casilla17A.LoadModel("Models/casilla17A.obj");
	casilla18A = Model();
	casilla18A.LoadModel("Models/casilla18A.obj");
	casilla19A = Model();
	casilla19A.LoadModel("Models/casilla19A.obj");
	casilla20A = Model();
	casilla20A.LoadModel("Models/casilla20A.obj");
	casilla21A = Model();
	casilla21A.LoadModel("Models/casilla21A.obj");
	casilla22A = Model();
	casilla22A.LoadModel("Models/casilla22A.obj");
	casilla23A = Model();
	casilla23A.LoadModel("Models/casilla23A.obj");
	casilla24A = Model();
	casilla24A.LoadModel("Models/casilla24A.obj");
	casilla25A = Model();
	casilla25A.LoadModel("Models/casilla25A.obj");
	casilla26A = Model();
	casilla26A.LoadModel("Models/casilla26A.obj");
	casilla27A = Model();
	casilla27A.LoadModel("Models/casilla27A.obj");
	casilla28A = Model();
	casilla28A.LoadModel("Models/casilla28A.obj");
	casilla29A = Model();
	casilla29A.LoadModel("Models/casilla29A.obj");
	casilla30A = Model();
	casilla30A.LoadModel("Models/casilla30A.obj");
	casilla31A = Model();
	casilla31A.LoadModel("Models/casilla31A.obj");
	casilla32A = Model();
	casilla32A.LoadModel("Models/casilla32A.obj");
	casilla33A = Model();
	casilla33A.LoadModel("Models/casilla33A.obj");
	casilla34A = Model();
	casilla34A.LoadModel("Models/casilla34A.obj");
	casilla35A = Model();
	casilla35A.LoadModel("Models/casilla35A.obj");
	casilla36A = Model();
	casilla36A.LoadModel("Models/casilla36A.obj");
	casilla37A = Model();
	casilla37A.LoadModel("Models/casilla37A.obj");
	casilla38A = Model();
	casilla38A.LoadModel("Models/casilla38A.obj");
	casilla39A = Model();
	casilla39A.LoadModel("Models/casilla39A.obj");
	casilla40A = Model();
	casilla40A.LoadModel("Models/casilla40A.obj");

	//CASILLAS "ILUMINADAS" (COCINADO)
	casilla01AR = Model();
	casilla01AR.LoadModel("Models/casilla01AR.obj");
	casilla02AR = Model();
	casilla02AR.LoadModel("Models/casilla02AR.obj");
	casilla03AR = Model();
	casilla03AR.LoadModel("Models/casilla03AR.obj");
	casilla04AR = Model();
	casilla04AR.LoadModel("Models/casilla04AR.obj");
	casilla05AR = Model();
	casilla05AR.LoadModel("Models/casilla05AR.obj");
	casilla06AR = Model();
	casilla06AR.LoadModel("Models/casilla06AR.obj");
	casilla07AR = Model();
	casilla07AR.LoadModel("Models/casilla07AR.obj");
	casilla08AR = Model();
	casilla08AR.LoadModel("Models/casilla08AR.obj");
	casilla09AR = Model();
	casilla09AR.LoadModel("Models/casilla09AR.obj");
	casilla10AR = Model();
	casilla10AR.LoadModel("Models/casilla10AR.obj");
	casilla11AR = Model();
	casilla11AR.LoadModel("Models/casilla11AR.obj");
	casilla12AR = Model();
	casilla12AR.LoadModel("Models/casilla12AR.obj");
	casilla13AR = Model();
	casilla13AR.LoadModel("Models/casilla13AR.obj");
	casilla14AR = Model();
	casilla14AR.LoadModel("Models/casilla14AR.obj");
	casilla15AR = Model();
	casilla15AR.LoadModel("Models/casilla15AR.obj");
	casilla16AR = Model();
	casilla16AR.LoadModel("Models/casilla16AR.obj");
	casilla17AR = Model();
	casilla17AR.LoadModel("Models/casilla17AR.obj");
	casilla18AR = Model();
	casilla18AR.LoadModel("Models/casilla18AR.obj");
	casilla19AR = Model();
	casilla19AR.LoadModel("Models/casilla19AR.obj");
	casilla20AR = Model();
	casilla20AR.LoadModel("Models/casilla20AR.obj");
	casilla21AR = Model();
	casilla21AR.LoadModel("Models/casilla21AR.obj");
	casilla22AR = Model();
	casilla22AR.LoadModel("Models/casilla22AR.obj");
	casilla23AR = Model();
	casilla23AR.LoadModel("Models/casilla23AR.obj");
	casilla24AR = Model();
	casilla24AR.LoadModel("Models/casilla24AR.obj");
	casilla25AR = Model();
	casilla25AR.LoadModel("Models/casilla25AR.obj");
	casilla26AR = Model();
	casilla26AR.LoadModel("Models/casilla26AR.obj");
	casilla27AR = Model();
	casilla27AR.LoadModel("Models/casilla27AR.obj");
	casilla28AR = Model();
	casilla28AR.LoadModel("Models/casilla28AR.obj");
	casilla29AR = Model();
	casilla29AR.LoadModel("Models/casilla29AR.obj");
	casilla30AR = Model();
	casilla30AR.LoadModel("Models/casilla30AR.obj");
	casilla31AR = Model();
	casilla31AR.LoadModel("Models/casilla31AR.obj");
	casilla32AR = Model();
	casilla32AR.LoadModel("Models/casilla32AR.obj");
	casilla33AR = Model();
	casilla33AR.LoadModel("Models/casilla33AR.obj");
	casilla34AR = Model();
	casilla34AR.LoadModel("Models/casilla34AR.obj");
	casilla35AR = Model();
	casilla35AR.LoadModel("Models/casilla35AR.obj");
	casilla36AR = Model();
	casilla36AR.LoadModel("Models/casilla36AR.obj");
	casilla37AR = Model();
	casilla37AR.LoadModel("Models/casilla37AR.obj");
	casilla38AR = Model();
	casilla38AR.LoadModel("Models/casilla38AR.obj");
	casilla39AR = Model();
	casilla39AR.LoadModel("Models/casilla39AR.obj");
	casilla40AR = Model();
	casilla40AR.LoadModel("Models/casilla40AR.obj");
	
	// MODELOS DE LAS CASILLAS
	modeloCasilla01M = Model();
	modeloCasilla01M.LoadModel("Models/raidenCasilla01.obj");
	modeloCasilla02M = Model();
	modeloCasilla02M.LoadModel("Models/scorpionCasilla02.obj");
	modeloCasilla03M = Model();
	modeloCasilla03M.LoadModel("Models/shaoKahnCasilla03.obj");
	modeloCasilla04M = Model();
	modeloCasilla04M.LoadModel("Models/hellMountainsCasilla04.obj");
	modeloCasilla05M = Model();
	modeloCasilla05M.LoadModel("Models/viewerCasilla05.obj");
	modeloCasilla06M = Model();
	modeloCasilla06M.LoadModel("Models/treeStumpCasilla06.obj");
	modeloCasilla07M = Model();
	modeloCasilla07M.LoadModel("Models/pineTreeCasilla07.obj");
	modeloCasilla08M = Model();
	modeloCasilla08M.LoadModel("Models/fireDragonCasilla08.obj");
	modeloCasilla09M = Model();
	modeloCasilla09M.LoadModel("Models/scorpionCasilla09.obj");
	modeloCasilla11M = Model();
	modeloCasilla11M.LoadModel("Models/wolfCasilla11.obj");
	modeloCasilla12M = Model();
	modeloCasilla12M.LoadModel("Models/barakaCasilla12.obj");
	modeloCasilla13M = Model();
	modeloCasilla13M.LoadModel("Models/boCasilla13.obj");
	modeloCasilla14M = Model();
	modeloCasilla14M.LoadModel("Models/cassieCasilla14.obj");
	modeloCasilla15M = Model();
	modeloCasilla15M.LoadModel("Models/skullCasilla15.obj");
	modeloCasilla16M = Model();
	modeloCasilla16M.LoadModel("Models/rockyCasilla16.obj");
	modeloCasilla17M = Model();
	modeloCasilla17M.LoadModel("Models/neo_CortexCasilla17.obj");
	modeloCasilla18M = Model();
	modeloCasilla18M.LoadModel("Models/frogCasilla18.obj");
	modeloCasilla19M = Model();
	modeloCasilla19M.LoadModel("Models/polarCasilla19.obj");
	modeloCasilla20M = Model();
	modeloCasilla20M.LoadModel("Models/wizardCasilla20.obj");
	modeloCasilla21M = Model();
	modeloCasilla21M.LoadModel("Models/pinstripeCasilla21.obj");
	modeloCasilla22M = Model();
	modeloCasilla22M.LoadModel("Models/lionCasilla22.obj");
	modeloCasilla23M = Model();
	modeloCasilla23M.LoadModel("Models/babytCasilla23.obj");
	modeloCasilla24M = Model();
	modeloCasilla24M.LoadModel("Models/aku_akuCasilla24.obj");
	modeloCasilla25M = Model();
	modeloCasilla25M.LoadModel("Models/palm_treeCasilla25.obj");
	modeloCasilla26M = Model();
	modeloCasilla26M.LoadModel("Models/flowerCasilla26.obj");
	modeloCasilla27M = Model();
	modeloCasilla27M.LoadModel("Models/basic_treeCasilla27.obj");
	ModeloCasilla28 = Model();
	ModeloCasilla28.LoadModel("Models/brianCasilla28.obj");
	ModeloCasilla29 = Model();
	ModeloCasilla29.LoadModel("Models/ernieCasilla29.obj");
	ModeloCasilla30 = Model();
	ModeloCasilla30.LoadModel("Models/loisCasilla30.obj");
	ModeloCasilla31 = Model();
	ModeloCasilla31.LoadModel("Models/megCasilla31.obj");
	ModeloCasilla32 = Model();
	ModeloCasilla32.LoadModel("Models/peterCasilla32.obj");
	ModeloCasilla33 = Model();
	ModeloCasilla33.LoadModel("Models/joeCasilla33.obj");
	ModeloCasilla34 = Model();
	ModeloCasilla34.LoadModel("Models/chrisCasilla34.obj");
	ModeloCasilla35 = Model();
	ModeloCasilla35.LoadModel("Models/drunkenCasilla35.obj");
	ModeloCasilla36 = Model();
	ModeloCasilla36.LoadModel("Models/treeCasilla36.obj");
	ModeloCasilla37 = Model();
	ModeloCasilla37.LoadModel("Models/ChristmasTreeCasilla37.obj");
	ModeloCasilla38 = Model();
	ModeloCasilla38.LoadModel("Models/vinnyCasilla38.obj");
	ModeloCasilla39 = Model();
	ModeloCasilla39.LoadModel("Models/flowersCasilla39.obj");
	ModeloCasilla40 = Model();
	ModeloCasilla40.LoadModel("Models/carterCasilla40.obj");

	//CARRETERA
	recta = Model();
	recta.LoadModel("Models/recta.obj");
	curva = Model();
	curva.LoadModel("Models/curva.obj");

	// MODELO DEL AVATAR PARA EL RECORRIDO (SUBZERO)
	torsoSubZero = Model();
	torsoSubZero.LoadModel("Models/avatarSubZeroCuerpo.obj");
	cinturaSubZero = Model();
	cinturaSubZero.LoadModel("Models/avatarSubZeroCintura.obj");
	brazoDerechoSubZero = Model();
	brazoDerechoSubZero.LoadModel("Models/avatarSubZeroBrazoDerecho.obj");
	brazoIzquieroSubZero = Model();
	brazoIzquieroSubZero.LoadModel("Models/avatarSubZeroBrazoIzquierdo.obj");
	piernaDerechaSubZero = Model();
	piernaDerechaSubZero.LoadModel("Models/avatarSubZeroPiernaDerecha.obj");
	piernaIzquierdaSubZero = Model();
	piernaIzquierdaSubZero.LoadModel("Models/avatarSubZeroPiernaIzquierda.obj");

	// MODELOS PARA ANIMACIONES
	// SUBZERO
	subZeroAnimacion = Model();
	subZeroAnimacion.LoadModel("Models/subZeroAnimacion.obj");
	scorpionCabeza = Model();
	scorpionCabeza.LoadModel("Models/scorpionCabeza.obj");
	scorpionCuerpo = Model();
	scorpionCuerpo.LoadModel("Models/scorpionCuerpo.obj");
	baseSubzero = Model();
	baseSubzero.LoadModel("Models/baseSubzero.obj");
	// CRASH
	crashAnimacion = Model();
	crashAnimacion.LoadModel("Models/crashAnimacion.obj");

	// MODELOS DEL ENTORNO
	globo = Model();
	globo.LoadModel("Models/globo.obj");
	casaCynthia = Model();
	casaCynthia.LoadModel("Models/casaCynthia.obj");
	arboltablero1 = Model();
	arboltablero1.LoadModel("Models/arboltablero.obj");
	palmeratablero = Model();
	palmeratablero.LoadModel("Models/palmeratablero.obj");
	arbolsinhojas = Model();
	arbolsinhojas.LoadModel("Models/o00_7100.obj");
	arboltablero2 = Model();
	arboltablero2.LoadModel("Models/obj_0402_tree3.obj");
	flores1 = Model();
	flores1.LoadModel("Models/flowers.obj");
	arbusto = Model();
	arbusto.LoadModel("Models/SM_item_flower1.obj");
	carro1 = Model();
	carro1.LoadModel("Models/NinaCadyFEShape.obj");
	ermac = Model();
	ermac.LoadModel("Models/MK-X_iOS_OUTWORLD_Ermac_MK-X.obj");
	goro = Model();
	goro.LoadModel("Models/goro.obj");
	cage = Model();
	cage.LoadModel("Models/cage.obj");
	kabal = Model();
	kabal.LoadModel("Models/kabal.obj");
	esqueleto = Model();
	esqueleto.LoadModel("Models/CrashSkeleton.obj");
	Architect = Model();
	Architect.LoadModel("Models/Architect.obj");
	cleveland = Model();
	cleveland.LoadModel("Models/cleveland.obj");
	glenn_quagmire = Model();
	glenn_quagmire.LoadModel("Models/glenn_quagmire.obj");
	herbert = Model();
	herbert.LoadModel("Models/herbert.obj");
	Chicken_Nitro = Model();
	Chicken_Nitro.LoadModel("Models/Chicken_Nitro.obj");
	MK9_X360_STG_PROP_Statue_Goro = Model();
	MK9_X360_STG_PROP_Statue_Goro.LoadModel("Models/MK9_X360_STG_PROP_Statue_Goro.obj");
	mesa = Model();
	mesa.LoadModel("Models/RageTable.obj");
	sombrero = Model();
	sombrero.LoadModel("Models/KRN_KL_Hat_St.obj");
	hacha = Model();
	hacha.LoadModel("Models/KRN_NW_Tomahawk_St.obj");
	estrella = Model();
	estrella.LoadModel("Models/estrella.obj");
	bazooka = Model();
	bazooka.LoadModel("Models/Bazooka.obj");
	box1 = Model();
	box1.LoadModel("Models/akuaku.obj");
	box2 = Model();
	box2.LoadModel("Models/nitro.obj");
	box3 = Model();
	box3.LoadModel("Models/bounce_crate.obj");

	// MODELOS PARA LA TRASNFORMACION
	scorpionOriginal = Model();
	scorpionOriginal.LoadModel("Models/scorpionOriginal.obj");
	scorpionTransformacion = Model();
	scorpionTransformacion.LoadModel("Models/scorpionTransformacion.obj");
	fireball = Model();
	fireball.LoadModel("Models/bolaDeFuego.obj");
	lampara = Model();
	lampara.LoadModel("Models/Portal_Totem.obj");

	// MODELO AUXILIAR
	esfera = Model();
	esfera.LoadModel("Models/esfera.obj");

	//CARROS DE CARRETERA
	carroCortex = Model();
	carroCortex.LoadModel("Models/carroCortex.obj");
	carroCrunch = Model();
	carroCortex.LoadModel("Models/carroCrunch.obj");
	carroCoco = Model();
	carroCoco.LoadModel("Models/carroCoco.obj");

										// ##################################### SKYBOX ##################################### \\

	// SKYBOX DE DIA 
	std::vector<std::string> skyboxFaces01;
	skyboxFaces01.push_back("Textures/Skybox/Skybox5Dia.tga");
	skyboxFaces01.push_back("Textures/Skybox/Skybox1Dia.tga");
	skyboxFaces01.push_back("Textures/Skybox/Skybox4Dia.tga");
	skyboxFaces01.push_back("Textures/Skybox/Skybox2Dia.tga");
	skyboxFaces01.push_back("Textures/Skybox/Skybox3Dia.tga");
	skyboxFaces01.push_back("Textures/Skybox/Skybox6Dia.tga");

	skyboxDia = Skybox(skyboxFaces01);

	// SKYBOX DE NOCHE
	std::vector<std::string> skyboxFaces02;
	skyboxFaces02.push_back("Textures/Skybox/Skybox5Noche.tga");
	skyboxFaces02.push_back("Textures/Skybox/Skybox1Noche.tga");
	skyboxFaces02.push_back("Textures/Skybox/Skybox4Noche.tga");
	skyboxFaces02.push_back("Textures/Skybox/Skybox2Noche.tga");
	skyboxFaces02.push_back("Textures/Skybox/Skybox3Noche.tga");
	skyboxFaces02.push_back("Textures/Skybox/Skybox6Noche.tga");

	skyboxNoche = Skybox(skyboxFaces02);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	// LUZ DIRECCIONAL
	DirectionalLight* auxLight = &mainLight;
	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.1f,
		0.0f, -1.0f, 0.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-200.0f, 4.0f, 80.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;
	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	// LUZ LIGADA AL PERSONAJE POR LA NOCHE
	spotLights[1] = SpotLight(1.0f, 0.0f, 1.0f,
		5.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.001f,
		20.0f);
	spotLightCount++;
	
	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset=0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

										// ##################################### TIEMPO ##################################### \\

	// PARA CONTROLAR EL TIEMPO
	glfwSetTime(0);

										// ##################################### GRADOS ALEATORIOS ##################################### \\

	// INICIALIZAR LA SEMILLA SOLO UNA VEZ
	std::srand(static_cast<unsigned>(std::time(0)));

	// PARA GRADOS DE X DADO 8 CARAS
	std::vector<int> listaX = { 180, -180 };
	int gradosDeX = listaX[std::rand() % listaX.size()];

	// PARA GRADOS DE Y DADO 8 CARAS
	std::vector<int> listaY = { 45, 135, 225, 315, -45, -135, -225, -315 };
	int gradosDeY = listaY[std::rand() % listaY.size()];

	// PARA GRADOS DE Z DADO 8 CARAS
	std::vector<int> listaZ = { 25,-25 };
	int gradosDeZ = listaZ[std::rand() % listaZ.size()];

	// PARA GRADOS DE X_1 DADO DE 4 CARAS
	std::vector<int> listaX_1 = { 0, 115, 115 , 115 };
	int gradosDeX_1 = listaX_1[std::rand() % listaX_1.size()];

	// PARA GRADOS DE X_2 DADO DE 4 CARAS
	std::vector<int> listaX_2 = { 0, -115, -115 , -115 };
	int gradosDeX_2 = listaX_2[std::rand() % listaX_2.size()];

	// PARA GRADOS DE Y_1 DADO DE 4 CARAS
	std::vector<int> listaY_1 = { 60, 120, 180, 240, 300, 360, -60, -120, -180, -240, -300, -360 };
	int gradosDeY_1 = listaY_1[std::rand() % listaY_1.size()];

	//Se agregan nuevos frames 

	printf("\nTeclas para uso de Keyframes:\n");
	printf("Presionar barra espaciadora para reproducir animación.\n");
	printf("Presionar 0 para volver a habilitar reproducción de la animación.\n");

	printf("Presionar L para guardar frame.\n");
	printf("Presionar P para habilitar guardar un nuevo frame.\n");

	printf("Presionar 1 para mover en X negativo.\n");
	printf("Presionar 3 para mover en X positivo.\n");

	printf("Presionar 1 para mover en X negativo.\n");
	printf("Presionar 3 para mover en X positivo.\n");

	printf("Presionar G para mover en Y negativo.\n");
	printf("Presionar F para mover en Y positivo.\n");

	printf("Presionar 6 para rotar (giro) en sentido horario (incrementa 90).\n");
	printf("Presionar 7 para rotar (giro) en sentido antihorario (decrementa 90).\n");

	printf("Presionar 2 para habilitar la modificación de las variables nuevamente.\n");

	printf("Presionar 8 para rotar alas en sentido anti horario\n");
	printf("Presionar 9 para rotar alas en sentido  horario\n");


	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

											// ##################################### BAJAR AMBOS DADOS (Y) ##################################### \\
		//-------Para Keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

		// PARA BAJAR
		// TECLA Y
		if (mainWindow.getsubeBajaDado() == true)
		{
			// HACER QUE EL DADO BAJE
			if (subeBajaDado8 > 7.0f)
			{
				subeBajaDado8 -= subeBajaDadoOffset8 * deltaTime;
			}
			// CUANDO LLEGUE AL FINAL
			else
			{
				// ROTAR EN X
				switch (gradosDeX)
				{
				case 180:
					if (rotaDadox8 < 180)
					{
						rotaDadox8 += rotaDadoxOffset8 * deltaTime;
					}
					else
					{
						// ROTAR EN Y
						switch (gradosDeY)
						{
						case 45:
							if (rotaDadoy8 < 45)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 6;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 3;
									break;
								}
							}
							break;
						case -45:
							if (rotaDadoy8 > -45)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 7;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 2;
									break;
								}
							}
							break;
						case 135:
							if (rotaDadoy8 < 135)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 5;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 4;
									break;
								}
							}
							break;
						case -135:
							if (rotaDadoy8 > -135)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 8;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 1;
									break;
								}
							}
							break;
						case 225:
							if (rotaDadoy8 < 225)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 8;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 1;
									break;
								}
							}
							break;
						case -225:
							if (rotaDadoy8 > -225)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 5;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 4;
									break;
								}
							}
							break;
						case 315:
							if (rotaDadoy8 < 315)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 7;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 2;
									break;
								}
							}
							break;
						case -315:
							if (rotaDadoy8 > -315)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 6;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 3;
									break;
								}
							}
							break;
						}
					}
					break;
				case -180:
					if (rotaDadox8 > -180)
					{
						rotaDadox8 -= rotaDadoxOffset8 * deltaTime;
					}
					else
					{
						// ROTAR EN Y
						switch (gradosDeY)
						{
						case 45:
							if (rotaDadoy8 < 45)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 6;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 3;
									break;
								}
							}
							break;
						case -45:
							if (rotaDadoy8 > -45)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 7;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 2;
									break;
								}
							}
							break;
						case 135:
							if (rotaDadoy8 < 135)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 5;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 4;
									break;
								}
							}
							break;
						case -135:
							if (rotaDadoy8 > -135)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 8;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 1;
									break;
								}
							}
							break;
						case 225:
							if (rotaDadoy8 < 225)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 8;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 1;
									break;
								}
							}
							break;
						case -225:
							if (rotaDadoy8 > -225)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 5;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 4;
									break;
								}
							}
							break;
						case 315:
							if (rotaDadoy8 < 315)
							{
								rotaDadoy8 += rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								// ROTAR EN Z
								// ELEGIR EL NUMERO DEL LADO
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 7;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 2;
									break;
								}
							}
							break;
						case -315:
							if (rotaDadoy8 > -315)
							{
								rotaDadoy8 -= rotaDadoyOffset8 * deltaTime;
							}
							else
							{
								switch (gradosDeZ)
								{
								case 25:
									if (rotaDadoz8 < 25)
									{
										rotaDadoz8 += rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 6;
									break;
								case -25:
									if (rotaDadoz8 > -25)
									{
										rotaDadoz8 -= rotaDadozOffset8 * deltaTime;
									}
									resultado8Caras = 3;
									break;
								}
							}
							break;
						}
					}
					break;
				}
			} // AQUI TERMINA EL ELSE DEL DADO 8
		}

		// PARA BAJAR
		// TECLA Y
		if (mainWindow.getsubeBajaDado() == true)
		{
			// HACER QUE EL DADO BAJE
			if (subeBajaDado4 > 3.1f)
			{
				subeBajaDado4 -= subeBajaDadoOffset4 * deltaTime;
			}
			// CUANDO LLEGUE AL FINAL
			else
			{
				// ROTAR EN Y
				switch (gradosDeY_1)
				{
				case 60:
					if (rotaDadoy4 < 60)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 2;
							break;
						}
					}
					break;
				case -60:
					if (rotaDadoy4 > -60)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 4;
							break;
						}
					}
					break;
				case 120:
					if (rotaDadoy4 < 120)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 4;
							break;
						}
					}
					break;
				case -120:
					if (rotaDadoy4 > -120)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 2;
							break;
						}
					}
					break;
				case 180:
					if (rotaDadoy4 < 180)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 3;
							break;
						}
					}
					break;
				case -180:
					if (rotaDadoy4 > -180)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 3;
							break;
						}
					}
					break;
				case 240:
					if (rotaDadoy4 < 240)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 2;
							break;
						}
					}
					break;
				case -240:
					if (rotaDadoy4 > -240)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 4;
							break;
						}
					}
					break;
				case 300:
					if (rotaDadoy4 < 300)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 4;
							break;
						}
					}
					break;
				case -300:
					if (rotaDadoy4 > -300)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_2)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case -115:
							if (rotaDadox4 > -115)
							{
								rotaDadox4 -= rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 2;
							break;
						}
					}
					break;
				case 360:
					if (rotaDadoy4 < 360)
					{
						rotaDadoy4 += rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 3;
							break;
						}
					}
					break;
				case -360:
					if (rotaDadoy4 > -360)
					{
						rotaDadoy4 -= rotaDadoyOffset4 * deltaTime;
					}
					else
					{
						// ROTAR EN X
						switch (gradosDeX_1)
						{
						case 0:
							resultado4Caras = 1;
							break;
						case 115:
							if (rotaDadox4 < 115)
							{
								rotaDadox4 += rotaDadoxOffset4 * deltaTime;
							}
							resultado4Caras = 3;
							break;
						}
					}
					break;
				}
			}
		}

											// ##################################### SUMA DE AMBOS DADOS ##################################### \\

		// RESULTADO DE LOS DADOS
		if (resultado8Caras != 0 && resultado4Caras != 0)
		{
			resultado = resultado4Caras + resultado8Caras;
			//printf("RESULTADO = %i", resultado);
		}

							// ##################################### RESULTADO DIFERENTE AL ANTERIOR PARA ACTUALIZAR POSICION ##################################### \\

		// VERIFICAR SI 'RESULTADO' HA CAMBIADO
		if (resultado != resultadoAnterior01) {
			mueveAvatar01Base = mueveAvatar01; // ALMACENAR LA POSICION ACTUAL COMO BASE
			resultadoAnterior01 = resultado;     // ACTUALIZA EL VALOR ANTERIOR
			//printf(" MUEVEAVATAR01BASE = %f y RESULTADOANTERIOR01 = %i             \n", mueveAvatar01Base, resultadoAnterior01);
		}

		// VERIFICAR SI 'RESULTADO' HA CAMBIADO
		if (resultado != resultadoAnterior02) {
			mueveAvatar02Base = mueveAvatar02; // ALMACENAR LA POSICION ACTUAL COMO BASE
			resultadoAnterior02 = resultado;     // ACTUALIZA EL VALOR ANTERIOR
			//printf(" EL SEGUNDOOOOOO = %f y RESULTADOANTERIOR01 = %i             \n", mueveAvatar02Base, resultadoAnterior01);
		}

		// VERIFICAR SI 'RESULTADO' HA CAMBIADO
		if (resultado != resultadoAnterior03) {
			mueveAvatar03Base = mueveAvatar03; // ALMACENAR LA POSICION ACTUAL COMO BASE
			resultadoAnterior03 = resultado;     // ACTUALIZA EL VALOR ANTERIOR
			//printf(" EL SEGUNDOOOOOO = %f y RESULTADOANTERIOR01 = %i             \n", mueveAvatar02Base, resultadoAnterior01);
		}

		// VERIFICAR SI 'RESULTADO' HA CAMBIADO
		if (resultado != resultadoAnterior04) {
			mueveAvatar04Base = mueveAvatar04; // ALMACENAR LA POSICION ACTUAL COMO BASE
			resultadoAnterior04 = resultado;     // ACTUALIZA EL VALOR ANTERIOR
			//printf(" EL SEGUNDOOOOOO = %f y RESULTADOANTERIOR01 = %i             \n", mueveAvatar02Base, resultadoAnterior01);
		}

											// ##################################### LO QUE RESTA DE AVANZAR ##################################### \\

		// DIFERENCIA
		if (((mueveAvatar01 + (resultado * 20)) > 200))
		{
			diferencia = (mueveAvatar01Base + (resultado * 20)) - 200;
			diferencia = abs(diferencia);

			if (diferencia < 1)
			{
				conta += 1;
			}
		}
		if (conta > 0)
		{
			diferencia = 0.0f;
		}

		// DIFERENCIA
		if (((mueveAvatar02 + (resultado * 20)) > 200))
		{
			diferencia01 = (mueveAvatar02Base + (resultado * 20)) - 200;
			diferencia01 = abs(diferencia01);

			if (diferencia01 < 1)
			{
				conta01 += 1;
			}
		}
		if (conta01 > 0)
		{
			diferencia01 = 0.0f;
		}

		// DIFERENCIA
		if (((mueveAvatar03 + (resultado * 20)) > 200))
		{
			diferencia02 = (mueveAvatar03Base + (resultado * 20)) - 200;
			diferencia02 = abs(diferencia02);

			if (diferencia02 < 1)
			{
				conta02 += 1;
			}
		}
		if (conta02 > 0)
		{
			diferencia02 = 0.0f;
		}

											// ##################################### AVANZAR CON EL RESULTADO ##################################### \\

		// MOVIMIENTO AVATAR
		if (mueveAvatar01 <= 200)
		{
			//printf("AVATAR VALOR: %f", mueveAvatar01);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar01 < mueveAvatar01Base + (resultado * 20))
			{

				mueveAvatar01 += mueveAvatar01Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}

				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
			}
		}
		else if (rotaAvatar01 > -90)
		{
			rotaAvatar01 -= rotaAvatar01Offset * deltaTime;

			// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
			if (subebaja)
			{
				if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
				{
					rotaBrazoD += rotaBrazoDOffset * deltaTime;
					rotaBrazoI -= rotaBrazoIOffset * deltaTime;
					rotaPiernaD -= rotaPiernaDOffset * deltaTime;
					rotaPiernaI += rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			else
			{
				if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
				{
					rotaBrazoD -= rotaBrazoDOffset * deltaTime;
					rotaBrazoI += rotaBrazoIOffset * deltaTime;
					rotaPiernaD += rotaPiernaDOffset * deltaTime;
					rotaPiernaI -= rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
		}
		else if (diferencia > 0 && hayDiferencia)
		{
			// printf("RESULTADO = %f", diferencia);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar02 < diferencia)
			{

				mueveAvatar02 += mueveAvatar02Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
			}
			else
			{
				hayDiferencia = !hayDiferencia;
			}
		}
		else if (mueveAvatar02 <= 200)
		{
			//printf("AVATAR VALOR: %f", mueveAvatar01);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar02 < mueveAvatar02Base + (resultado * 20))
			{

				mueveAvatar02 += mueveAvatar02Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}

				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}

			}
		}
		else if (rotaAvatar02 > -90)
		{
			rotaAvatar02 -= rotaAvatar02Offset * deltaTime;

			// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
			if (subebaja)
			{
				if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
				{
					rotaBrazoD += rotaBrazoDOffset * deltaTime;
					rotaBrazoI -= rotaBrazoIOffset * deltaTime;
					rotaPiernaD -= rotaPiernaDOffset * deltaTime;
					rotaPiernaI += rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			else
			{
				if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
				{
					rotaBrazoD -= rotaBrazoDOffset * deltaTime;
					rotaBrazoI += rotaBrazoIOffset * deltaTime;
					rotaPiernaD += rotaPiernaDOffset * deltaTime;
					rotaPiernaI -= rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
		}
		else if (diferencia01 > 0 && hayDiferencia01)
		{
			// printf("RESULTADO = %f", diferencia);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar03 < diferencia01)
			{

				mueveAvatar03 += mueveAvatar03Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
			}
			else
			{
				hayDiferencia01 = !hayDiferencia01;
			}
		}
		else if (mueveAvatar03 <= 200)
		{
			//printf("AVATAR VALOR: %f", mueveAvatar01);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar03 < mueveAvatar03Base + (resultado * 20))
			{

				mueveAvatar03 += mueveAvatar03Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}

				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}

			}
		}
		else if (rotaAvatar03 > -90)
		{
			rotaAvatar03 -= rotaAvatar03Offset * deltaTime;

			// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
			if (subebaja)
			{
				if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
				{
					rotaBrazoD += rotaBrazoDOffset * deltaTime;
					rotaBrazoI -= rotaBrazoIOffset * deltaTime;
					rotaPiernaD -= rotaPiernaDOffset * deltaTime;
					rotaPiernaI += rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			else
			{
				if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
				{
					rotaBrazoD -= rotaBrazoDOffset * deltaTime;
					rotaBrazoI += rotaBrazoIOffset * deltaTime;
					rotaPiernaD += rotaPiernaDOffset * deltaTime;
					rotaPiernaI -= rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
		}
		else if (diferencia02 > 0 && hayDiferencia02)
		{
			// printf("RESULTADO = %f", diferencia);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar04 < diferencia02)
			{

				mueveAvatar04 += mueveAvatar04Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}
			}
			else
			{
				hayDiferencia02 = !hayDiferencia02;
			}
		}
		else if (mueveAvatar04 <= 200)
		{
			//printf("AVATAR VALOR: %f", mueveAvatar01);
			// RECORRIDO DEL AVATAR
			if (mueveAvatar04 < mueveAvatar04Base + (resultado * 20))
			{

				mueveAvatar04 += mueveAvatar04Offset * deltaTime;

				// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
				if (subebaja)
				{
					if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
					{
						rotaBrazoD += rotaBrazoDOffset * deltaTime;
						rotaBrazoI -= rotaBrazoIOffset * deltaTime;
						rotaPiernaD -= rotaPiernaDOffset * deltaTime;
						rotaPiernaI += rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}

				}
				else
				{
					if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
					{
						rotaBrazoD -= rotaBrazoDOffset * deltaTime;
						rotaBrazoI += rotaBrazoIOffset * deltaTime;
						rotaPiernaD += rotaPiernaDOffset * deltaTime;
						rotaPiernaI -= rotaPiernaIOffset * deltaTime;
					}
					else
					{
						subebaja = !subebaja;
					}
				}

			}
		}
		else if (rotaAvatar04 > -90)
		{
			rotaAvatar04 -= rotaAvatar04Offset * deltaTime;

			// ROTACION DE LOS BRAZOS Y PIERNAS DEL AVATAR
			if (subebaja)
			{
				if (rotaBrazoD < 45.0f && rotaBrazoI > -45.0f && rotaPiernaD > -45.0f && rotaPiernaI < 45.0f)
				{
					rotaBrazoD += rotaBrazoDOffset * deltaTime;
					rotaBrazoI -= rotaBrazoIOffset * deltaTime;
					rotaPiernaD -= rotaPiernaDOffset * deltaTime;
					rotaPiernaI += rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}
			else
			{
				if (rotaBrazoD > -45.0f && rotaBrazoI < 45.0f && rotaPiernaD < 45.0f && rotaPiernaI > -45.0f)
				{
					rotaBrazoD -= rotaBrazoDOffset * deltaTime;
					rotaBrazoI += rotaBrazoIOffset * deltaTime;
					rotaPiernaD += rotaPiernaDOffset * deltaTime;
					rotaPiernaI -= rotaPiernaIOffset * deltaTime;
				}
				else
				{
					subebaja = !subebaja;
				}
			}

		}
		else
		{
												// REINICAR TODOS LOS VALORES AL COMPLETAR UNA VUELTA
												
			// VARIABLES PARA ANIMACION DEL DADO DE 8 CARAS
			subeBajaDado8 = 35.0f;
			rotaDadox8 = 0.0f;
			rotaDadoy8 = 0.0f;
			rotaDadoz8 = 0.0f;

			// VARIABLES PARA ANIMACION DEL DADO DE 4 CARAS
			subeBajaDado4 = 35.0f;
			rotaDadox4 = 0.0f;
			rotaDadoy4 = 0.0f;

			// RRESULTADO DEL DADO
			resultado4Caras = 0;
			resultado8Caras = 0;
			resultado = 0;

			// VARIABLES PARA ANIAMCION DE RECORRIDO
			mueveAvatar01 = 0.0f;
			mueveAvatar01Base = 0.0f;
			resultadoAnterior01 = 0;
			mueveAvatar02 = 0.0f;
			mueveAvatar02Base = 0.0f;
			resultadoAnterior02 = 0;
			mueveAvatar03 = 0.0f;
			mueveAvatar03Base = 0.0f;
			resultadoAnterior03 = 0;
			mueveAvatar04 = 0.0f;
			mueveAvatar04Base = 0.0f;
			resultadoAnterior04 = 0;
			diferencia = 0.0f;
			hayDiferencia = true;
			conta = 0;
			diferencia01 = 0.0f;
			hayDiferencia01 = true;
			conta01 = 0;
			diferencia02 = 0.0f;
			hayDiferencia02 = true;
			conta02 = 0;

			// VARIABLES PARA LA ANIMACION DE LA VUELTA 
			rotaAvatar01 = 0.0f;
			rotaAvatar02 = 0.0f;
			rotaAvatar03 = 0.0f;
			rotaAvatar04 = 0.0f;

			// VARIABLES PARA ANIMACIÓN DE LOS BRAZOS Y PIERNAS
			rotaBrazoD = 0.0f;
			rotaBrazoI = 0.0f;
			rotaPiernaD = 0.0f;
			rotaPiernaI = 0.0f;
			subebaja = true;

			// ANIMACIONES DE CASILLAS
			// CASILLA 02
			raidenSubeBaja = -8.0f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			raidenRota = 0.0f;
			raidenCont01 = 0;
			raidenCont02 = 0;
			raiden = true;
			raidenTiempo = 0.0f;

			// CASILLA 03
			scorpionSubeBaja = -9.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			scorpionRota = 0.0f;
			scorpionCont01 = 0;
			scorpionCont02 = 0;
			scorpion = true;
			scorpionTiempo = 0.0f;

			// CASILLA 04
			shaoSubeBaja = -9.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			shaoRota = 0.0f;
			shaoCont01 = 0;
			shaoCont02 = 0;
			shao = true;
			shaoTiempo = 0.0f;

			// CASILLA 05
			hellSubeBaja = -13.0f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			hellRota = 0.0f;
			hellCont01 = 0;
			hellCont02 = 0;
			hell = true;
			hellTiempo = 0.0f;

			// CASILLA 06
			viewerSubeBaja = -11.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			viewerRota = 0.0f;
			viewerCont01 = 0;
			viewerCont02 = 0;
			viewer = true;
			viewerTiempo = 0.0f;

			// CASILLA 07
			tree_stumpSubeBaja = -9.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			tree_stumpRota = 0.0f;
			tree_stumpCont01 = 0;
			tree_stumpCont02 = 0;
			tree_stump = true;
			tree_stumpTiempo = 0.0f;

			// CASILLA 08
			pine_treeSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			pine_treeRota = 0.0f;
			pine_treeCont01 = 0;
			pine_treeCont02 = 0;
			pine_tree = true;
			pine_treeTiempo = 0.0f;

			// CASILLA 09
			fire_dragonSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			fire_dragonRota = 0.0f;
			fire_dragonCont01 = 0;
			fire_dragonCont02 = 0;
			fire_dragon = true;
			fire_dragonTiempo = 0.0f;

			// CASILLA 10
			scorpion2SubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			scorpion2Rota = 0.0f;
			scorpion2Cont01 = 0;
			scorpion2Cont02 = 0;
			scorpion2 = true;
			scorpion2Tiempo = 0.0f;

			// CASILLA 11
			wolfSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			wolfRota = 0.0f;
			wolfCont01 = 0;
			wolfCont02 = 0;
			wolf = true;
			wolfTiempo = 0.0f;

			// CASILLA 12
			BarakaSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			BarakaRota = 0.0f;
			BarakaCont01 = 0;
			BarakaCont02 = 0;
			Baraka = true;
			BarakaTiempo = 0.0f;

			// CASILLA 13
			boSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			boRota = 0.0f;
			boCont01 = 0;
			boCont02 = 0;
			bo = true;
			boTiempo = 0.0f;

			// CASILLA 14
			cassieSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			cassieRota = 0.0f;
			cassieCont01 = 0;
			cassieCont02 = 0;
			cassie = true;
			cassieTiempo = 0.0f;

			// CASILLA 15
			skullSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			skullRota = 0.0f;
			skullCont01 = 0;
			skullCont02 = 0;
			skull = true;
			skullTiempo = 0.0f;

			// CASILLA 16
			rockySubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			rockyRota = 0.0f;
			rockyCont01 = 0;
			rockyCont02 = 0;
			rocky = true;
			rockyTiempo = 0.0f;

			// CASILLA 17
			drneoSubeBaja = -15.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			drneoRota = 0.0f;
			drneoCont01 = 0;
			drneoCont02 = 0;
			drneo = true;
			drneoTiempo = 0.0f;

			// CASILLA 18
			frogSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			frogRota = 0.0f;
			frogCont01 = 0;
			frogCont02 = 0;
			frog = true;
			frogTiempo = 0.0f;

			// CASILLA 19
			polarSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			polarRota = 0.0f;
			polarCont01 = 0;
			polarCont02 = 0;
			polar = true;
			polarTiempo = 0.0f;

			// CASILLA 20
			wizardSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			wizardRota = 0.0f;
			wizardCont01 = 0;
			wizardCont02 = 0;
			wizard = true;
			wizardTiempo = 0.0f;

			// CASILLA 21
			pinstripeSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			pinstripeRota = 0.0f;
			pinstripeCont01 = 0;
			pinstripeCont02 = 0;
			pinstripe = true;
			pinstripeTiempo = 0.0f;

			// CASILLA 22
			 lionSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			 lionRota = 0.0f;
			 lionCont01 = 0;
			 lionCont02 = 0;
			 lion = true;
			 lionTiempo = 0.0f;

			// CASILLA 23
			babytSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			babytRota = 0.0f;
			babytCont01 = 0;
			babytCont02 = 0;
			babyt = true;
			babytTiempo = 0.0f;

			// CASILLA 24
			akuakuSubeBaja = -14.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			akuakuRota = 0.0f;
			akuakuCont01 = 0;
			akuakuCont02 = 0;
			akuaku = true;
			akuakuTiempo = 0.0f;

			// CASILLA 25
			palm_treeSubeBaja = -15.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			palm_treeRota = 0.0f;
			palm_treeCont01 = 0;
			palm_treeCont02 = 0;
			palm_tree = true;
			palm_treeTiempo = 0.0f;

			// CASILLA 26
			flowersSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			flowersRota = 0.0f;
			flowersCont01 = 0;
			flowersCont02 = 0;
			flowers = true;
			flowersTiempo = 0.0f;

			// CASILLA 27
			basicSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			basicRota = 0.0f;
			basicCont01 = 0;
			basicCont02 = 0;
			basic = true;
			basicTiempo = 0.0f;

			// CASILLA 28
			 brianSubeBaja = -14.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			 brianRota = 0.0f;
			  brianCont01 = 0;
			  brianCont02 = 0;
			  brian = true;
			  brianTiempo = 0.0f;

			// CASILLA 29
			ernieSubeBaja = -13.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			ernieRota = 0.0f;
			ernieCont01 = 0;
			ernieCont02 = 0;
			ernie = true;
			ernieTiempo = 0.0f;

			// CASILLA 30
			luisaSubeBaja = -13.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			luisaRota = 0.0f;
			luisaCont01 = 0;
			luisaCont02 = 0;
			luisa = true;
			luisaTiempo = 0.0f;

			// CASILLA 31
			megSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			megRota = 0.0f;
			megCont01 = 0;
			megCont02 = 0;
			meg = true;
			megTiempo = 0.0f;

			// CASILLA 32
			peterSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			peterRota = 0.0f;
			peterCont01 = 0;
			peterCont02 = 0;
			peter = true;
			peterTiempo = 0.0f;

			// CASILLA 33
			joeSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			joeRota = 0.0f;
			joeCont01 = 0;
			joeCont02 = 0;
			joe = true;
			joeTiempo = 0.0f;

			// CASILLA 34
			chrisSubeBaja = -20.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			chrisRota = 0.0f;
			chrisCont01 = 0;
			chrisCont02 = 0;
			chris = true;
			chrisTiempo = 0.0f;

			// CASILLA 35
			casaSubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			casaRota = 0.0f;
			casaCont01 = 0;
			casaCont02 = 0;
			casa = true;
			casaTiempo = 0.0f;

			// CASILLA 36
			treeSubeBaja = -12.9f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			treeRota = 0.0f;
			treeCont01 = 0;
			treeCont02 = 0;
			tree = true;
			treeTiempo = 0.0f;

			// CASILLA 37
			navidadSubeBaja = -14.0f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			navidadRota = 0.0f;
			navidadCont01 = 0;
			navidadCont02 = 0;
			navidad = true;
			navidadTiempo = 0.0f;

			// CASILLA 38
			vinnySubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			vinnyRota = 0.0f;
			vinnyCont01 = 0;
			vinnyCont02 = 0;
			vinny = true;
			vinnyTiempo = 0.0f;

			// CASILLA 39
			flowers2SubeBaja = -12.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			flowers2Rota = 0.0f;
			flowers2Cont01 = 0;
			flowers2Cont02 = 0;
			flowers2 = true;
			flowers2Tiempo = 0.0f;

			// CASILLA 40
			carterSubeBaja = -13.5f; //PARA BAJARLO Y NO SE VEA EN EL TABLERO
			carterRota = 0.0f;
			carterCont01 = 0;
			carterCont02 = 0;
			carter = true;
			carterTiempo = 0.0f;

			// COCINADO EN LAS CASILLAS
			cocinado01 = 0;
			cocinado02 = 0;
			cocinado03 = 0;
			cocinado04 = 0;
			cocinado05 = 0;
			cocinado06 = 0;
			cocinado07 = 0;
			cocinado08 = 0;
			cocinado09 = 0;
			cocinado10 = 0;
			cocinado11 = 0;
			cocinado12 = 0;
			cocinado13 = 0;
			cocinado14 = 0;
			cocinado15 = 0;
			cocinado16 = 0;
			cocinado17 = 0;
			cocinado18 = 0;
			cocinado19 = 0;
			cocinado20 = 0;
			cocinado21 = 0;
			cocinado22 = 0;
			cocinado23 = 0;
			cocinado24 = 0;
			cocinado25 = 0;
			cocinado26 = 0;
			cocinado27 = 0;
			cocinado28 = 0;
			cocinado29 = 0;
			cocinado30 = 0;
			cocinado31 = 0;
			cocinado32 = 0;
			cocinado33 = 0;
			cocinado34 = 0;
			cocinado35 = 0;
			cocinado36 = 0;
			cocinado37 = 0;
			cocinado38 = 0;
			cocinado39 = 0;
		}

									// ##################################### ACTIVAR ANIMACION DE LOS MODELOS DE CASILLAS ##################################### \\

		// ACTIVAR BANDERAS DE ANIMACION ESPECIAL
		// CASILLA 2 - 10
		if (mueveAvatar01 >= 20)
		{
			raidenCont01 += 1;
		}
		if (mueveAvatar01 >= 40)
		{
			scorpionCont01 += 1;
		}
		if (mueveAvatar01 >= 60)
		{
			shaoCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar01 >= 80)
		{
			hellCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar01 >= 100)
		{
			viewerCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar01 >= 120)
		{
			tree_stumpCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar01 >= 140)
		{
			pine_treeCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar01 >= 160)
		{
			fire_dragonCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar01 >= 180)
		{
			scorpion2Cont01 += 1; //SE CAMBIA AL MODELO NUEVO

		}
		if (mueveAvatar01 >= 200)
		{
			wolfCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		// CASILLA 11 - 20
		if (mueveAvatar02 >= 20)
		{
			BarakaCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 40)
		{
			boCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 60)
		{
			cassieCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 80)
		{
			skullCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 100)
		{
			rockyCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 120)
		{
			drneoCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 140)
		{
			frogCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 160)
		{
			polarCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 180)
		{
			wizardCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar02 >= 200)
		{
			pinstripeCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		// CASILLA 21 - 30
		if (mueveAvatar03 >= 20)
		{
			lionCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 40)
		{
			babytCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 60)
		{
			akuakuCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 80)
		{
			palm_treeCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 100)
		{
			flowersCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 120)
		{
			basicCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 140)
		{
			brianCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 160)
		{
			ernieCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 180)
		{
			luisaCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar03 >= 200)
		{
			megCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		// CASILLA 31 - 39
		if (mueveAvatar04 >= 20)
		{
			peterCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar04 >= 40)
		{
			joeCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar04 >= 60)
		{
			chrisCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar04 >= 80)
		{
			casaCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar04 >= 100)
		{
			treeCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar04 >= 120)
		{
			navidadCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar04 >= 140)
		{
			vinnyCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar04 >= 160)
		{
			flowers2Cont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}
		if (mueveAvatar04 >= 180)
		{
			carterCont01 += 1; //SE CAMBIA AL MODELO NUEVO
		}

										// ##################################### SUBIR AMBOS DADOS (U) ##################################### \\

		// PARA SUBIR
		// U
		if (mainWindow.getsubeBajaDado() == false)
		{
			if (subeBajaDado8 < 35.0f)
			{
				subeBajaDado8 += subeBajaDadoOffset8 * deltaTime;
			}
			else
			{
				// REGRESAR A SU ESTADO ORIGINAL Y REASIGNAR LOS VALORES DE LOS GRADOS
				gradosDeX = listaX[std::rand() % listaX.size()];
				rotaDadox8 = 0.0f;
				gradosDeY = listaY[std::rand() % listaY.size()];
				rotaDadoy8 = 0.0f;
				gradosDeZ = listaZ[std::rand() % listaZ.size()];
				rotaDadoz8 = 0.0f;
				resultado8Caras = 0;
			}
		}

		// PARA SUBIR
		// U
		if (mainWindow.getsubeBajaDado() == false)
		{
			if (subeBajaDado4 < 35.0f)
			{
				subeBajaDado4 += subeBajaDadoOffset4 * deltaTime;
			}
			else
			{
				// REGRESAR A SU ESTADO ORIGINAL Y REASIGNAR LOS VALORES DE LOS GRADOS

				gradosDeX_1 = listaX_1[std::rand() % listaX_1.size()];
				gradosDeX_2 = listaX_2[std::rand() % listaX_2.size()];
				rotaDadox4 = 0.0f;
				gradosDeY_1 = listaY_1[std::rand() % listaY_1.size()];
				rotaDadoy4 = 0.0f;
				resultado4Caras = 0;
			}
		}

									// ##################################### ANIMACION DE LOS MODELOS DE LAS CASILLAS ##################################### \\

		// INTERACCIINES ESPECIALES DE CASILLAS
		// RAIDEN
		if (raidenCont01 >= 1 && raidenCont02 < 1)
		{
			cocinado01 += 1;
			//printf("ENTRO\n");
			if (raiden)
			{
				if (raidenSubeBaja < 10.9f)
				{
					raidenSubeBaja += raidenSubeBajaOffset * deltaTime;
					raidenRota += raidenRotaOffset * deltaTime;
					raidenTiempo = glfwGetTime();

				}
				else
				{
					if ((glfwGetTime() - raidenTiempo) > 3)
					{
						//printf("02 = %f",raidenRota);
						raiden = !raiden;
					}
				}
			}
			else
			{
				if (raidenSubeBaja > -8.0f)
				{
					raidenSubeBaja -= raidenSubeBajaOffset * deltaTime;
					raidenRota -= raidenRotaOffset * deltaTime;
				}
				else
				{
					//printf("YA NO VUELVE A ENTRAR");
					raidenCont02 += 1;
					cocinado01 = 0;
				}
			}
		}
		// SCORPION
		if (scorpionCont01 >= 1 && scorpionCont02 < 1)
		{
			cocinado02 += 1;
			//printf("ENTRO\n");
			if (scorpion)
			{
				if (scorpionSubeBaja < 11.1f)
				{
					scorpionSubeBaja += scorpionSubeBajaOffset * deltaTime;
					if (scorpionRota <= 360) {
						scorpionRota += scorpionRotaOffset * deltaTime;
					}
					scorpionTiempo = glfwGetTime();

				}
				else
				{
					if ((glfwGetTime() - scorpionTiempo) > 3)
					{
						scorpion = !scorpion;
					}
				}
			}
			else
			{
				if (scorpionSubeBaja > -10.0f)
				{
					scorpionSubeBaja -= scorpionSubeBajaOffset * deltaTime;
					scorpionRota -= scorpionRotaOffset * deltaTime;
				}
				else
				{
					//printf("YA NO VUELVE A ENTRAR");
					scorpionCont02 += 1;
					cocinado02 = 0;
				}
			}
		}
		// SHAO
		if (shaoCont01 >= 1 && shaoCont02 < 1)
		{
			cocinado03 += 1;
			/*printf("ENTRO\n");*/
			if (shao)
			{
				if (shaoSubeBaja < 10.9f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					shaoSubeBaja += shaoSubeBajaOffset * deltaTime;
					if (shaoRota <= 360) {
						shaoRota += hellRotaOffset * deltaTime;
					}
					shaoTiempo = glfwGetTime();

				}
				else
				{
					if ((glfwGetTime() - shaoTiempo) > 3)
					{
						shao = !shao;
					}
				}
			}
			else
			{
				if (shaoSubeBaja > -9.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					shaoSubeBaja -= shaoSubeBajaOffset * deltaTime;
					shaoRota -= shaoRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					shaoCont02 += 1;
					cocinado03 = 0;
				}
			}
		}
		// HELL
		if (hellCont01 >= 1 && hellCont02 < 1)
		{
			cocinado04 += 1;
			/*printf("ENTRO\n");*/
			if (hell)
			{
				if (hellSubeBaja < 9.9f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					hellSubeBaja += hellSubeBajaOffset * deltaTime;
					if (hellRota <= 360) {
						hellRota += hellRotaOffset * deltaTime;
					}
					hellTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", hellRota);*/
					if ((glfwGetTime() - hellTiempo) > 3)
					{
						hell = !hell;
					}
				}
			}
			else
			{
				if (hellSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					hellSubeBaja -= hellSubeBajaOffset * deltaTime;
					hellRota -= hellRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					hellCont02 += 1;
					cocinado04 = 0;
				}
			}
		}
		// VIEWER
		if (viewerCont01 >= 1 && viewerCont02 < 1)
		{
			cocinado05 += 1;
			/*printf("ENTRO\n");*/
			if (viewer)
			{
				if (viewerSubeBaja < 7.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					viewerSubeBaja += viewerSubeBajaOffset * deltaTime;
					if (viewerRota <= 360) {
						viewerRota += viewerRotaOffset * deltaTime;
					}



					viewerTiempo = glfwGetTime();

				}
				else
				{
					//printf("variable rota %f", viewerRota);
					if ((glfwGetTime() - viewerTiempo) > 3)
					{
						viewer = !viewer;
					}
				}
			}
			else
			{
				if (viewerSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					viewerSubeBaja -= viewerSubeBajaOffset * deltaTime;
					viewerRota -= viewerRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					viewerCont02 += 1;
					cocinado05 = 0;
				}
			}
		}
		// TREE_STUMP 
		if (tree_stumpCont01 >= 1 && tree_stumpCont02 < 1)
		{
			cocinado06 += 1;
			/*printf("ENTRO\n");*/
			if (tree_stump)
			{
				if (tree_stumpSubeBaja < 9.55f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					tree_stumpSubeBaja += tree_stumpSubeBajaOffset * deltaTime;
					if (tree_stumpRota <= 360) {
						tree_stumpRota += tree_stumpRotaOffset * deltaTime;
					}



					tree_stumpTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - tree_stumpTiempo) > 3)
					{
						tree_stump = !tree_stump;
					}
				}
			}
			else
			{
				if (tree_stumpSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					tree_stumpSubeBaja -= tree_stumpSubeBajaOffset * deltaTime;
					tree_stumpRota -= tree_stumpRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					tree_stumpCont02 += 1;
					cocinado06 = 0;
				}
			}
		}
		// PINE_TREE
		if (pine_treeCont01 >= 1 && pine_treeCont02 < 1)
		{
			cocinado07 += 1;
			/*printf("ENTRO\n");*/
			if (pine_tree)
			{
				if (pine_treeSubeBaja < 10.7f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					pine_treeSubeBaja += pine_treeSubeBajaOffset * deltaTime;
					if (pine_treeRota <= 360) {
						pine_treeRota += pine_treeRotaOffset * deltaTime;
					}



					pine_treeTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - pine_treeTiempo) > 3)
					{
						pine_tree = !pine_tree;
					}
				}
			}
			else
			{
				if (pine_treeSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					pine_treeSubeBaja -= pine_treeSubeBajaOffset * deltaTime;
					pine_treeRota -= pine_treeRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					pine_treeCont02 += 1;
					cocinado07 = 0;
				}
			}
		}
		// FIRE_DRAGON
		if (fire_dragonCont01 >= 1 && fire_dragonCont02 < 1)
		{
			cocinado08 += 1;
			/*printf("ENTRO\n");*/
			if (fire_dragon)
			{
				if (fire_dragonSubeBaja < 7.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					fire_dragonSubeBaja += fire_dragonSubeBajaOffset * deltaTime;
					if (fire_dragonRota <= 360) {
						fire_dragonRota += fire_dragonRotaOffset * deltaTime;
					}



					fire_dragonTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - fire_dragonTiempo) > 3)
					{
						fire_dragon = !fire_dragon;
					}
				}
			}
			else
			{
				if (fire_dragonSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					fire_dragonSubeBaja -= fire_dragonSubeBajaOffset * deltaTime;
					fire_dragonRota -= fire_dragonRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					fire_dragonCont02 += 1;
					cocinado08 = 0;
				}
			}
		}
		// SCORPION ANIMAL
		if (scorpion2Cont01 >= 1 && scorpion2Cont02 < 1)
		{
			cocinado09 += 1;
			/*printf("ENTRO\n");*/
			if (scorpion2)
			{
				if (scorpion2SubeBaja < 6.9f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					scorpion2SubeBaja += scorpion2SubeBajaOffset * deltaTime;
					if (scorpion2Rota <= 360) {
						scorpion2Rota += scorpion2RotaOffset * deltaTime;
					}



					scorpion2Tiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - scorpion2Tiempo) > 3)
					{
						scorpion2 = !scorpion2;
					}
				}
			}
			else
			{
				if (scorpion2SubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					scorpion2SubeBaja -= scorpion2SubeBajaOffset * deltaTime;
					scorpion2Rota -= scorpion2RotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					scorpion2Cont02 += 1;
					cocinado09 = 0;
				}
			}
		}
		// WOLF
		if (wolfCont01 >= 1 && wolfCont02 < 1)
		{
			cocinado10 += 1;
			/*printf("ENTRO\n");*/
			if (wolf)
			{
				if (wolfSubeBaja < 7.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					wolfSubeBaja += wolfSubeBajaOffset * deltaTime;
					if (wolfRota <= 360) {
						wolfRota += wolfRotaOffset * deltaTime;
					}



					wolfTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - wolfTiempo) > 3)
					{
						wolf = !wolf;
					}
				}
			}
			else
			{
				if (wolfSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					wolfSubeBaja -= wolfSubeBajaOffset * deltaTime;
					wolfRota -= wolfRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					wolfCont02 += 1;
					cocinado10 = 0;
				}
			}
		}
		// BARAKA
		if (BarakaCont01 >= 1 && BarakaCont02 < 1)
		{
			cocinado11 += 1;
			/*printf("ENTRO\n");*/
			if (Baraka)
			{
				if (BarakaSubeBaja < 11.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					BarakaSubeBaja += BarakaSubeBajaOffset * deltaTime;
					if (BarakaRota <= 360) {
						BarakaRota += BarakaRotaOffset * deltaTime;
					}



					BarakaTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - BarakaTiempo) > 3)
					{
						Baraka = !Baraka;
					}
				}
			}
			else
			{
				if (BarakaSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					BarakaSubeBaja -= BarakaSubeBajaOffset * deltaTime;
					BarakaRota -= BarakaRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					BarakaCont02 += 1;
					cocinado11 = 0;
				}
			}
		}
		// BO
		if (boCont01 >= 1 && boCont02 < 1)
		{
			cocinado12 += 1;
			/*printf("ENTRO\n");*/
			if (bo)
			{
				if (boSubeBaja < 9.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					boSubeBaja += boSubeBajaOffset * deltaTime;
					if (boRota <= 360) {
						boRota += boRotaOffset * deltaTime;
					}



					boTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - boTiempo) > 3)
					{
						bo = !bo;
					}
				}
			}
			else
			{
				if (boSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					boSubeBaja -= boSubeBajaOffset * deltaTime;
					boRota -= boRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					boCont02 += 1;
					cocinado12 = 0;
				}
			}
		}
		// CASSIE
		if (cassieCont01 >= 1 && cassieCont02 < 1)
		{
			cocinado13 += 1;
			/*printf("ENTRO\n");*/
			if (cassie)
			{
				if (cassieSubeBaja < 11.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					cassieSubeBaja += cassieSubeBajaOffset * deltaTime;
					if (cassieRota <= 360) {
						cassieRota += cassieRotaOffset * deltaTime;
					}



					cassieTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - cassieTiempo) > 3)
					{
						cassie = !cassie;
					}
				}
			}
			else
			{
				if (cassieSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					cassieSubeBaja -= cassieSubeBajaOffset * deltaTime;
					cassieRota -= cassieRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					cassieCont02 += 1;
					cocinado13 = 0;
				}
			}
		}
		// SKULL
		if (skullCont01 >= 1 && skullCont02 < 1)
		{
			cocinado14 += 1;
			/*printf("ENTRO\n");*/
			if (skull)
			{
				if (skullSubeBaja < 8.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					skullSubeBaja += skullSubeBajaOffset * deltaTime;
					if (skullRota <= 360) {
						skullRota += skullRotaOffset * deltaTime;
					}



					skullTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - skullTiempo) > 3)
					{
						skull = !skull;
					}
				}
			}
			else
			{
				if (skullSubeBaja > -5.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					skullSubeBaja -= skullSubeBajaOffset * deltaTime;
					skullRota -= skullRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					skullCont02 += 1;
					cocinado14 = 0;
				}
			}
		}
		// ROCKY
		if (rockyCont01 >= 1 && rockyCont02 < 1)
		{
			cocinado15 += 1;
			/*printf("ENTRO\n");*/
			if (rocky)
			{
				if (rockySubeBaja < 8.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					rockySubeBaja += rockySubeBajaOffset * deltaTime;
					if (rockyRota <= 360) {
						rockyRota += rockyRotaOffset * deltaTime;
					}

					rockyTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - rockyTiempo) > 3)
					{
						rocky = !rocky;
					}
				}
			}
			else
			{
				if (rockySubeBaja > -5.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					rockySubeBaja -= rockySubeBajaOffset * deltaTime;
					rockyRota -= rockyRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					rockyCont02 += 1;
					cocinado15 = 0;
				}
			}
		}
		// DRNERO
		if (drneoCont01 >= 1 && drneoCont02 < 1)
		{
			cocinado16 += 1;
			/*printf("ENTRO\n");*/
			if (drneo)
			{
				if (drneoSubeBaja < 6.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					drneoSubeBaja += drneoSubeBajaOffset * deltaTime;
					if (drneoRota <= 360) {
						drneoRota += drneoRotaOffset * deltaTime;
					}



					drneoTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - drneoTiempo) > 3)
					{
						drneo = !drneo;
					}
				}
			}
			else
			{
				if (drneoSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					drneoSubeBaja -= drneoSubeBajaOffset * deltaTime;
					drneoRota -= drneoRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					drneoCont02 += 1;
					cocinado16 = 0;
				}
			}
		}
		// FROG
		if (frogCont01 >= 1 && frogCont02 < 1)
		{
			cocinado17 += 1;
			/*printf("ENTRO\n");*/
			if (frog)
			{
				if (frogSubeBaja < 8.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					frogSubeBaja += frogSubeBajaOffset * deltaTime;
					if (frogRota <= 360) {
						frogRota += frogRotaOffset * deltaTime;
					}



					frogTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - frogTiempo) > 3)
					{
						frog = !frog;
					}
				}
			}
			else
			{
				if (frogSubeBaja > -5.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					frogSubeBaja -= frogSubeBajaOffset * deltaTime;
					frogRota -= frogRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					frogCont02 += 1;
					cocinado17 = 0;
				}
			}
		}
		// POLAR
		if (polarCont01 >= 1 && polarCont02 < 1)
		{
			cocinado18 += 1;
			/*printf("ENTRO\n");*/
			if (polar)
			{
				if (polarSubeBaja < 8.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					polarSubeBaja += polarSubeBajaOffset * deltaTime;
					if (polarRota <= 360) {
						polarRota += polarRotaOffset * deltaTime;
					}



					polarTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - polarTiempo) > 3)
					{
						polar = !polar;
					}
				}
			}
			else
			{
				if (polarSubeBaja > -8.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					polarSubeBaja -= polarSubeBajaOffset * deltaTime;
					polarRota -= polarRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					polarCont02 += 1;
					cocinado18 = 0;
				}
			}
		}
		// WIZARD
		if (wizardCont01 >= 1 && wizardCont02 < 1)
		{
			cocinado19 += 1;
			/*printf("ENTRO\n");*/
			if (wizard)
			{
				if (wizardSubeBaja < 8.8f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					wizardSubeBaja += wizardSubeBajaOffset * deltaTime;
					if (wizardRota <= 360) {
						wizardRota += wizardRotaOffset * deltaTime;
					}



					wizardTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - wizardTiempo) > 3)
					{
						wizard = !wizard;
					}
				}
			}
			else
			{
				if (wizardSubeBaja > -11.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					wizardSubeBaja -= wizardSubeBajaOffset * deltaTime;
					wizardRota -= wizardRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					wizardCont02 += 1;
					cocinado19 = 0;
				}
			}
		}
		// PINSTRIPE
		if (pinstripeCont01 >= 1 && pinstripeCont02 < 1)
		{
			cocinado20 += 1;
			/*printf("ENTRO\n");*/
			if (pinstripe)
			{
				if (pinstripeSubeBaja < 10.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					pinstripeSubeBaja += pinstripeSubeBajaOffset * deltaTime;
					if (pinstripeRota <= 360) {
						pinstripeRota += pinstripeRotaOffset * deltaTime;
					}



					pinstripeTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - pinstripeTiempo) > 3)
					{
						pinstripe = !pinstripe;
					}
				}
			}
			else
			{
				if (pinstripeSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					pinstripeSubeBaja -= pinstripeSubeBajaOffset * deltaTime;
					pinstripeRota -= pinstripeRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					pinstripeCont02 += 1;
					cocinado20 = 0;
				}
			}
		}
		// LION
		if (lionCont01 >= 1 && lionCont02 < 1)
		{
			cocinado21 += 1;
			/*printf("ENTRO\n");*/
			if (lion)
			{
				if (lionSubeBaja < 7.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					lionSubeBaja += lionSubeBajaOffset * deltaTime;
					if (lionRota <= 360) {
						lionRota += lionRotaOffset * deltaTime;
					}



					lionTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - lionTiempo) > 3)
					{
						lion = !lion;
					}
				}
			}
			else
			{
				if (lionSubeBaja > -10.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					lionSubeBaja -= lionSubeBajaOffset * deltaTime;
					lionRota -= lionRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					lionCont02 += 1;
					cocinado21 = 0;
				}
			}
		}
		// BABYT
		if (babytCont01 >= 1 && babytCont02 < 1)
		{
			cocinado22 += 1;
			/*printf("ENTRO\n");*/
			if (babyt)
			{
				if (babytSubeBaja < 6.2f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					babytSubeBaja += babytSubeBajaOffset * deltaTime;
					if (babytRota <= 360) {
						babytRota += babytRotaOffset * deltaTime;
					}



					babytTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - babytTiempo) > 3)
					{
						babyt = !babyt;
					}
				}
			}
			else
			{
				if (babytSubeBaja > -10.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					babytSubeBaja -= babytSubeBajaOffset * deltaTime;
					babytRota -= babytRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					babytCont02 += 1;
					cocinado22 = 0;
				}
			}
		}
		// AKUAKU
		if (akuakuCont01 >= 1 && akuakuCont02 < 1)
		{
			cocinado23 += 1;
			/*printf("ENTRO\n");*/
			if (akuaku)
			{
				if (akuakuSubeBaja < 5.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					akuakuSubeBaja += akuakuSubeBajaOffset * deltaTime;
					if (akuakuRota <= 360) {
						akuakuRota += akuakuRotaOffset * deltaTime;
					}



					akuakuTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - akuakuTiempo) > 3)
					{
						akuaku = !akuaku;
					}
				}
			}
			else
			{
				if (akuakuSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					akuakuSubeBaja -= akuakuSubeBajaOffset * deltaTime;
					akuakuRota -= akuakuRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					akuakuCont02 += 1;
					cocinado23 = 0;
				}
			}
		}
		if (palm_treeCont01 >= 1 && palm_treeCont02 < 1)
		{
			cocinado24 += 1;
			/*printf("ENTRO\n");*/
			if (palm_tree)
			{
				if (palm_treeSubeBaja < 8.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					palm_treeSubeBaja += palm_treeSubeBajaOffset * deltaTime;
					if (palm_treeRota <= 360) {
						palm_treeRota += palm_treeRotaOffset * deltaTime;
					}



					palm_treeTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - palm_treeTiempo) > 3)
					{
						palm_tree = !palm_tree;
					}
				}
			}
			else
			{
				if (palm_treeSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					palm_treeSubeBaja -= palm_treeSubeBajaOffset * deltaTime;
					palm_treeRota -= palm_treeRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					palm_treeCont02 += 1;
					cocinado24 = 0;
				}
			}
		}
		// FLOWERS
		if (flowersCont01 >= 1 && flowersCont02 < 1)
		{
			cocinado25 += 1;
			/*printf("ENTRO\n");*/
			if (flowers)
			{
				if (flowersSubeBaja < 7.2f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					flowersSubeBaja += flowersSubeBajaOffset * deltaTime;
					if (flowersRota <= 360) {
						flowersRota += flowersRotaOffset * deltaTime;
					}



					flowersTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - flowersTiempo) > 3)
					{
						flowers = !flowers;
					}
				}
			}
			else
			{
				if (flowersSubeBaja > -12.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					flowersSubeBaja -= flowersSubeBajaOffset * deltaTime;
					flowersRota -= flowersRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					flowersCont02 += 1;
					cocinado25 = 0;
				}
			}
		}
		if (basicCont01 >= 1 && basicCont02 < 1)
		{
			cocinado26 += 1;
			/*printf("ENTRO\n");*/
			if (basic)
			{
				if (basicSubeBaja < 6.2f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					basicSubeBaja += basicSubeBajaOffset * deltaTime;
					if (basicRota <= 360) {
						basicRota += basicRotaOffset * deltaTime;
					}



					basicTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - basicTiempo) > 3)
					{
						basic = !basic;
					}
				}
			}
			else
			{
				if (basicSubeBaja > -10.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					basicSubeBaja -= basicSubeBajaOffset * deltaTime;
					basicRota -= basicRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					basicCont02 += 1;
					cocinado26 = 0;
				}
			}
		}
		// BRIAN
		if (brianCont01 >= 1 && brianCont02 < 1)
		{
			cocinado27 += 1;
			/*printf("ENTRO\n");*/
			if (brian)
			{
				if (brianSubeBaja < 8.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					brianSubeBaja += brianSubeBajaOffset * deltaTime;
					if (brianRota <= 360) {
						brianRota += brianRotaOffset * deltaTime;
					}



					brianTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - brianTiempo) > 3)
					{
						brian = !brian;
					}
				}
			}
			else
			{
				if (brianSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					brianSubeBaja -= brianSubeBajaOffset * deltaTime;
					brianRota -= brianRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					brianCont02 += 1;
					cocinado27 = 0;
				}
			}
		}
		// ERNIE
		if (ernieCont01 >= 1 && ernieCont02 < 1)
		{
			cocinado28 += 1;
			/*printf("ENTRO\n");*/
			if (ernie)
			{
				if (ernieSubeBaja < 10.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					ernieSubeBaja += ernieSubeBajaOffset * deltaTime;
					if (ernieRota <= 360) {
						ernieRota += ernieRotaOffset * deltaTime;
					}



					ernieTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - ernieTiempo) > 3)
					{
						ernie = !ernie;
					}
				}
			}
			else
			{
				if (ernieSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					ernieSubeBaja -= ernieSubeBajaOffset * deltaTime;
					ernieRota -= ernieRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					ernieCont02 += 1;
					cocinado28 = 0;
				}
			}
		}
		// LUISA
		if (luisaCont01 >= 1 && luisaCont02 < 1)
		{
			cocinado29 += 1;
			/*printf("ENTRO\n");*/
			if (luisa)
			{
				if (luisaSubeBaja < 10.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					luisaSubeBaja += luisaSubeBajaOffset * deltaTime;
					if (luisaRota <= 360) {
						luisaRota += luisaRotaOffset * deltaTime;
					}



					luisaTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - luisaTiempo) > 3)
					{
						luisa = !luisa;
					}
				}
			}
			else
			{
				if (luisaSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					luisaSubeBaja -= luisaSubeBajaOffset * deltaTime;
					luisaRota -= luisaRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					luisaCont02 += 1;
					cocinado29 = 0;
				}
			}
		}
		// MEG
		if (megCont01 >= 1 && megCont02 < 1)
		{
			cocinado30 += 1;
			/*printf("ENTRO\n");*/
			if (meg)
			{
				if (megSubeBaja < 10.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					megSubeBaja += megSubeBajaOffset * deltaTime;
					if (megRota <= 360) {
						megRota += megRotaOffset * deltaTime;
					}



					megTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - megTiempo) > 3)
					{
						meg = !meg;
					}
				}
			}
			else
			{
				if (megSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					megSubeBaja -= megSubeBajaOffset * deltaTime;
					megRota -= megRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					megCont02 += 1;
					cocinado30 = 0;
				}
			}
		}
		// PETER
		if (peterCont01 >= 1 && peterCont02 < 1)
		{
			cocinado31 += 1;
			/*printf("ENTRO\n");*/
			if (peter)
			{
				if (peterSubeBaja < 10.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					peterSubeBaja += peterSubeBajaOffset * deltaTime;
					if (peterRota <= 360) {
						peterRota += peterRotaOffset * deltaTime;
					}



					peterTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - peterTiempo) > 3)
					{
						peter = !peter;
					}
				}
			}
			else
			{
				if (peterSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					peterSubeBaja -= peterSubeBajaOffset * deltaTime;
					peterRota -= peterRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					peterCont02 += 1;
					cocinado31 = 0;
				}
			}
		}
		// JOE
		if (joeCont01 >= 1 && joeCont02 < 1)
		{
			cocinado32 += 1;
			/*printf("ENTRO\n");*/
			if (joe)
			{
				if (joeSubeBaja < 10.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					joeSubeBaja += joeSubeBajaOffset * deltaTime;
					if (joeRota <= 360) {
						joeRota += joeRotaOffset * deltaTime;
					}



					joeTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - joeTiempo) > 3)
					{
						joe = !joe;
					}
				}
			}
			else
			{
				if (joeSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					joeSubeBaja -= joeSubeBajaOffset * deltaTime;
					joeRota -= joeRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					joeCont02 += 1;
					cocinado32 = 0;
				}
			}
		}
		// CHRIS
		if (chrisCont01 >= 1 && chrisCont02 < 1)
		{
			cocinado33 += 1;
			/*printf("ENTRO\n");*/
			if (chris)
			{
				if (chrisSubeBaja < -1.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					chrisSubeBaja += chrisSubeBajaOffset * deltaTime;
					if (chrisRota <= 360) {
						chrisRota += chrisRotaOffset * deltaTime;
					}



					chrisTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - chrisTiempo) > 3)
					{
						chris = !chris;
					}
				}
			}
			else
			{
				if (chrisSubeBaja > -20.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					chrisSubeBaja -= chrisSubeBajaOffset * deltaTime;
					chrisRota -= chrisRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					chrisCont02 += 1;
					cocinado33 = 0;
				}
			}
		}
		// CASA
		if (casaCont01 >= 1 && casaCont02 < 1)
		{
			cocinado34 += 1;
			/*printf("ENTRO\n");*/
			if (casa)
			{
				if (casaSubeBaja < 10.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					casaSubeBaja += casaSubeBajaOffset * deltaTime;
					if (casaRota <= 360) {
						casaRota += casaRotaOffset * deltaTime;
					}



					casaTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - casaTiempo) > 3)
					{
						casa = !casa;
					}
				}
			}
			else
			{
				if (casaSubeBaja > -20.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					casaSubeBaja -= casaSubeBajaOffset * deltaTime;
					casaRota -= casaRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					casaCont02 += 1;
					cocinado34 = 0;
				}
			}
		}
		// TREE
		if (treeCont01 >= 1 && treeCont02 < 1)
		{
			cocinado35 += 1;
			/*printf("ENTRO\n");*/
			if (tree)
			{
				if (treeSubeBaja < 10.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					treeSubeBaja += treeSubeBajaOffset * deltaTime;
					if (treeRota <= 360) {
						treeRota += treeRotaOffset * deltaTime;
					}



					treeTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - treeTiempo) > 3)
					{
						tree = !tree;
					}
				}
			}
			else
			{
				if (treeSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					treeSubeBaja -= treeSubeBajaOffset * deltaTime;
					treeRota -= treeRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					treeCont02 += 1;
					cocinado35 = 0;
				}
			}
		}
		// NAVIDAD
		if (navidadCont01 >= 1 && navidadCont02 < 1)
		{
			cocinado36 += 1;
			/*printf("ENTRO\n");*/
			if (navidad)
			{
				if (navidadSubeBaja < 8.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					navidadSubeBaja += navidadSubeBajaOffset * deltaTime;
					if (navidadRota <= 360) {
						navidadRota += navidadRotaOffset * deltaTime;
					}



					navidadTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - navidadTiempo) > 3)
					{
						navidad = !navidad;
					}
				}
			}
			else
			{
				if (navidadSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					navidadSubeBaja -= navidadSubeBajaOffset * deltaTime;
					navidadRota -= navidadRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					navidadCont02 += 1;
					cocinado36 = 0;
				}
			}
		}
		// VINNY
		if (vinnyCont01 >= 1 && vinnyCont02 < 1)
		{
			cocinado37 += 1;
			/*printf("ENTRO\n");*/
			if (vinny)
			{
				if (vinnySubeBaja < 8.5f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					vinnySubeBaja += vinnySubeBajaOffset * deltaTime;
					if (vinnyRota <= 360) {
						vinnyRota += vinnyRotaOffset * deltaTime;
					}



					vinnyTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - vinnyTiempo) > 3)
					{
						vinny = !vinny;
					}
				}
			}
			else
			{
				if (vinnySubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					vinnySubeBaja -= vinnySubeBajaOffset * deltaTime;
					vinnyRota -= vinnyRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					vinnyCont02 += 1;
					cocinado37 = 0;
				}
			}
		}
		// FLOWERS2
		if (flowers2Cont01 >= 1 && flowers2Cont02 < 1)
		{
			cocinado38 += 1;
			/*printf("ENTRO\n");*/
			if (flowers2)
			{
				if (flowers2SubeBaja < 10.0f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					flowers2SubeBaja += flowers2SubeBajaOffset * deltaTime;
					if (flowers2Rota <= 360) {
						flowers2Rota += flowers2RotaOffset * deltaTime;
					}



					flowers2Tiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - flowers2Tiempo) > 3)
					{
						flowers2 = !flowers2;
					}
				}
			}
			else
			{
				if (flowers2SubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					flowers2SubeBaja -= flowers2SubeBajaOffset * deltaTime;
					flowers2Rota -= flowers2RotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					flowers2Cont02 += 1;
					cocinado38 = 0;
				}
			}
		}
		// CARTER
		if (carterCont01 >= 1 && carterCont02 < 1)
		{
			cocinado39 += 1;
			/*printf("ENTRO\n");*/
			if (carter)
			{
				if (carterSubeBaja < 10.6f) //VARIABLE EN LA QUE TIENE QUE SUBIR
				{
					carterSubeBaja += carterSubeBajaOffset * deltaTime;
					if (carterRota <= 360) {
						carterRota += carterRotaOffset * deltaTime;
					}



					carterTiempo = glfwGetTime();

				}
				else
				{
					/*printf("variable rota %f", tree_stumpRota);*/
					if ((glfwGetTime() - carterTiempo) > 3)
					{
						carter = !carter;
					}
				}
			}
			else
			{
				if (carterSubeBaja > -15.5f) //ES LA VARIABLE QUE SE MODIFICO PARA BAJAR EL MODELO
				{
					carterSubeBaja -= carterSubeBajaOffset * deltaTime;
					carterRota -= carterRotaOffset * deltaTime;
				}
				else
				{
					/*printf("YA NO VUELVE A ENTRAR");*/
					carterCont02 += 1;
					cocinado39 = 0;
				}
			}
		}

									// ##################################### ANIMACION DE LOS PERSONAJES DEL EQUIPO ##################################### \\
		// ROTACION DEL BRAZO SUBZERO
		if (subebajaSubZeroBrazo)
		{
			anguloVariaSubzero += 0.5 * deltaTime;
			if (rotaBrazoSubZero < 135.0f )
			{
				rotaBrazoSubZero += rotaBrazoDOffset * deltaTime;
			}
			else
			{
				subebajaSubZeroBrazo = !subebajaSubZeroBrazo;
			}
		}
		else
		{
			anguloVariaSubzero += 0.5 * deltaTime;
			if (rotaBrazoSubZero > 0.0f)
			{
				rotaBrazoSubZero -= rotaBrazoDOffset * deltaTime;
			}
			else
			{
				subebajaSubZeroBrazo = !subebajaSubZeroBrazo;
			}
		}

		// ROTACION DE CRASH
		if (rotaCrash <= 0)
		{
			rotaCrash -= rotaCrashOffset * deltaTime;
			anguloVariaCrash += 0.5 * deltaTime;
		}


		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

								// ##################################### CONTROL LUZ DIRECCIONAL ##################################### 
		glm::vec3 sunDirection;
		FaseDia = now - dianocheTiempo;

		if (FaseDia < totalDia) {
			auxLight = &mainLight;
			skyboxDia.DrawSkybox(currentCamera->calculateViewMatrix(), projection);
			esNoche = false;
			esDia = true;

			//Simulando el sol de este a oeste
			angle = (FaseDia / totalDia) *2.0f * pi;
			sunDirection = glm::vec3(cos(angle), -sin(angle), 0.0f);
			intensidad = 0.8f; //Maxima intensidad durante el día
			mainLight.SetDirection(sunDirection);
			mainLight.SetIntensity(0.5f);
			mainLight.SetAmbientIntensity(0.5f);
			
		}
		else if (FaseDia < (totalDia + atardecer)) {
			auxLight = &mainLight;
			skyboxDia.DrawSkybox(currentCamera->calculateViewMatrix(), projection);

			// Disminuimos la intensidad gradualmente
			float atardecerProgress = (FaseDia - totalDia) / atardecer; // Progreso de 0 a 1 durante el atardecer
			// Asegúrate de que la intensidad no baje de 0.1f
			float minIntensity = 0.1f; // Intensidad mínima
			float maxIntensity = 0.5f; // Intensidad máxima
			   // Ajusta la intensidad

			// Actualiza la dirección del sol
			sunDirection = glm::vec3(cos(pi) * (1.0f - atardecerProgress), -sin(pi) * (1.0f - atardecerProgress), 0.0f);
			adjustedIntensity = maxIntensity - (maxIntensity - minIntensity) * atardecerProgress;
			if (adjustedIntensity < 0.2f)
			{
				adjustedIntensity = 0.2f;
				skyboxNoche.DrawSkybox(currentCamera->calculateViewMatrix(), projection);
				esNoche = true;
				esDia = false;
			}
			mainLight.SetDirection(sunDirection);
			mainLight.SetIntensity(adjustedIntensity);
			mainLight.SetAmbientIntensity(adjustedIntensity); // También ajustamos la intensidad ambiental
		}
		else if(FaseDia<ciclototal){
			
			//printf("Estoy entrando");
			/*auxLight = &mainLight2;*/
			skyboxNoche.DrawSkybox(currentCamera->calculateViewMatrix(), projection);
			mainLight.SetIntensity(0.2f);
			mainLight.SetAmbientIntensity(0.2f); // También ajustamos la intensidad ambiental
			
		}
		else {
			dianocheTiempo = glfwGetTime();
		}

		/*	if ((glfwGetTime() - dianocheTiempo) < 120)
		{

			skyboxDia.DrawSkybox(camera.calculateViewMatrix(), projection);
			mainLight.SetDirection(sunDirection);
		}
		else if ((glfwGetTime() - dianocheTiempo) < 240)
		{
			auxLight = &mainLight2;
			skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else
		{
			dianocheTiempo = glfwGetTime();
		}*/

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

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
		/*spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());*/

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

											// ##################################### MATRICES AUXILIAR ##################################### \\

		// MATRIZ AUXILIAR PARA LAS CASILLAS
		glm::mat4 modelauxCasillas(1.0);

		// MATRIZ AUXILIAR PARA EL AVATAR DE RECORRIDO (SUBZERO)
		glm::mat4 modelauxTorso(1.0);
		glm::mat4 modelauxBrazoDerecho(1.0);
		glm::mat4 modelauxBrazoIzquierdo(1.0);
		glm::mat4 modelauxCintura(1.0);
		glm::mat4 modelauxPiernaDerecha(1.0);
		glm::mat4 modelauxPiernaIzquierda(1.0);

		// MTRAIZ AUXILIAR PARA LA ANIMACION DE LOS PERSONAJES
		glm::mat4 modelauxSubZeroAnimacion(1.0);
		glm::mat4 modelauxSubZeroBrazoAnimacion(1.0);

		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();
		
											// ##################################### DADOS ##################################### \\

		// DADO DE 4 CARAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, subeBajaDado4, 20.0));
		// ANIMACION DEL DADO
		model = glm::rotate(model, rotaDadox4 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotaDadoy4 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dado4CarasM.RenderModel();

		// DADO DE 8 CARAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, subeBajaDado8, -20.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		// ANIMACION DEL DADO
		model = glm::rotate(model, rotaDadox8 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotaDadoz8 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, rotaDadoy8 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dado8CarasM.RenderModel();

											// ##################################### CASILLAS ##################################### \\

		// CASILLAS 
		model = glm::mat4(1.0);

		// 1
		model = glm::translate(model, glm::vec3(-100.0f, 0.3f, 100.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (esDia)
		{
			casilla01A.RenderModel();
		}
		else if (esNoche)
		{
			casilla01M.RenderModel();
		}
		/*else
		{
			dianocheTiempo = glfwGetTime();
		}*/

		//casilla01A.RenderModel(); // Amarillo
		//casilla01M.RenderModel(); // Azul
		//casilla01AR.RenderModel(); // Cocinadas


		model = modelauxCasillas; // A PARTIR DE 

		// 2
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));
		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado01 >= 1)
		{
			casilla02AR.RenderModel();
		}

		if (esDia)
		{
			casilla02A.RenderModel();
		}
		else if (esNoche)
		{
			casilla02M.RenderModel();
		}


		//casilla02M.RenderModel();
		//casilla02A.RenderModel();
		//casilla02AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 3
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado02 >= 1)
		{
			casilla03AR.RenderModel();
		}

		if (esDia)
		{
			casilla03A.RenderModel();
		}
		else if (esNoche)
		{
			casilla03M.RenderModel();
		}

		//casilla03M.RenderModel();
		//casilla03A.RenderModel();
		//casilla03AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 4
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado03 >= 1)
		{
			casilla04AR.RenderModel();
		}

		if (esDia)
		{
			casilla04A.RenderModel();
		}
		else if (esNoche)
		{
			casilla04M.RenderModel();
		}

		//casilla04M.RenderModel();
		//casilla04A.RenderModel();
		//casilla04AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 5
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado04 >= 1)
		{
			casilla05AR.RenderModel();
		}

		if (esDia)
		{
			casilla05A.RenderModel();
		}
		else if (esNoche)
		{
			casilla05M.RenderModel();
		}

		//casilla05M.RenderModel();
		//casilla05A.RenderModel();
		//casilla05AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 6
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado05 >= 1)
		{
			casilla06AR.RenderModel();
		}

		if (esDia)
		{
			casilla06A.RenderModel();
		}
		else if (esNoche)
		{
			casilla06M.RenderModel();
		}

		//casilla06M.RenderModel();
		//casilla06A.RenderModel();
		//casilla06AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 7
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado06 >= 1)
		{
			casilla07AR.RenderModel();
		}

		if (esDia)
		{
			casilla07A.RenderModel();
		}
		else if (esNoche)
		{
			casilla07M.RenderModel();
		}


		//casilla07M.RenderModel();
		//casilla07A.RenderModel();
		//casilla07AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 8
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado07 >= 1)
		{
			casilla08AR.RenderModel();
		}

		if (esDia)
		{
			casilla08A.RenderModel();
		}
		else if (esNoche)
		{
			casilla08M.RenderModel();
		}


		//casilla08M.RenderModel();
		//casilla08A.RenderModel();
		//casilla08AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 9
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado08 >= 1)
		{
			casilla09AR.RenderModel();
		}


		if (esDia)
		{
			casilla09A.RenderModel();
		}
		else if (esNoche)
		{
			casilla09M.RenderModel();
		}

		//casilla09M.RenderModel();
		//casilla09A.RenderModel();
		//casilla09AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 10
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado09 >= 1)
		{
			casilla10AR.RenderModel();
		}

		if (esDia)
		{
			casilla10A.RenderModel();
		}
		else if (esNoche)
		{
			casilla10M.RenderModel();
		}


		//casilla10M.RenderModel();
		//casilla10A.RenderModel();
		//casilla10AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 11
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado10 >= 1)
		{
			casilla11AR.RenderModel();
		}

		if (esDia)
		{
			casilla11A.RenderModel();
		}
		else if (esNoche)
		{
			casilla11M.RenderModel();
		}

		//casilla11M.RenderModel();
		//casilla11A.RenderModel();
		//casilla11AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 12
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado11 >= 1)
		{
			casilla12AR.RenderModel();
		}

		if (esDia)
		{
			casilla12A.RenderModel();
		}
		else if (esNoche)
		{
			casilla12M.RenderModel();
		}


		//casilla12M.RenderModel();
		//casilla12A.RenderModel();
		//casilla12AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 13
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado12 >= 1)
		{
			casilla13AR.RenderModel();
		}

		if (esDia)
		{
			casilla13A.RenderModel();
		}
		else if (esNoche)
		{
			casilla13M.RenderModel();
		}

		//casilla13M.RenderModel();
		//casilla13A.RenderModel();
		//casilla13AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 14
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado13 >= 1)
		{
			casilla14AR.RenderModel();
		}

		if (esDia)
		{
			casilla14A.RenderModel();
		}
		else if (esNoche)
		{
			casilla14M.RenderModel();
		}


		//casilla14M.RenderModel();
		//casilla14A.RenderModel();
		//casilla14AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 15
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));
		/*model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado14 >= 1)
		{
			casilla15AR.RenderModel();
		}


		if (esDia)
		{
			casilla15A.RenderModel();
		}
		else if (esNoche)
		{
			casilla15M.RenderModel();
		}

		//casilla15M.RenderModel();
		//casilla15A.RenderModel();
		//casilla15AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 16
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado15 >= 1)
		{
			casilla16AR.RenderModel();
		}

		if (esDia)
		{
			casilla16A.RenderModel();
		}
		else if (esNoche)
		{
			casilla16M.RenderModel();
		}

		//casilla16M.RenderModel();
		//casilla16A.RenderModel();
		//casilla16AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 17
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado16 >= 1)
		{
			casilla17AR.RenderModel();
		}

		if (esDia)
		{
			casilla17A.RenderModel();
		}
		else if (esNoche)
		{
			casilla17M.RenderModel();
		}

		//casilla17M.RenderModel();
		//casilla17A.RenderModel();
		//casilla17AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 18
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado17 >= 1)
		{
			casilla18AR.RenderModel();
		}

		if (esDia)
		{
			casilla18A.RenderModel();
		}
		else if (esNoche)
		{
			casilla18M.RenderModel();
		}

		//casilla18M.RenderModel();
		//casilla18A.RenderModel();
		//casilla18AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 19
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado18 >= 1)
		{
			casilla19AR.RenderModel();
		}

		if (esDia)
		{
			casilla19A.RenderModel();
		}
		else if (esNoche)
		{
			casilla19M.RenderModel();
		}

		//casilla19M.RenderModel();
		//casilla19A.RenderModel();
		//casilla19AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 20
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));
		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado19 >= 1)
		{
			casilla20AR.RenderModel();
		}

		if (esDia)
		{
			casilla20A.RenderModel();
		}
		else if (esNoche)
		{
			casilla20M.RenderModel();
		}

		//casilla20M.RenderModel();
		//casilla20A.RenderModel();
		//casilla20AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 21
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 20.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado20 >= 1)
		{
			casilla21AR.RenderModel();
		}

		if (esDia)
		{
			casilla21A.RenderModel();
		}
		else if (esNoche)
		{
			casilla21M.RenderModel();
		}

		//casilla21M.RenderModel();
		//casilla21A.RenderModel();
		//casilla21AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 22
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado21 >= 1)
		{
			casilla22AR.RenderModel();
		}

		if (esDia)
		{
			casilla22A.RenderModel();
		}
		else if (esNoche)
		{
			casilla22M.RenderModel();
		}

		//casilla22M.RenderModel();
		//casilla22A.RenderModel();
		//casilla22AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 23
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado22 >= 1)
		{
			casilla23AR.RenderModel();
		}

		if (esDia)
		{
			casilla23A.RenderModel();
		}
		else if (esNoche)
		{
			casilla23M.RenderModel();
		}

		//casilla23M.RenderModel();
		//casilla23A.RenderModel();
		//casilla23AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 24
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado23 >= 1)
		{
			casilla24AR.RenderModel();
		}

		if (esDia)
		{
			casilla24A.RenderModel();
		}
		else if (esNoche)
		{
			casilla24M.RenderModel();
		}

		//casilla24M.RenderModel();
		//casilla24A.RenderModel();
		//casilla24AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 25
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado24 >= 1)
		{
			casilla25AR.RenderModel();
		}

		if (esDia)
		{
			casilla25A.RenderModel();
		}
		else if (esNoche)
		{
			casilla25M.RenderModel();
		}

		//casilla25M.RenderModel();
		//casilla25A.RenderModel();
		//casilla25AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 26
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado25 >= 1)
		{
			casilla26AR.RenderModel();
		}

		if (esDia)
		{
			casilla26A.RenderModel();
		}
		else if (esNoche)
		{
			casilla26M.RenderModel();
		}

		//casilla26M.RenderModel();
		//casilla26A.RenderModel();
		//casilla26AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 27
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado26 >= 1)
		{
			casilla27AR.RenderModel();
		}


		if (esDia)
		{
			casilla27A.RenderModel();
		}
		else if (esNoche)
		{
			casilla27M.RenderModel();
		}
		//casilla27M.RenderModel();
		//casilla27A.RenderModel();
		//casilla27AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 28
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));
		/*model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado27 >= 1)
		{
			casilla28AR.RenderModel();
		}


		if (esDia)
		{
			casilla28A.RenderModel();
		}
		else if (esNoche)
		{
			casilla28M.RenderModel();
		}
		//casilla28M.RenderModel();
		//casilla28A.RenderModel();
		//casilla28AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 29
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado28 >= 1)
		{
			casilla29AR.RenderModel();
		}

		if (esDia)
		{
			casilla29A.RenderModel();
		}
		else if (esNoche)
		{
			casilla29M.RenderModel();
		}

		//casilla29M.RenderModel();
		//casilla29A.RenderModel();
		//casilla29AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 30
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado29 >= 1)
		{
			casilla30AR.RenderModel();
		}


		if (esDia)
		{
			casilla30A.RenderModel();
		}
		else if (esNoche)
		{
			casilla30M.RenderModel();
		}

		//casilla30M.RenderModel();
		//casilla30A.RenderModel();
		//casilla30AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 31
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 0.0));

		modelauxCasillas = model; // GUARDA

		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado30 >= 1)
		{
			casilla31AR.RenderModel();
		}

		if (esDia)
		{
			casilla31A.RenderModel();
		}
		else if (esNoche)
		{
			casilla31M.RenderModel();
		}

		//casilla31M.RenderModel();
		//casilla31A.RenderModel();
		//casilla31AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 32
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado31 >= 1)
		{
			casilla32AR.RenderModel();
		}

		if (esDia)
		{
			casilla32A.RenderModel();
		}
		else if (esNoche)
		{
			casilla32M.RenderModel();
		}

		//casilla32M.RenderModel();
		//casilla32A.RenderModel();
		//casilla32AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 33
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado32 >= 1)
		{
			casilla33AR.RenderModel();
		}

		if (esDia)
		{
			casilla33A.RenderModel();
		}
		else if (esNoche)
		{
			casilla33M.RenderModel();
		}

		//casilla33M.RenderModel();
		//casilla33A.RenderModel();
		//casilla33AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 34
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado33 >= 1)
		{
			casilla34AR.RenderModel();
		}

		if (esDia)
		{
			casilla34A.RenderModel();
		}
		else if (esNoche)
		{
			casilla34M.RenderModel();
		}

		//casilla34M.RenderModel();
		//casilla34A.RenderModel();
		//casilla34AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 35
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado34 >= 1)
		{
			casilla35AR.RenderModel();
		}

		if (esDia)
		{
			casilla35A.RenderModel();
		}
		else if (esNoche)
		{
			casilla35M.RenderModel();
		}

		//casilla35M.RenderModel();
		//casilla35A.RenderModel();
		//casilla35AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 36
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado35 >= 1)
		{
			casilla36AR.RenderModel();
		}

		if (esDia)
		{
			casilla36A.RenderModel();
		}
		else if (esNoche)
		{
			casilla36M.RenderModel();
		}

		//casilla36M.RenderModel();
		//casilla36A.RenderModel();
		//casilla36AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 37
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado36 >= 1)
		{
			casilla37AR.RenderModel();
		}

		if (esDia)
		{
			casilla37A.RenderModel();
		}
		else if (esNoche)
		{
			casilla37M.RenderModel();
		}

		//casilla37M.RenderModel();
		//casilla37A.RenderModel();
		//casilla37AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 38
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado37 >= 1)
		{
			casilla38AR.RenderModel();
		}

		if (esDia)
		{
			casilla38A.RenderModel();
		}
		else if (esNoche)
		{
			casilla38M.RenderModel();
		}

		//casilla38M.RenderModel();
		//casilla38A.RenderModel();
		//casilla38AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 39
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado38 >= 1)
		{
			casilla39AR.RenderModel();
		}

		if (esDia)
		{
			casilla39A.RenderModel();
		}
		else if (esNoche)
		{
			casilla39M.RenderModel();
		}

		//casilla39M.RenderModel();
		//casilla39A.RenderModel();
		//casilla39AR.RenderModel();

		model = modelauxCasillas; // A PARTIR DE 

		// 40
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0));

		modelauxCasillas = model; // GUARDA
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		if (cocinado39 >= 1)
		{
			casilla40AR.RenderModel();
		}

		if (esDia)
		{
			casilla40A.RenderModel();
		}
		else if (esNoche)
		{
			casilla40M.RenderModel();
		}

											// ##################################### MODELOS DE LAS CASILLAS ##################################### \\

		// RAIDEN - CASILLA 02
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, /*9.9f*/raidenSubeBaja, 80.0)); //EN EL TRANSLATE DE Y SE CAMBIA POR EL NOMBRE DE LA VARIABLE
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -raidenRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); //SE LE AUMENTA EL ROUTETE DONDE SE PONE ROTA EN TODAS VA EL -
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla01M.RenderModel();

		// SCORPION - CASILLA 03
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f,/* 10.1f*/scorpionSubeBaja, 60.0));
		model = glm::rotate(model, -scorpionRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla02M.RenderModel();

		// SHAO KAHN - CASILLA 04
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, /*9.9f*/shaoSubeBaja, 40.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -shaoRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla03M.RenderModel();

		// HELL MOUNTAIN - CASILLA 05
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, /*4.4f*/hellSubeBaja, 20.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -hellRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla04M.RenderModel();

		// VIEWER - CASILLA 06
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, /*5.5f*/viewerSubeBaja, 0.0));
		model = glm::rotate(model, -viewerRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla05M.RenderModel();

		// TREE STUMP - CASILLA 07
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, /*8.55f*/tree_stumpSubeBaja, -20.0));
		model = glm::rotate(model, -tree_stumpRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla06M.RenderModel();

		// PINE TREE - CASILLA 08
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, /*9.7f*/pine_treeSubeBaja, -40.0));
		model = glm::rotate(model, -pine_treeRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla07M.RenderModel();

		// FIRE DRAGON - CASILLA 09
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f, /*6.0f*/fire_dragonSubeBaja, -55.0));
		model = glm::rotate(model, -fire_dragonRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla08M.RenderModel();

		// SCORPION - CASILLA 10
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-120.0f,/* 5.9f*/scorpion2SubeBaja, -80.0));
		model = glm::rotate(model, -scorpion2Rota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla09M.RenderModel();



		// WOLF - CASILLA 11
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-100.0f, /*5.9f*/wolfSubeBaja, -120.0));
		model = glm::rotate(model, -wolfRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla11M.RenderModel();

		// BARAKA - CASILLA 12
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-80.0f, /*10.0f*/BarakaSubeBaja, -120.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -BarakaRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.5f, 8.5f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla12M.RenderModel();

		// BO RAI CHO - CASILLA 13
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-60.0f, /*8.5f*/boSubeBaja, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -boRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla13M.RenderModel();

		// CASSIE CAGE - CASILLA 14
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-40.0f, /*10.0f*/cassieSubeBaja, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -cassieRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.5f, 8.5f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla14M.RenderModel();

		// SKULL - CASILLA 15
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-20.0f, /*2.0f*/skullSubeBaja, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -skullRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.325f, 0.325f, 0.325f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla15M.RenderModel();

		// ROCKY ROAD - CASILLA 16
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, /*2.0f*/rockySubeBaja, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -rockyRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.325f, 0.325f, 0.325f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla16M.RenderModel();

		// NEOCORTEX - CASILLA 17
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(20.0f, /*4.0f*/drneoSubeBaja, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -drneoRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla17M.RenderModel();

		// FROG - CASILLA 18
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(40.0f, /*2.0f*/frogSubeBaja, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -frogRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla18M.RenderModel();

		// POLAR - CASILLA 19
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(60.0f, /*5.0f*/polarSubeBaja, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -polarRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.16f, 0.16f, 0.16f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla19M.RenderModel();

		// WIZARD - CASILLA 20
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(80.0f, /*6.8f*/wizardSubeBaja, -120.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -wizardRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.18f, 0.18f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla20M.RenderModel();

		// PINSTRIPE - CASILLA 21
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, /*pinstripe*/pinstripeSubeBaja, -100.0));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -pinstripeRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla21M.RenderModel();

		// LION - CASILLA 22
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, /*6.0f*/lionSubeBaja, -80.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -lionRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla22M.RenderModel();

		// BABY T - CASILLA 23
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, /*5.2f*/babytSubeBaja, -60.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -babytRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla23M.RenderModel();

		// AKU AKU - CASILLA 24
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, /*4.0f*/akuakuSubeBaja, -40.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -akuakuRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla24M.RenderModel();

		// PALM_TREE - CASILLA 25
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, /*6.0f*/palm_treeSubeBaja, -20.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -palm_treeRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla25M.RenderModel();

		// FLOWERS - CASILLA 26
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, /*4.2f*/flowersSubeBaja, 0.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -flowersRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla26M.RenderModel();

		// BASIC_TREE - CASILLA 27
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(120.0f, /*5.2f*/basicSubeBaja, 20.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -basicRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		modeloCasilla27M.RenderModel();

		//Brian - Casilla28
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, /*7.5f*/brianSubeBaja, 40.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -brianRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla28.RenderModel();

		//Ernie - Casilla29
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(124.0f, /*9.5f*/ernieSubeBaja, 60.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -ernieRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla29.RenderModel();

		//Lois - Casilla30
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, /*9.5f*/luisaSubeBaja, 80.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -luisaRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla30.RenderModel();

		//Meg - Casilla31
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, /*9.0f*/megSubeBaja, 120.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -megRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla31.RenderModel();

		//Peter - Casilla32
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, /*9.0f*/peterSubeBaja, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -peterRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla32.RenderModel();

		//Joe - Casilla33
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, /*9.0f*/joeSubeBaja, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -joeRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla33.RenderModel();

		//Chris - Casilla34
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, /*-1.0f*/chrisSubeBaja, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -chrisRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla34.RenderModel();

		//Drunken - Casilla35
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, /*4.5f*/casaSubeBaja, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -casaRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla35.RenderModel();

		//Arbol - Casilla36
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, /*9.5f*/treeSubeBaja, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -treeRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla36.RenderModel();

		//Arbol Navidad - Casilla37
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, /*7.0f*/navidadSubeBaja, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -navidadRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla37.RenderModel();

		//Vinny - Casilla38
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, /*7.5f*/vinnySubeBaja, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -vinnyRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla38.RenderModel();

		//Flores - Casilla39
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, /*7.0f*/flowers2SubeBaja, 125.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -flowers2Rota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla39.RenderModel();

		//Carter - Casilla40
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, /*9.6f*/carterSubeBaja, 120.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -carterRota * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ModeloCasilla40.RenderModel();

											// ##################################### SUBZERO AVATAR ##################################### \\

		// AVATAR SUB ZERO PARA RECORRIDO
		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(-100.0f, 19.8f, 100.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		// RECORRIDO AVATAR
		// EL PRIMER TRANSLATE (HASTA LLEGAR A UNA PARTE)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mueveAvatar01));
		model = glm::rotate(model, rotaAvatar01 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		// RECORRIDO AVATAR
		// EL PRIMER TRANSLATE (HASTA LLEGAR A UNA PARTE)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mueveAvatar02));
		model = glm::rotate(model, rotaAvatar02 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		// RECORRIDO AVATAR
		// EL PRIMER TRANSLATE (HASTA LLEGAR A UNA PARTE)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mueveAvatar03));
		model = glm::rotate(model, rotaAvatar03 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		// RECORRIDO AVATAR
		// EL PRIMER TRANSLATE (HASTA LLEGAR A UNA PARTE)
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mueveAvatar04));
		model = glm::rotate(model, rotaAvatar04 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));


		modelauxTorso = model; // GUARDA TORSO

		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		torsoSubZero.RenderModel();

		model = modelauxTorso; // A PARTIR DE TORSO

		// LUZ LIGADA AL PERSONAJE
		glm::vec3 posicion = glm::vec3(model[3]);
		glm::vec3 direccion = glm::vec3(model[2]);

		if (esNoche)
		{
			spotLights[1].SetFlash(posicion, direccion);
		}

		model = glm::translate(model, glm::vec3(-3.5f, 2.0f, -0.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		modelauxBrazoDerecho = model; // GUARDA BRAZO DERECHO

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxBrazoDerecho; // A PARTIR DE BRAZO DERECHO

		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.1f));
		model = glm::rotate(model, -rotaBrazoD * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoDerechoSubZero.RenderModel();

		model = modelauxTorso; // A PARTIR DE TORSO

		model = glm::translate(model, glm::vec3(3.5f, 2.0f, -0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		modelauxBrazoIzquierdo = model; // GUARDA BRAZO IZQUIERDO

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxBrazoIzquierdo; // A PARTIR DE BRAZO IZQUIERDO

		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.1f));
		model = glm::rotate(model, rotaBrazoI * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brazoIzquieroSubZero.RenderModel();

		model = modelauxTorso; // A PARTIR DE TORSO

		model = glm::translate(model, glm::vec3(0.0f, -5.0f, 0.0f));

		modelauxCintura = model; // GUARDA CINTURA

		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cinturaSubZero.RenderModel();

		model = modelauxCintura; //  PARTIR DE LA CINTURA

		model = glm::translate(model, glm::vec3(-1.3f, -1.5f, 0.0f));

		modelauxPiernaDerecha = model; // GUARDA PIERNA DERECHA

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxPiernaDerecha; // A PARTIR DE LA PIERNA DERECHA

		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		model = glm::rotate(model, rotaPiernaD * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piernaDerechaSubZero.RenderModel();

		model = modelauxCintura; //  PARTIR DE LA CINTURA

		model = glm::translate(model, glm::vec3(1.3f, -1.5f, 0.0f));

		modelauxPiernaIzquierda = model; // GUARDA PIERNA IZQUIERDA

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxPiernaIzquierda; // A PARTIR DE LA PIERNA IZQUIERDA

		model = glm::translate(model, glm::vec3(0.0f, 0.3f, 0.0f));
		model = glm::rotate(model, rotaPiernaI * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		piernaIzquierdaSubZero.RenderModel();

											// ##################################### MODELOS DE ANIMACIONES ##################################### \\

		// SUBZERO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f + (1.0 * sin(glm::radians(anguloVariaSubzero * 10))),
												14.0f, 
												-10.0 +(1.0 * cos(glm::radians(anguloVariaSubzero * 10)))));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		modelauxSubZeroAnimacion = model; // GUARDA

		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		subZeroAnimacion.RenderModel();

		model = modelauxSubZeroAnimacion; // A PARTIR DEL CUERPO 

		model = glm::translate(model, glm::vec3(-2.3f, 4.2f, -0.2f));
		model = glm::rotate(model, rotaBrazoSubZero * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		modelauxSubZeroBrazoAnimacion = model; // GUARDA ARTICULACION

		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esfera.RenderModel();

		model = modelauxSubZeroBrazoAnimacion; //  A PARTIR DE LA ARTICULACION

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		scorpionCabeza.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 5.0f, -20.0));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		scorpionCuerpo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 2.0f, -10.0));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		baseSubzero.RenderModel();

		// CRASH
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-15.0f + (10.0 * sin(anguloVariaCrash) * cos(anguloVariaCrash)) / (10.0 + sin(anguloVariaCrash) * sin(anguloVariaCrash)) 
												, 6.3f, 
												-45.0 + (10.0 * cos(anguloVariaCrash)) / (10.0 + sin(anguloVariaCrash) * sin(anguloVariaCrash)) ));
		model = glm::rotate(model, rotaCrash * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		crashAnimacion.RenderModel();

											// ##################################### TRANSFORMACION ##################################### \\

		if ((glfwGetTime() - tiempoTransformacion) < 10)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-210.0f, 10.1f, 0.0));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			scorpionOriginal.RenderModel();
		}
		else if ((glfwGetTime() - tiempoTransformacion) < 20)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-210.0f, 10.1f, 0.0));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			scorpionOriginal.RenderModel();

			if (escala01 < 50 && escala02 < 50 && escala03 < 50)
			{
				escala01 += escala01Offset * deltaTime;
				escala02 += escala02Offset * deltaTime;
				escala03 += escala03Offset * deltaTime;
			}
		}
		else if ((glfwGetTime() - tiempoTransformacion) < 30)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-210.0f, 10.1f, 0.0));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			scorpionTransformacion.RenderModel();

			if (escala01 > 0 && escala02 > 0 && escala03 > 0)
			{
				escala01 -= escala01Offset * deltaTime;
				escala02 -= escala02Offset * deltaTime;
				escala03 -= escala03Offset * deltaTime;
			}
		}
		else if ((glfwGetTime() - tiempoTransformacion) < 40)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-210.0f, 10.1f, 0.0));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			scorpionTransformacion.RenderModel();
		}
		else if ((glfwGetTime() - tiempoTransformacion) < 50)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-210.0f, 10.1f, 0.0));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			scorpionTransformacion.RenderModel();

			if (escala01 < 50 && escala02 < 50 && escala03 < 50)
			{
				escala01 += escala01Offset * deltaTime;
				escala02 += escala02Offset * deltaTime;
				escala03 += escala03Offset * deltaTime;
			}
		}
		else if ((glfwGetTime() - tiempoTransformacion) < 60)
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-210.0f, 10.1f, 0.0));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			scorpionOriginal.RenderModel();

			if (escala01 > 0 && escala02 > 0 && escala03 > 0)
			{
				escala01 -= escala01Offset * deltaTime;
				escala02 -= escala02Offset * deltaTime;
				escala03 -= escala03Offset * deltaTime;
			}
		}
		else
		{
			tiempoTransformacion = glfwGetTime();
		}

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-210.0f, 10.1f, 0.0));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(escala01, escala02, escala03));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		fireball.RenderModel();

												// ##################################### CARRO ##################################### \\

		//CARROS CARRETERA

		model = glm::mat4(1.0);

		if (!enMovimientoX && !enMovimientoZ) {
			if (mueveCarro < 320) {
				// Movimiento en el primer tramo (en el eje X)
				mueveCarro += mueveCarroOffset * deltaTime;

				// Actualiza la posición del modelo
				model = glm::translate(glm::mat4(1.0f), glm::vec3(-160.0f + mueveCarro, 0.0f, 160.0f));
				model = glm::rotate(model, glm::radians(giraCarro), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else {
				// Solo entra en la curva una vez
				if (!enCurva) {
					enCurva = true;
				}

				if (giraCarro < giraCarroTarget) { // Rota hasta alcanzar el ángulo objetivo
					giraCarro += 1.0f * deltaTime;

					mueveCarro += curvaCarroOffset * deltaTime;

					// Calcular el vector de dirección
					float radians = glm::radians(giraCarro);
					glm::vec3 direccion;
					direccion.x = cos(radians);
					direccion.z = sin(radians);

					// Actualiza la posición del modelo durante la curva
					model = glm::translate(glm::mat4(1.0f), glm::vec3(-160.0f + mueveCarro, 0.0f, 160.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(giraCarro), glm::vec3(0.0f, 1.0f, 0.0f));
				}
				else {
					giraCarro = giraCarroTarget;
					enCurva = false;

					if (mueveCarro2 < 320) {
						mueveCarro2 += mueveCarroOffset * deltaTime;
						model = glm::translate(glm::mat4(1.0f), glm::vec3(-160.0f + mueveCarro, 0.0f, 160.0f - mueveCarro2)) * glm::rotate(glm::mat4(1.0f), glm::radians(giraCarro), glm::vec3(0.0f, 1.0f, 0.0f));
					}
					else {
						enMovimientoX = true;
						mueveCarro2 = 320.0f;
						giraCarro = giraCarroTarget;
					}
				}
			}
		}
		else if (enMovimientoX) {
			//printf("Estado de enMovimientoX: %d, mueveCarro2: %f\n", enMovimientoZ, mueveCarro2);

			if (!enCurva) {
				enCurva = true;
			}

			if (giraCarro < giraCarroTargetX) {
				giraCarro += 1.0f * deltaTime;
				if (giraCarro > giraCarroTargetX) {
					giraCarro = giraCarroTargetX;
				}
				float radians = glm::radians(giraCarro);
				model = glm::translate(glm::mat4(1.0f), glm::vec3(-160.0f + mueveCarro, 0.0f, -160.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(giraCarro), glm::vec3(0.0f, 1.0f, 0.0f));

				//printf("Durante curva -> mueveCarro: %f, giraCarro: %f\n", mueveCarro, giraCarro);
			}

			// Cambia al movimiento en Z positivo cuando llega a -160 en X
			if (giraCarro >= giraCarroTargetX) {
				if (mueveCarro > 0) { // Mover en X negativo hasta alcanzar -160
					mueveCarro -= mueveCarroOffset * deltaTime;
					model = glm::translate(glm::mat4(1.0f), glm::vec3(-160.0f + mueveCarro, 0.0f, -160.0f)) *
						glm::rotate(glm::mat4(1.0f), glm::radians(giraCarro), glm::vec3(0.0f, 1.0f, 0.0f));
				}
				else {
					// Cambio a movimiento en Z positivo
					enMovimientoX = false;
					enMovimientoZ = true;
					enCurva = false;
					mueveCarro = 0.0f; // Asegurar que se detenga exactamente en -160 en X
					mueveCarro2 = 0.0f; // Asegurar que se detenga exactamente en -160 en X
					giraCarro = giraCarroTargetX; // Mantener el ángulo final de 270°
				}
			}

			//printf("Final X movimiento -> mueveCarro: %f, giraCarro: %f\n", mueveCarro, giraCarro);
		}
		else if (enMovimientoZ) {
			// Solo entra en la curva una vez
			if (!enCurva) {
				enCurva = true;
			}

			if (giraCarro < 0) { // Solo girar 5 grados (de 270 a 265)
				giraCarro -= 0.5f * deltaTime; // Velocidad de giro más lenta
				mueveCarro2 += curvaCarroOffset * deltaTime;

				// Calcular el vector de dirección
				float radians = glm::radians(giraCarro);
				glm::vec3 direccion;
				direccion.x = cos(radians);
				direccion.z = sin(radians);

				// Actualiza la posición del modelo durante la curva
				model = glm::translate(glm::mat4(1.0f),
					glm::vec3(-160.0f, 0.0f, -160.0f + mueveCarro2)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(giraCarro), glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else {
				giraCarro = 0.0f; // Mantener un giro muy sutil
				enCurva = false;

				if (mueveCarro2 < 320) {
					mueveCarro2 += mueveCarroOffset * deltaTime;
					model = glm::translate(glm::mat4(1.0f),
						glm::vec3(-160.0f, 0.0f, -160.0f + mueveCarro2)) *
						glm::rotate(glm::mat4(1.0f), glm::radians(giraCarro), glm::vec3(0.0f, 1.0f, 0.0f));
				}
				else {
					enMovimientoZ = false;
					mueveCarro2 = 0.0f;
					giraCarro = 90.0f;
				}
			}

			//printf("Durante curva -> mueveCarro2: %f, giraCarro: %f\n", mueveCarro2, giraCarro);
		}
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carroCoco.RenderModel();

											// ##################################### CARRETERA ##################################### \\

		//CARRETERA
		//RECTA 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(34.2f, -1.0f, 166.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 12.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		recta.RenderModel();

		//CURVA 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(166.0f, -1.0f, 161.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		curva.RenderModel();

		//RECTA 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(169.0f, -1.0f, -35.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 12.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		recta.RenderModel();
	
		//CURVA 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(164.5f, -1.0f, -166.8));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		curva.RenderModel();

		//RECTA 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(34.0f, -1.0f, -170.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 12.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		recta.RenderModel();

		//CURVA 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-164.0f, -1.0f, -165.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		curva.RenderModel();

		//RECTA 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-167.0f, -1.0f, -35.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 12.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		recta.RenderModel();

		//CURVA 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-162.5f, -1.0f, 162.9));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		curva.RenderModel();

											// ##################################### ENTORNO ##################################### \\

		// GLOBO 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 150.0f, 250.0));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		globo.RenderModel();

		// GLOBO 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 150.0f, -250.0));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		globo.RenderModel();

		// GLOBO 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 150.0f, 250.0));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		globo.RenderModel();

		// GLOBO 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 150.0f, -250.0));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		globo.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, -1.0f, 65.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, -1.0f, 130.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, -1.0f, -65.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, -1.0f, -130.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.0f, -1.0f, 210.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, -1.0f, 210.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 210.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, -1.0f, 210.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, -1.0f, 210.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-210.0f, -1.0f, 130.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-210.0f, -1.0f, 65.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();


		////Casa Cynthia
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(-210.0f, -1.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-210.0f, -1.0f, -65.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-210.0f, -1.0f, -130.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, -1.0f, -210.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-65.0f, -1.0f, -210.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -210.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(65.0f, -1.0f, -210.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//Casa Cynthia
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.0f, -1.0f, -210.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		casaCynthia.RenderModel();

		//ESQUELETO CRASH
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, -1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		esqueleto.RenderModel();

		//ESTATUA1 CRASH
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, -1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MK9_X360_STG_PROP_Statue_Goro.RenderModel();

		//ARCHITECT CRASH
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 0.5f, 198.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Architect.RenderModel();

		//CLEVELAND
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 0.5f, -198.0f));
		/*model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cleveland.RenderModel();

		//Glenn
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 0.5f, -198.0f));
		/*model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glenn_quagmire.RenderModel();

		//HERBERT THE PERVERT
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 0.5f, 198.0f));
		model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		herbert.RenderModel();

		//CHICKEN
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 1.0f, 10.0f));
		/*model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Chicken_Nitro.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 60.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arboltablero1.RenderModel();

		//PALMERA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		palmeratablero.RenderModel();

		//ARBOL SIN HOJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbolsinhojas.RenderModel();

		//ARBOL 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arboltablero2.RenderModel();

		//CARRO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(55.0f, 7.0f, 10.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.18f, 0.18f, 0.18f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carro1.RenderModel();

		//MODELOS 4
		//ERMARC
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.5f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ermac.RenderModel();

		//Goro
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.5f, 20.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		goro.RenderModel();

		//Kabal
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, 0.5f, 15.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		kabal.RenderModel();

		//Cage
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 0.5f, 20.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.5f, 8.5f, 8.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cage.RenderModel();


		//MESA DE ITEMS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 55.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 15.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();

		//SOMBRERO ITEM
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.2f, 58.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sombrero.RenderModel();

		//HACHA ITEM
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 7.4f, 58.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hacha.RenderModel();

		//ESTRELLA ITEM
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, 7.4f, 58.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		estrella.RenderModel();

		//BAZOOKA ITEM
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(15.0f, 7.4f, 53.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bazooka.RenderModel();

		//BOX1 ITEM
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(28.0f, 7.4f, 52.0f));
		/*model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));*/
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		box1.RenderModel();

		//BOX2 ITEM
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(24.0f, 7.4f, 52.0f));
		/*model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));*/
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		box2.RenderModel();

		//BOX3 ITEM
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 7.4f, 52.0f));
		/*model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));*/
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		box3.RenderModel();

		//PRIMERO LADO LLENANDO DE FLORES
		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -50.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -30.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -10.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 10.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 30.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 50.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//SEGUNDO LADO DEL TABLERO

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//TERCER LADO
		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -50.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -30.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -10.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 10.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 30.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 50.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//CUARTA 
		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, -70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//TERCER LADO
		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, 70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(30.0f, 0.0f, 70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		//FLORES ROJAS
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		flores1.RenderModel();

		//ARBUSTO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 70.0f));
		/*model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		arbusto.RenderModel();

		glm::mat4 modelAuxave(1.0);

		//ANIMACION AVE 
		//CUERPO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(movAve_x - 100.0f, 50.0f + movAve_y, movAve_z + 100.0f));
		model = glm::rotate(model, giroAve * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelAuxave = model;
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo.RenderModel();

		model = modelAuxave;
		//ALAIZQ
		model = glm::rotate(model, giroAla * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaDer.RenderModel();

		model = modelAuxave;
		//ALADER
		model = glm::rotate(model, giroAla * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaIzq.RenderModel();




											// ##################################### SUELO Y LETRERO ANIMADO ##################################### \\

		//SUELO DE EN MEDIO
		toffsetsuelou += 0.01f;
		toffset = glm::vec2(toffsetletrerou, toffsetletrerov);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(10.0f, 5.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		pasto.UseTexture();
		meshList[2]->RenderMesh();

		//LETRERO MONOPOLY
		toffsetletrerou += 0.001f * deltaTime;  // Mueve el letrero hacia la derecha
		toffset = glm::vec2(toffsetletrerou, toffsetletrerov);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(80.0f, 10.0f, 150.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		letrero.UseTexture();
		meshList[4]->RenderMesh();

		



		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1 && reproduciranimacion>0)
		{
			printf("Ya puedes reproducir de nuevo la animación con la tecla de barra espaciadora'\n");
			reproduciranimacion = 0;
			habilitaranimacion++;

		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
			reinicioFrame++;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}


	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAve_x -= 10.0f;
			printf("\n movAve_x es: %f\n", movAve_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_2])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
			ciclo2++;
			printf("\n Ya puedes modificar tu variable de nuevo \n");
		}
	}

	if (keys[GLFW_KEY_3])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAve_x += 10.0f;
			printf("\n movAve_x es: %f\n", movAve_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_4])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAve_z -= 10.0f;
			printf("\n movAve_z es: %f\n", movAve_z);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}

	if (keys[GLFW_KEY_5])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAve_z += 10.0f;
			printf("\n movAvion_z es: %f\n", movAve_z);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}

	if (keys[GLFW_KEY_6])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			giroAve += 90.0f;
			printf("\n giroAve es: %f\n", giroAve);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}

	if (keys[GLFW_KEY_7])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			giroAve -= 90.0f;
			printf("\n giroAve es: %f\n", giroAve);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}

	if (keys[GLFW_KEY_8])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			giroAla += 35.0f;
			printf("\n giroAla es: %f\n", giroAla);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}

	if (keys[GLFW_KEY_9])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			giroAla -= 35.0f;
			printf("\n giroAla es: %f\n", giroAla);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}

	if (keys[GLFW_KEY_F])
	{
		if (ciclo < 1)
		{
			movAve_y += 10.0f;
			printf("\n movAve_y es: %f\n", movAve_y);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_G])
	{
		if (ciclo < 1)
		{
			movAve_y -= 10.0f;
			printf("\n movAve_y es: %f\n", movAve_y);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
}