#pragma once
#include <vector>
#include <fstream>
#include "Vector3D.h"
#include "Vector2D.h"

using namespace std;

class ImportedData
{
public:
	vector<Vector3D> VnPoints;
	vector<Vector3D> PointsData;
	vector<Vector2D> UvData;
	vector<vector<Vector3D>> faces;

	//���캯������������
	ImportedData();
	~ImportedData();


	//��ȡ���ݺ���
	void GetData();
};