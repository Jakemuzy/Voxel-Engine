
#include <FastNoiseLite.h>
#include <thread>
#include <future>
#include <chrono>
FastNoiseLite noise;

//Eventually make these static members

// Pos, Norm, and TexCoords
float positions[108] = {
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

float normals[108] = {
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

float textures[108] = {
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

struct Block{
    float x, y, z;
    unsigned int blockID;
};

class Chunk {
private:
    const static int width = 64, length = 64, height = 128;
    const static int waterLevel = 4;
    int chunkOffsetX, chunkOffsetZ;
    unsigned int chunkVAO;
    int totalBlocks = 0;

    std::vector<float> vertices = {};
    int heightMap[width*height];
    int chunkBounds[24];

public:
    
    Chunk(int offsetX, int offsetZ){
        chunkOffsetX = offsetX;
        chunkOffsetZ = offsetZ;
    }

    void genChunk(int offsetX, int offsetZ){

        // Generate height map 
        int xOffset = offsetX * width;
        int zOffset = offsetZ * length;
        populateHeightmap(xOffset, zOffset);
        genChunkBounds();

        // Populate Chunk with blocks
        vertices.resize(totalBlocks * 36);
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

                if (maxY <= 4)
                    blockType = 4;

                // Bitwise occlusion flags
                std::uint8_t occlusion = 0;                                                                    // 0, 5, 1, 4, 2, 3, because that's the order the face data is stored in the position, normal and texture vectors
                occlusion |= (x < width - 1 && i < totalBlocks && heightMap[x + z * width + 1] > y) << 0;   // Right 10000000
                occlusion |= (x > 0 && heightMap[x + z * width - 1] > y) << 5;                              // Left 01000000
                occlusion |= (z < length - 1 && i < totalBlocks && heightMap[x + z * width + width] > y) << 1; // Front 00100000
                occlusion |= (z > 0 && heightMap[x + z * width - width] > y) << 4;                             // Back 00010000
                occlusion |= (y < maxY - 1) << 2;                                                              // Top 00001000
                occlusion |= (y > 0) << 3;                                                                     // Bottom 00000100

                // Chooses which vertices to render, depending on occlusion data
                for (int j = 0; j < 108; j += 3)
                {

                    // If breaks i % 18 == 0, check to see if it's at beginning of vertices for each face
                    int currentFace = j / 18;
                    if (occlusion & (1 << currentFace))
                    {
                        j += 15;
                        continue;
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

    void populateHeightmap(int xOffset, int zOffset)
    {
        for (int i = 0; i < width * length; i++)
        {
            int x = i % width;
            int z = (i / length) % width;

            float maxHeight = fabs(noise.GetNoise((float)(x + xOffset), (float)(z + zOffset))) * height; // No idea why these values are negative

            if (maxHeight <= 4)
                maxHeight = 4;
            heightMap[i] = static_cast<int>(maxHeight);
            totalBlocks += static_cast<int>(maxHeight);
            // heightMap[i] = 128;
            // totalBlocks += (int)128;
        }
    }

    void calculateOcclusion(int x, int y, int z){

    }
    
    void updateChunk(){

    }

    void drawChunk(glm::mat4& view, glm::mat4& proj)
    {
        if(false)   //Frust cull
            return;
        glBindVertexArray(chunkVAO);
        glBindTexture(GL_TEXTURE_2D_ARRAY, 1);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);
    }

    void genChunkBounds(){
        
        int minX = chunkOffsetX * width;           
        int maxX = chunkOffsetX * width + width;
        int minY = 0;
        int maxY = height;
        int minZ = chunkOffsetZ * length;          
        int maxZ = chunkOffsetZ * length + length;     
        
        // Bottom
        chunkBounds[0] = minX; chunkBounds[1] = minY; chunkBounds[2] = minZ;       //Back Left
        chunkBounds[3] = minX; chunkBounds[4] = minY; chunkBounds[5] = maxZ;       //Front Left
        chunkBounds[6] = maxX; chunkBounds[7] = minY; chunkBounds[8] = minZ;       //Back Right
        chunkBounds[9] = maxX; chunkBounds[10] = minY; chunkBounds[11] = maxZ;     //Front Right
        
        // Top
        chunkBounds[12] = minX; chunkBounds[13] = maxY; chunkBounds[14] = minZ;    //Back Left
        chunkBounds[15] = minX; chunkBounds[16] = maxY; chunkBounds[17] = maxZ;    //Front Left
        chunkBounds[18] = maxX; chunkBounds[19] = maxY; chunkBounds[20] = minZ;    //Back Right
        chunkBounds[21] = maxX; chunkBounds[22] = maxY; chunkBounds[23] = maxZ;    //Front Right

        //chunkBounds[] = maxX; chunkBounds[22] = maxY; chunkBounds[23] = maxZ;    //Center

    }

    bool frustrumCull(glm::mat4& view, glm::mat4& proj){

        /*
        glm::mat4 frustrum = glm::inverse(view * proj);

        std::vector<glm::vec3> points = {};
        //points.emplace_back(chunkBounds[0], chunkBounds[1], chunkBounds[2]);
        points.emplace_back(chunkBounds[3], chunkBounds[4], chunkBounds[5]);
        //points.emplace_back(chunkBounds[6], chunkBounds[7], chunkBounds[8]);
        //points.emplace_back(chunkBounds[9], chunkBounds[10], chunkBounds[11]);
        //points.emplace_back(chunkBounds[12], chunkBounds[13], chunkBounds[14]);
        //points.emplace_back(chunkBounds[15], chunkBounds[16], chunkBounds[17]);
        //points.emplace_back(chunkBounds[18], chunkBounds[19], chunkBounds[20]);
        //points.emplace_back(chunkBounds[21], chunkBounds[22], chunkBounds[23]);

        std::vector<bool> test = {};

        // Frustum plane normals
        glm::vec4 lPlaneNorm = glm::vec4(frustrum[3][0] + frustrum[0][0], frustrum[3][1] + frustrum[0][1], frustrum[3][2] + frustrum[0][2], frustrum[3][3] + frustrum[0][3]);
        glm::vec4 rPlaneNorm = glm::vec4(frustrum[3][0] - frustrum[0][0], frustrum[3][1] - frustrum[0][1], frustrum[3][2] - frustrum[0][2], frustrum[3][3] - frustrum[0][3]);
        glm::vec4 bPlaneNorm = glm::vec4(frustrum[3][0] + frustrum[1][0], frustrum[3][1] + frustrum[1][1], frustrum[3][2] + frustrum[1][2], frustrum[3][3] + frustrum[1][3]);
        glm::vec4 tPlaneNorm = glm::vec4(frustrum[3][0] - frustrum[1][0], frustrum[3][1] - frustrum[1][1], frustrum[3][2] - frustrum[1][2], frustrum[3][3] - frustrum[1][3]);
        glm::vec4 nPlaneNorm = glm::vec4(frustrum[3][0] + frustrum[2][0], frustrum[3][1] + frustrum[2][1], frustrum[3][2] + frustrum[2][2], frustrum[3][3] + frustrum[2][3]);
        glm::vec4 fPlaneNorm = glm::vec4(frustrum[3][0] - frustrum[2][0], frustrum[3][1] - frustrum[2][1], frustrum[3][2] - frustrum[2][2], frustrum[3][3] - frustrum[2][3]);

        // Divided by plane x y and z to normalize
        lPlaneNorm /= sqrt(lPlaneNorm.x * lPlaneNorm.x + lPlaneNorm.y * lPlaneNorm.y + lPlaneNorm.z * lPlaneNorm.z);
        rPlaneNorm /= sqrt(rPlaneNorm.x * rPlaneNorm.x + rPlaneNorm.y * rPlaneNorm.y + rPlaneNorm.z * rPlaneNorm.z);
        bPlaneNorm /= sqrt(bPlaneNorm.x * bPlaneNorm.x + bPlaneNorm.y * bPlaneNorm.y + bPlaneNorm.z * bPlaneNorm.z);
        tPlaneNorm /= sqrt(tPlaneNorm.x * tPlaneNorm.x + tPlaneNorm.y * tPlaneNorm.y + tPlaneNorm.z * tPlaneNorm.z);
        nPlaneNorm /= sqrt(nPlaneNorm.x * nPlaneNorm.x + nPlaneNorm.y * nPlaneNorm.y + nPlaneNorm.z * nPlaneNorm.z);
        fPlaneNorm /= sqrt(fPlaneNorm.x * fPlaneNorm.x + fPlaneNorm.y * fPlaneNorm.y + fPlaneNorm.z * fPlaneNorm.z);


        for(auto& point: points){

            // Points in chunk distances from plane
            float lDist = (point.x * lPlaneNorm.x + point.y * lPlaneNorm.y + point.z * lPlaneNorm.z + lPlaneNorm.w);
            float rDist = (point.x * rPlaneNorm.x + point.y * rPlaneNorm.y + point.z * rPlaneNorm.z + rPlaneNorm.w);
            float bDist = (point.x * bPlaneNorm.x + point.y * bPlaneNorm.y + point.z * bPlaneNorm.z + bPlaneNorm.w);
            float tDist = (point.x * tPlaneNorm.x + point.y * tPlaneNorm.y + point.z * tPlaneNorm.z + tPlaneNorm.w);
            float nDist = (point.x * nPlaneNorm.x + point.y * nPlaneNorm.y + point.z * nPlaneNorm.z + nPlaneNorm.w);
            float fDist = (point.x * fPlaneNorm.x + point.y * fPlaneNorm.y + point.z * fPlaneNorm.z + fPlaneNorm.w);

            std::cout << lDist << " " << rDist << " " << bDist << " " << tDist << " " << nDist << " " << fDist << " \n";
            if (lDist < 0 && rDist < 0 && bDist < 0 && tDist < 0 && nDist < 0 && fDist < 0)
                test.push_back(true);
            else 
                test.push_back(false);
        }

        int count = 0;
        for(auto& val : test)
        {
            //std::cout << val << " ";
            if(val)
                count++;
        }
        //std::cout << "\n";

        if(count == test.size()){
            //std::cout << "CULL\n";
            //return true;
        } 
            //std::cout << "NOT\n";

        return false; // The point is inside

    }
        */

        glm::mat4 frust = proj * view;
        std::vector<glm::vec4> planes;
        std::vector<glm::vec3> points = {};
        std::vector<bool> truth = {};

        points.emplace_back(chunkBounds[0], chunkBounds[1], chunkBounds[2]);
        points.emplace_back(chunkBounds[3], chunkBounds[4], chunkBounds[5]);
        points.emplace_back(chunkBounds[6], chunkBounds[7], chunkBounds[8]);
        points.emplace_back(chunkBounds[9], chunkBounds[10], chunkBounds[11]);
        points.emplace_back(chunkBounds[12], chunkBounds[13], chunkBounds[14]);
        points.emplace_back(chunkBounds[15], chunkBounds[16], chunkBounds[17]);
        points.emplace_back(chunkBounds[18], chunkBounds[19], chunkBounds[20]);
        points.emplace_back(chunkBounds[21], chunkBounds[22], chunkBounds[23]);

        planes.emplace_back(glm::vec4(frust[3] + frust[0]));
        planes.emplace_back(glm::vec4(frust[3] - frust[0]));
        planes.emplace_back(glm::vec4(frust[3] + frust[1]));
        planes.emplace_back(glm::vec4(frust[3] - frust[1]));
        planes.emplace_back(glm::vec4(frust[3] + frust[2]));
        planes.emplace_back(glm::vec4(frust[3] - frust[2]));

        bool inside = false;
        int count = 0;
        for(auto& plane: planes){
            float length = sqrt(plane.x*plane.x + plane.y*plane.y + plane.z*plane.z);
            plane.x /= length;
            plane.y /= length;
            plane.z /= length;
            plane.w /= length;

            //std::cout << count << " " << plane.x << " " << plane.y << " " << plane.z << " " << plane.w << " \n";

            //std::cout << count;
            for(auto& point : points){
                //point = frust * glm::vec4(point,1.0f);
                float distance = plane.x * point.x + plane.y * point.y + plane.z * point.z + plane.w;
                //std::cout << " " << distance << " ";
                inside = inside | distance < 0;
            }
            //std::cout << "\n";
            count++;
        }

        if(!inside)
            std::cout << "CULLED";
        return !(inside);

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
        int maxThreads = std::thread::hardware_concurrency() / 2; // Limit active threads

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
    
    void draw(glm::mat4& view, glm::mat4 proj){
        for(Chunk& chunk : chunks){

            //float time = glfwGetTime();
            chunk.drawChunk(view, proj);
            //std::cout << glfwGetTime() - time << "\n";
        }
    }
};