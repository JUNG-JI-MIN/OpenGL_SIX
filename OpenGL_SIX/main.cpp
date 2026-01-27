#include "FrameWork.h"

// 전역 변수 정의 (extern 선언은 FrameWork.h에 있음)
static GLuint width, height;
static GLuint shaderProgramID; //--- 세이더 프로그램 이름
static GLuint vertexShader; //--- 버텍스 세이더 객체
static GLuint fragmentShader; //--- 프래그먼트 세이더 객체
static void make_vertexShaders(const char* filePath);
static void make_fragmentShaders(const char* filePath);
static GLuint make_shaderProgram();
static GLvoid drawScene();
static GLvoid Reshape(int w, int h);

CFrameWork framework;
// 파일을 읽어서 문자열로 반환하는 함수
char* filetobuf(const char* file)
{
    FILE* fptr;
    long length;
    char* buf;
    fptr = fopen(file, "rb"); // Open file for reading
    if (!fptr) // Return NULL on failure
        return NULL;
    fseek(fptr, 0, SEEK_END); // Seek to the end of the file
    length = ftell(fptr); // Find out how many bytes into the file we are
    buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
    fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
    fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
    fclose(fptr); // Close the file
    buf[length] = 0; // Null terminator
    return buf; // Return the buffer
}
// 타이머 함수 구현
void TimerFunction(int value) {

	framework.Update();

    glutPostRedisplay();  // 화면 다시 그리기
    glutTimerFunc(16, TimerFunction, 1);  // 다음 타이머 설정
    
}
void onKey(unsigned char key, int x, int y) {

	framework.keyboardInput(key, x, y);

    glutPostRedisplay();
}

void offkey(unsigned char key, int x, int y) {
    framework.keyboardUpInput(key, x, y);
    glutPostRedisplay();
}

void onSpecialKey(int key, int x, int y) {
    
    glutPostRedisplay();
}
void onSpecialKeyUp(int key, int x, int y) {
    
    glutPostRedisplay();
}
void onMouse(int button, int state, int x, int y) {
    
    framework.mouseInput(button, state, x, y);

}
void onMouseMotion(int x, int y) {
	framework.mousemove(x, y);
    glutPostRedisplay();
}
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
    width = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
    //--- 윈도우 생성하기
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("Example1");
    //--- GLEW 초기화하기
    glewExperimental = GL_TRUE;
    glewInit();
    //--- 세이더 읽어와서 세이더 프로그램 만들기: 사용자 정의함수 호출
    make_vertexShaders("vertex.glsl"); //--- 버텍스 세이더 만들기
    make_fragmentShaders("fragment.glsl"); //--- 프래그먼트 세이더 만들기
    shaderProgramID = make_shaderProgram(); //--- 세이더 프로그램 만들기

	framework.Init(new CScene());

    glutDisplayFunc(drawScene); //--- 출력 콜백 함수
    glutTimerFunc(16, TimerFunction, 1);  // 60 FPS
    glutKeyboardFunc(onKey); // 키보드
	glutKeyboardUpFunc(offkey); // 떼기
    glutSpecialFunc(onSpecialKey); // 특수키
    glutSpecialUpFunc(onSpecialKeyUp); // 떼기
    glutMouseFunc(onMouse); // 마우스 콜백 등록
    glutMotionFunc(onMouseMotion);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}

GLvoid drawScene() {
    glViewport(0, 0, width, height);

    glClearColor(0.5f,0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgramID);
    // 각 객체의 회전 행렬을 셰이더에 전달
    // 깊이 테스트와 뒷면 제거 활성화
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // 뒷면 제거 설정
    glCullFace(GL_BACK);        // 뒷면을 제거

	// 투명도 처리를 위한 블렌딩 활성화
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

    framework.Render(shaderProgramID);

    glutSwapBuffers();
}

//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
    glViewport(0, 0, w, h);
}



void make_vertexShaders(const char* filePath)
{
    GLchar* vertexSource;
    //--- 버텍스 세이더 읽어 저장하고 컴파일 하기
    //--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
    vertexSource = filetobuf(filePath);
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
}

void make_fragmentShaders(const char* filePath)
{
    GLchar* fragmentSource;
    //--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
    fragmentSource = filetobuf(filePath); // 프래그세이더 읽어오기
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
}

GLuint make_shaderProgram()
{
    GLint result;
    GLchar* errorLog = NULL;
    GLuint shaderID;
    shaderID = glCreateProgram(); //--- 세이더 프로그램 만들기
    glAttachShader(shaderID, vertexShader); //--- 세이더 프로그램에 버텍스 세이더 붙이기
    glAttachShader(shaderID, fragmentShader); //--- 세이더 프로그램에 프래그먼트 세이더 붙이기
    glLinkProgram(shaderID); //--- 세이더 프로그램 링크하기
    glDeleteShader(vertexShader); //--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
    glDeleteShader(fragmentShader);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result); // ---세이더가 잘 연결되었는지 체크하기
    if (!result) {
        glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
        std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
        return false;
    }
    glUseProgram(shaderID); //--- 만들어진 세이더 프로그램 사용하기
    //--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
    //--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
    //--- 사용하기 직전에 호출할 수 있다.
    return shaderID;
}

