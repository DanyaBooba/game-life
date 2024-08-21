void ClearTerminal() {
	printf("\e[1;1H\e[2J");
}

void PrintHelp() {
	ClearTerminal();
	printf("Добро пожаловать в Игру Жизнь!\n\n");
	printf("Игра придумана английским математиком Джоном Конвеем в 1970 году.\n\n");
	printf("Дата разработки: 21 августа 2024.\n\n");
	printf("Версия: v1.0.0\n\n");
    printf("Автор: Даниил Дыбка, daniil@dybka.ru.\n\n");
    printf("Для продолжения нажмите [Enter].\n");
}
