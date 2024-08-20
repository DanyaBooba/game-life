void ClearTerminal() {
	printf("\e[1;1H\e[2J");
}

void PrintHelp() {
	ClearTerminal();
	printf("Добро пожаловать в Игру Жизнь!\n\n");
    printf("Автор: Даниил Дыбка.\n\n");
    printf("Для продолжения нажмите Enter.\n");
}
