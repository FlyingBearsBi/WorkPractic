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

	//构造函数与析构函数
	ImportedData();
	~ImportedData();


	//获取数据函数
	void GetData();
};