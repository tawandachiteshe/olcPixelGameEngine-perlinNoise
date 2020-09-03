#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"
#include <math.h>

class Example : public olc::PixelGameEngine
{
private:
	olc::vi2d pos;
	olc::vi2d velocity;
	const int width = 240;
	const int height = 240;
	int octaves;
	float persistance = 0.23;
	float lacunarity = 2.0f;
	olc::vi2d offset;

	float scale = 0.2f;

	olc::vi2d* octaveOffsets = nullptr;

	int* perlinNoiseSamples = nullptr;
public:
	Example()
	{
		sAppName = "Playing Is For Kids";
		perlinNoiseSamples = new int[width * height];
		this->octaves = 7;
		octaveOffsets = new olc::vi2d[octaves];
		offset = olc::vi2d(1, 1);

		float amplitude = 1.0f;
		float frequency = 1.0f;
		float noiseHeight = 0;

		float maxNoiseHeight = -2147483648;
		float minNoiseHeight = 2147483647;

		for (int i = 0; i < this->octaves; i++)
		{
			int offsetX = (rand() % width) + offset.x;
			int offsetY = (rand() % height) + offset.y;
			std::cout << offsetX << " " << offsetY << "\n";
			octaveOffsets[i] = olc::vi2d(offsetX, offsetY);
		}

		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < height; x++)
			{
				for (int i = 0; i < octaves; i++)
				{
					float sampleX = (float)x / width;
					float sampleY = (float)y / height;

					//std::cout << sampleX << " " << sampleY << "\n";
					
					float perlinNoiseValue = stb_perlin_ridge_noise3((float)x / (float)width, (float)y / (float)height, 1.0f, 2.0f, 0.93f, 1.2f, 6) * -1.0f;
					if (signbit(perlinNoiseValue))
						perlinNoiseValue *= -1;
					noiseHeight = perlinNoiseValue;
					//frequency *= lacunarity;
					/*
					if (noiseHeight > maxNoiseHeight)
						maxNoiseHeight = noiseHeight;
					else if (noiseHeight < minNoiseHeight)
						minNoiseHeight = noiseHeight;
						*/
					//std::cout << perlinNoiseValue << "\n";
					perlinNoiseSamples[y * width + x] = noiseHeight * 255;
				}
			}
		}
	}

public:
	bool OnUserCreate() override
	{
		
		for (size_t y = 0; y < width; y++)
		{
			for (size_t x = 0; x < height; x++)
			{
				//std::cout << perlinNoiseSamples[y * width + x] << " ";
			}

			std::cout << "\n";
		}
		
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int y = 0; y < width; y++)
		{

			for (int x = 0; x < height; x++)
			{
				Draw({x, y}, olc::Pixel(perlinNoiseSamples[y * width + x], 0, 0));
			}
			
		}
		
		return true;
	}

	~Example() 
	{
		delete[] perlinNoiseSamples;
	}
};


int main()
{
	Example demo;



	std::cout << stb_perlin_noise3(0.4f, 0.54f, 1.0f, 0, 0, 0) * 255 << "\n";
	
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	
	return 0;
}
