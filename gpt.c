#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct TreeNode
{
	char data;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

// Function to create a new node
TreeNode *createNode(char data)
{
	TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// Function to decode the encoded text using the Huffman tree
void decodeHuffman(TreeNode *root, char *encodedText, FILE *outputFile)
{
	TreeNode *curr = root;
	int i = 0;

	while (encodedText[i] != '\0')
	{
		if (encodedText[i] == '0')
		{
			curr = curr->left;
		}
		else if (encodedText[i] == '1')
		{
			curr = curr->right;
		}
		printf("left?%d | right?%d | data?%c\n", curr->left == NULL, curr->right == NULL, curr->data);
		if (curr->left == NULL && curr->right == NULL)
		{
			// Leaf node, print the character to the output file
			fprintf(outputFile, "%c", curr->data);
			printf("data:%c\n", curr->data);
			curr = root; // Reset back to the root
		}
		printf("i:%d\n", i);
		i++;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Usage: %s <encoded text-file> <tree in bracket notation> <decoded text-file>\n", argv[0]);
		return 1;
	}

	char *encodedTextFile = argv[1];
	char *treeString = argv[2];
	char *decodedTextFile = argv[3];

	FILE *encodedFile = fopen(encodedTextFile, "r");
	FILE *decodedFile = fopen(decodedTextFile, "w");

	if (encodedFile == NULL || decodedFile == NULL)
	{
		printf("Error opening input or output files.\n");
		return 1;
	}

	// Build the Huffman tree from the bracket notation
	int i = 0;
	TreeNode *root = NULL;
	TreeNode *stack[256];
	int stackIndex = -1;

	while (treeString[i] != '\0')
	{
		if (treeString[i] == '(' && treeString[i + 1] == ')' && treeString[i + 2] == '(' && treeString[i + 3] == ')')
			i = i + 4;
		if (treeString[i] == '(')
		{
			i++;
			char data = treeString[i];
			printf("data:%c | tree:%c | i:%d\n", data, treeString[i], i);
			TreeNode *newNode = createNode(data);
			if (root == NULL)
			{
				root = newNode;
			}
			else
			{
				TreeNode *parent = stack[stackIndex];
				if (parent->left == NULL)
				{
					parent->left = newNode;
				}
				else
				{
					parent->right = newNode;
				}
			}
			stack[++stackIndex] = newNode;
		}
		else if (treeString[i] == ')')
		{
			stackIndex--;
		}
		i++;
	}

	// Read the encoded text
	char encodedText[256];
	if (fgets(encodedText, sizeof(encodedText), encodedFile) == NULL)
	{
		perror("Error reading input from file");
		return 1;
	}
	// printf("zo:%s\n", encodedText);

	// Decode and write to the output file
	decodeHuffman(root, encodedText, decodedFile);

	fclose(encodedFile);
	fclose(decodedFile);

	return 0;
}
