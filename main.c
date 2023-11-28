#include <stdio.h>
#include <math.h>
#include <string.h>
void exit(int);
#define max(a, b) ((a)>(b)?(a):(b))

/// vacuum magnetic permeability constant (g.cm/us^2/MA^2)
double const MuZero = 4 * 3.1415926 * 1.0e-2;
/// critical internal energy density (10^5*J/cm^3)
double Ec = 0.1;
/// boundary magnetic field (1000*Tesla)
double B0 = 0.2;
/// resistivity below Ec (100*mO.cm)
double EtaS = 9.7e-5;
/// resistivity above Ec (100*mO.cm)
double EtaL = 100 * 9.7e-5;

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Convert string to double type value
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
double StringToDouble(char * str)
{
	double value;
	sscanf(str, "%lf", &value);
	return(value);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Identify strings containing "=" and perform format
/// conversion
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
char * CheckAndConvertString(char str[500])
{
	char * pStr = NULL;
	for(int i = 0; i < 500; i++)
	{
		if(str[i] == '\0')break;
		if(str[i] == '=')
		{
			str[i] = ' ';
			pStr = str;
			break;
		}
	}
	return(pStr);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Open file
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
FILE * OpenFile(char * fileName, char * mode)
{
	FILE * fp = fopen(fileName, mode);
	if(fp == NULL)
	{
		printf("can not open file：%s\n", fileName);
		exit(1);
	}
	return(fp);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Read the four parameters Ec, B0, EtaS, and EtaL 
/// from the input file fileName
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
void ReadParametersFromInputFile(char * fileName)
{
	///////////////////////////////////// open file
	FILE * fp = OpenFile(fileName, "r");
	///////////////////////////////////// read parameters
	char line[500];
	while(!feof(fp))
	{
		fgets(line, 500, fp);
		char * lineConverted = CheckAndConvertString(line);
		if(lineConverted != NULL)
		{
			char word1[500], word2[500];
			sscanf(lineConverted, "%s%s", word1, word2);
			if(strcmp(word1, "Ec") == 0)
			{
				Ec = StringToDouble(word2);
			}
			else if(strcmp(word1, "B0") == 0)
			{
				B0 = StringToDouble(word2);
			}
			else if(strcmp(word1, "EtaS") == 0)
			{
				EtaS = StringToDouble(word2);
			}
			else if(strcmp(word1, "EtaL") == 0)
			{
				EtaL = StringToDouble(word2);
			}
			else
			{
				printf("file format error：unkown variable name\n");
				exit(1);
			}
		}
	}
	///////////////////////////////////// close file
	fclose(fp);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Macro: Integration from t0 to t1
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
#define INTEGRATE(kernel_in_t, t0, t1, result) \
{ \
	int const n = 10000; \
	double const deltT = (t1 - t0) / n; \
	/*/////////////////////////*/ \
	double sum = 0.0; \
	for(int i = 1; i <= n; i++) \
	{ \
		double t = t0 + deltT * (i - 0.5); \
		sum += kernel_in_t; \
	} \
	sum *= deltT; \
	/*/////////////////////////*/ \
	result = sum; \
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Integration function A
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
double IntegrateFuncA(double a)
{
	double result;
	INTEGRATE(exp(a * (1.0 - 1.0 / (t * t))) / (t * t), 0.0, 1.0, result);
	return(result);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Integration function B
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
double IntegrateFuncB(double a)
{
	double result;
	INTEGRATE(exp(a * (1.0 - 1.0 / t)) / t, 0.0, 1.0, result);
	return(result);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Integration function C
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
double IntegrateFuncC(double a)
{
	double result;
	INTEGRATE(exp(a * (1.0 - t * t)), 0.0, 1.0, result);
	return(result);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// The first Bc(h) relation
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
double BcTohOne(double h)
{
	double const f1 = IntegrateFuncA(0.5 * h / EtaS);
	double const f3 = IntegrateFuncC(0.5 * h / EtaL);
    return B0 / (1 + (EtaS / EtaL) * (f3 / f1));
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// The second Bc(h) relation
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
double BcTohTwo(double h)
{
	double const f1 = IntegrateFuncA(0.5 * h / EtaS);
	double const f2 = IntegrateFuncB(h / EtaS);
	return sqrt(2 * MuZero * Ec * (h / EtaS) * (f1 * f1 / f2));
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Obtain the intersection point of two curves, 
/// BcTohOne (h) and BcTohTwo (h)
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
void CalcBcAndh(double * out_bc, double * out_h)
{
	double bc, h;
	//////////////////////////////// set the range for searching of h
	double hMin, hMax, factorMin, factorMax;
	{
		double const bcApproximate = sqrt(2 * MuZero * Ec);
		double const hApproximate = EtaL * (B0 - bcApproximate) / bcApproximate;
		hMax = max(EtaL, 10 * hApproximate);
		hMin = max(1e-15, 0.1 * hApproximate);
		factorMin = BcTohOne(hMin) - BcTohTwo(hMin);
		factorMax = BcTohOne(hMax) - BcTohTwo(hMax);
		if(factorMin * factorMax >= 0)
		{
			printf("out of parameter range：please tune hMin or hMax in the code，so as to enlarge the searching range of h.\n");
			exit(1);
		}
	}
	//////////////////////////////// find h, and calculate bc
	do
	{
		if( hMax - hMin < 1e-15)
		{
			h = (hMin * factorMax - hMax * factorMin) / (factorMax - factorMin);
			bc = 0.5 * (BcTohOne(h) + BcTohTwo(h));
			break;
		}
		double const hTemp = 0.5 * (hMin + hMax);
		double const factor = BcTohOne(hTemp) - BcTohTwo(hTemp);
		if( factorMin * factor < 0)
		{
			hMax = hTemp;
			factorMax = factor;
		}
		else
		{
			hMin = hTemp;
			factorMin = factor;
		}
	}while(1);
	//////////////////////////////// output
	(*out_bc) = bc;
	(*out_h) = h;
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Numerically integrates f'(u) to obtain f(u)
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
double FuFromIntegration(double u, double bc, double h, double factorL, double factorS)
{
	double fu;
	/////////////////////////////////
	if(u < 1)
	{
		double const a = 0.5 * h / EtaL;
		/////////////////////////////
		double integrated;
		INTEGRATE(exp(a * (1.0 - t * t)), 0.0, u, integrated);
		fu = B0 + factorL * integrated;
	}
	else
	{
		double const a = 0.5 * h / EtaS;
		/////////////////////////////
		double integrated;
		INTEGRATE(exp(a * (1.0 - t * t)), 1.0, u, integrated);
		fu = bc + factorS * integrated;
	}
	/////////////////////////////////
	return fu;
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Output curve of f(u)
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
void OutputCurveOfFu(double bc, double h, char * fileName)
{
	///////////////////////////////////// open file
	FILE * fp = OpenFile(fileName, "w");
	///////////////////////////////////// output f(u) curve data
	double const factorL = (bc - B0) / IntegrateFuncC(0.5 * h / EtaL);
	double const factorS = -bc / IntegrateFuncA(0.5 * h / EtaS);
	//////////
	int const n = 10000;
	double const hMax = 1.0 + 2.0 * sqrt(2.0 * EtaS / h);
	double const deltU = hMax / n;
	//////////
    fprintf(fp, "u              \tf(u)\n");
    fprintf(fp, "               \t1000Tesla\n");
	for(int i = 0; i <= n; i++)
	{
		double u = i * deltU;
    	fprintf(fp, "%-15.6E\t%-15.6E\n", u, FuFromIntegration(u, bc, h, factorL, factorS));
	}
	///////////////////////////////////// close file
	fclose(fp);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Output the two curves of the two relations of Bc(h)
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
void OutputCurvesOfBcToh(double h, char * fileName)
{
	///////////////////////////////////// open file
	FILE * fp = OpenFile(fileName, "w");
	///////////////////////////////////// outout curves data
	int const n = 200;
	double deltH = (2 * h) / n;
	fprintf(fp, "h              \tBc             \tBc\n");
	fprintf(fp, "               \t1000Tesla      \t1000Tesla\n");
	fprintf(fp, "               \tRelation-I     \tRelation-II\n");
	for(int i = 1; i <= n; i++)
	{
		double const hTemp = i * deltH;
		fprintf(fp, "%-15.6E\t%-15.6E\t%-15.6E\n", hTemp, BcTohOne(hTemp), BcTohTwo(hTemp));
	}
	///////////////////////////////////// close file
	fclose(fp);
}

/// mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
/// Main
/// wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
int main()
{
	///////////////////////////////////////// Read the input parameters from file
	ReadParametersFromInputFile("input.txt");
	printf("The input parameters are:\n");
	printf("Ec = %-15.6E\n", Ec);
	printf("B0 = %-15.6E\n", B0);
	printf("EtaS = %-15.6E\n", EtaS);
	printf("EtaL = %-15.6E\n\n", EtaL);
	///////////////////////////////////////// Calculate Bc, h
	double bc, h;
	CalcBcAndh(&bc, &h);
	printf("Results:\n");
    printf("Bc = %-15.6E\n", bc);
	printf("h = %-15.6E\n", h);
	///////////////////////////////////////// Output various intermediate results
	printf("\nWritting curves to files...\n");
	OutputCurvesOfBcToh(h, "BcToh-DoubleCurves.txt");
	OutputCurveOfFu(bc, h, "f-u.txt");
	///////////////////////////////////////// Finish
	printf("\nfinished.\n");
	return(0);
}
