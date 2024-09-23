int main(int argc, char * argv[])
// dans codeblocks, ajouter vos paramètres dans project->Set program's arguments->program arguments
{
	int	i;
	printf("nombre total =%d\n",argc);
	for (i=0;i<argc;i++)
		printf("%s\n",argv[i]);
	return 0;
}
