
#include <FastNoiseLite.h>
#include <thread>
#include <future>
#include <chrono>
FastNoiseLite noise;

//Eventually make these static members

// Pos, Norm, and TexCoords
std::vector<float> positions = {
    0.5f, -0.5f, -0.5f, // Right
    0.5f, 0.5f, 0.5f, 
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f, 
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f, 

    -0.5f, -0.5f, 0.5f, // Front
     0.5f, -0.5f, 0.5f,
     0.5f, 0.5f, 0.5f, 
     0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f, 

    -0.5f, 0.5f, -0.5f,   // Top
     0.5f, 0.5f, 0.5f, 
     0.5f, 0.5f, -0.5f, 
     0.5f, 0.5f, 0.5f, 
    -0.5f, 0.5f, -0.5f, 
    -0.5f, 0.5f, 0.5f, 

    -0.5f, -0.5f, -0.5f,  // Bottom
     0.5f, -0.5f, -0.5f, 
     0.5f, -0.5f, 0.5f, 
     0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f, -0.5f,  // Back
     0.5f, 0.5f, -0.5f, 
     0.5f, -0.5f, -0.5f, 
     0.5f, 0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, 0.5f, -0.5f,

    -0.5f, 0.5f, 0.5f,  // Left
    -0.5f, 0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f
};

std::vector<float> normals = {
    1.0f, 0.0f, 0.0f, // Right
    1.0f, 0.0f, 0.0f, 
    1.0f, 0.0f, 0.0f, 
    1.0f, 0.0f, 0.0f, 
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    0.0f, 0.0f, 1.0f, // Front
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 
    0.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, // Top
    0.0f, 1.0f, 0.0f, 
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 

    0.0f, -1.0f, 0.0f,  // Bottom
    0.0f, -1.0f, 0.0f, 
    0.0f, -1.0f, 0.0f, 
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 
    0.0f, -1.0f, 0.0f, 

    0.0f, 0.0f, -1.0f, // Back
    0.0f, 0.0f, -1.0f, 
    0.0f, 0.0f, -1.0f, 
    0.0f, 0.0f, -1.0f, 
    0.0f, 0.0f, -1.0f, 
    0.0f, 0.0f, -1.0f, 

    -1.0f, 0.0f, 0.0f, // Left
    -1.0f, 0.0f, 0.0f, 
    -1.0f, 0.0f, 0.0f, 
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f, 
    -1.0f, 0.0f, 0.0f
};

/*
std::vector<float> textures = {
    1.0f, 1.0f, 1 / 12.0, // Right
    0.0f, 0.0f, 1 / 12.0, 
    0.0f, 1.0f, 1 / 12.0, 
    0.0f, 0.0f, 1 / 12.0, 
    1.0f, 1.0f, 1 / 12.0, 
    1.0f, 0.0f, 1 / 12.0,

    1.0f, 1.0f, 3 / 12.0, // Front
    0.0f, 1.0f, 3 / 12.0, 
    0.0f, 0.0f, 3 / 12.0, 
    0.0f, 0.0f, 3 / 12.0, 
    1.0f, 0.0f, 3 / 12.0, 
    1.0f, 1.0f, 3 / 12.0,

    1.0f, 0.0f, 5 / 12.0, // Top
    0.0f, 1.0f, 5 / 12.0, 
    0.0f, 0.0f, 5 / 12.0, 
    0.0f, 1.0f, 5 / 12.0, 
    1.0f, 0.0f, 5 / 12.0, 
    1.0f, 1.0f, 5 / 12.0,

    1.0f, 1.0f, 7 / 12.0, // Bottom
    0.0f, 1.0f, 7 / 12.0, 
    0.0f, 0.0f, 7 / 12.0, 
    0.0f, 0.0f, 7 / 12.0, 
    1.0f, 0.0f, 7 / 12.0, 
    1.0f, 1.0f, 7 / 12.0,

    1.0f, 1.0f, 9 / 12.0, // Back
    0.0f, 0.0f, 9 / 12.0,
    0.0f, 1.0f, 9 / 12.0, 
    0.0f, 0.0f, 9 / 12.0, 
    1.0f, 1.0f, 9 / 12.0, 
    1.0f, 0.0f, 9 / 12.0,

    0.0f, 0.0f, 11 / 12.0, // Left
    1.0f, 0.0f, 11 / 12.0, 
    1.0f, 1.0f, 11 / 12.0, 
    1.0f, 1.0f, 11 / 12.0, 
    0.0f, 1.0f, 11 / 12.0, 
    0.0f, 0.0f, 11 / 12.0
};
*/

std::vector<float> textures = {
    1.0f, 1.0f, 0, // Right
    0.0f, 0.0f, 0,
    0.0f, 1.0f, 0,
    0.0f, 0.0f, 0,
    1.0f, 1.0f, 0,
    1.0f, 0.0f, 0,

    1.0f, 1.0f, 1, // Front
    0.0f, 1.0f, 1,
    0.0f, 0.0f, 1,
    0.0f, 0.0f, 1,
    1.0f, 0.0f, 1,
    1.0f, 1.0f, 1,

    1.0f, 0.0f, 2, // Top
    0.0f, 1.0f, 2,
    0.0f, 0.0f, 2,
    0.0f, 1.0f, 2,
    1.0f, 0.0f, 2,
    1.0f, 1.0f, 2,

    1.0f, 1.0f, 3, // Bottom
    0.0f, 1.0f, 3,
    0.0f, 0.0f, 3,
    0.0f, 0.0f, 3,
    1.0f, 0.0f, 3,
    1.0f, 1.0f, 3,

    1.0f, 1.0f, 4, // Back
    0.0f, 0.0f, 4,
    0.0f, 1.0f, 4,
    0.0f, 0.0f, 4,
    1.0f, 1.0f, 4,
    1.0f, 0.0f, 4,

    0.0f, 0.0f, 5, // Left
    1.0f, 0.0f, 5,
    1.0f, 1.0f, 5,
    1.0f, 1.0f, 5,
    0.0f, 1.0f, 5,
    0.0f, 0.0f, 5
};

class Block
{
private:
    glm::vec3 worldPos;
    unsigned int blockID;
public:
    Block(glm::vec3 pos, unsigned int blockType){
        worldPos = pos;
        blockID = blockType;
    }
    glm::vec3 getPos(){
        return worldPos;
    }
    unsigned int getID(){
        return blockID;
    }
};

class Chunk {
private:
    const static int width = 32, length = 32, height = 128;
    unsigned int chunkVAO, textureID;
    int totalBlocks = 0;

    std::vector<Block> blocks = {};  //Not used currently
    std::vector<float> vertices = {};
    std::vector<int> heightMap = {};

    void populateHeightmap(int xOffset, int zOffset){
        //heightMap.resize(width * length);
        for (int i = 0; i < width * length; i++)
        {
            int x = i % width;
            int z = (i / length) % width;

            float maxHeight = fabs(noise.GetNoise((float)(x + xOffset), (float)(z + zOffset))) * height; // No idea why these values are negative

            heightMap[i] = static_cast<int>(maxHeight);
            totalBlocks += static_cast<int>(maxHeight);
            //heightMap[i] = 128;
            //totalBlocks += (int)128;
        }
    }


public:
    

    Chunk(int offsetX, int offsetZ){
        heightMap.resize(width * length);
        
    }

    void genChunk(int offsetX, int offsetZ){

        // Generate height map 
        int xOffset = offsetX * width;
        int zOffset = offsetZ * length;
        populateHeightmap(xOffset, zOffset);
        
        // Populate Chunk with blocks
        vertices.resize(totalBlocks * 72);
        int index = 0;
        for (int i = 0; i < width * length; i++)
        {
            int x = i % width;
            int z = (i / length) % width;
            int maxY = heightMap[x + z * width];
            for (int y = 0; y < maxY; y++)
            {

                // Block Texture
                unsigned int blockType = 0; //Dirt
                if (y == maxY - 1)
                    blockType = 1;  //Grass
                else if (y <= maxY - 7)
                    blockType = 3;  //Stone

                // Bitwise occlusion flags
                std::uint8_t occlusion = 0;                                                                    // 0, 5, 1, 4, 2, 3, because that's the order the face data is stored in the position, normal and texture vectors
                occlusion |= (x < width - 1 && i < totalBlocks && heightMap[x + z * width + 1] > y) << 0;      // Right 10000000
                occlusion |= (x > 0 && heightMap[x + z * width - 1] > y) << 5;                                 // Left 01000000
                occlusion |= (z < length - 1 && i < totalBlocks && heightMap[x + z * width + width] > y) << 1; // Front 00100000
                occlusion |= (z > 0 && heightMap[x + z * width - width] > y) << 4;                             // Back 00010000
                occlusion |= (y < maxY - 1) << 2;                                                              // Top 00001000
                occlusion |= (y > 0) << 3;                                                                     // Bottom 00000100

                // Chooses which vertices to render, depending on occlusion data
                for (int j = 0; j < positions.size(); j += 3)
                {

                    // If breaks i % 18 == 0, check to see if it's at beginning of vertices for each face
                    int currentFace = j / 18;
                    if (occlusion & (1 << currentFace))
                    {
                        j += 15;
                        continue;
                    }

                    //Adding vertices to chunk
                    if (index+7 > vertices.size()){
                        vertices.resize(vertices.size() + 7);
                        //std::cout << "HEIGHTMAP ERROR";
                    }
                        
                    vertices[index++] = positions[j] + x + offsetX * width;
                    vertices[index++] = positions[j + 1] + y;
                    vertices[index++] = positions[j + 2] + z + offsetZ * length;
                    vertices[index++] = currentFace;
                    vertices[index++] = textures[j];
                    vertices[index++] = textures[j + 1];
                    vertices[index++] = textures[j + 2] + blockType*6;

                }
            }
        }


    }

    void genVAO()
    {
        unsigned int chunkVBO;

        glGenVertexArrays(1, &chunkVAO);
        glGenBuffers(1, &chunkVBO);

        glBindBuffer(GL_ARRAY_BUFFER, chunkVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glBindVertexArray(chunkVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *)(4 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        
    }
    
    std::vector<Block>& getBlocks(){
        return blocks;
    }

    void calculateOcclusion(int x, int y, int z){

    }
    
    void updateChunk(){
        for(Block& block : blocks){

        }
    }

    void drawChunk(){
        glBindVertexArray(chunkVAO);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 1);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);
    }

};


class World {
private:
    std::vector<Chunk> chunks;
    int seed = 1337;

    std::vector<std::thread> workers;
    std::mutex mtx;

public:
    World(int chunksX, int chunksZ){
        srand(time(NULL));
        int seed = rand();

        noise.SetSeed(seed);
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise.SetFrequency(0.00522);
        noise.SetFractalOctaves(8.0);

        auto start = std::chrono::high_resolution_clock::now();

        int trialCount = 1;
        int maxThreads = std::thread::hardware_concurrency() / 3; // Limit active threads

        chunks.reserve(chunksX * chunksZ);
        for(int x = 0; x < chunksX; x++){
            for(int z = 0; z < chunksZ; z++){
                chunks.emplace_back(x, z);
            }
        }

        for(int trials = 0; trials < trialCount; trials++){
            for (int x = 0; x < chunksX; x++)
            {
                for (int z = 0; z < chunksZ; z++)
                {

                    //Thread for separate chunks
                    Chunk &chunkRef = chunks[x + z*chunksX];
                    workers.emplace_back(&Chunk::genChunk, &chunkRef, x, z);

                    //Wait for chunks to load if max threads has been reached
                    if(workers.size() >= maxThreads){
                        for(auto& thread : workers){
                            if (thread.joinable()){
                                thread.join(); 
                            }
                        }
                        workers.clear();
                    }
                }
            }
            //Join final threads
            for (auto &thread : workers)
            {
                if (thread.joinable())
                {
                    thread.join();
                }
            }
            workers.clear();
        }

        //Generate chunk VAOs
        for(auto& chunk : chunks){
            chunk.genVAO();
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "Average World Gen Time: " << duration.count()/(1000000.0f * trialCount) << "\n";
    }
    
    void draw(){
        for(Chunk& chunk : chunks){

            //float time = glfwGetTime();
            chunk.drawChunk();
            //std::cout << glfwGetTime() - time << "\n";
        }
    }
};