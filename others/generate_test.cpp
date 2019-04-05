
# define TYPEDEF_ARR_ELEMENT

typedef int arr_element;

#include <cstdio>
#include <chrono>
using namespace std;
#include "../src/generate.h"

int generate_space[200050];

auto random_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

Generate gen(200000, random_seed);

int gentest[100];
int main ()
{
	gen.distribution(generate_space, 200000, std_distribution::student_t_distribution);
	for (int i = 0; i < 200000; i++) {
		//printf("%d\n",generate_space[i]);
		if(-20 <= generate_space[i] && generate_space[i] <= 20)gentest[generate_space[i]+20]++;
	}
	for (int i = 0; i < 41; i++) {
		printf("%2d %d", i-20,gentest[i]);
		// for (int j = 0; j < gentest[i]; j++) {
		// 	printf("*");
		// }
		puts("");
	}
}