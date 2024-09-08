#include <stdio.h>
#include <unistd.h>

void ft_pwd()
{
    char cwd[3];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd() error");
}

// int main()
// {
//     ft_pwd();
//     return 0;
// }