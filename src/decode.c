#include "../inc/huffman.h"

void	decode(char *tree, char *encoded) {
	FILE *treeFile = fopen(tree, "r"); // tree.txt
	if (treeFile == NULL) {
		perror("Error opening the treefile");
		exit (1);
	}
	t_node *root = readTree(treeFile);
	if (!root) {
		perror("Error Re-creating the tree");
		exit (1);
	}
	fclose(treeFile);
	FILE *encodedFile = fopen(encoded, "r"); // encoded.txt
	if (encodedFile == NULL) {
		perror("Error opening the encodedFile");
		exit (1);
	}

	FILE *decodedFile = fopen("decoded.txt", "w");
	decodeFile(encodedFile, decodedFile, root);
	fclose(encodedFile);
	fclose(decodedFile);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		return (printf("%sInvalid number of args!%s\n%sTo run the program do: ./a.out <tree_file.txt> <\"binary\".txt>%s\n", BRED, RESET, ICYAN, RESET));

	decode(argv[1], argv[2]);
	return 0;
}
