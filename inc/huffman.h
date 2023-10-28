#ifndef HUFFMAN_H
# define HUFFMAN_H

# include "header.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_node {
	struct s_node *parent;
	struct s_node *child[2];
	char letter;
}	t_node;

/*
 * Read the tree from the file in () bracket format
 * @param the Path of the tree file
 * @return new node of the tree
 */ 
t_node	*readTree(FILE *file);

/* 
 * Read the created tree and print the correct letter to the output file(decoded.txt)
 * @param encoded file File descriptor
 * @param decoded file File descriptor
 * @param root of the tree
 */
void	decodeFile(FILE *inputFile, FILE *outputFile, t_node *root);

#endif