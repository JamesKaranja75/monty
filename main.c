#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

bus_t bus = {NULL, NULL, NULL, 0};

/**
 * main - monty code interpreter
 * @argc: number of arguments
 * @argv: monty file location
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
char *content = NULL;
FILE *file;
size_t size = 0;
ssize_t read_line = 1;
stack_t *stack = NULL;
unsigned int counter = 0;
int ch;

if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}

file = fopen(argv[1], "r");
bus.file = file;

if (!file)
{
fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
exit(EXIT_FAILURE);
}

while (read_line > 0 && (ch = fgetc(file)) != EOF)
{
size = 0;
content = NULL;

while (ch != EOF && ch != '\n')
{
if (size == 0)
{
size = 128; /* Initial capacity, you can adjust this value */
content = (char *)malloc(size);
if (content == NULL)
{
perror("malloc failed");
exit(EXIT_FAILURE);
}
}
else if (size % 128 == 0)
{
size *= 2;
content = (char *)realloc(content, size);
if (content == NULL)
{
perror("realloc failed");
exit(EXIT_FAILURE);
}
}

content[size++] = (char)ch;
ch = fgetc(file);
}

if (size > 0)
{
content = (char *)realloc(content, size + 1);
if (content == NULL)
{
perror("realloc failed");
exit(EXIT_FAILURE);
}
content[size] = '\0';
}

bus.content = content;
counter++;

if (read_line > 0)
{
execute(content, &stack, counter, file);
}

free(content);
}

free_stack(stack);
fclose(file);
return 0;
}
