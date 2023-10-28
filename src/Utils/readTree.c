#include "../../inc/huffman.h"

t_node *readTree(FILE *file) {
	char ch = fgetc(file);
	if (ch == '(') {
		t_node *newNode = (t_node *)malloc(sizeof(t_node));
		newNode->child[0] = NULL;
		newNode->child[1] = NULL;
		newNode->letter = '\0';
		while ((ch = fgetc(file)) != EOF) {
			if (ch == ')')
				return newNode;
			else if (ch == '(') {
				ungetc(ch, file);
				if (newNode->child[0] == NULL)
					newNode->child[0] = readTree(file);
				else
					newNode->child[1] = readTree(file);
			}
			else
				newNode->letter = ch;
		}
		return newNode;
	}
	return NULL;
}
