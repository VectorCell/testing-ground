#include <cstdio>

int main(int argc, char *argv[])
{
	int i = 0;
	i = ++i + i++;
	printf("%d\n", i);
	return 0;
}