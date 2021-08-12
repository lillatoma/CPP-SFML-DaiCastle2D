#pragma once

#include <random>

struct RandomDevice
{

private:
	std::mt19937 MT;


public:

	RandomDevice()
	{
		Init();
	}
	RandomDevice(const unsigned int& seed)
	{
		MT.seed(seed);
	}

	void Init()
	{
		std::random_device rd;
		MT.seed(rd());
	}
	int RandomInt(double a, double b)
	{
		std::uniform_int_distribution<int> dist(a, b);
		return dist(MT);
	}
	int* RandomIntCont(double a, double b, int count)
	{
		std::uniform_int_distribution<int> dist(a, b);
		int* V = new int[count + 1];
		for (int i = 0; i < count; i++)
			V[i] = dist(MT);
		return V;
	}
	double RandomReal(double a, double b)
	{
		std::uniform_real_distribution<double> dist(a, b);
		return dist(MT);
	}
	double* RandomRealCont(double a, double b, int count)
	{
		std::uniform_real_distribution<double> dist(a, b);
		double* V = new double[count + 1];
		for (int i = 0; i < count; i++)
			V[i] = dist(MT);
		return V;
	}

	float RandomFloat(double a, double b)
	{
		std::uniform_real_distribution<double> dist(a, b);
		return dist(MT);
	}
	float* RandomFloatCont(double a, double b, int count)
	{
		std::uniform_real_distribution<double> dist(a, b);
		float* V = new float[count + 1];
		for (int i = 0; i < count; i++)
			V[i] = dist(MT);
		return V;
	}


	void SetSeed(const unsigned int& seed)
	{
		MT.seed(seed);
	}

};