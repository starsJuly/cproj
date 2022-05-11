#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define Buffer_Size 4097
char buffer[Buffer_Size];

int main() {
	FILE *stream = NULL;
	long fSize = 0;
	stream = fopen("test.txt", "rb");
	if (!stream) {
		fprintf(stderr, "Open failed: %s\n", strerror(errno));
		exit(1);
	}
	
	fseek(stream, -3, SEEK_END);
	fSize = ftell(stream);
	int isEof = feof(stream);
	char cstr[4]; 
	cstr[3] = '\0';
	int r = fread(cstr, 1, 3, stream);
	isEof = feof(stream);
	assert(fSize < Buffer_Size);
	fseek(stream, 0, SEEK_SET);
	size_t ret = fread(buffer, sizeof(char), Buffer_Size-1, stream);
	
	printf("%s| - From file ( Size: %d )\n", buffer, ret);
	
	fclose(stream);

	return 0;
}