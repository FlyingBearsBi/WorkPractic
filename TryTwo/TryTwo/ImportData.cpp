#include "ImportData.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

ImportedData::ImportedData()
{/*empty*/
}

ImportedData::~ImportedData()
{
	/*empty*/
}


void ImportedData::GetData()
{
	ifstream infile;
	infile.open("E://WorkSpace//PhotoBase//african_head.txt");
	if (infile.fail()) return;
	string line;
	while (!infile.eof()) {
		getline(infile, line);
		istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v "))
		{
			iss >> trash;
			Vector3D v;
			iss >> v.x >> v.y >> v.z;
			PointsData.push_back(v);
		}
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			Vector3D n;
			iss >> n.x >> n.y >> n.z;
			VnPoints.push_back(n);
		}
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			Vector2D uv;
			iss >> uv.x >> uv.y;
			UvData.push_back(uv);
		}
		else if (!line.compare(0, 2, "f "))
		{
			vector<Vector3D> f;
			Vector3D tmp;
			iss >> trash;
			while (iss >> tmp.x >> trash >> tmp.y >> trash >> tmp.z) {
				tmp.x--;
				tmp.y--;
				tmp.z--;
				f.push_back(tmp);
			}
			faces.push_back(f);
		}
	}
}
//void ImportedData::GetData()
//{
//    ifstream infile;
//    infile.open("E://WorkSpace//PhotoBase//african_head.txt");
//
//    if (!infile.is_open())
//    {
//        cout << "0";
//    }
//    string sline, s0;
//
//    while (getline(infile, sline))
//    {
//        if (sline[0] == 'v')
//        {
//            if (sline[1] == 'n')
//            {
//                istringstream ins(sline);
//                Vector3D newpoint = Vector3D();
//                ins >> s0 >> newpoint.x >> newpoint.y >> newpoint.z;
//                VnPoints.push_back(newpoint);
//            }
//            else if (sline[1] == 't')
//            {
//            }
//            else
//            {
//                istringstream ins(sline);
//                Vector3D newpoint = Vector3D();
//                ins >> s0 >> newpoint.x >> newpoint.y >> newpoint.z;
//                PointsData.push_back(newpoint);
//            }
//        }
//        else if (sline[0] == 'f')
//        {
//            int leng = sline.size();
//            vector<int> faceIter(3);
//            int n = 0;
//            for (int i = 0; i < leng; i++)
//            {
//                if (sline[i] == ' ')
//                {
//                    int k = 0;
//                    while (sline[i + k] != '/')
//                    {
//                        k++;
//                    }
//                    string ans(sline, i, k);
//                    istringstream ins(ans);
//                    ins >> faceIter[n++];
//                }
//            }
//            for (int k = 0; k < 3; k++)
//            {
//                faceIter[k]--;
//            }
//            face.push_back(faceIter);
//        }
//    }
//    int len = face.size();
//}