#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

void generateBox(float x, float y, float z, string nome);
void generateBoxDiv(float x, float y, float z,int div, string nome);
string polarToCart(float radius, float alpha, float beta);
void generateSphere(float radius, int slices, int stacks, string nome);
void generatePlane(float x, string nome);
void generateCone(float radius, float height, int slices, int stacks, string nome);
string polarToCartCone(float radius,float height, float alpha);

int main(int argc, char* argv[]){
    
    string obj = argv[1];
    if(obj.compare("plane")==0){
    	if(argc != 4){
    		cout << "Nº de argumentos errado\n";
    		return 0;
    	}
    	else{
    		generatePlane(stof(argv[2]),argv[3]);
    	}
    }
    else if(obj.compare("box")==0){
    	if(argc != 6 && argc != 7){
    		cout << "Nº de argumentos errado\n";
    		return 0;
    	}
    	else if(argc==6){
    		generateBox(stof(argv[2]),stof(argv[3]),stof(argv[4]),argv[5]);
    	}
    	else{
    		generateBoxDiv(stof(argv[2]),stof(argv[3]),stof(argv[4]),stoi(argv[5]),argv[6]);
    	}
    }
    else if(obj.compare("sphere")==0){
    	if(argc != 6){
    		cout << "Nº de argumentos errado\n";
    		return 0;
    	}
    	else{
    		generateSphere(stof(argv[2]),stoi(argv[3]),stoi(argv[4]),argv[5]);
    	}
    }
    else if(obj.compare("cone")==0){
    	if(argc != 7){
    		cout << "Nº de argumentos errado\n";
    		return 0;
    	}
    	else{
    		generateCone(stof(argv[2]),stof(argv[3]),stoi(argv[4]),stoi(argv[5]),argv[6]);
    	}
    }
    else{
    	cout << "Comando não reconhecido\n";
    }


    return 0;
}


void generatePlane(float x, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	file << -x << ", " << 0 << ", " << -x << "\n";
	file << -x << ", " << 0 << ", " << x << "\n";
	file << x << ", " << 0 << ", " << x << "\n";
	file << -x << ", " << 0 << ", " << -x << "\n";
	file << x << ", " << 0 << ", " << x << "\n";
	file << x << ", " << 0 << ", " << -x << "\n";

	file.close();
}

void generateBox(float x, float y, float z, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	float xx=x/2;
	float yy=y/2;
	float zz=z/2;
	// face trás
	file << xx << ", " << yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
	// face cima
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
	// face frente
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	// face baixo
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	// face esquerda
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << -zz << "\n";
	file << -xx << ", " << -yy << ", " << zz << "\n";
	file << -xx << ", " << yy << ", " << zz << "\n";
	// direita
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << zz << "\n";
	file << xx << ", " << -yy << ", " << -zz << "\n";
	file << xx << ", " << yy << ", " << -zz << "\n";
	
	file.close();
}

void generateBoxDiv(float x, float y, float z, int div, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	float xx = x/-2;
	float yy = y/-2;
	float zz = z/-2;
	float incX = x/div;
	float incY = y/div;
	float incZ = z/div;

	//frente
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx+incX*j << ", " << yy+incY*(i+1) << ", " << -zz << "\n";
			file << xx+incX*(j) << ", " << yy+incY*(i) << ", " << -zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i) << ", " << -zz << "\n";
			file << xx+incX*j << ", " << yy+incY*(i+1) << ", " << -zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i) << ", " << -zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i+1) << ", " << -zz << "\n";
		}
	}

	//trás
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx+incX*j << ", " << yy+incY*(i+1) << ", " << zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i) << ", " << zz << "\n";
			file << xx+incX*(j) << ", " << yy+incY*(i) << ", " << zz << "\n";
			file << xx+incX*j << ", " << yy+incY*(i+1) << ", " << zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i+1) << ", " << zz << "\n";
			file << xx+incX*(j+1) << ", " << yy+incY*(i) << ", " << zz << "\n";
		}
	}

	//esquerda
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*j << "\n";
			file << xx << ", " << yy+incY*(i) << ", " << zz+incZ*j << "\n";
			file << xx << ", " << yy+incY*(i) << ", " << zz+incZ*(j+1) << "\n";
			file << xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*j << "\n";
			file << xx << ", " << yy+incY*(i) << ", " << zz+incZ*(j+1) << "\n";
			file << xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*(j+1) << "\n";
		}
	}			

	//direita
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
		file << -xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*j << "\n";
		file << -xx << ", " << yy+incY*(i) << ", " << zz+incZ*(j+1) << "\n";
		file << -xx << ", " << yy+incY*(i) << ", " << zz+incZ*j << "\n";
		file << -xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*j << "\n";
		file << -xx << ", " << yy+incY*(i+1) << ", " << zz+incZ*(j+1) << "\n";
		file << -xx << ", " << yy+incY*(i) << ", " << zz+incZ*(j+1) << "\n";
		}
	}	

	//cima
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx+incX*(j+1) << ", " << -yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*j << ", " << -yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*(j) << ", " << -yy << ", " << zz+incZ*(i+1) << "\n";
			file << xx+incX*(j+1) << ", " << -yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*j << ", " << -yy << ", " << zz+incZ*(i+1) << "\n";
			file << xx+incX*(j+1) << ", " << -yy << ", " << zz+incZ*(i+1) << "\n";
		}
	}		

	//baixo
	for (int i = 0; i < div; ++i){
		for (int j = 0; j < div; ++j)
		{
			
			file << xx+incX*(j+1) << ", " << yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*(j) << ", " << yy << ", " << zz+incZ*(i+1) << "\n";
			file << xx+incX*j << ", " << yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*(j+1) << ", " << yy << ", " << zz+incZ*i << "\n";
			file << xx+incX*(j+1) << ", " << yy << ", " << zz+incZ*(i+1) << "\n";
			file << xx+incX*j << ", " << yy << ", " << zz+incZ*(i+1) << "\n";
		}
	}		



	file.close();
}

void generateSphere(float radius, int slices, int stacks, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);
	
	float alpha = 0.0f;
	float beta = M_PI/-2;

	float sliceSize = 2*M_PI/slices;
	float stackSize = M_PI/stacks;

	//inicio da construção
	
	for(int i = 0; i < stacks; ++i){
		for (int j = 0; j < slices; ++j)
		{
			//file << "glColor3f(1.0f, 0.0f, 0.0f);\n";
			file << polarToCart(radius,alpha,beta);
			file << polarToCart(radius,alpha,beta+stackSize);
			file << polarToCart(radius,alpha+sliceSize,beta);
			//file << "glColor3f(0.0f, 0.0f, 1.0f);\n";
			file << polarToCart(radius,alpha,beta+stackSize);
			file << polarToCart(radius,alpha+sliceSize,beta+stackSize);
			file << polarToCart(radius,alpha+sliceSize,beta);
			alpha+=sliceSize;
		}
		beta+=stackSize;
		alpha=0;
	}

	
	file.close();
}

void generateCone(float radius, float height, int slices, int stacks, string nome){

	string path = "../models/" + nome;

	ofstream file;
	file.open(path);

	float stackSize = height/stacks;
	float sliceSize = 2*M_PI/slices;
	float alpha = 0.0f;
	float r = 0.0f;
	float rUp = 0.0f;
	float yy= height/-2;

	for(int i=0;i<slices;i++){
	    alpha = i*sliceSize;
	    file << polarToCartCone(0,yy,0);
        file << polarToCartCone(radius,yy,alpha+sliceSize);
        file << polarToCartCone(radius,yy,alpha);

	}

	for(int i = 0; i < stacks; i++){


        r=(((float)stacks-i)/stacks)*radius;
        rUp=(((float)stacks-(i+1))/stacks)*radius;
        for(int j = 0; j < slices; j++){

            alpha=j*sliceSize;

            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha+sliceSize);
            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha);
            file << polarToCartCone(r,yy+stackSize*i,alpha+sliceSize);
            file << polarToCartCone(rUp,yy+stackSize*(i+1),alpha+sliceSize);


		}
	}


	file.close();
}

string polarToCart(float radius, float alpha, float beta){
	float x = radius*cos(beta)*sin(alpha);
	float y = radius*sin(beta);
	float z = radius*cos(beta)*cos(alpha);
	return to_string(x) + ", " + to_string(y) + ", " + to_string(z) + "\n";
	//return "glVertex3f(" + to_string(x) + "f, " + to_string(y) + "f, " + to_string(z) + "f);\n";
}

string polarToCartCone(float radius,float height, float alpha){
	float x = radius*sin(alpha);
	float y = height;
	float z = radius*cos(alpha);
	return to_string(x) + ", " + to_string(y) + ", " + to_string(z)+"\n";
}