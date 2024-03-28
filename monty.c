#include "monty.h"

/* Global variable */
stack_t *stack = NULL;

/* Main function */
int main(int argc, char *argv[])
{
    /* Check for correct usage */
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    /* Open Monty bytecode file */
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Read and execute Monty bytecode instructions */
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int line_number = 0;
    while ((read = getline(&line, &len, file)) != -1)
    {
        line_number++;
        /* Tokenize line to extract opcode and argument */
        char *opcode = strtok(line, " \n\t");
        if (opcode && opcode[0] != '#')
        {
            char *arg = strtok(NULL, " \n\t");
            /* Find and execute function corresponding to opcode */
            if (strcmp(opcode, "push") == 0)
                push(&stack, arg ? atoi(arg) : 0);
            else if (strcmp(opcode, "pall") == 0)
                pall(&stack, line_number);
            else
            {
                fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
                exit(EXIT_FAILURE);
            }
        }
    }

    /* Close file and free memory */
    fclose(file);
    free(line);
    return (EXIT_SUCCESS);
}
