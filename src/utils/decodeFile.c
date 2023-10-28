#include "../../inc/huffman.h"

void decodeFile(FILE *inputFile, FILE *outputFile, t_node *root)
{
	t_node *current = root;
	char ch;
	while ((ch = fgetc(inputFile)) != EOF)
	{
		if (ch == '0')
			current = current->child[0];
		else if (ch == '\n')
		{
			fputc('\n', outputFile);
			current = root;
		}
		else
			current = current->child[1];
		if (!current->child[0] && !current->child[1])
		{
			fputc(current->letter, outputFile);
			current = root;
		}
	}
}
