#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct TextureObject {
	string t_Id;
	string t_Source;
};

struct AnimationFrame {

	string textureID;
	int xOffset;
	int yOffset;
};

struct AnimationSequence{

	string a_Id;
	int frameCount;
	int speed;
	int width;
	int height;
};

struct LevelObj
{
	string type, tex;
	int cat, x, y, w, h, flip, sX, sY, rot;
	float sratio;
};

struct SoundObject
{
	string s_Id, s_Source;
};

#define texArray vector<TextureObject> 
#define animArray vector<AnimationSequence>
#define animFrameArray vector<AnimationFrame>
#define objArray vector<LevelObj>
#define soundArray vector<SoundObject>

ofstream myFile;

void writeTexture(texArray inputTex)
{
	// Insert condition for empty input
	myFile.open("D:/Personal Coding/TMLTest/texture1.tml", ios::out);
	myFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	myFile << "<textures>" << endl;
	for(int i=0; i < inputTex.size(); i++)
		myFile << " <texture id=\"" << inputTex[i].t_Id << "\" source=\"" << inputTex[i].t_Source<< "\"/>" << endl;
	myFile << "</textures>" << endl;
	myFile.close();
}

void writeSound(soundArray inputSound)
{
	// Insert condition for empty input
	myFile.open("D:/Personal Coding/TMLTest/sounds1.tml", ios::out);
	myFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	myFile << "<sounds>" << endl;
	for (int i = 0; i < inputSound.size(); i++)
		myFile << " <effect id=\"" << inputSound[i].s_Id << "\" source=\"" << inputSound[i].s_Source << "\"/>" << endl;
	for (int i = 0; i < inputSound.size(); i++)
		myFile << " <music id=\"" << inputSound[i].s_Id << "\" source=\"" << inputSound[i].s_Source << "\"/>" << endl;
	myFile << "</sounds>" << endl;
	myFile.close();
}

void writeAnim(animArray inputAnim, animFrameArray inputFrame)
{
	// Insert condition for empty input
	myFile.open("D:/Personal Coding/TMLTest/anima1.tml", ios::out);
	myFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	myFile << "<animations>" << endl;
	for (int i = 0; i < inputAnim.size(); i++) {
		myFile << " <sequence id=\"" << inputAnim[i].a_Id << "\" frameCount=\"" << inputAnim[i].frameCount << "\" speed=\"" <<
			inputAnim[i].speed << "\" width=\"" << inputAnim[i].width << "\" height=\"" << inputAnim[i].height << "\">" << endl;
		for (int j = 0; j < inputAnim[i].frameCount; j++) {
			myFile << "  <frame textureID=\"" << inputFrame[j].textureID << "\" xOffset=\"" << inputFrame[j].xOffset <<
				"\" yOffset=\"" << inputFrame[j].yOffset << "\"/>" << endl;
		}
		myFile << " </sequence>" << endl;
	}
	myFile << "</animations>" << endl;
	myFile.close();
}

void writeObj(objArray inputObj) {

	myFile.open("D:/Personal Coding/TMLTest/levelobjects.tml", ios::out);
	myFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
	myFile << "<objects>"<<endl;
	for (int i = 0; i < inputObj.size(); i++)
		myFile << " <object type=\"" << inputObj[i].type << "\" category=\""<< inputObj[i].cat << "\" texture=\""
		<< inputObj[i].tex << "\" x=\"" << inputObj[i].x << "\" y=\"" << inputObj[i].y << 
		"\" w=\"" << inputObj[i].w << "\" h=\"" << inputObj[i].h << "\" flip=\"" << inputObj[i].flip <<
		"\" sX=\"" << inputObj[i].sX << "\" sY=\"" << inputObj[i].sY << "\" sratio=\""
		<< inputObj[i].sratio << "\" rot=\"" << inputObj[i].rot << "\"/>"<<endl;
	myFile << "</objects>" << endl;
}

void main()
{
	texArray test;
	animArray atest;
	objArray otest;
	animFrameArray aftest;
	soundArray stest;

	for (int i = 0; i < 4; i++)
	{
		test.push_back(TextureObject());
		test[i].t_Id = "player";
		test[i].t_Source = "Assets/src.png";
	}
	writeTexture(test);

	for (int i = 0; i < 4; i++)
	{
		stest.push_back(SoundObject());
		stest[i].s_Id = "sound" + to_string(i);
		stest[i].s_Source = "Assets/Sounds/sound" + to_string(i) + ".wav";
	}
	writeSound(stest);

	for (int i = 0; i < 4; i++)
	{
		atest.push_back(AnimationSequence());
		atest[i].a_Id = "playyy";
		atest[i].frameCount = 2;
		atest[i].speed = 1;
		atest[i].width = 22;
		atest[i].height = 13;
		for (int j = 0; j < atest[i].frameCount; j++)
		{
			aftest.push_back(AnimationFrame());
			aftest[j].textureID = "ladada";
			aftest[j].xOffset = 11;
			aftest[j].yOffset = 13;
		}
	}
	writeAnim(atest, aftest);
	
	for (int i = 0; i < 4; i++)
	{
		otest.push_back(LevelObj());
		otest[i].type = "WARRRRRR";
		otest[i].tex = "WARRRRRR";
		otest[i].cat = 13;
		otest[i].x = 3;
		otest[i].y = 113;
		otest[i].w = 23;
		otest[i].h = 34;
		otest[i].sX = 63;
		otest[i].sY = 0;
		otest[i].rot = 1;
		otest[i].flip = 4;
		otest[i].sratio = 1.14;
	}
	writeObj(otest);
}