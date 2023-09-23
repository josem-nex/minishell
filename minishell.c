#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#define BLUE_TEXT "\x1B[34m"
#define RESET_TEXT "\x1B[0m"
#define RED_TEXT "\x1B[31m"
#define GREEN_TEXT "\x1B[32m"
/*
Para ejecutar un programa desde el minishell utilice run <programa> <argumentos>

This project is a simplistic implementation of a Linux console. It provides basic functionality such as executing commands, changing directories, listing files, and running programs. The project utilizes C programming language and various system libraries.

*/
typedef struct
{
    char *name;
    void (*func)(char **args);
} Command;

char **split_whitespaces(char *buf)
{
    char **argv = malloc(100 * sizeof(char *));
    char *part = strtok(buf, " \n");
    int i = 0;
    while (part != NULL)
    {
        argv[i++] = part;
        part = strtok(NULL, " \n");
    }
    argv[i] = NULL;
    return argv;
}

#pragma region Commands

void cmdExit(char **args)
{
    exit(0);
}
void cmdHola(char **args)
{
    printf("Hola!\n");
}
void cmdClear(char **args)
{
    system("clear");
}
void cmdLs(char **args)
{
    DIR *dir = opendir(".");
    if (dir == NULL)
        printf("Error al abrir el directorio\n");
    else
    {
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == 8)
            {
                printf(RED_TEXT "%s\n" RESET_TEXT, ent->d_name);
            }
            else
            {
                printf(BLUE_TEXT "%s\n" RESET_TEXT, ent->d_name);
            }
        }
    }
}
void cmdCd(char **args)
{
    if (args[1] == NULL)
    {
        printf("Debe introducir un argumento al comando.\n");
    }
    else
    {
        int rs = chdir(args[1]);
        if (rs < 0)
        {
            printf("Ese directorio no existe.\n");
        }
    }
}
void cmdList(Command *commands)
{
    printf(RED_TEXT "Lista de comandos disponibles:\n" RESET_TEXT);
    int i = 0;
    while (commands[i].func != NULL)
    {
        printf(GREEN_TEXT "%s\n" RESET_TEXT, commands[i].name);
        i++;
    }
}
void cmdRun(char **args)
{
    int pid = fork();
    if (pid == 0)
    {
        execv(args[1], &args[1]);
        printf("Error desconocido [exec].\n");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        printf("Error desconocido [hijo].\n");
    }
}

#pragma endregion

int main()
{
    system("clear");
    char buf[1000];
    char path[1000];
    char *line;
    Command commands[] = {
        {"hola", cmdHola},
        {"exit", cmdExit},
        {"clear", cmdClear},
        {"ls", cmdLs},
        {"cd", cmdCd},
        {"list", cmdList},
        {"run", cmdRun},
        {"", NULL}};
    while (1)
    {
        getcwd(path, sizeof(path));
        printf("~%s$ ", path);
        line = fgets(buf, 1000, stdin);

        char **argv = split_whitespaces(line);
        char *input = argv[0];
        int i = 0;
        while (commands[i].func != NULL)
        {
            if (strcmp("list", input) == 0)
            {
                cmdList(commands);
                break;
            }
            else if (strcmp(commands[i].name, input) == 0)
            {
                commands[i].func(argv);
                break;
            }
            i++;
        }
        if (commands[i].func == NULL)
        {
            printf("Ese comando no existe, utilice el comando list para ver la lista de comandos.\n");
        }
    }
}
