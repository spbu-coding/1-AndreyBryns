#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const unsigned int MAX_STRING_LENGTH = 32;

void free_array(char **array, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
		free(array[i]);
	
	free(array);
}

double medium_rectangle_method(double a, double b, double step_size)
{
	double result = 0.0, step_length = (b - a) / step_size;
	for (double i = a; i < b; i += step_length)
	{		
		result += sin((i + i + step_length) / 2.0) * step_length;
	}
	
	return result;
}

double simpson_method(double a, double b, double step_size)
{
	double step_length = (b - a) / step_size, result = (step_length / 6.0) * (sin(a) + sin(b));
	for (double i = a; i < b; i += step_length)
	{
		result += sin((i + i + step_length) / 2.0) * (step_length / 6.0) * 4.0;
		if (i + step_length < b)
			result += sin(i) * (step_length / 3.0);
	}
	
	return result;
}

int read_input(double *a, double *b)
{
	if (scanf("%lf%lf", a, b) != 2)
	{
		fprintf(stderr, "Cannot read input\n");
		return -1;
	}
	
	if ((*a) > (*b) || (*a) < 0 || (*b) > M_PI)
	{
		fprintf(stderr, "Invalid input\n");
		return -2;
	}
	
	return 0;
}

char **method_comparison(double a, double b, const unsigned int *step_sizes, unsigned int step_sizes_length)
{
	char **result = (char **)malloc(sizeof(char *) * step_sizes_length);
	if (!result)
	{
		fprintf(stderr, "Cannot allocate memory for array of result strings\n");
		
		return NULL;
	}
	
	for (unsigned int i = 0; i < step_sizes_length; i++)
	{
		double medium_rectangle_method_result = medium_rectangle_method(a, b, step_sizes[i]), simpson_method_result = simpson_method(a, b, step_sizes[i]);
		
		if (!(result[i] = (char *)malloc(sizeof(char) * MAX_STRING_LENGTH)))
		{
			fprintf(stderr, "Cannot allocate memory for result string number %d\n", i);
			free_array(result, i);
			return NULL;
		}
		
		if (!sprintf(result[i], "%d %.5f %.5f", step_sizes[i], medium_rectangle_method_result, simpson_method_result))
		{
			fprintf(stderr, "Cannot write result to result string number %d\n", i);
			free_array(result, step_sizes_length);
			return NULL;
		}
	}
	
	return result;
}

int main()
{
	const unsigned int step_sizes_length = 6, step_sizes[] = {6, 10, 20, 100, 500, 1000};
	double a, b;
	
	if (read_input(&a, &b))
	{
		return 1;
	}
	
	char **answer = method_comparison(a, b, step_sizes, step_sizes_length);
	if (!answer)
	{
		return 1;
	}
	
	for (unsigned int i = 0; i < step_sizes_length; i++)
	{
		if (printf("%s\n", answer[i]) < 0)
		{
			fprintf(stderr, "Cannot write result number %d\n", i);
		}
	}
	
	free_array(answer, step_sizes_length);
	return 0;
}
