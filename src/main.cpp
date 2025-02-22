#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>
#include <Shader.h>
#include <Camera.h>

#include <World.h>

namespace fs = std::filesystem;

// Global Variables
Camera camera(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
bool firstMouse = true, disableMouseMovement = false;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float lastX = 400, lastY = 300;
float timeSinceLastCursorFocus = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{

    // If cursor hovering over imgui window
    /*
    if ((*ioptr).WantCaptureMouse && glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL) {
        return;
    }
    */
    if (disableMouseMovement)
        return;

    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}
void processInput(GLFWwindow* window)
{
    //Escape
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
        std::cout << "Closed Window\n";
    }

    // Move
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

}

unsigned int loadTex3D(std::string paths[6])
{
    stbi_set_flip_vertically_on_load(false);

    unsigned int texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_3D, texID);

    int width, height, depth = 6, nrChannels;
    std::vector<unsigned char> texData;

    for (int i = 0; i < 6; i++)
    {
        std::string fileLoc = paths[i];
        const char *fileLocation = fileLoc.c_str();

        unsigned char *data = stbi_load(fileLocation, &width, &height, &nrChannels, 4);
        texData.insert(texData.end(), data, data + (width * height * 4));

        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE_3D, texID);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texData[0]);
    glGenerateMipmap(GL_TEXTURE_3D);

    return texID;
}
void loadTexArray(std::vector<std::string> paths, unsigned int& texID)
{
    stbi_set_flip_vertically_on_load(false);

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texID);

    int width, height, depth = paths.size(), nrChannels;
    std::vector<unsigned char> texData;

    for (int i = 0; i < paths.size(); i++)
    {
        std::string fileLoc = paths[i];
        const char *fileLocation = fileLoc.c_str();

        unsigned char *data = stbi_load(fileLocation, &width, &height, &nrChannels, 4);
        if (!data) // Check if loading failed
        {
            std::cerr << "Error: Failed to load texture: " << paths[i] << std::endl;
            continue;
        }

        if (width == 0 || height == 0) // Check for invalid image size
        {
            std::cerr << "Error: Invalid texture dimensions for " << paths[i] << std::endl;
            stbi_image_free(data);
            continue;
        }
        texData.insert(texData.end(), data, data + (width * height * 4));

        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE_2D_ARRAY, texID);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, width, height, depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texData[0]);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    //return texID;
}
unsigned int generateBlockTexture(std::string blockName)
{
    std::string folderPath = "dependencies\\textures\\";
    std::string topTexture = folderPath + blockName + "_top.png", sideTexture = folderPath + blockName + "_side.png", bottomTexture = folderPath + blockName + "_bottom.png";

    // Auto generate paths for each texture side of block
    std::vector<std::string> paths = {};
    std::ifstream top(topTexture.c_str());
    std::ifstream bottom(bottomTexture.c_str());
    std::ifstream side(sideTexture.c_str());

    // Determine if each side exists
    paths.push_back(sideTexture);
    paths.push_back(sideTexture);
    if (top.good())
        paths.push_back(topTexture);
    else
        paths.push_back(sideTexture);
    if (bottom.good())
        paths.push_back(bottomTexture);
    else
        paths.push_back(sideTexture);

    paths.push_back(sideTexture);
    paths.push_back(sideTexture);

    //std::string texturePaths[6] = {paths[0], paths[1], paths[2], paths[3], paths[4], paths[5]};
    ///unsigned int cubemapID = loadTex3D(texturePaths);
    unsigned int cubemapID;
    loadTexArray(paths, cubemapID);

    return cubemapID;
}
unsigned int loadAllTextures(){
    std::string folderPath = "dependencies\\textures\\blocks\\";

    std::vector<std::string> paths = {};
    for (const auto &entry : fs::directory_iterator(folderPath))
    {
        if (fs::is_regular_file(entry))
        {
            fs::path filePath = entry.path();
            std::string blockName = filePath.filename().string();

            // If block is already in paths, skip

            if(std::find(paths.begin(), paths.end(), filePath.string()) != paths.end()){
                std::cout << blockName << " already generated\n";
                continue;
            }
                

            if(blockName.find("_top.png"))
                blockName = blockName.substr(0, blockName.find("_top.png"));
            if (blockName.find("_side.png"))
                blockName = blockName.substr(0, blockName.find("_side.png"));
            if (blockName.find("_bottom.png"))
                blockName = blockName.substr(0, blockName.find("_bottom.png"));

            //Make it just the block name
            std::string topTexture = folderPath + blockName + "_top.png", sideTexture = folderPath + blockName + "_side.png", bottomTexture = folderPath + blockName + "_bottom.png";

            // Auto generate paths for each texture side of block
            std::ifstream top(topTexture.c_str());
            std::ifstream bottom(bottomTexture.c_str());
            std::ifstream side(sideTexture.c_str());

            // Determine if each side exists
            paths.push_back(sideTexture);
            paths.push_back(sideTexture);
            if (top.good())
                paths.push_back(topTexture);
            else
                paths.push_back(sideTexture);
            if (bottom.good())
                paths.push_back(bottomTexture);
            else
                paths.push_back(sideTexture);

            paths.push_back(sideTexture);
            paths.push_back(sideTexture);
        }
    }

    unsigned int cubemapID;
    loadTexArray(paths, cubemapID);

    return cubemapID;
}


int main(void){ 
    //Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    int windowWidth = 1200, windowHeight = 800;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);

    //Callback functions
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //Call the function, every window resize
    glfwSetCursorPosCallback(window, mouseCallback);

    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        abort();
    }
    glfwMakeContextCurrent(window);

    //Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        abort();
    }

    //Viewport
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Render Settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_3D);
    glDepthFunc(GL_LESS);
    //glEnable(GL_POLYGON_MODE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //World
    World newWorld(10, 10);

    Shader blockShader("dependencies/shaders/block.vert", "dependencies/shaders/block.frag");
    //unsigned int grass = generateBlockTexture("grass");
    unsigned int grass = loadAllTextures();
    //unsigned int dirt = generateBlockTexture("dirt");


    //Matrix
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 1000.0f);

    // Main Loop
    while (!glfwWindowShouldClose(window))
    {
        // Delta Time
        deltaTime = glfwGetTime() - lastFrame;
        lastFrame = glfwGetTime();

        // Buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Inputs
        processInput(window);
        view = camera.GetViewMatrix();

        // Draw
        blockShader.use();
        blockShader.setMat4("model", model);
        blockShader.setMat4("view", view);
        blockShader.setMat4("projection", projection);
        
        newWorld.draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}  