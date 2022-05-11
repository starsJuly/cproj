#include <stdio.h>
int va = 0;
namespace scope {
	void at() {
		printf("va = %d\n", va);
	}
}