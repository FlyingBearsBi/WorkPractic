// TryTwo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <sstream>
#include <vector>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <algorithm>
#include "ImportData.h"
#include "Matrix4x4.h"
#include "Vector3i.h"
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

using namespace std;

const float width = 800.0f;
const float height = 800.0f;
const Vector3D light_dir(0, 0, -1);
ImportedData Data;
float* zbuffer = new float[width * height];
Vector3D camera(0, 0, 3.0f);
const float depth = 255.0f;
Model* model = NULL;


//2DDA算法画直线
void drawLine(int x0, int y0, int x1, int y1) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = std::max(std::abs(dx), std::abs(dy));

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = x0;
    float y = y0;
    for (int i = 0; i <= steps; ++i) {
        //pixels.push_back({ static_cast<int>(x), static_cast<int>(y) });
        x += xIncrement;
        y += yIncrement;
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x / (width/2) - 1, y / (height/2) - 1);
        glEnd();
    }
}

//绘制三角形

void drawtriangleNoLight(Vector3D t0, Vector3D t1, Vector3D t2)
{
    float xMin = min(min(t0.x, t1.x), t2.x);
    float xMax = max(max(t0.x, t1.x), t2.x);
    float yMin = min(min(t0.y, t1.y), t2.y);
    float yMax = max(max(t0.y, t1.y), t2.y);
    //cout << "三角形顶点：[(" << t0.x << ",  " << t0.y << "), (" << t1.x << ", " << t1.y << "), (" << t2.x << ", " << t2.y << ")]" << endl;
    //cout << "左区间" << xMin << "    右区间" << xMax << "   下区间" << yMin << "    上区间" << yMax << endl;
    for (int y = yMin; y < yMax; y++)
    {
        for (int x = xMin; x < xMax; x++)
        {
            Vector3D pPoint = Vector3D(x, y, 1);
            Vector3D centricPoint = Barycentric(t0, t1, t2, pPoint);
            if (!(centricPoint.x < 0 || centricPoint.y < 0 || centricPoint.z < 0))
            {
                glBegin(GL_POINTS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(x / (width / 2) - 1, y / (height / 2) - 1);
                glEnd();
            }
        }
    }
}

//带光照绘制三角形
void drawtriangleLight(Vector3D t0, Vector3D t1, Vector3D t2, float intensity, float *zbuffer)
{
    if (t0.y == t1.y && t0.y == t2.y) return;
    Vector3D Vertex[3];
    Vertex[0] = t0;
    Vertex[1] = t1;
    Vertex[2] = t2;
    float xMin = min(min(t0.x, t1.x), t2.x);
    float xMax = max(max(t0.x, t1.x), t2.x);
    float yMin = min(min(t0.y, t1.y), t2.y);
    float yMax = max(max(t0.y, t1.y), t2.y);
    //cout << "三角形顶点：[(" << t0.x << ",  " << t0.y << "), (" << t1.x << ", " << t1.y << "), (" << t2.x << ", " << t2.y << ")]" << endl;
    //cout << "左区间" << xMin << "    右区间" << xMax << "   下区间" << yMin << "    上区间" << yMax << endl;
    for (int y = yMin; y < yMax; y++)
    {
        for (int x = xMin; x < xMax; x++)
        {
            Vector3D pPoint = Vector3D(x, y, 1);
            Vector3D centricPoint = Barycentric(t0, t1, t2, pPoint);
            //Vector3D centricPointt = Barycentric(t2, t1, t0, pPoint);
            if (centricPoint.x < 0 || centricPoint.y < 0 || centricPoint.z < 0) continue;
            pPoint.z = 0;
            pPoint.z = t0.z * centricPoint.x + t1.z * centricPoint.y + t2.z * centricPoint.z;
            int k = pPoint.x+ pPoint.y* width;
            if (zbuffer[k] < pPoint.z)
            {
                zbuffer[k] = pPoint.z;
                glBegin(GL_POINTS);
                glColor3f(1.0f * intensity, 1.0f * intensity, 1.0f * intensity);
                glVertex2f(x / (width / 2) - 1, y / (height / 2) - 1);
                glEnd();
             }
        }
    }
}

//带光照和纹理绘制三角形
void drawtriangleLightAndUr(Vector3D t0, Vector3D t1, Vector3D t2, float intensity, float* zbuffer, Vector2D uv0, Vector2D uv1, Vector2D uv2)
{
    if (t0.y == t1.y && t0.y == t2.y) return;
    Vector3D Vertex[3];
    Vertex[0] = t0;
    Vertex[1] = t1;
    Vertex[2] = t2;
    float xMin = min(min(t0.x, t1.x), t2.x);
    float xMax = max(max(t0.x, t1.x), t2.x);
    float yMin = min(min(t0.y, t1.y), t2.y);
    float yMax = max(max(t0.y, t1.y), t2.y);
    //cout << "三角形顶点：[(" << t0.x << ",  " << t0.y << "), (" << t1.x << ", " << t1.y << "), (" << t2.x << ", " << t2.y << ")]" << endl;
    //cout << "左区间" << xMin << "    右区间" << xMax << "   下区间" << yMin << "    上区间" << yMax << endl;
    for (int y = yMin; y < yMax; y++)
    {
        for (int x = xMin; x < xMax; x++)
        {
            Vector3D pPoint = Vector3D(x, y, 1);
            Vector3D centricPoint = Barycentric(t0, t1, t2, pPoint);
            Vector2D uvP;
            //Vector3D centricPointt = Barycentric(t2, t1, t0, pPoint);
            if (centricPoint.x < 0 || centricPoint.y < 0 || centricPoint.z < 0) continue;
            uvP.x = centricPoint.x * uv0.x + centricPoint.y * uv1.x + centricPoint.z * uv2.x;
            uvP.y = centricPoint.x * uv0.y + centricPoint.y * uv1.y + centricPoint.z * uv2.y;
            pPoint.z = 0;
            pPoint.z = t0.z * centricPoint.x + t1.z * centricPoint.y + t2.z * centricPoint.z;
            TGAColor color = model->diffuse(uvP);
            //cout << "着色R " << color.r << ",G: " << color.g << ", B: "<< color.b << endl;
            //cout << "新着色R " << color.r * intensity << ",G: " << color.g * intensity << ", B: " << color.b * intensity << endl;
            //cout << "改着色R " << color.r * intensity / 255 << ",G: " << color.g * intensity / 255 << ", B: " << color.b * intensity / 255 << endl;
            int k = pPoint.x + pPoint.y * width;
            if (zbuffer[k] < pPoint.z)
            {
                zbuffer[k] = pPoint.z;
                glBegin(GL_POINTS);
                glColor3ub(color.r * intensity, color.g * intensity, color.b * intensity);
                //glColor3f(color.r * intensity / 255, color.g * intensity / 255, color.b * intensity / 255);
                glVertex2f(x / (width / 2) - 1, y / (height / 2) - 1);
                glEnd();
            }
        }
    }
}



//线框模式绘制模型
void drawPictureLine()
{
    for (int i = 0; i < Data.faces.size(); i++)
    {
        vector<Vector3D> face = Data.faces[i];
        for (int j = 0; j < 3; j++)
        {
            Vector3D v0 = Data.PointsData[face[j].x];
            Vector3D v1 = Data.PointsData[face[(j + 1) % 3].x];
            int x0 = (v0.x + 1) * width / 2;
            int y0 = (v0.y + 1) * height / 2;
            int x1 = (v1.x + 1) * width / 2;
            int y1 = (v1.y + 1) * height/ 2;
            drawLine(x0, y0, x1, y1);
        }
    }
}


//三角形填充模式绘制模型(不带光照)
void drawPictureTriangleVerOne()
{
    for (int i = 0; i < Data.faces.size(); i++)
    {
        vector<Vector3D> face = Data.faces[i];
        Vector3D ScreenCoords[3];
        Vector3D WorldCoords[3];
        for (int j = 0; j < 3; j++)
        {
            Vector3D v0 = Data.PointsData[face[j].x];
            ScreenCoords[j].x = (v0.x + 1) * width / 2;
            ScreenCoords[j].y = (v0.y + 1) * height / 2;
            ScreenCoords[j].z = 1.0f;
            WorldCoords[j] = v0;
        }
        Vector3D n1 = (WorldCoords[2] - WorldCoords[0]).cross((WorldCoords[1] - WorldCoords[0]));
        n1 = n1.normalize();
        float intensity = n1.dot(light_dir);
        if (intensity > 0)
        {
            drawtriangleNoLight(ScreenCoords[0], ScreenCoords[1], ScreenCoords[2]);
        }
    }
}
//三角形填充模式绘制模型(带光照)(z-buffer缓冲)
void drawPictureTriangleVerTwo()
{
    float* zbuffer = new float[width * height];
    for (int i = width * height; i--; zbuffer[i] = -std::numeric_limits<float>::max());
    for (int i = 0; i < Data.faces.size(); i++)
    {
        vector<Vector3D> face = Data.faces[i];
        Vector3D ScreenCoords[3];
        Vector3D WorldCoords[3];

        for (int j = 0; j < 3; j++)
        {
            Vector3D v0 = Data.PointsData[face[j].x];
            ScreenCoords[j].x = (v0.x + 1) * width / 2;
            ScreenCoords[j].y = (v0.y + 1) * height / 2;
            ScreenCoords[j].z = 1.0f;
            WorldCoords[j] = v0;
        }
        Vector3D n1 = (WorldCoords[2] - WorldCoords[0]).cross((WorldCoords[1] - WorldCoords[0]));
        n1 = n1.normalize();
        float intensity = n1.dot(light_dir);
        if (intensity > 0)
        {
            drawtriangleLight(ScreenCoords[0], ScreenCoords[1], ScreenCoords[2], intensity, zbuffer);
        }
    }
    delete zbuffer;
}

////三角形填充模式绘制模型(带光照)(z-buffer)（使用透视版本)
void drawPictureTriangleVerThree()
{
    float* zbuffer = new float[width * height];
    for (int i = 0; i < width * height; i++) {
        zbuffer[i] = std::numeric_limits<int>::min();
    }
    Matrix4x4 Projection;
    Matrix4x4 ViewPort;
    ViewPort = ViewPort.BuildViewPort(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);
    Projection.data[3][2] = -1.0f / camera.z;

    for (int i = 0; i < Data.faces.size(); i++)
    {
        vector<Vector3D> face = Data.faces[i];
        Vector3D ScreenCoords[3];
        Vector3D WorldCoords[3];
        Vector3i ScreenCoordsi[3];
        for (int j = 0; j < 3; j++)
        {
            Vector3D v0 = Data.PointsData[face[j].x];
            Vector4D v(v0.x, v0.y, v0.z, 1.0f);

            Matrix4x4 mid = ViewPort * Projection;
            //ViewPort.Show();
            //Projection.Show();
            //mid.Show();
            Vector4D v2 = mid * v;
            Vector3D v1(v2.x / v2.w, v2.y / v2.w, v2.z / v2.w);
            ScreenCoords[j] = v1;
            WorldCoords[j] = v0;
            ScreenCoords[j].ToiPoint();
        }
        Vector3D n1 = (WorldCoords[2] - WorldCoords[0]).cross((WorldCoords[1] - WorldCoords[0]));
        n1 = n1.normalize();
        float intensity = n1.dot(light_dir);
        if (intensity > 0)
        {
            drawtriangleLight(ScreenCoords[0], ScreenCoords[1], ScreenCoords[2], intensity, zbuffer);
        }
    }
    delete zbuffer;
}

//第四版，带光照，z-buffer,透视和纹理
void drawPictureTriangleVerFour()
{
    float* zbuffer = new float[width * height];
    for (int i = 0; i < width * height; i++) {
        zbuffer[i] = std::numeric_limits<int>::min();
    }
    Matrix4x4 Projection;
    Matrix4x4 ViewPort;
    ViewPort = ViewPort.BuildViewPort(width / 8, height / 8, width * 3 / 4, height * 3 / 4, depth);
    Projection.data[3][2] = -1.0f / camera.z;
    TGAImage image(width, height, TGAImage::RGB);

    for (int i = 0; i < Data.faces.size(); i++)
    {
        vector<Vector3D> face = Data.faces[i];
        Vector3D ScreenCoords[3];
        Vector3D WorldCoords[3];
        for (int j = 0; j < 3; j++)
        {
            Vector3D v0 = Data.PointsData[face[j].x];
            Vector4D v(v0.x, v0.y, v0.z, 1.0f);
            Matrix4x4 mid = ViewPort * Projection;
            Vector4D v2 = mid * v;
            Vector3D v1(v2.x / v2.w, v2.y / v2.w, v2.z / v2.w);
            ScreenCoords[j] = v1;
            WorldCoords[j] = v0;
            ScreenCoords[j].ToiPoint();
        }
        Vector3D n1 = (WorldCoords[2] - WorldCoords[0]).cross((WorldCoords[1] - WorldCoords[0]));
        n1 = n1.normalize(); 
        float intensity = n1.dot(light_dir);
        if (intensity > 0)
        {
            Vector2D uv[3];
            for (int k = 0; k < 3; k++)
            {
                uv[k] = Data.UvData[face[k].y];
                uv[k].x = uv[k].x * 1024;
                uv[k].y = uv[k].y * 1024;
                uv[k].ToiPoint();
            }
            drawtriangleLightAndUr(ScreenCoords[0], ScreenCoords[1], ScreenCoords[2], intensity, zbuffer, uv[0], uv[1], uv[2]);
        }
    }
    delete zbuffer;
}

int main()
{
    Data.GetData();
    model = new Model("E://WorkSpace//PhotoBase//african_head.obj");
    glfwInit();

    //创建窗口对象
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* 创建窗口对象和窗口参数*/
    window = glfwCreateWindow(800, 800, "Learning OpenGL", NULL, NULL);
    if (!window)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    /* 确保上下文 */
    glfwMakeContextCurrent(window);


    //设定窗口参数
    //参数说明：    中心位置和半轴长度

    glViewport(0, 0, width, height);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        //drawtriangle(t0, t1, t2);
        //drawPictureLine();
        //drawPictureTriangleVerOne();
        //drawPictureTriangleVerTwo();
        //drawPictureTriangleVerThree();
        drawPictureTriangleVerFour();
        //glPointSize(10);
        //glBegin(GL_POINTS);
        //glColor3f(0, 100.0f, 100.0f);
        //glVertex2f(0, 0);
        //glEnd();
        glMatrixMode(GL_MODELVIEW);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
