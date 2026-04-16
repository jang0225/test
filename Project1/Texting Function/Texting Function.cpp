#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

/*
const int MAX_N = 10;
bool hasError;

// [입력] v: 출력할 double 값
// [출력] 소수점 둘째 자리까지 반올림된 문자열 (정수면 소수점 없이, 예: 3.00→"3", 1.50→"1.5")
string formatVal(double v) {
    // 주어진 double형 변수 v를 출력 형식에 맞는 문자열로 반환하는 코드 
    double v_hun;
    v_hun = v * 100;
    v = round(v_hun) / 100;

    if ((int)v == v) {
        return to_string(int(v));
    }
    else if ((int)(v * 10) == v * 10) {
        return to_string(int(v)) + "." + to_string(abs((int)(v * 10) % 10));
    }
    else {
        return to_string((int)v) + "." + to_string(abs((int)(v * 10) % 10)) + to_string(abs((int)(v * 100) % 10));
    }
}

// ===================== 행렬 연산 함수 =====================
// 행렬은 MAX_N x MAX_N 크기의 2차원 배열과 실제 행 수(rows), 열 수(cols)로 표현된다.
// C++에서 다차원 배열은 함수의 반환값으로 사용할 수 없으므로,
// 결과를 저장할 배열과 크기 변수를 call by reference로 전달받아 저장한다.

// 행렬 덧셈: A + B = C
// [입력] A (a_rows x a_cols), B (b_rows x b_cols)
// [출력] C (c_rows x c_cols): A와 B의 요소별 합
// [에러] 차원 불일치 시 hasError = true
void matAdd(double A[][MAX_N], int a_rows, int a_cols,
    double B[][MAX_N], int b_rows, int b_cols,
    double C[][MAX_N], int& c_rows, int& c_cols) {
    // 행렬 덧셈 구현 및 에러 핸들링 
    if (a_rows == b_rows && a_cols == b_cols) {
        for (int i = 0; i < a_rows; i++) {
            for (int j = 0; j < a_cols; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        c_rows = a_rows;
        c_cols = a_cols;
    }
    else {
        hasError = true;
    }

}

// 행렬 뺄셈: A - B = C
// [입력] A (a_rows x a_cols), B (b_rows x b_cols)
// [출력] C (c_rows x c_cols): A와 B의 요소별 차
// [에러] 차원 불일치 시 hasError = true
void matSub(double A[][MAX_N], int a_rows, int a_cols,
    double B[][MAX_N], int b_rows, int b_cols,
    double C[][MAX_N], int& c_rows, int& c_cols) {
    // 행렬 뺄셈 구현 및 에러 핸들링 
    if (a_rows == b_rows && a_cols == b_cols) {
        for (int i = 0; i < a_rows; i++) {
            for (int j = 0; j < a_cols; j++) {
                C[i][j] = A[i][j] - B[i][j];
            }
        }

        c_rows = a_rows;
        c_cols = a_cols;

    }
    else {
        hasError = true;
    }

}

// 행렬 곱셈: A * B = C
// [입력] A (a_rows x a_cols), B (b_rows x b_cols)
// [출력] C (c_rows x c_cols): A와 B의 행렬 곱 (c_rows = a_rows, c_cols = b_cols)
// [에러] a_cols != b_rows 시 hasError = true
void matMul(double A[][MAX_N], int a_rows, int a_cols,
    double B[][MAX_N], int b_rows, int b_cols,
    double C[][MAX_N], int& c_rows, int& c_cols) {
    // 행렬 곱셈 구현 및 에러 핸들링 
    if (a_cols != b_rows) {
        hasError = true;
    }
    else {
        double temp[MAX_N][MAX_N];
        for (int i = 0; i < a_rows; i++) {
            for (int j = 0; j < b_cols; j++) {
                temp[i][j] = 0;
                for (int k = 0; k < a_cols; k++) {
                    temp[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        for (int i = 0; i < a_rows; i++) {
            for (int j = 0; j < b_cols; j++) {
                C[i][j] = temp[i][j];
            }
        }
        c_rows = a_rows;
        c_cols = b_cols;

    }
}

// 스칼라 곱: scalar * A = C
// [입력] scalar: 스칼라 값, A (a_rows x a_cols)
// [출력] C (c_rows x c_cols): A의 모든 요소에 scalar를 곱한 결과
void matScalarMul(double scalar,
    double A[][MAX_N], int a_rows, int a_cols,
    double C[][MAX_N], int& c_rows, int& c_cols) {
    // 행렬 스칼라 곱 구현 
    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < a_cols; j++) {
            C[i][j] = A[i][j] * scalar;
        }
    }
    c_rows = a_rows;
    c_cols = a_cols;
}

// 스칼라 나누기: A / scalar = C
// [입력] A (a_rows x a_cols), scalar: 나눌 스칼라 값
// [출력] C (c_rows x c_cols): A의 모든 요소를 scalar로 나눈 결과
// [에러] scalar가 0일 시 hasError = true
void matScalarDiv(double A[][MAX_N], int a_rows, int a_cols,
    double scalar,
    double C[][MAX_N], int& c_rows, int& c_cols) {
    // 행렬 스칼라 나누기 구현 및 에러 핸들링
    if (scalar == 0) {
        hasError = true;
    }
    else {
        for (int i = 0; i < a_rows; i++) {
            for (int j = 0; j < a_cols; j++) {
                C[i][j] = A[i][j] / scalar;
            }
        }
        c_rows = a_rows;
        c_cols = a_cols;
    }
}

// 전치: T(A) = C
// [입력] A (a_rows x a_cols)
// [출력] C (c_rows x c_cols): A의 전치 행렬 (c_rows = a_cols, c_cols = a_rows)
void matTranspose(double A[][MAX_N], int a_rows, int a_cols,
    double C[][MAX_N], int& c_rows, int& c_cols) {
    // 행렬 전치 구현 
    double temp[MAX_N][MAX_N];
    for (int i = 0; i < a_cols; i++) {
        for (int j = 0; j < a_rows; j++) {
            temp[i][j] = A[j][i];
        }
    }

    for (int i = 0; i < a_cols; i++) {
        for (int j = 0; j < a_rows; j++) {
            C[i][j] = temp[i][j];
        }
    }
    c_rows = a_cols;
    c_cols = a_rows;
}

// 행렬식 (재귀적 여인수 전개)
// [입력] m: n x n 정방 행렬
// [출력] 반환값: m의 행렬식 (double)
double matDet(double m[][MAX_N], int n) {
    // 행렬식 계산 구현 
    double Calculate = 0;
    double subMat[MAX_N][MAX_N];

    if (n == 1) {
        return m[0][0];
    }

    for (int i = 0; i < n; i++) {             //i가 제외할 열을 의미함
        for (int j = 0; j < n - 1; j++) {
            for (int k = 0; k < n - 1; k++) {
                if (k < i) {
                    subMat[j][k] = m[j + 1][k];
                }
                else if (k >= i) {
                    subMat[j][k] = m[j + 1][k + 1];
                }
            }

        }
        Calculate += pow(-1, i) * m[0][i] * matDet(subMat, n - 1);
    }
    return Calculate;
}

// ===================== 행렬 문자열 파서 =====================
// "a,b;c,d" 형태의 문자열을 받아 행렬로 파싱

// [입력] mat: '[' ']' 사이의 문자열 (예: "1,2;3,4")
// [출력] res: 파싱된 행렬, rows: 행 수, cols: 열 수
void parseMatrixLiteral(const string& mat,
    double res[][MAX_N], int& rows, int& cols) {
    /* 주어진 형식의 문자열을 파싱하여 res 행렬에 저장 
    size_t first_semmi = mat.find(';', 0);
    size_t pos = 0;
    size_t ends = 0;
    rows = 0;
    cols = 0;

    size_t j = 0;

    if (first_semmi == string::npos) {
        while (mat.find(',', pos) != string::npos) {
            ends = mat.find(',', pos);
            res[rows][cols] = stod(mat.substr(pos, ends - pos));

            cols++;
            pos = ends + 1;
        }
        res[rows][cols] = stod(mat.substr(pos));
        cols++;

    }
    else {
        while (mat.find(';', pos) != string::npos) {
            ends = mat.find(';', pos);
            for (size_t i = pos; i < ends; i = j + 1) {
                j = mat.find(',', i);
                if (j == string::npos || j > ends) {
                    res[rows][cols] = stod(mat.substr(i, ends - i));
                    cols++;
                    break;
                }
                else {
                    res[rows][cols] = stod(mat.substr(i, j - i));
                    cols++;
                }
            }
            rows++;
            cols = 0;
            pos = ends + 1;
        }
        for (size_t i = pos; i < mat.length(); i = j + 1) {
            j = mat.find(',', i);
            if (j == string::npos) {
                res[rows][cols] = stod(mat.substr(i));
                cols++;
                break;
            }
            else {
                res[rows][cols] = stod(mat.substr(i, j - i));
                cols++;
            }
        }
    }
    rows++;
}

// ===================== 파서 함수 =====================
// 재귀 하강 파서 (recursive descent parser)
//
// parseExpr:    +, - 처리 (가장 낮은 우선순위)
// parseTerm:    *, / 처리
// parsePrimary: T(), det(), 괄호, 행렬, 숫자 (가장 높은 우선순위)
//
// 진입점은 parseExpr이며, 내부에서 parseTerm → parsePrimary 순서로 호출됨

/* 구현할 함수 아님!! 상호 재귀를 위한 전방 선언 
void parseExpr(const string& s, int& pos,
    double res[][MAX_N], int& rows, int& cols, bool& isScalar); //1x1행렬은 isScalar가 false고 scalar면 true임

// 처리 문자: T(), det(), (), [], 숫자
// [입력] s: 전체 수식 문자열, pos: 현재 읽기 위치
// [출력] res: 파싱/계산된 결과 행렬, rows/cols: 결과 크기,
//        isScalar: 결과가 스칼라이면 true, pos: 소비한 만큼 전진
// [에러] 비정방 행렬의 det 시 hasError = true
void parsePrimary(const string& s, int& pos,
    double res[][MAX_N], int& rows, int& cols, bool& isScalar) {
    if (hasError) return;

    if (pos > (int)s.length()) return;

    // T(expr): 'T('를 확인하면 내부 수식을 재귀적으로 파싱한 뒤, 전치 연산을 적용하여 res에 저장
    if (s[pos] == 'T') {
        pos++;
        if (s[pos] == '(') {
            pos++;
            parseExpr(s, pos, res, rows, cols, isScalar);
            if (hasError) return;

            matTranspose(res, rows, cols, res, rows, cols);
            if (hasError) return;
        }
        if (s[pos] == ')') {
            pos++;
        }
        return;
    }

    // det(expr): 'det('를 확인하면 내부 수식을 재귀적으로 파싱한 뒤, 정방 행렬 여부를 검사하고 행렬식을 계산하여 res의 [0][0] 위치에 저장
    if (pos + 4 < (int)s.length() && s[pos] == 'd' && s[pos + 1] == 'e' && s[pos + 2] == 't' && s[pos + 3] == '(') {
        pos += 4;

        parseExpr(s, pos, res, rows, cols, isScalar);
        if (hasError) return;

        if (rows == cols) {
            res[0][0] = matDet(res, rows);
            isScalar = true;
        }
        else {
            hasError = true;
        }
        if (s[pos] == ')') {
            pos++;
        }
        return;
    }

    // 괄호 (expr): '('를 확인하면 내부 수식을 재귀적으로 파싱하여 res에 저장
    if (s[pos] == '(') {
        pos++;
        parseExpr(s, pos, res, rows, cols, isScalar);
        if (hasError) return;
        if (s[pos] == ')') {
            pos++;
        }
        return;
    }

    // 행렬 리터럴 [...]: 대괄호 내부 문자열을 추출하여 res로 파싱
    if (s[pos] == '[') {
        pos++;
        int i = 0;
        int rem_posi = pos;
        while (s[pos] != ']') {
            pos++;
            i++;
        }
        string new_s = s.substr(rem_posi, i);

        parseMatrixLiteral(new_s, res, rows, cols);
        if (hasError) return;

        if (s[pos] == ']') {
            pos++;
        }
        return;
    }

    // 숫자(스칼라): 정수 리터럴을 읽어 res의 [0][0] 위치에 저장
    if (isdigit(s[pos]) != 0) {
        int i = 0;
        int rem_posi = pos;
        while (pos < (int)s.length() && isdigit(s[pos]) != 0) {
            pos++;
            i++;
        }
        res[0][0] = stod(s.substr(rem_posi, i));
        isScalar = true;
        return;
    }
}

// 처리 문자: *, /
// [입력] s: 전체 수식 문자열, pos: 현재 읽기 위치
// [출력] res: 연속된 *,/ 연산을 모두 수행한 결과 행렬, rows/cols: 결과 크기,
//        isScalar: 결과가 스칼라이면 true, pos: 소비한 만큼 전진
// [에러] 차원 불일치 등 연산 에러 시 hasError = true
void parseTerm(const string& s, int& pos,
    double res[][MAX_N], int& rows, int& cols, bool& isScalar) {
    if (hasError) return;

    // 1) 좌측 피연산자 파싱
    parsePrimary(s, pos, res, rows, cols, isScalar);
    if (hasError) return;

    // 2) 연속되는 * 또는 / 를 왼쪽부터 처리
    while (pos < (int)s.length() && (s[pos] == '*' || s[pos] == '/')) {
        // 우측 피연산자를 파싱한 뒤, 연산자와 좌/우 피연산자의 타입(스칼라/행렬)에 따라
        // 적절한 연산(스칼라 나눗셈, 스칼라 곱셈, 행렬 곱셈)을 수행하고 결과를 res에 저장
        /* 위 내용을 아래에 구현하시오 
        double r_mat[MAX_N][MAX_N];
        int r_rows = 0, r_cols = 0;
        bool r_isScalar = false;
        pos++;

        parsePrimary(s, pos, r_mat, r_rows, r_cols, r_isScalar);
        if (hasError) return;

        if (isScalar == true) {
            double scal = (double)res[0][0];
            matScalarMul(scal, r_mat, r_rows, r_cols, res, rows, cols);
        }
        else if (r_isScalar == true) {
            double scal = (double)r_mat[0][0];
            matScalarDiv(res, rows, cols, scal, res, rows, cols);
        }
        else {
            matMul(res, rows, cols, r_mat, r_rows, r_cols, res, rows, cols);
        }
        isScalar = false;
    }
}

// 처리 문자: +, - (가장 낮은 우선순위, 파서 진입점)
// [입력] s: 전체 수식 문자열, pos: 현재 읽기 위치
// [출력] res: 연속된 +,- 연산을 모두 수행한 결과 행렬, rows/cols: 결과 크기,
//        isScalar: 결과가 스칼라이면 true, pos: 소비한 만큼 전진
// [에러] 차원 불일치 등 연산 에러 시 hasError = true
void parseExpr(const string& s, int& pos,
    double res[][MAX_N], int& rows, int& cols, bool& isScalar) {
    if (hasError) return;

    // 1) 좌측 피연산자 파싱 (parseTerm이 *,/를 먼저 처리)
    parseTerm(s, pos, res, rows, cols, isScalar);
    if (hasError) return;

    // 2) 연속되는 + 또는 - 를 왼쪽부터 처리
    while (pos < (int)s.length() && (s[pos] == '+' || s[pos] == '-')) {
        // 우측 피연산자를 파싱한 뒤, 연산자에 따라 덧셈 또는 뺄셈을 수행하고 결과를 res에 저장
        /* 위 내용을 아래에 구현하시오 
        double r_mat[MAX_N][MAX_N];
        int r_rows = 0, r_cols = 0;
        bool r_isScalar = false;
        char rem_pos = s[pos];
        pos++;

        parseTerm(s, pos, r_mat, r_rows, r_cols, r_isScalar);
        if (hasError) return;

        if (rem_pos == '+') {
            matAdd(res, rows, cols, r_mat, r_rows, r_cols, res, rows, cols);
        }
        else {
            matSub(res, rows, cols, r_mat, r_rows, r_cols, res, rows, cols);
        }
    }
}

// ===================== main =====================

int main() {
    string input;
    getline(cin, input);

    hasError = false;
    int pos = 0;
    double result[MAX_N][MAX_N];
    int rows = 0, cols = 0;
    bool isScalar = false;

    parseExpr(input, pos, result, rows, cols, isScalar);

    if (hasError) {
        cout << "Error while evaluating!" << endl;
        return 0;
    }

    if (isScalar) {
        cout << formatVal(result[0][0]) << endl;
    }
    else {
        string out = "[";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (j > 0) out += ",";
                out += formatVal(result[i][j]);
            }
            if (i < rows - 1) out += ";";
        }
        out += "]";
        cout << out << endl;
    }

    return 0;
}
*/


// Just for testing git
int main() {
    cout << "Hello world!" << endl;
    return 0;
}