#pragma once
#define pi acos(-1)
#define getch _getch
#define scanf scanf_s
#define printf printf_s

#define WINH 600//窗口高度
#define WINW 800//窗口宽度
#define DEBUG 0//DEBUG模式
#define BATCHDRAW 1//是否使用缓存绘制
#define MD_LS_SQUARE 1//线型模式：方形刷子
#define MD_LS_LINE 0//线型模式：线刷子
#define VIEW_MAX_NUM 10//最大view个数
#define SPLINE_ITEM_MAX_NUM 10
#define MAT3_MAXN 100 //MAT3最大高度
#define MAT4_MAXN 100 //MAT4最大高度
#define MAT_ELEMENT_EPS (2e-15)

using namespace std;

namespace myGraphcis {
    struct Vector3;
    struct Matrix3n;
    using Points = Matrix3n;
    class Matrix;
    struct Matrix4x4;
    void OELFill(int* poly, int n, COLORREF col);
    Matrix4x4 Mat4_OrthoProjection(string face);
    Matrix4x4 Mat4_OrthoProjection();

    bitset<WINW* WINH> seedFill_fillMap;
    //填充图案
    BYTE FILL_PATTERN[9] = { "\xff\xff\xff\xff\xff\xff\xff\xff" };
    //线型信息结构体
    struct sLINESTYLE {
        int thinkness;
        unsigned int pattern;
        int mode;//mode = 0, 直线刷子，mode = 1，方形刷子
    }LINE_STYLE_DATA = { 1,(unsigned int)-1, MD_LS_LINE };
    //当前view个数
    int VIEWCNT = 0;
    //view信息结构体
    struct sVIEW {
        int x1, y1, x2, y2;
    } VIEW_DATA[VIEW_MAX_NUM] = { { 0,0,WINW,WINH } };
    
    
    //3x3矩阵(变换矩阵)
    struct Matrix3x3 {
        double d[3][3];

        double* operator [](int i) {
            return this->d[i];
        }
        //矩阵乘法
        Matrix3x3 operator * (const Matrix3x3& mat) {
            Matrix3x3 res = { 0 };
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        res.d[i][j] += this->d[i][k] * mat.d[k][j];
                    }
                }
            }
            return res;
        }
        //矩阵加法
        Matrix3x3 operator + (const Matrix3x3& mat) {
            Matrix3x3 res = { 0 };
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    res.d[i][j] = this->d[i][j] + mat.d[i][j];
                }
            }
            return res;
        }
        //矩阵减法
        Matrix3x3 operator - (const Matrix3x3& mat) {
            Matrix3x3 res = { 0 };
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    res.d[i][j] = this->d[i][j] - mat.d[i][j];
                }
            }
            return res;
        }

        friend ostream& operator << (ostream& out, const Matrix3x3& mat) {
            for (int i = 0; i < 3; i++) {
                if (i == 0) {
                    out << "\n┌ ";
                }
                else if (i == 2) {
                    out << "└ ";
                }
                else {
                    out << "│ ";
                }

                for (int j = 0; j < 3; j++) {
                    out << mat.d[i][j] << " ";
                }

                if (i == 0) {
                    out << "┐\n";
                }
                else if (i == 2) {
                    out << "┘\n";
                }
                else {
                    out << "│\n";
                }
            }
            return out;
            
        }
        
    };
    //4x4矩阵(变换矩阵)
    struct Matrix4x4 {
        double d[4][4];

        double* operator [](int i) {
            return this->d[i];
        }
        //矩阵乘法
        Matrix4x4 operator * (const Matrix4x4& mat) {
            Matrix4x4 res = { 0 };
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < 4; k++) {
                        res.d[i][j] += this->d[i][k] * mat.d[k][j];
                    }
                }
            }
            return res;
        }
        //矩阵加法
        Matrix4x4 operator + (const Matrix4x4& mat) {
            Matrix4x4 res = { 0 };
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    res.d[i][j] = this->d[i][j] + mat.d[i][j];
                }
            }
            return res;
        }
        //矩阵减法
        Matrix4x4 operator - (const Matrix4x4& mat) {
            Matrix4x4 res = { 0 };
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    res.d[i][j] = this->d[i][j] - mat.d[i][j];
                }
            }
            return res;
        }

        friend ostream& operator << (ostream& out, const Matrix4x4& mat) {
            for (int i = 0; i < 4; i++) {
                if (i == 0) {
                    out << "\n┌ ";
                }
                else if (i == 3) {
                    out << "└ ";
                }
                else {
                    out << "│ ";
                }

                for (int j = 0; j < 4; j++) {
                    out << mat.d[i][j] << " ";
                }

                if (i == 0) {
                    out << "┐\n";
                }
                else if (i == 3) {
                    out << "┘\n";
                }
                else {
                    out << "│\n";
                }
            }
            return out;

        }

    };
    //3维向量(2维点)
    struct Vector3 {
        double d[3];

        double &operator [](int i) {
            return this->d[i];
        }
        Vector3 operator * (const Matrix3x3 &mat) {
            Vector3 res = { 0 };
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    res.d[i] += this->d[j] * mat.d[j][i];
                }
            }
            return res;
        }
        friend Vector3 operator * (const double &k, const Vector3 &vec3) {
            return { vec3.d[0] * k, vec3.d[1] * k, vec3.d[2] * k };
        }

        Vector3 operator + (const Vector3 &v) {
            Vector3 res = { 0 };
            for (int i = 0; i < 3; i++) {
                res.d[i] = this->d[i] + v.d[i];
            }
            return res;
        }

        Vector3 operator - (const Vector3& v) {
            Vector3 res = { 0 };
            for (int i = 0; i < 3; i++) {
                res.d[i] = this->d[i] - v.d[i];
            }
            return res;
        }

        friend ostream& operator << (ostream& out, const Vector3& vec) {
            out << "[ " << vec.d[0] << " " << vec.d[1] << " " << vec.d[2] << " ]";
            return out;
        }

        Vector3 Normalize() const{
            return { d[0] / d[2], d[1] / d[2], 1 };
        }

        Vector3 IgoreZ() const{
            return { d[0], d[1], 1 };
        }

    };
    //4维向量(3维点)
    struct Vector4 {
        double d[4];

        double& operator [](int i) {
            return this->d[i];
        }
        Vector4 operator * (const Matrix4x4& mat) {
            Vector4 res = { 0 };
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    res.d[i] += this->d[j] * mat.d[j][i];
                }
            }
            return res;
        }

        Vector4 operator + (const Vector4& v) {
            Vector4 res = { 0 };
            for (int i = 0; i < 4; i++) {
                res.d[i] = this->d[i] + v.d[i];
            }
            return res;
        }

        Vector4 operator - (const Vector4& v) {
            Vector4 res = { 0 };
            for (int i = 0; i < 4; i++) {
                res.d[i] = this->d[i] - v.d[i];
            }
            return res;
        }

        friend ostream& operator << (ostream& out, const Vector4& vec) {
            out << "[ " << vec.d[0] << " " << vec.d[1] << " " << vec.d[2] << " " << vec.d[3] << " ]";
            return out;
        }
        Vector4 Normalize() {
            return { d[0] / d[3], d[1] / d[3], d[2] / d[3], 1 };
        }

        Vector3 GetVec3(string face) {
            Vector4 normalized = this->Normalize();
            if (face == "xy") {
                return { normalized[0], normalized[1], 1 };
            }
            else if (face == "xz") {
                return { normalized[0], normalized[2], 1 };
            }
            else if (face == "yz") {
                return { normalized[1], normalized[2], 1 };
            }
        }
        Vector3 GetVec3() {
            return this->GetVec3("xz");
        }

    };
    double Vec4DisSqr(Vector4 p1, Vector4 p2) {
        Vector4 d = p1 - p2;
        return (d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
    }
    //3xn矩阵(2维点集)
    class Matrix3n {
    public:
        vector<Vector3> arrays;
        int n;

        Matrix3n() {}
        Matrix3n(vector<Vector3> lines) {
            this->arrays = lines;
            this->n = arrays.size();
        }
        Matrix3n(vector<double> a) {
            for (int i = 0; i + 2 < a.size(); i += 3) {
                arrays.push_back({ a[i],a[i + 1],a[i + 2] });
            }
            this->n = arrays.size();
        }
        Matrix3n(double a, int n) {
            for (int i = 0; i < n; i ++) {
                arrays.push_back({a,a,a});
            }
            this->n = arrays.size();
        }
        Matrix3n(int n, vector<double> a) {
            for (int i = 0; i + 2 < a.size(); i += 3) {
                arrays.push_back({ a[i],a[i + 1],a[i + 2] });
            }
            this->n = arrays.size();
        }

        int size() const{
            return this->arrays.size();
        }
        Vector3 &operator [](const int &i) {
            return arrays[i];
        }
        Matrix3n operator * (const Matrix3x3& mat) {
            Matrix3n res = {0,this->n};
            for (int i = 0; i < this->n; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        res[i][j] += this->arrays[i][k] * mat.d[k][j];
                    }
                }
            }
            return res;
        }
        friend ostream& operator << (ostream& out, const Matrix3n& mat) {
            for (int i = 0; i < mat.size(); i++) {
                if (i == 0) {
                    out << "\n┌ ";
                }
                else if (i == mat.size()-1) {
                    out << "└ ";
                }
                else {
                    out << "│ ";
                }

                for (int j = 0; j < 3; j++) {
                    if (abs(mat.arrays[i].d[j]) < MAT_ELEMENT_EPS) {
                        out << 0 << " ";
                    }
                    else{
                        out << mat.arrays[i].d[j] << " ";

                    }
                }

                if (i == 0) {
                    out << "┐\n";
                }
                else if (i == mat.size()-1) {
                    out << "┘\n";
                }
                else {
                    out << "│\n";
                }
            }
            return out;

        }
        Matrix3n Normalize() {
            Matrix3n mat3n = *this;
            for (int i = 0; i < mat3n.size(); i++) {
                mat3n[i] = mat3n[i].Normalize();
            }
            return mat3n;
        }
        Matrix3n AddEndPoint(Vector3 dir1, Vector3 dir2) {
            Matrix3n res = *this;
            res.arrays.insert(res.arrays.begin(), (arrays[1] - dir1).IgoreZ());
            res.arrays.insert(res.arrays.end(), (arrays[res.arrays.size()-2] + dir1).IgoreZ());
            return res;
        }
        Matrix3n AddEndPoint() {
            Matrix3n res = *this;
            res.arrays.insert(res.arrays.begin(), *res.arrays.begin());
            res.arrays.insert(res.arrays.end(), *res.arrays.rbegin());
            return res;
        }
        Matrix3n MakeRound() {
            Matrix3n res = *this;
            res.arrays.insert(res.arrays.begin(), *res.arrays.rbegin());
            res.arrays.insert(res.arrays.end(), res.arrays[1]);
            res.arrays.insert(res.arrays.end(), res.arrays[2]);
            return res;
        }
    };
    //4xn矩阵(3维点集)
    class Matrix4n {
    public:
        vector<Vector4> arrays;
        int n;
        Matrix4n() {}

        Matrix4n(vector<Vector4> lines) {
            this->arrays = lines;
            this->n = arrays.size();
        }
        Matrix4n(vector<double> a) {
            for (int i = 0; i + 3 < a.size(); i += 4) {
                arrays.push_back({ a[i],a[i + 1],a[i + 2],a[i+3]});
            }
            this->n = arrays.size();
        }
        Matrix4n(double a, int n) {
            for (int i = 0; i < n; i++) {
                this->arrays.push_back({ a,a,a });
            }
            this->n = arrays.size();
        }
        Matrix4n(int n, vector<double> a) {
            for (int i = 0; i + 3 < a.size(); i += 4) {
                arrays.push_back({ a[i],a[i + 1],a[i + 2],a[i+3]});
            }
            this->n = arrays.size();
        }
        int size() const{
            return this->arrays.size();
        }

        Vector4& operator [](int i) {
            return arrays[i];
        }
        Matrix4n operator * (const Matrix4x4& mat) {
            Matrix4n res = {0, this->size()};
            for (int i = 0; i < this->size(); i++) {
                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < 4; k++) {
                        res[i][j] += this->arrays[i][k] * mat.d[k][j];
                    }
                }
            }
            return res;
        }
        friend ostream& operator << (ostream& out, const Matrix4n& mat) {
            for (int i = 0; i < mat.size(); i++) {
                if (i == 0) {
                    out << "\n┌ ";
                }
                else if (i == mat.size() - 1) {
                    out << "└ ";
                }
                else {
                    out << "│ ";
                }

                for (int j = 0; j < 4; j++) {
                    if (abs(mat.arrays[i].d[j]) < MAT_ELEMENT_EPS) {
                        out << 0 << " ";
                    }
                    else {
                        out << mat.arrays[i].d[j] << " ";
                    }
                }

                if (i == 0) {
                    out << "┐\n";
                }
                else if (i == mat.size() - 1) {
                    out << "┘\n";
                }
                else {
                    out << "│\n";
                }
            }
            return out;

        }
        Matrix3n GetMat3n(string face) {
            Matrix3n mat3n;

            for (int i = 0; i < this->n; i++) {
                mat3n[i] = (this->arrays[i]).GetVec3(face);
            }
            return mat3n;
        }
        Matrix3n GetMat3n() {
            Matrix3n mat3n;
            for (int i = 0; i < this->n; i++) {
                mat3n.arrays.push_back(this->arrays[i].GetVec3());
            }
            return mat3n;
        }
    };
    //mesh网格(保存模型)
    class Mesh {
    public :
        Matrix4n vertexs;
        vector<vector<int> > faces;
        Matrix4n GetFace(int ind) {
            Matrix4n mat4n;
            for (auto i : faces[ind]) {
                mat4n.arrays.push_back(this->vertexs[i]);
            }
            return mat4n;
        }
        friend Mesh &operator * (Mesh &mesh, const Matrix4x4 &mat) {
            Mesh *res = new Mesh;
            res->vertexs = mesh.vertexs * mat;
            res->faces = mesh.faces;
            return *res;
        }
    };
    typedef std::function<Vector3(double)> CurveSegment;
    CurveSegment operator * (const double& k, const CurveSegment& segs) {
        return [k, &segs](double x)->Vector3 {
            return k * segs(x);
            };
    }
    //曲线类
    class Curve {
    public:
        vector<CurveSegment> segments;
        int size() {
            return segments.size();
        }
        CurveSegment& operator [] (int ind) {
            return segments[ind];
        }
        

        Curve(){}
        //根据y=f(x)生成曲线
        Curve(double st, double ed, function<double(double)> f) {
            for (double i = st; i <= ed; i += 1) {
                segments.push_back([i,f](double t)->Vector3{
                    return{ i + t, f(t + i),1 };
                });
            }
        }

        //根据参数方程生成曲线
        Curve(double st, double ed, function<Vector3(double)> f) {
            for (double i = st; i <= ed; i += 1) {
                segments.push_back([i,f](double t)->Vector3 {
                    return f(i+t);
                });
                if (i + 1 > ed) {
                    
                }
            }
        }

        Curve(int sz) {
            segments = vector<CurveSegment>(sz);
        }

        Curve GetWeighted(function<double(double)>f1, function<double(double)>f2) {
            Curve res;
            for (int i = 1; i < (this->size()); i++) {
                auto seg_i = (*this)[i];
                auto seg_last = (*this)[i-1];
                res.segments.push_back([f1, f2, seg_i, seg_last](double t)->Vector3 {
                    return f1(t) * seg_last(t / 2) + f2(t) * seg_i(0.5 + t / 2);
                });
            }
            return res;
        }
        Curve GetWeighted() {
            return this->GetWeighted([](double x) {return x; }, [](double x) {return 1 - x; });
        }

    };

    class Canvas {
    public:
        void DrawArrow(Vector3 p1, Vector3 p2);
        int w = WINW, h = WINH;
        struct Axis {
            double ppu;
            double unit;
            int x, y;
        } axis = { 50, 1, WINW / 2,WINH / 2 };
        void Init() {
            initgraph(w, h);
            setbkcolor(WHITE);
            setcolor(BLACK);
            cleardevice();
        }
        void SetAxis(int x, int y, double scale)
        {
            double unit = 1;

            //pixelsPerUnit 单位长度对应像素数
            double ppu = 10 / scale;
            while (ppu >= 100) {
                unit /= 10;
                ppu /= 10;
            }

            while (ppu < 10) {
                unit *= 10;
                ppu *= 10;
            }
            this->axis.ppu = ppu;
            this->axis.unit = unit;
            this->axis.x = x;
            this->axis.y = y;
        }
        void SetAxis(double scale) {
            SetAxis(axis.x, axis.y, scale);
        }
        void DrawAxis()
        {
            //单位长度大小
            double unit = this->axis.unit;
            //pixelsPerUnit 单位长度对应像素数
            double ppu = this->axis.ppu;
            int x0 = this->axis.x;
            int y0 = this->axis.y;

            COLORREF col = getcolor();
            COLORREF bkmode = getbkmode();
            COLORREF fillcol = getfillcolor();

            setbkmode(TRANSPARENT);
            int colorArg = max(0, (sqrt(ppu) - 2.26227766016) / 0.43377);
            setcolor(RGB(255 - colorArg * 2, 255 - colorArg * 2, 255 - colorArg * 2));
            settextstyle(15, 0, _T("Consolas"));
            double ppu10 = 10 * ppu;
            double unit10 = 10 * unit;

            for (int i = 1; x0 + i * ppu <= this->w; i++) {
                line(x0 + i * ppu, 0, x0 + i * ppu, this->h);
                TCHAR s[100];
                swprintf_s(s, _T("%.1lf"), i * unit);
                outtextxy(x0 + i * ppu + 2, y0 + 2, s);
            }
            for (int i = 1; x0 - i * ppu >= 0; i++) {
                line(x0 - i * ppu, 0, x0 - i * ppu, this->h);
                TCHAR s[100];
                swprintf_s(s, _T("-%.1lf"), i * unit);
                outtextxy(x0 - i * ppu + 2, y0 + 2, s);
            }
            for (int i = 1; y0 + i * ppu <= WINH; i++) {
                line(0, y0 + i * ppu, WINW, y0 + i * ppu);
                TCHAR s[100];
                swprintf_s(s, _T("-%.1lf"), i * unit);
                outtextxy(x0 + 2, y0 + i * ppu + 2, s);
            }
            for (int i = 1; y0 - i * ppu >= 0; i++) {
                line(0, y0 - i * ppu, WINW, y0 - i * ppu);
                TCHAR s[100];
                swprintf_s(s, _T("%.1lf"), i * unit);
                outtextxy(x0 + 2, y0 - i * ppu + 2, s);
            }

            setcolor(RGB(220, 220, 220));

            for (int i = 1; x0 + i * ppu10 <= this->w; i++) {
                line(x0 + i * ppu10, 0, x0 + i * ppu10, this->h);
                TCHAR s[100];
                swprintf_s(s, _T("%.1lf"), i * unit10);
                outtextxy(x0 + i * ppu10 + 2, y0 + 2, s);
            }
            for (int i = 1; x0 - i * ppu10 >= 0; i++) {
                line(x0 - i * ppu10, 0, x0 - i * ppu10, this->w);
                TCHAR s[100];
                swprintf_s(s, _T("%c%.1lf"), '-', i * unit10);
                outtextxy(x0 - i * ppu10 + 2, y0 + 2, s);
            }
            for (int i = 1; y0 + i * ppu10 <= this->h; i++) {
                line(0, y0 + i * ppu10, this->w, y0 + i * ppu10);
                TCHAR s[100];
                swprintf_s(s, _T("%c%.1lf"), '-', i * unit10);
                outtextxy(x0 + 2, y0 + i * ppu10 + 2, s);
            }
            for (int i = 1; y0 - i * ppu10 >= 0; i++) {
                line(0, y0 - i * ppu10, this->w, y0 - i * ppu10);
                TCHAR s[100];
                swprintf_s(s, _T("%.1lf"), i * unit10);
                outtextxy(x0 + 2, y0 - i * ppu10 + 2, s);
            }

            setcolor(RGB(80, 80, 80));
            setfillcolor(RGB(80, 80, 80));
            line(0, y0, this->w, y0);
            line(x0, 0, x0, this->h);
            fillcircle(x0, y0, 2);
            outtextxy(x0 + 2, y0 + 2, _T("0"));

            setfillcolor(fillcol);
            setcolor(col);
            setbkmode(bkmode);
        }
        Canvas(int w, int h) {
            this->w = w;
            this->h = h;
            axis = { 50, 1, w / 2, h / 2 };
            SetAxis(w / 2, h / 2, 1);
        }
        Vector3 GetPos(const Vector3& pos) {
            Vector3 res = pos.Normalize();
            res[0] = this->axis.x + (res[0] / this->axis.unit) * this->axis.ppu;
            res[1] = this->axis.y - (res[1] / this->axis.unit) * this->axis.ppu;
            return res;
        }
        void DrawPoint(Vector3 pos)
        {
            Vector3 winPos = GetPos(pos);
            long long colArg = 255 - min(255, abs(winPos[0] - this->axis.x) + abs(winPos[1] - this->axis.y));
            if (colArg >= 250 || winPos[0] > WINW || winPos[0] < 0 || winPos[1] > WINH || winPos[1] < 0) {
                return;
            }
            settextstyle(15 - min(5, colArg / 20), 0, _T("Consolas"));
            COLORREF col = getcolor();
            COLORREF bkmode = getbkmode();
            COLORREF fillcol = getfillcolor();
            setcolor(RGB(colArg, colArg, colArg));
            setbkmode(TRANSPARENT);
            setfillcolor(RGB(80, 80, 80));
            fillcircle(winPos[0], winPos[1], 2);
            TCHAR s[30];
            swprintf_s(s, _T("(%.1lf,%.1lf)"), pos[0], pos[1]);
            outtextxy(winPos[0] + 2, winPos[1] + 2, s);
            setcolor(col);
            setfillcolor(fillcol);
            setbkmode(bkmode);
        }
        void DrawCruve(Curve crv) {
            for (int i = 0; i < crv.size(); i++) {
                for (double j = 0; j < 1; j += 1.0 / 100) {
                    double next = j + 1.0 / 100;
                    Vector3 p1 = crv[i](j);
                    Vector3 p2 = crv[i](next);
                    auto pos1 = GetPos(p1);
                    auto pos2 = GetPos(p2);
                    line(pos1[0], pos1[1], pos2[0], pos2[1]);
                }
            }
        }
        //绘制2维图形多边形（填充）
        void DrawFillPolygon(Matrix3n mat) {
            int* poly = (int*)malloc(2 * mat.size() * sizeof(int));
            for (int i = 0; i < mat.size(); i++) {
                auto pos = GetPos(mat[i]);
                poly[i * 2] = pos[0];
                poly[i * 2 + 1] = pos[1];
            }
            OELFill(poly, mat.size(), LIGHTGRAY);
        }
        //绘制2维图形多边形
        void DrawPolygon(Matrix3n mat) {
            int* poly = (int*)malloc(2 * mat.size() * sizeof(int));
            for (int i = 0; i < mat.size(); i++) {
                auto pos = GetPos(mat[i]);
                DrawPoint(mat[i]);
                poly[i * 2] = pos[0];
                poly[i * 2 + 1] = pos[1];
            }
            polygon((POINT*)poly, mat.size());
        }
        //绘制2维图形线
        void DrawLine(Vector3 p1, Vector3 p2) {
            auto pos1 = GetPos(p1);
            auto pos2 = GetPos(p2);
            line(pos1[0], pos1[1], pos2[0], pos2[1]);
        }
        //3维模型渲染器
        void Mesh_Render(Mesh& mesh) {

            for (int i = 0; i < mesh.faces.size(); i++) {
                Matrix4n x = mesh.GetFace(i);
                DrawPolygon((mesh.GetFace(i) * Mat4_OrthoProjection()).GetMat3n());
            }
        }
    };
    //可变大小矩阵
    class Matrix {
    public:
        vector<vector<double> >d;
        int w, h;

        Matrix() {}
        Matrix(int h, int w) {
            this->w = w;
            this->h = h;
            d = vector<vector<double> >(h, vector<double>(w, 0));
        }
        Matrix(int h, int w, int val) {
            this->w = w;
            this->h = h;
            d = vector<vector<double> >(h, vector<double>(w, val));
        }
        Matrix(int h, int w, vector<double> list) {
            this->w = w;
            this->h = h;
            d = vector<vector<double> >(h, vector<double>(w));
            int cnt = 0;
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    d[i][j] = list[cnt++];
                }
            }
        }
        Matrix(vector<Vector3> list) {
            this->h = list.size();
            this->w = 3;
            d = vector<vector<double> >(h, vector<double>(w));
            int cnt = 0;
            for (auto x : list) {
                d[cnt++] = { x[0], x[1], x[2] };
            }
        }

        vector<double>& operator [](int i) {
            return this->d[i];
        }
        //矩阵乘法
        Matrix operator * (const Matrix& mat) {
            if (w != mat.h) {
                throw "Matrix shape mismatch!";
                return *this;
            }
            Matrix res = { h, mat.w, 0 };
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < mat.w; j++) {
                    for (int k = 0; k < w; k++) {
                        res.d[i][j] += this->d[i][k] * mat.d[k][j];
                    }
                }
            }
            return res;
        }
        //矩阵加法
        Matrix operator + (const Matrix& mat) {
            if (w != mat.w || h != mat.h) {
                throw "Matrix shape mismatch!";
                return *this;
            }
            Matrix res = { h, w, 0 };
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    res.d[i][j] = this->d[i][j] + mat.d[i][j];
                }
            }
            return res;
        }
        //矩阵减法
        Matrix operator - (const Matrix& mat) {
            if (w != mat.w || h != mat.h) {
                throw "Matrix shape mismatch!";
                return *this;
            }
            Matrix res = { h, w, 0 };
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    res.d[i][j] = this->d[i][j] - mat.d[i][j];
                }
            }
            return res;
        }
        //输出矩阵
        friend ostream& operator << (ostream& out, const Matrix& mat) {
            for (int i = 0; i < mat.h; i++) {
                if (mat.h == 1) {
                    out << "\n[";
                }
                else if (i == 0) {
                    out << "\n┌ ";
                }
                else if (i == mat.h - 1) {
                    out << "└ ";
                }
                else {
                    out << "│ ";
                }

                for (int j = 0; j < mat.w; j++) {
                    out << mat.d[i][j] << " ";
                }

                if (mat.h == 1) {
                    out << "]\n";
                }
                else if (i == 0) {
                    out << "┐\n";
                }
                else if (i == mat.h - 1) {
                    out << "┘\n";
                }
                else {
                    out << "│\n";
                }
            }
            return out;

        }

        static Matrix Identity(int index) {
            Matrix res(index, index, 0);
            for (int i = 0; i < index; i++) {
                res[i][i] = 1;
            }
            return res;
        }
    };
    class Vector : public Matrix {
    public:
        static enum eDir {
            horizontal, vertical
        };
        Vector() {};
        eDir dir;
        Vector(int len) {
            this->w = len;
            this->h = 1;
            dir = horizontal;
            d = vector<vector<double> >(1, vector<double>(len, 0));
        }
        //dir = 0横向, dir = 1竖向
        Vector(int len, eDir direction) {
            this->dir = direction;
            if (direction == horizontal) {
                this->w = len;
                this->h = 1;
                d = vector<vector<double> >(1, vector<double>(len, 0));
            }
            else {
                this->w = 1;
                this->h = len;
                d = vector<vector<double> >(len, vector<double>(1, 0));
            }

        }
        Vector(int len, int val) {
            this->w = len;
            this->h = 1;
            dir = horizontal;
            d = vector<vector<double> >(1, vector<double>(len, val));
        }
        //dir = 0横向, dir = 1竖向
        Vector(int len, eDir direction, int val) {
            this->dir = direction;
            if (direction == horizontal) {
                this->w = len;
                this->h = 1;
                d = vector<vector<double> >(1, vector<double>(len, val));
            }
            else {
                this->w = 1;
                this->h = len;
                d = vector<vector<double> >(len, vector<double>(1, val));
            }

        }
        Vector(vector<double> list) {
            this->w = list.size();
            this->h = 1;
            this->dir = horizontal;
            int cnt = 0;
            d = vector<vector<double> >(h, vector<double>(w));
            for (auto x : list) {
                (*this)[cnt++] = x;
            }
        }
        //dir = 0横向, dir = 1竖向
        Vector(vector<double> list, eDir direciton) {
            if (direciton == horizontal) {
                this->w = list.size();
                this->h = 1;
            }
            else {
                this->w = 1;
                this->h = list.size();
            }
            d = vector<vector<double> >(h, vector<double>(w));
            this->dir = direciton;
            int cnt = 0;
            for (auto x : list) {
                (*this)[cnt++] = x;
            }
        }
        double& operator [](int i) {
            if (dir == 0) {
                return this->d[0][i];
            }
            else {
                return this->d[i][0];
            }
        }

    };
    //=====================第二章============================
    //数值微分画线算法（DDA）
    void DDALine(int x1, int y1, int x2, int y2, COLORREF col)
    {
        int print_max_i = LINE_STYLE_DATA.thinkness - 1 >> 1;
        int print_begin_i = -(LINE_STYLE_DATA.thinkness >> 1);
        int ls_mode = LINE_STYLE_DATA.mode;
        int printCnt = 0, thickCnt = 0;
        auto printPixel = [&thickCnt, &printCnt, print_max_i, print_begin_i, ls_mode](int x, int y, COLORREF col, bool dir/*0横向 1纵向*/) {
            if (thickCnt >= LINE_STYLE_DATA.thinkness) {
                printCnt = (printCnt + 1) % 32;
                thickCnt = 0;
            }
            thickCnt++;

            if ((LINE_STYLE_DATA.pattern & (1 << printCnt)) == 0) {
                return;
            }
            if (LINE_STYLE_DATA.mode == MD_LS_SQUARE) {
                printCnt = (printCnt + 1) % 32;
                thickCnt = -LINE_STYLE_DATA.thinkness;
            }

            if (ls_mode == MD_LS_LINE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    if (dir == 0) {
                        putpixel(x + i, y, col);
                    }
                    else {
                        putpixel(x, y + i, col);
                    }
                }
            }
            else if (ls_mode == MD_LS_SQUARE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    for (int j = print_begin_i; j <= print_max_i; j++) {
                        putpixel(x + i, y + j, col);
                    }
                }
            }
            };
        double k = (y2 - y1) / (double)(x2 - x1);

        if (abs(k) <= 1) {
            if (x2 < x1) {
                swap(x1, x2);
                swap(y1, y2);
            }
            for (double x = x1, y = y1; x <= x2; x++) {
                printPixel((int)x, (int)(y + 0.5), col, 1);

                y += k;
            }
        }

        if (abs(k) > 1) {
            if (y2 < y1) {
                swap(x1, x2);
                swap(y1, y2);
            }
            for (double x = x1, y = y1; y <= y2; y++) {
                printPixel((int)(x + 0.5), (int)y, col, 0);
                x += 1 / k;
            }
        }
    }
    //中点画线算法（MP）
    void MPLine(int x1, int y1, int x2, int y2, COLORREF col)
    {
        int print_max_i = LINE_STYLE_DATA.thinkness - 1 >> 1;
        int print_begin_i = -(LINE_STYLE_DATA.thinkness >> 1);
        int ls_mode = LINE_STYLE_DATA.mode;
        int printCnt = 0, thickCnt = 0;
        bool flag_lastPrint = 0;
        auto printPixel = [&flag_lastPrint, &thickCnt, &printCnt, print_max_i, print_begin_i, ls_mode](int x, int y, COLORREF col, bool dir/*0横向 1纵向*/) {
            if (thickCnt >= LINE_STYLE_DATA.thinkness) {
                printCnt = (printCnt + 1) % 32;
                thickCnt = 0;
            }
            thickCnt++;

            if ((LINE_STYLE_DATA.pattern & (1 << printCnt)) == 0) {
                if (ls_mode == MD_LS_SQUARE && flag_lastPrint) {
                    thickCnt = -2 * LINE_STYLE_DATA.thinkness;
                }
                flag_lastPrint = 0;
                return;
            }
            flag_lastPrint = 1;
            if (ls_mode == MD_LS_LINE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    if (dir == 0) {
                        putpixel(x + i, y, col);
                    }
                    else {
                        putpixel(x, y + i, col);
                    }
                }
            }
            else if (ls_mode == MD_LS_SQUARE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    for (int j = print_begin_i; j <= print_max_i; j++) {
                        putpixel(x + i, y + j, col);
                    }
                }
            }
            };

        if (x2 < x1) {
            swap(x1, x2);
            swap(y1, y2);
        }
        int a = y1 - y2;
        int b = x2 - x1;

        if (abs(b) >= abs(a) && a <= 0) {
            int d = 2 * a + b;
            for (int x = x1, y = y1; x <= x2; x++) {
                printPixel(x, y, col, 1);
                if (d < 0) {
                    d = d + 2 * a + 2 * b;
                    y++;
                }
                else {
                    d = d + 2 * a;
                }

            }
        }
        if (abs(b) >= abs(a) && a > 0) {
            int d = 2 * a - b;
            for (int x = x1, y = y1; x <= x2; x++) {
                printPixel(x, y, col, 1);
                if (d > 0) {
                    d = d + 2 * a - 2 * b;
                    y--;
                }
                else {
                    d = d + 2 * a;
                }

            }
        }
        if (abs(b) < abs(a) && a >= 0) {
            int d = -a + 2 * b;
            for (int x = x2, y = y2; y <= y1; y++) {
                printPixel(x, y, col, 0);
                if (d > 0) {
                    d = d + 2 * b - 2 * a;
                    x--;
                }
                else {
                    d = d + 2 * b;
                }

            }
        }
        if (abs(b) < abs(a) && a < 0) {
            int d = a + 2 * b;
            for (int x = x1, y = y1; y <= y2; y++) {
                printPixel(x, y, col, 0);
                if (d > 0) {
                    d = d + 2 * b + 2 * a;
                    x++;
                }
                else {
                    d = d + 2 * b;
                }

            }
        }


    }
    //BH画线算法（Bresenham）
    void BHLine(int x1, int y1, int x2, int y2, COLORREF col)
    {
        int print_max_i = LINE_STYLE_DATA.thinkness - 1 >> 1;
        int print_begin_i = -(LINE_STYLE_DATA.thinkness >> 1);
        int ls_mode = LINE_STYLE_DATA.mode;
        int printCnt = 0, thickCnt = 0;
        bool flag_lastPrint = 0;
        auto printPixel = [&flag_lastPrint, &thickCnt, &printCnt, print_max_i, print_begin_i, ls_mode](int x, int y, COLORREF col, bool dir/*0横向 1纵向*/) {
            if (thickCnt >= LINE_STYLE_DATA.thinkness) {
                printCnt = (printCnt + 1) % 32;
                thickCnt = 0;
            }
            thickCnt++;

            if ((LINE_STYLE_DATA.pattern & (1 << printCnt)) == 0) {
                if (ls_mode == MD_LS_SQUARE && flag_lastPrint) {
                    thickCnt = -2 * LINE_STYLE_DATA.thinkness;
                }
                flag_lastPrint = 0;
                return;
            }
            flag_lastPrint = 1;
            if (ls_mode == MD_LS_LINE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    if (dir == 0) {
                        putpixel(x + i, y, col);
                    }
                    else {
                        putpixel(x, y + i, col);
                    }
                }
            }
            else if (ls_mode == MD_LS_SQUARE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    for (int j = print_begin_i; j <= print_max_i; j++) {
                        putpixel(x + i, y + j, col);
                    }
                }
            }
            };


        if (x2 < x1) {
            swap(x1, x2);
            swap(y1, y2);
        }
        int dy = y2 - y1;
        int dx = x2 - x1;

        if (abs(dx) >= abs(dy) && dy >= 0) {
            int d = dx - 2 * dy;
            for (int x = x1, y = y1; x <= x2; x++) {
                printPixel(x, y, col, 1);
                if (d < 0) {
                    d += 2 * dx - 2 * dy;
                    y++;
                }
                else {
                    d += -2 * dy;
                }

            }
        }
        if (abs(dx) >= abs(dy) && dy < 0) {
            int d = -2 * dy - dx;
            for (int x = x1, y = y1; x <= x2; x++) {
                printPixel(x, y, col, 1);
                if (d > 0) {
                    d += -2 * dx - 2 * dy;
                    y--;
                }
                else {
                    d += -2 * dy;
                }

            }
        }
        if (abs(dx) < abs(dy) && dy >= 0) {
            int d = 2 * dx - dy;
            for (int x = x1, y = y1; y <= y2; y++) {
                printPixel(x, y, col, 0);
                if (d > 0) {
                    d += 2 * dx - 2 * dy;
                    x++;
                }
                else {
                    d += 2 * dx;
                }

            }
        }
        if (abs(dx) < abs(dy) && dy < 0) {
            int d = -2 * dx - dy;
            for (int x = x2, y = y2; y <= y1; y++) {
                printPixel(x, y, col, 0);
                if (d < 0) {
                    d += -2 * dx - 2 * dy;
                    x--;
                }
                else {
                    d += -2 * dx;
                }

            }
        }

    }
    //中点画圆算法（MP）
    void MPCircle(int x0, int y0, int r, COLORREF col)
    {
        int print_max_i = LINE_STYLE_DATA.thinkness - 1 >> 1;
        int print_begin_i = -(LINE_STYLE_DATA.thinkness >> 1);
        int ls_mode = LINE_STYLE_DATA.mode;
        int printCnt = 0, thickCnt = 0;
        bool flag_lastPrint = 0;
        auto printPixel = [&flag_lastPrint, &thickCnt, &printCnt, print_max_i, print_begin_i, ls_mode](int x, int y, COLORREF col, bool dir/*0横向 1纵向*/) {
            if (ls_mode == MD_LS_LINE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    if (dir == 0) {
                        putpixel(x + i, y, col);
                    }
                    else {
                        putpixel(x, y + i, col);
                    }
                }
            }
            else if (ls_mode == MD_LS_SQUARE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    for (int j = print_begin_i; j <= print_max_i; j++) {
                        putpixel(x + i, y + j, col);
                    }
                }
            }
            };
        auto putPixel_8 = [&thickCnt, &printCnt, &ls_mode, &flag_lastPrint, printPixel](int x0, int y0, int x, int y, COLORREF col) {
            if (thickCnt >= LINE_STYLE_DATA.thinkness) {
                printCnt = (printCnt + 1) % 32;
                thickCnt = 0;
            }
            thickCnt++;

            if ((LINE_STYLE_DATA.pattern & (1 << printCnt)) == 0) {
                if (ls_mode == MD_LS_SQUARE && flag_lastPrint) {
                    thickCnt = -2 * LINE_STYLE_DATA.thinkness;
                }
                flag_lastPrint = 0;
                return;
            }
            flag_lastPrint = 1;
            printPixel(x0 + x, y0 + y, col, 1);
            printPixel(x0 - x, y0 + y, col, 1);
            printPixel(x0 + x, y0 - y, col, 1);
            printPixel(x0 - x, y0 - y, col, 1);

            printPixel(x0 + y, y0 + x, col, 0);
            printPixel(x0 - y, y0 + x, col, 0);
            printPixel(x0 + y, y0 - x, col, 0);
            printPixel(x0 - y, y0 - x, col, 0);
            };
        double d = 1.25 - r;
        for (int x = 0, y = r; x <= y; x++) {
            putPixel_8(x0, y0, x, y, col);
            if (d < 0) {
                d += 2 * x + 3;
            }
            else {
                d += 2 * x - 2 * y + 5;
                y--;
            }
        }

    }
    //中点画椭圆算法（MP）
    void MPEllipse(int x0, int y0, int a, int b, COLORREF col) {
        int print_max_i = LINE_STYLE_DATA.thinkness - 1 >> 1;
        int print_begin_i = -(LINE_STYLE_DATA.thinkness >> 1);
        int ls_mode = LINE_STYLE_DATA.mode;
        int printCnt = 0, thickCnt = 0;
        bool flag_lastPrint = 0;
        auto printPixel = [&flag_lastPrint, &thickCnt, &printCnt, print_max_i, print_begin_i, ls_mode](int x, int y, COLORREF col, bool dir/*0横向 1纵向*/) {
            if (ls_mode == MD_LS_LINE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    if (dir == 0) {
                        putpixel(x + i, y, col);
                    }
                    else {
                        putpixel(x, y + i, col);
                    }
                }
            }
            else if (ls_mode == MD_LS_SQUARE) {
                for (int i = print_begin_i; i <= print_max_i; i++) {
                    for (int j = print_begin_i; j <= print_max_i; j++) {
                        putpixel(x + i, y + j, col);
                    }
                }
            }
            };
        auto putPixel_4 = [&thickCnt, &printCnt, &ls_mode, &flag_lastPrint, printPixel](int x0, int y0, int x, int y, COLORREF col, bool dir) {
            if (thickCnt >= LINE_STYLE_DATA.thinkness) {
                printCnt = (printCnt + 1) % 32;
                thickCnt = 0;
            }
            thickCnt++;

            if ((LINE_STYLE_DATA.pattern & (1 << printCnt)) == 0) {
                if (ls_mode == MD_LS_SQUARE && flag_lastPrint) {
                    thickCnt = -2 * LINE_STYLE_DATA.thinkness;
                }
                flag_lastPrint = 0;
                return;
            }
            flag_lastPrint = 1;
            printPixel(x0 + x, y0 + y, col, dir);
            printPixel(x0 - x, y0 + y, col, dir);
            printPixel(x0 + x, y0 - y, col, dir);
            printPixel(x0 - x, y0 - y, col, dir);
            };
        double d = -(a * a * b) + (b * b) + (a * a / 4);
        for (int x = 0, y = b; a * a * y >= b * b * x && x <= a; x++) {
            putPixel_4(x0, y0, x, y, col, 1);
            if (d < 0) {
                d += b * b * (2 * x + 3);
            }
            else {
                d += b * b * (2 * x + 3) + a * a * (2 - 2 * y);
                y--;
            }
        }

        d = -(b * b * a) + (a * a) + (b * b / 4);
        for (int x = a, y = 0; a * a * y <= b * b * x && y <= b; y++) {
            putPixel_4(x0, y0, x, y, col, 0);
            if (d < 0) {
                d += a * a * (2 * y + 3);
            }
            else {
                d += a * a * (2 * y + 3) + b * b * (2 - 2 * x);
                x--;
            }
        }
    }
    //4向种子填充
    void SeedFill_4(int x, int y, COLORREF boundaryColor, COLORREF fillColor)
    {
        if (BATCHDRAW) BeginBatchDraw();

        seedFill_fillMap.reset();

        queue<pair<int, int> >queue_points;
        queue_points.push({ x, y });
        while (!queue_points.empty()) {
            int x_i = queue_points.front().first;
            int y_i = queue_points.front().second;
            queue_points.pop();

            COLORREF pixelColor = getpixel(x_i, y_i);
            if (pixelColor == boundaryColor || pixelColor == fillColor) {
                continue;
            }
            if ((FILL_PATTERN[y_i % 8] & (1 << (7 - x_i % 8)))) {
                putpixel(x_i, y_i, fillColor);
            }

            if (x_i + 1 < WINW && seedFill_fillMap[(x_i + 1) * WINH + y_i] == 0) {
                queue_points.push({ x_i + 1,y_i });
                seedFill_fillMap[(x_i + 1) * WINH + y_i] = 1;
            }
            if (x_i - 1 >= 0 && seedFill_fillMap[(x_i - 1) * WINH + y_i] == 0) {
                queue_points.push({ x_i - 1,y_i });
                seedFill_fillMap[(x_i - 1) * WINH + y_i] = 1;
            }
            if (y_i + 1 < WINH && seedFill_fillMap[x_i * WINH + y_i + 1] == 0) {
                queue_points.push({ x_i, y_i + 1 });
                seedFill_fillMap[x_i * WINH + y_i + 1] = 1;
            }
            if (y_i - 1 >= 0 && seedFill_fillMap[x_i * WINH + y_i - 1] == 0) {
                queue_points.push({ x_i, y_i - 1 });
                seedFill_fillMap[x_i * WINH + y_i - 1] = 1;
            }

        }

        if (BATCHDRAW) EndBatchDraw();
    }
    //8向种子填充
    void SeedFill_8(int x, int y, COLORREF boundaryColor, COLORREF fillColor)
    {
        if (BATCHDRAW) BeginBatchDraw();

        seedFill_fillMap.reset();

        queue<pair<int, int> >queue_points;
        queue_points.push({ x, y });
        while (!queue_points.empty()) {
            int x_i = queue_points.front().first;
            int y_i = queue_points.front().second;
            queue_points.pop();

            COLORREF pixelColor = getpixel(x_i, y_i);
            if (pixelColor == boundaryColor || pixelColor == fillColor) {
                continue;
            }
            if ((FILL_PATTERN[y_i % 8] & (1 << (7 - x_i % 8)))) {
                putpixel(x_i, y_i, fillColor);
            }

            if (x_i + 1 < WINW && seedFill_fillMap[(x_i + 1) * WINH + y_i] == 0) {
                queue_points.push({ x_i + 1,y_i });
                seedFill_fillMap[(x_i + 1) * WINH + y_i] = 1;
            }
            if (x_i - 1 >= 0 && seedFill_fillMap[(x_i - 1) * WINH + y_i] == 0) {
                queue_points.push({ x_i - 1,y_i });
                seedFill_fillMap[(x_i - 1) * WINH + y_i] = 1;
            }
            if (y_i + 1 < WINH && seedFill_fillMap[x_i * WINH + y_i + 1] == 0) {
                queue_points.push({ x_i, y_i + 1 });
                seedFill_fillMap[x_i * WINH + y_i + 1] = 1;
            }
            if (y_i - 1 >= 0 && seedFill_fillMap[x_i * WINH + y_i - 1] == 0) {
                queue_points.push({ x_i, y_i - 1 });
                seedFill_fillMap[x_i * WINH + y_i - 1] = 1;
            }
            if (x_i + 1 < WINW && y_i + 1 < WINH && seedFill_fillMap[(x_i + 1) * WINH + y_i + 1] == 0) {
                queue_points.push({ x_i + 1,y_i + 1 });
                seedFill_fillMap[(x_i + 1) * WINH + y_i + 1] = 1;
            }
            if (x_i + 1 < WINW && y_i - 1 >= 0 && seedFill_fillMap[(x_i + 1) * WINH + y_i - 1] == 0) {
                queue_points.push({ x_i + 1,y_i - 1 });
                seedFill_fillMap[(x_i + 1) * WINH + y_i - 1] = 1;
            }
            if (x_i - 1 >= 0 && y_i + 1 < WINH && seedFill_fillMap[(x_i - 1) * WINH + y_i + 1] == 0) {
                queue_points.push({ x_i - 1, y_i + 1 });
                seedFill_fillMap[(x_i - 1) * WINH + y_i + 1] = 1;
            }
            if (x_i - 1 >= 0 && y_i - 1 >= 0 && seedFill_fillMap[(x_i - 1) * WINH + y_i - 1] == 0) {
                queue_points.push({ x_i - 1, y_i - 1 });
                seedFill_fillMap[(x_i - 1) * WINH + y_i - 1] = 1;
            }

        }

        if (BATCHDRAW) EndBatchDraw();
    }
    //有序边表填充（Ordered Edge List）
    void OELFill(int* poly, int n, COLORREF col)//多边形有序边表填充（Ordered Edge List）
    {
        struct Edge {
            double x;
            double step;
            int ymax;
            Edge* next;
        };

        auto DelEdge = [](Edge*& p) {
            if (p != NULL) {
                Edge* temp = p->next;
                free(p);
                p = temp;
            }
            };
        auto InsEdge = [](Edge*& p, Edge* e) {
            Edge* temp = p, * newEdge = new Edge;
            newEdge->x = e->x;
            newEdge->step = e->step;
            newEdge->ymax = e->ymax;
            p = newEdge;
            newEdge->next = temp;
            };

        //建立有序边表
        Edge* v[WINH] = { NULL };
        int y_st = WINH, y_ed = 0;
        for (int i = 0; i < n; i++) {
            int ind = 2 * i;
            int x_i = poly[ind];
            int y_i = poly[ind + 1];

            //确定y范围
            y_st = min(y_st, y_i);
            y_ed = max(y_ed, y_i);

            int ind_last = 2 * (i - 1 >= 0 ? i - 1 : n - 1);
            int x_last = poly[ind_last];
            int y_last = poly[ind_last + 1];

            double k = (y_i - y_last) / (double)(x_i - x_last);
            if (k != 0) {
                Edge* temp;
                temp = new Edge;
                temp->step = 1 / k;
                temp->ymax = max(y_i, y_last);
                temp->x = y_last > y_i ? x_i : x_last;
                InsEdge(v[min(y_i, y_last)], temp);
            }

        }

        if (DEBUG) {
            for (int i = 10; i <= WINH - 10; i += 10) {
                BHLine(0, i, WINW, i, RGB(200, 200, 200));
            }
        }

        //构造活化边表，填充区域

        Edge* activeEdge = NULL;
        Edge* p;
        for (int h = y_st; h <= y_ed; h++) {

            int border_l = WINW, border_r = 0;
            //更新已存在的活化边
            p = activeEdge;
            Edge* last = NULL;
            while (p != NULL) {
                if (h >= p->ymax) {
                    //删除边
                    DelEdge(p);
                    if (last != NULL) {
                        last->next = p;
                    }
                    else {
                        activeEdge = p;
                    }
                    continue;
                }
                p->x += p->step;

                border_l = min(border_l, p->x);
                border_r = max(border_r, p->x);
                last = p;
                p = p->next;
            }

            //加入新边
            p = v[h];
            while (p != NULL) {
                border_l = min(border_l, p->x);
                border_r = max(border_r, p->x);

                InsEdge(activeEdge, p);
                p = p->next;
            }

            //填充
            bool flag_fill[WINW] = { 0 };
            p = activeEdge;
            while (p != NULL) {
                flag_fill[(int)(p->x + 0.5)] ^= 1;
                if (DEBUG) {
                    if (h % 10 == 0) {
                        MPCircle((int)(p->x + 0.5), h, 2, RGB(100, 100, 100));
                        SeedFill_4((int)(p->x + 0.5), h, RGB(100, 100, 100), RGB(100, 100, 100));
                    }
                }
                p = p->next;
            }
            bool state_fill = 0;
            for (int x = border_l; x <= border_r; x++) {
                if (flag_fill[x]) {
                    state_fill ^= 1;
                }
                if (state_fill) {
                    if (FILL_PATTERN[h % 8] & (1 << (7 - x % 8)))
                        putpixel(x, h, col);
                    if (DEBUG) {
                        if (h % 10 == 0) {
                            putpixel(x, h, BLUE);
                            putpixel(x, h + 1, BLUE);
                            putpixel(x, h - 1, BLUE);
                        }
                    }
                }
                else if (DEBUG) {
                    if (h % 10 == 0) {
                        putpixel(x, h, RGB(100, 100, 100));
                        putpixel(x, h + 1, RGB(100, 100, 100));
                        putpixel(x, h - 1, RGB(100, 100, 100));
                    }
                }
            }
            if (DEBUG) {
                if (h % 10 == 0) {
                    MPLine(border_l, h - 5, border_l, h + 5, RGB(100, 30, 30));
                    MPLine(border_r, h - 5, border_r, h + 5, RGB(100, 30, 30));
                }

            }
        }
    }
    //边填充算法（Edge Fill）
    void EFFill(int* poly, int n, COLORREF col)//边缘标志填充（Edge Flag Fill）算法
    {
        bool flag_fill[WINW + 1][WINH + 1] = { 0 };

        int border_l = WINW, border_r = 0, border_u = 0, border_d = WINH;
        for (int i = 0; i < n; i++) {
            int last_i = i - 1;
            if (last_i < 0) last_i += n;
            int x_i = poly[i * 2];
            int y_i = poly[i * 2 + 1];
            int x_last = poly[last_i * 2];
            int y_last = poly[last_i * 2 + 1];

            double b = (x_i - x_last) / (double)(y_i - y_last);
            double c = (-x_i * y_last + y_i * x_last) / (double)(y_i - y_last);

            int min_y = min(y_i, y_last);
            int max_y = max(y_i, y_last);

            border_d = min(y_i, border_d);
            border_u = max(y_i, border_u);
            border_l = min(x_i, border_l);
            border_r = max(x_i, border_r);

            double x = min_y * b + c;

            for (int y = min_y; y < max_y; y++) {
                flag_fill[(int)(x + 0.5)][y] ^= 1;
                x += b;
            }
        }

        for (int y = border_d; y <= border_u; y++) {
            bool state = 0;
            for (int x = border_l; x <= border_r; x++) {
                if (flag_fill[x][y]) {
                    state ^= 1;
                }
                if (state) {
                    if (FILL_PATTERN[y % 8] & (1 << (7 - x % 8))) {
                        putpixel(x, y, col);
                    }

                }

            }
        }
        if (DEBUG) {
            setlinestyle(PS_SOLID, 2);
            setcolor(RGB(100, 100, 100));
            rectangle(border_l, border_u, border_r, border_d);
        }
    }
    //栅栏填充算法（边填充改进）
    void EFFill_Fence(int* poly, int n, COLORREF col)//栅栏边缘填充算法
    {
        bool flag_flip[WINW][WINH] = { 0 };

        int border_u = 0, border_d = WINH, border_l = WINW, border_r = 0;

        for (int i = 0; i < n; i++) {
            int ind = 2 * i;
            int ind_last = 2 * (i - 1 >= 0 ? i - 1 : n - 1);

            int x_i = poly[ind];
            int y_i = poly[ind + 1];

            border_u = max(y_i, border_u);
            border_d = min(y_i, border_d);
            border_r = max(x_i, border_r);
            border_l = min(x_i, border_l);

            int x_last = poly[ind_last];
            int y_last = poly[ind_last + 1];

            double b = (x_i - x_last) / (double)(y_i - y_last);
            double c = (-x_i * y_last + y_i * x_last) / (double)(y_i - y_last);

            int y_min = min(y_i, y_last);
            int y_max = max(y_i, y_last);

            double x = y_min * b + c;
            for (int y = y_min; y < y_max; y++) {
                flag_flip[(int)(x + 0.5)][y] ^= 1;
                x += b;
            }
        }

        int mid = border_l + border_r >> 1;
        for (int y = border_d; y <= border_u; y++) {
            bool state_fill;

            state_fill = 0;
            for (int x = border_l; x <= mid; x++) {
                if (flag_flip[x][y]) {
                    state_fill ^= 1;
                }
                if (state_fill) {
                    if (FILL_PATTERN[y % 8] & (1 << (7 - x % 8))) {
                        putpixel(x, y, col);
                    }
                }
            }
            state_fill = 0;
            for (int x = border_r; x > mid; x--) {
                if (flag_flip[x][y]) {
                    state_fill ^= 1;
                }
                if (state_fill) {
                    if (FILL_PATTERN[y % 8] & (1 << (7 - x % 8))) {
                        putpixel(x, y, col);
                    }
                }
            }
        }
        if (DEBUG) {
            setlinestyle(PS_DASH, 2);
            setcolor(RGB(50, 50, 50));
            line(mid, border_u, mid, border_d);
            setlinestyle(PS_SOLID, 2);
            setcolor(RGB(100, 100, 100));
            rectangle(border_l, border_u, border_r, border_d);
        }
    }
    //设置填充样式
    void SetFillPattern(BYTE* pattern)
    {
        for (int i = 0; i < 8; i++)
            FILL_PATTERN[i] = pattern[i];
    }
    //设置view信息
    int SetView(int x1, int y1, int x2, int y2, int viewCnt = VIEWCNT)
    {
        if (x1 == x2 || y1 == y2) return -1;

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        VIEW_DATA[viewCnt] = { x1,y1,x2,y2 };

        return 0;
    }
    //获取view信息
    sVIEW* GetView(int viewCnt = VIEWCNT)
    {
        if (viewCnt > VIEWCNT) return NULL;

        return &VIEW_DATA[viewCnt];
    }
    //根据view裁剪直线
    void ViewClipLine(int x1, int y1, int x2, int y2, COLORREF col)//窗口裁剪直线
    {

        bool flag_vertical = 0;
        double line_k;
        double line_b;
        if (x2 != x1) {
            line_k = (y2 - y1) / (double)(x2 - x1);
            line_b = y1 - x1 * line_k;
        }
        else {
            flag_vertical = 1;
        }

        //临时数据类型point = pair<int, int>
        using point = pair<int, int>;

        //顺序：上下右左
        auto checkState = [](point p) -> int {
            sVIEW* view = GetView();
            int res = 0;
            if (p.second > view->y2) {
                res |= 1 << 3;
            }
            if (p.second < view->y1) {
                res |= 1 << 2;
            }
            if (p.first > view->x2) {
                res |= 1 << 1;
            }
            if (p.first < view->x1) {
                res |= 1 << 0;
            }
            return res;
            };

        auto findPoint = [line_k, line_b, flag_vertical](int edge, point p1, point p2) -> point {
            point res;
            if (edge & 0b1000) {
                //上
                if (flag_vertical) {
                    res.first = p1.first;
                }
                else {
                    res.first = (int)((GetView()->y2 - 1 - line_b) / line_k + 0.5);
                }
                res.second = GetView()->y2 - 1;
            }
            else if (edge & 0b0100) {
                //下
                if (flag_vertical) {
                    res.first = p1.first;
                }
                else {
                    res.first = (int)((GetView()->y1 + 1 - line_b) / line_k + 0.5);
                }
                res.second = GetView()->y1 + 1;
            }
            else if (edge & 0b0010) {
                //右
                if (line_k == 0) {
                    res.second = p1.second;
                }
                else {
                    res.second = (int)(line_k * (GetView()->x2 - 1) + line_b + 0.5);
                }
                res.first = GetView()->x2 - 1;
            }
            else if (edge & 0b0001) {
                //左
                if (line_k == 0) {
                    res.second = p1.second;
                }
                else {
                    res.second = (int)(line_k * (GetView()->x1 + 1) + line_b + 0.5);
                }
                res.first = GetView()->x1 + 1;
            }
            return res;
            };

        point p1 = { x1, y1 }, p2 = { x2, y2 };
        int cnt_check = 0;
        while (cnt_check <= 4) {
            cnt_check++;
            int state_p1 = checkState(p1);
            int state_p2 = checkState(p2);

            //直线完全在窗口外，舍去
            if (state_p1 & state_p2) {
                return;
            }

            //直线在窗口内，绘制
            if (state_p1 == 0 && state_p2 == 0) {
                MPLine(p1.first, p1.second, p2.first, p2.second, col);
                return;
            }

            if (state_p1) {
                p1 = findPoint(state_p1, p1, p2);
                continue;
            }
            if (state_p2) {
                p2 = findPoint(state_p2, p1, p2);
                continue;
            }
        }
    }
    //根据view裁剪多边形
    void ViewClipPolygon(int* poly, int n, COLORREF col, int* res = NULL, int* resCnt = NULL)
    {
        const int blockSize = 10;

        bool flag_temp = 0;

        //第i条边裁剪多边形存放位置4*n*i
        int* temp = (int*)malloc(5 * blockSize * n * sizeof(int));
        for (int i = 0; i < 2 * n; i++) {
            temp[i] = poly[i];
        }
        if (res == NULL) {
            flag_temp = 1;
            res = (int*)malloc(blockSize * n * sizeof(int));
        }
        bool flag_vertical;//直线是否垂直
        double line_k;//斜率
        double line_b;//截距

        //临时数据类型point = pair<int, int>
        using point = pair<int, int>;

        //找到直线与边界交点edge
        auto findPoint = [&line_k, &line_b, &flag_vertical](int edge, point p1, point p2) -> point {
            point res;
            if (edge & 0b1000) {
                //上
                if (flag_vertical) {
                    res.first = p1.first;
                }
                else {
                    res.first = (int)((GetView()->y2 - line_b) / line_k + 0.5);
                }
                res.second = GetView()->y2;
            }
            else if (edge & 0b0100) {
                //下
                if (flag_vertical) {
                    res.first = p1.first;
                }
                else {
                    res.first = (int)((GetView()->y1 - line_b) / line_k + 0.5);
                }
                res.second = GetView()->y1;
            }
            else if (edge & 0b0010) {
                //右
                if (line_k == 0) {
                    res.second = p1.second;
                }
                else {
                    res.second = (int)(line_k * (GetView()->x2) + line_b + 0.5);
                }
                res.first = GetView()->x2;
            }
            else if (edge & 0b0001) {
                //左
                if (line_k == 0) {
                    res.second = p1.second;
                }
                else {
                    res.second = (int)(line_k * (GetView()->x1) + line_b + 0.5);
                }
                res.first = GetView()->x1;
            }
            return res;
            };
        auto judgePos = [](int edge, int x, int y) -> bool {
            bool res = 0;
            switch (edge)
            {
            case(0b1000):
                //上
                if (y >= GetView()->y2) {
                    res = 1;
                }
                else {
                    res = 0;
                }
                break;
            case(0b0100):
                //下
                if (y <= GetView()->y1) {
                    res = 1;
                }
                else {
                    res = 0;
                }
                break;
            case(0b0010):
                //右
                if (x >= GetView()->x2) {
                    res = 1;
                }
                else {
                    res = 0;
                }
                break;
            case(0b0001):
                //左
                if (x <= GetView()->x1) {
                    res = 1;
                }
                else {
                    res = 0;
                }
                break;
            default:
                break;
            }
            return res;
            };

        //遍历顺序，左右下上
        int cnt_last = n;//记录上一个边处理后多边形边数
        for (int i = 0; i < 4; i++) {
            int edge = 1 << i;
            int cnt = 0;
            int base_ind = blockSize * n * i;
            int save_ind = blockSize * n * (i + 1);
            auto savePoint = [&, save_ind, temp](int& cnt, point p) {
                temp[save_ind + 2 * cnt] = p.first;
                temp[save_ind + 2 * cnt + 1] = p.second;
                cnt++;
                };

            for (int j = 0; j < cnt_last; j++) {
                int ind = base_ind + 2 * j;
                int ind_next = base_ind + 2 * (j + 1 == cnt_last ? 0 : j + 1);

                int x_j = temp[ind];
                int y_j = temp[ind + 1];
                int x_next = temp[ind_next];
                int y_next = temp[ind_next + 1];

                //计算斜率、截距等
                flag_vertical = 0;
                if (x_j != x_next) {
                    line_k = (y_next - y_j) / (double)(x_next - x_j);
                    line_b = y_j - x_j * line_k;
                }
                else {
                    flag_vertical = 1;
                }

                //判断与边界位置关系, 不可见为1，可见为0
                bool pos_j = judgePos(edge, x_j, y_j);
                bool pos_next = judgePos(edge, x_next, y_next);

                if (!pos_j && !pos_next) {
                    //均在可见侧，记录next
                    savePoint(cnt, { x_next,y_next });

                }
                else if (pos_j && !pos_next) {
                    //只有出点在可见侧，记录next和交点位置
                    point p = findPoint(edge, { x_j,y_j }, { x_next,y_next });
                    savePoint(cnt, p);
                    savePoint(cnt, { x_next,y_next });
                }
                else if (!pos_j && pos_next) {
                    point p = findPoint(edge, { x_j,y_j }, { x_next,y_next });
                    savePoint(cnt, p);
                }

            }
            cnt_last = cnt;
        }

        for (int i = 0; i < cnt_last * 2; i++) {
            int ind = 4 * blockSize * n + i;
            res[i] = temp[ind];
        }
        free(temp);
        int cnt = cnt_last;
        //输出结果
        for (int i = 0; i < cnt; i++) {
            int ind = i * 2;
            int x_i = res[ind];
            int y_i = res[ind + 1];

            int ind_next = 2 * ((i + 1) == cnt ? 0 : i + 1);
            int x_next = res[ind_next];
            int y_next = res[ind_next + 1];
            MPLine(x_i, y_i, x_next, y_next, col);
        }
        if (flag_temp) {
            free(res);
        }
        if (resCnt != NULL) {
            *resCnt = cnt;
        }



    }
    //设置线型
    void SetLineStyle(int thinkness, unsigned int pattern = LINE_STYLE_DATA.pattern, int mode = LINE_STYLE_DATA.mode)
    {
        LINE_STYLE_DATA.thinkness = thinkness;
        LINE_STYLE_DATA.pattern = pattern;
        LINE_STYLE_DATA.mode = mode;
    }
    //=====================第三章============================
    //2维图形平移变换矩阵
    Matrix3x3 Mat3_Translation(double dx, double dy) {
        Matrix3x3 mat = {
            1,  0,  0,
            0,  1,  0,
            dx, dy, 1
        };
        return mat;
    }
    //2维图形缩放变换矩阵
    Matrix3x3 Mat3_Scaling(double xs, double ys) {
        Matrix3x3 mat = {
            xs, 0,  0,
            0,  ys, 0,
            0,  0,  1
        };
        return mat;
    }
    //2维图形旋转变换矩阵
    Matrix3x3 Mat3_Rotation(double angle) {
        Matrix3x3 mat = {
            cos(angle) , sin(angle),  0,
            -sin(angle), cos(angle),  0,
            0          , 0         ,  1
        };
        return mat;
    }
    //2维图形对称变换矩阵，axis="y","x","y=x","y=-x","o"
    Matrix3x3 Mat3_Relection(string axis) {
        Matrix3x3 mat = {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        };
        transform(axis.begin(), axis.end(), axis.begin(), ::tolower);
        if (axis == "y") {
            mat = {
            -1, 0, 0,
             0, 1, 0,
             0, 0, 1
            };
        }
        if (axis == "x") {
            mat = {
            1,  0, 0,
            0, -1, 0,
            0,  0, 1
            };
        }
        if (axis == "y=x") {
            mat = {
            0, 1, 0,
            1, 0, 0,
            0, 0, 1
            };
        }
        if (axis == "y=-x") {
            mat = {
             0, -1, 0,
            -1,  0, 0,
             0,  0, 1
            };
        }
        if (axis == "o") {
            mat = {
             -1,  0, 0,
              0, -1, 0,
              0,  0, 1
            };
        }
        return mat;
    }
    //2维图形剪切变换矩阵，axis="y","x","y=x","y=-x","o"
    Matrix3x3 Mat3_Shear(double xs, double ys) {
        Matrix3x3 mat = {
            1  , ys, 0,
            xs , 1 , 0,
            0  , 0 , 1
        };
        return mat;
    }
    //2维图形绕任意点旋转矩阵
    Matrix3x3 Mat3_Rotation(Vector3 pivot, double angle) {
        Matrix3x3 mat = Mat3_Translation(-pivot.d[0], -pivot.d[1]);
        mat = mat * Mat3_Rotation(angle);
        mat = mat * Mat3_Translation(pivot.d[0], pivot.d[1]);
        return mat;
    }
    //2维图形相对于任意点比例变换矩阵
    Matrix3x3 Mat3_Scaling(Vector3 pivot, double xs, double ys) {
        Matrix3x3 mat = Mat3_Translation(-pivot.d[0], -pivot.d[1]);
        mat = mat * Mat3_Scaling(xs,ys);
        mat = mat * Mat3_Translation(pivot.d[0], pivot.d[1]);
        return mat;
    }
    //2维图形相对于任意点中心对称变换矩阵
    Matrix3x3 Mat3_Relection(Vector3 pivot) {
        Matrix3x3 mat = Mat3_Translation(-pivot.d[0], -pivot.d[1]);
        mat = mat * Mat3_Relection("o");
        mat = mat * Mat3_Translation(pivot.d[0], pivot.d[1]);
        return mat;
    }
    //2维图形相对于任意点直线对称变换矩阵
    Matrix3x3 Mat3_Relection(double line_k, double line_b) {
        line_k = -line_k;
        double angle = atan(line_k);
        Matrix3x3 mat = Mat3_Translation(0, -line_b);
        mat = mat * Mat3_Rotation(angle);
        mat = mat * Mat3_Relection("x");
        mat = mat * Mat3_Rotation(-angle);
        mat = mat * Mat3_Translation(0, line_b);
        return mat;
    }
    //3维图形平移变换矩阵
    Matrix4x4 Mat4_Translation(double dx, double dy, double dz) {
        Matrix4x4 mat = {
            1 ,0 ,0 ,0,
            0 ,1 ,0 ,0,
            0 ,0 ,1 ,0,
            dx,dy,dz,1
        };
        return mat;
    }
    //3维图形缩放变换矩阵
    Matrix4x4 Mat4_Scaling(double sx, double sy, double sz) {
        Matrix4x4 mat = {
            sx,0 ,0 ,0,
            0 ,sy,0 ,0,
            0 ,0 ,sz,0,
            0 ,0 ,0 ,1
        };
        return mat;
    }
    //3维图形以任意点为中心缩放变换矩阵
    Matrix4x4 Mat4_Scaling(Vector4 pivot, double sx, double sy, double sz) {
        Matrix4x4 mat = Mat4_Translation(-pivot[0], -pivot[1], -pivot[2]);
        mat = mat * Mat4_Scaling(sx, sy, sz);
        mat = mat * Mat4_Translation(pivot[0], pivot[1], pivot[2]);
        return mat;
    }
    //3维图形旋转变换矩阵
    Matrix4x4 Mat4_Rotation(double angle, string axis) {
        double c = cos(angle);
        double s = sin(angle);
        if (axis == "z") {
            Matrix4x4 mat = {
                c  ,s ,0 ,0,
                -s ,c ,0 ,0,
                0  ,0 ,1 ,0,
                0  ,0 ,0 ,1
            };
            return mat;
        }
        else if (axis == "x") {
            Matrix4x4 mat = {
                1 ,0  ,0 ,0,
                0 ,c  ,s ,0,
                0 ,-s ,c ,0,
                0 ,0  ,0 ,1
            };
            return mat;
        }
        else if (axis == "y") {
            Matrix4x4 mat = {
                c  ,0 ,-s ,0,
                0  ,1 ,0  ,0,
                s  ,0 ,c  ,0,
                0  ,0 ,0  ,1
            };
            return mat;
        }

    }
    //三维图形绕任意直线旋转矩阵
    Matrix4x4 Mat4_Rotation(Vector4 p1, Vector4 p2, double angle) {
        //平移
        Matrix4x4 mat = Mat4_Translation(-p1[0], -p1[1], -p1[2]);

        //计算第一次旋转角
        double L = Vec4DisSqr(p1, p2);
        double l = (p1 - p2)[0] * (p1 - p2)[0] + (p1 - p2)[1] * (p1 - p2)[1];
        double angle1 = acos(1 - l / L / 2);
        
        //第一次旋转，直线位于xOz轴上
        mat = mat * Mat4_Rotation(angle1, "x");
        
        //计算第二次旋转角
        Vector4 v = p2 * mat;
        double angle2 = -atan(v[0] / v[2]);

        //第二次旋转，直线与z轴重合
        mat = mat * Mat4_Rotation(angle2, "y");

        //可以绕z轴进行旋转angle角
        mat = mat * Mat4_Rotation(angle, "z");

        //复原
        mat = mat * Mat4_Rotation(-angle2, "y");
        mat = mat * Mat4_Rotation(-angle1, "x");
        mat = mat * Mat4_Translation(p1[0], p1[1], p1[2]);
        return mat;
    }
    //3维图形对称变换矩阵, axis = "o, x, y, z, xoy, xoz, yoz"
    Matrix4x4 Mat4_Reflection(string axis) {
        Matrix4x4 mat = {
            1 ,0 ,0 ,0,
            0 ,1 ,0 ,0,
            0 ,0 ,1 ,0,
            0 ,0 ,0 ,1
        };
        if (axis == "o") {
            mat[0][0] = -1;
            mat[1][1] = -1;
            mat[2][2] = -1;
        }
        else if (axis == "x") {
            mat[1][1] = -1;
            mat[2][2] = -1;
            return mat;
        }
        else if (axis == "y") {
            mat[0][0] = -1;
            mat[2][2] = -1;
            return mat;
        }
        else if (axis == "z") {
            mat[0][0] = -1;
            mat[1][1] = -1;
            return mat;
        }
        else if (axis == "xoy") {
            mat[2][2] = -1;
        }
        else if (axis == "xoz") {
            mat[1][1] = -1;
        }
        else if (axis == "yoz") {
            mat[0][0] = -1;
        }
        return mat;
    }
    //3维图形剪切变换矩阵
    Matrix4x4 Mat4_Shear(double k1, double k2 ,string axis) {
        Matrix4x4 mat = {
            1 ,0 ,0 ,0,
            0 ,1 ,0 ,0,
            0 ,0 ,1 ,0,
            0 ,0 ,0 ,1
        };
        if (axis == "x") {
            mat[1][0] = k1;
            mat[2][0] = k2;
            return mat;
        }
        else if (axis == "y") {
            mat[0][1] = k1;
            mat[2][1] = k2;
            return mat;
        }
        else if (axis == "z") {
            mat[0][2] = k1;
            mat[1][2] = k2;
            return mat;
        }
    }
    //3维图形正交投影变换矩阵
    Matrix4x4 Mat4_OrthoProjection() {
        Matrix4x4 mat = {
            1 ,0 ,0 ,0,
            0 ,0 ,0 ,0,
            0 ,0 ,1 ,0,
            0 ,0 ,0 ,1
        };
        return mat;
    }
    Matrix4x4 Mat4_OrthoProjection(string face) {
        Matrix4x4 mat = Mat4_OrthoProjection();
        if (face == "xoy") {
            return Mat4_Rotation(-pi / 2, "x") * mat;
        }
        else if (face == "xoz") {
            return mat;
        }
        else if (face == "yoz") {
            return Mat4_Rotation(pi / 2, "z") * mat;
        }
    }
    //3维图形1点透视变换矩阵
    Matrix4x4 Mat4_1PointProjection(double s) {
        Matrix4x4 mat = {
            1 ,0 ,0 ,0   ,
            0 ,1 ,0 ,-1/s,
            0 ,0 ,1 ,0   ,
            0 ,0 ,0 ,1   
        };
        return mat;
    }
    //3维图形多点透视变换矩阵
    Matrix4x4 Mat4_3PointProjection(double px, double py, double pz) {
        Matrix4x4 mat = {
            1 ,0 ,0 ,-1/px,
            0 ,1 ,0 ,-1/py,
            0 ,0 ,1 ,-1/pz,
            0 ,0 ,0 ,1
        };
        return mat;
    }
    //====================第四章=======================
    //生成二次插值样条曲线
    Curve Crv_Quadratic2(Matrix3n mat3n) {
        Curve cruve(mat3n.size() - 2);
        Matrix3x3 mat = {
             2 , -4,  2,
            -3,   4, -1,
             1,   0,  0
        };

        for (int i = 0; i < cruve.size(); i++) {
            Matrix3x3 points = {
                mat3n[i][0],   mat3n[i][1],   1,
                mat3n[i + 1][0], mat3n[i + 1][1], 1,
                mat3n[i + 2][0], mat3n[i + 2][1], 1,
            };
            cruve[i] = [mat, points](double t)->Vector3 {
                return (Vector3({ t * t, t, 1 }) * mat * points).IgoreZ();
            };
        }
        return cruve;
    }
    //生成Hermite样条曲线
    Curve Crv_Hermite(Points points, Points tangents) {
        Curve crv(points.size() - 1);
        Matrix mat = {
            4,4,
            {
                2, -2, 1, 1,
                -3, 3,-2,-1,
                0,  0, 1, 0,
                1,  0, 0, 0
            }
        };
        for (int i = 0; i < points.size()-1; i++) {
            auto p0 = points[i], p1 = points[i+1];
            auto t0 = tangents[i], t1 = tangents[i + 1];
            Matrix mat_p = { { p0, p1, t0, t1 } };
            crv[i] = [mat, mat_p](double t) -> Vector3 {
                Vector vec_t = { {t * t * t,t * t,t,1} };
                Matrix res = vec_t * mat * mat_p;
                return { res[0][0], res[0][1], 1 };
            };
        }
        return crv;
    }

    //生成Cardinal样条曲线
    Curve Crv_Cardinal(Points points, double ts) {
        Curve crv(points.size() - 3);
        double s = (1 - ts) / 2;
        Matrix mat = {
            4,4,
            {
                -s,  2-s, s-2,   s,
                2*s, s-3, 3-2*s,-s,
                -s,  0,   s,     0,
                0,   1,   0,     0
            }
        };
        for (int i = 0; i+3 < points.size(); i++) {
            Matrix mat_p = { { points[i], points[i+1], points[i+2], points[i+3] }};
            
            crv[i] = [mat, mat_p](double t) -> Vector3 {
                Vector vec_t = { {t * t * t,t * t,t,1} };
                Matrix res = vec_t * mat * mat_p;
                return { res[0][0], res[0][1], 1 };
                };
        }
        return crv;
    }

    Curve Crv_Bezier(Matrix3n mat3n) {
        Curve cruve(1);
        cruve[0] = [mat3n](double t) -> Vector3 {
            int n = mat3n.size()-1;
            Vector3 res = { 0 };
            for (int i = 0; i <= n; i++) {
                int x = min(i, n - i);
                double b = 1;
                for (int j = 0; j < x; j++) {
                    b *= (n - j);
                }
                for (int j = 2; j <= x; j++) {
                    b /= j;
                }
                b *= pow(t, i);
                b *= pow(1 - t, n - i);
                res = res + b * mat3n.arrays[i];
            }
            return res.IgoreZ();
        };
        return cruve;
    }
    Curve Crv_BSpline(Matrix3n mat3n, int degree) {
        if (mat3n.size() - degree <= 0) {
            degree = 2;
            throw "Too big degree! Have turned to 2 automatically";
        }
        double factorial = 1;
        for (int i = 2; i <= degree; i++) {
            factorial *= i;
        }
        Curve cruve(mat3n.size() - degree);
        for (int k = 0; k < cruve.size(); k++) {
            cruve[k] = [k, mat3n, degree, factorial](double t)->Vector3 {
                Vector3 res = { 0 };
                for (int i = 0; i <= degree; i++) {
                    double sum = 0;
                    double temp;
                    for (int j = 0; j <= degree - i; j++) {
                        double comb = 1;

                        int x = min(j, degree + 1 - j);
                        for (int k = 0; k < x; k++) {
                            comb *= degree + 1 - k;
                        }
                        for (int k = 2; k <= x; k++) {
                            comb /= k;
                        }
                        temp = comb * pow(t + degree - i - j, degree);
                        if (j % 2 == 1) {
                            temp *= -1;
                        }
                        sum += temp;
                    }
                    sum /= factorial;
                    res = res + sum * mat3n.arrays[i + k];
                }
                return res;
            };
        }
        return cruve;
    }

    void Canvas::DrawArrow(Vector3 p1, Vector3 p2) {
        auto pos1 = GetPos(p1);
        auto pos2 = GetPos(p2);
        auto d = pos1 - pos2;
        auto pos_a = d * Mat3_Rotation(pi / 6);
        auto pos_b = d * Mat3_Rotation(-pi / 6);
        pos_a = pos2 + (7 / sqrt((pos_a[0] * pos_a[0]) + (pos_a[1] * pos_a[1])) * pos_a);
        pos_b = pos2 + (7 / sqrt((pos_b[0] * pos_b[0]) + (pos_b[1] * pos_b[1])) * pos_b);
        line(pos1[0], pos1[1], pos2[0], pos2[1]);
        line(pos2[0], pos2[1], pos_a[0], pos_a[1]);
        line(pos2[0], pos2[1], pos_b[0], pos_b[1]);
    }
}