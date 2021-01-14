#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.1415926535
#define E 2.718281828

void showCopyright(void);
void choice(void);
void starbar(int n);
void z_test(void);
double zfunction(double);
double Riemann_sum_z(double z, double fz,int n);
void t_test(void);
float avg (float num[], int n);
float standard_deviation (float num[ ], int n);
double tfunction(int df,double t);
float Riemann_sum_t(float x, float t, int df);
void Quit(void);

int main(void)
{
    showCopyright();
    while(1)
    {
        choice();
    }
    return 0;
}

void showCopyright()
{
    printf("**********************************************************************\n");
    printf("*                      Hypothesis test calculator                    *\n");
    printf("*                                                                    *\n");
    printf("*       This is a group project for Structured Programming (1001)    *\n");
	printf("*                           Statistics Programme	             *\n");				     
	printf("*                   BNU-HKBU United International College	     *\n");
    printf("*                  Copyright (c) 2019  All rights reserved.          *\n");
    printf("*                                                                    *\n");
    printf("*                                                                    *\n");
    printf("*         Build with MinGW Developer Studio on 11/24/2019            *\n");
    printf("**********************************************************************\n");
    printf("Press CMD + K + enter to continue . . .\n");
    getchar();
}
void choice()
{
    int i;
    
    do {
        
        printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
        printf("\t\t|                                               |\n");
        printf("\t\t|     Welcome to Hypothesis test calculator     |\n");
        printf("\t\t|                                               |\n");
        printf("\t\t|      Please Select The Following test:        |\n");
        printf("\t\t|                                               |\n");
        printf("\t\t|   $$-Z test             -- Press 1            |\n");
        printf("\t\t|   $$-T test             -- Press 2            |\n");
        printf("\t\t|   $$-Quit               -- Press 3            |\n");
        printf("\t\t|                                               |\n");
        printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
        
        printf("\n\n\n\n");
        
        printf("Please enter the  number corresponding to the choice:");
        scanf("%d", &i);
        
        switch (i)
        {
            case 1: z_test(); break;
            case 2: t_test(); break;
            case 3: Quit(); break;
            default: printf("Number should between 1 to 3!\n");
        }
        
    } while (1);
}

void z_test()
{
    int n, i, choice_test, choice_parameter_type;
    double sample_mean, population_mean, sigma, fz, p_value;
    double z, alpha;
    double sample_proportion, population_proportion;
    printf("Please enter 1 or 2 to choose that what your hypothesis about: 1) population mean 2) population proportion\n");
    scanf("%d", &choice_parameter_type);
    switch (choice_parameter_type)
    {
        case 1:
            //Choose what kind of test is going to be used
            printf("Please choose a test:\n");
            printf("1. H0:¦Ì=¦Ì0, H1:¦Ì¡Ù¦Ì0\n");
            printf("2. H0:¦Ì¡Ü¦Ì0, H1:¦Ì>¦Ì0\n");
            printf("3. H0:¦Ì¡Ý¦Ì0, H1:¦Ì<¦Ì0\n");
            scanf("%d", &choice_test);
            //Enter datas that are needed and check them
            printf("Please input the sample size n:\n");
            scanf("%d", &n);
            printf("Please input the population mean:\n");
            scanf("%lf", &population_mean);
            printf("Please input the sample mean:\n");
            scanf("%lf", &sample_mean);
            printf("Please input the population standard deviation:\n");
            scanf("%lf", &sigma);
            printf("Please input the level of significance:\n");
            scanf("%lf", &alpha);
            printf("Now the inputs are: \n");
            printf("n = %d, population mean = %f, sample mean = %f, population standard deviation = %f, level of significance = %f.\n", n, population_mean, sample_mean, sigma, alpha);
            //Calculate the test statistics
            z = (sample_mean - population_mean) / (sigma / sqrt(n));
            break;
        case 2:
            //Choose what kind of test is going to be used
            printf("Please choose a test:\n");
            printf("1. H0:p=p0, H1:p¡Ùp0\n");
            printf("2. H0:p¡Üp0, H1:p>p0\n");
            printf("3. H0:p¡Ýp0, H1:p<p0\n");
            scanf("%d", &choice_test);
            //Enter datas that are needed and check them
            printf("Please input the sample size n:\n");
            scanf("%d", &n);
            printf("Please input the population proportion:\n");
            scanf("%lf", &population_proportion);
            printf("Please input the sample proportion:\n");
            scanf("%lf", &sample_proportion);
            z = (sample_proportion - population_proportion) / sqrt(population_proportion * (1 - population_proportion) / n);
            printf("Please input the level of significance:\n");
            scanf("%lf", &alpha);
            printf("Now the inputs are: \n");
            printf("n = %d, population proportion = %f, sample proportion = %f, level of significance = %f.\n", n, population_proportion, sample_proportion, alpha);
            break;
    }
    printf("The critical value is %f.\n", z);
    //Calculate the p-value of the test statistic
    fz= zfunction(z);
    printf("fz = %lf\n",fz);
    p_value = Riemann_sum_z(z, fz, n);
    printf("The p value is %f.\n",p_value);
    //Modified of two_tail test
    if (choice_test == 1)
        alpha = alpha / 2;
    //Draw conclusion
    if(p_value < alpha)
        printf("We can reject the null hypothesis.\n");
    else
        printf("We can not reject the null hypothesis.\n");
    starbar(60);
    printf("Please choose:\n 1. quit\n 2. go to the main page\n 3. continue to use this test\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1: Quit();
            break;
        case 2: return;
            break;
        case 3: z_test();
            break;
        default: printf("Number should between 1--3!\n");
    }
}

double zfunction(double z)
{
    double f_z = pow(E, -0.5 * pow(z,2)) /  sqrt(2 * PI);
    return f_z;
}

double Riemann_sum_z(double z, double fz,int n)
{
    double total_area = 0, width, area, start_points, end_points;
    long m = 100000,i;
    start_points = z;
    end_points = 4 * z;
    width =(end_points - start_points)/ m;
    for (i = 1; i <= m; i++)
    {
        z= start_points + width * i;
        fz=zfunction(z);
        area = fz * width;
        total_area += area;
    }
    total_area = fabs(total_area);
    return total_area;
}


void t_test()
{
    int n = 1, choice_test, df, i;
    double alpha, sample_mean, s, population_mean;
    double test_statistics, p_value;
    printf("Please input the sample size n:\n");
    scanf("%d", &n);
    float num[n];
    float *p;
    starbar(60);
    printf("Please input the sample data: ");
    for (p = num; p < num + n; p++)
        scanf("%f", p);
    printf("The sample data as follows:\n");
    //Choose what kind of test is going to be used
    printf("Please choose a test:\n");
    printf("1. H0:¦Ì=¦Ì0, H1:¦Ì¡Ù¦Ì0\n");
    printf("2. H0:¦Ì¡Ü¦Ì0, H1:¦Ì>¦Ì0\n");
    printf("3. H0:¦Ì¡Ý¦Ì0, H1:¦Ì<¦Ì0\n");
    scanf("%d", &choice_test);
    //Enter datas that are needed and check them
    printf("Please input the population mean:\n");
    scanf("%lf", &population_mean);
    //Calculate the sample mean
    printf("The xbar is %f.\n", sample_mean = avg(num,n));
    printf("Please input the level of significance:\n");
    scanf("%lf", &alpha);
    //Calculate the sample standard deviation
    printf("The standard deviation is %f.\n", s = standard_deviation(num,n));
    printf("Now the data we have are:\n");
    printf("n = %d, sample mean = %lf, alpha=%lf, sample standard deviation = %lf, ¦Ì = %lf.\n", n, sample_mean, alpha, s, population_mean);
    df = n - 1;
    //Calculate the test statistic
    test_statistics = (sample_mean - population_mean) / (s / sqrt(n));
    printf("test statistics: %f\n", test_statistics);
    //Calculate the p-value of the test statistic
    p_value = tfunction(df,test_statistics);
    printf("p value: %f\n", p_value);
    //Modified of two_tail test
    if (choice_test == 1)
        alpha = alpha / 2;
    //Draw conclusion
    if(p_value < alpha)
        printf("We can reject the null hypothesis.\n");
    else
        printf("We can not reject the null hypothesis.\n");
    printf("That's end!\n");
    starbar(60);
    printf("Please choose:\n 1. quit\n 2. go to the main page\n 3. continue to use this test\n");
    scanf("%d",&i);
    switch(i)
    {
        case 1: Quit();
            break;
        case 2: return;
            break;
        case 3: t_test();
            break;
        default: printf("Number should between 1--3!\n");
    }
}

float avg(float num[], int n)
{
    float *p;
    float sum = 0.0f;
    for(p = num; p < num + n; p++)
    {
        sum += *p;
    }
    return sum / n;
}

float standard_deviation(float num[], int n)
{
    float *p;
    float avg1 = avg(num, n);
    float sum = 0.0f;
    for (p = num; p < num + n; p++)
        sum += (*p - avg1) * (*p - avg1);
    return sqrt(sum / (n-1));
    
}

double tfunction(int df,double t)
{
    double fac1 = 1.0, ft1, p;
    double fac2 = 1.0, ft2;
    double numerator = 1, denominator = 1;
    int i;
    if(df % 2 == 0)
    {
        for(i = 2; i <= (df - 2); i += 2)
        {
            denominator *= i;
        }
        for (i = 3; i <= (df - 1); i += 2)
        {
            numerator *= i;
        }
        fac1 = numerator / denominator;
        ft1 = fac1 / (2 * sqrt(df));
        printf("fx = %f\n", ft1);
        p = Riemann_sum_t(ft1, t, df);
        return p;
    }
    else
    {
        for(i = 2; i <= (df - 1); i += 2)
        {
            numerator *= i;
        }
        for (i = 3; i <= (df - 2); i += 2)
        {
            denominator *= i;
        }
        fac2 = numerator / denominator;
        ft2 = fac2 / (PI * sqrt(df));
        printf("fx = %f\n", ft2);
        p = Riemann_sum_t(ft2, t, df);
        return p;
    }
}

float Riemann_sum_t(float ft, float t, int df)
{
    float x, total_area = 0, width, area, start_points, end_points, fx;
    long n = 100000, i;
    start_points = t;
    end_points = 4 * t;
    width =(end_points - start_points)/ n;
    for (i = 1; i <= n; i++)
    {
        x = start_points + width * i;
        fx =  ft * pow(1 + x * x / df, -(df + 1) / 2);
        area = fx * width;
        total_area += area;
    }
    total_area = fabs(total_area);
    return total_area;
}


void Quit()
{
    exit(0);//quit the system
}

void starbar(int n)
{
    for(int i = 1; i <= n; i++)
        printf("*");
    printf("\n");
}

