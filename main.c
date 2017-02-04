#include "tryte.h"

int main(void) {
        Tryte_t temp;
        FILE *file;
        Text = (Tryte_t *)malloc(N);
        Data = (Tryte_t *)malloc(N);
        initStack();
        puts("Запишем в стек 5, 6, 7, 8");
        Tryte_t value = decimalToTernary(5);
        push(value); //5 
        value = summ(value, ONE);
        push(value); //6 
        value = summ(value, ONE);
        push(value); //7 
        push(summ(value, ONE)); //8 
        puts("Снимем последние три значения и выведем на монитор");
        printf("%d\n", ternaryToDecimal(pop()));
        printf("%d\n", ternaryToDecimal(pop()));
        printf("%d\n", ternaryToDecimal(pop()));
        puts("Положем восьмерку и снимем по очереди имеющиеся два занчения");
        push(summ(value, ONE)); //8 
        printf("%d\n", ternaryToDecimal(pop()));
        printf("%d\n", ternaryToDecimal(pop()));
        puts("Запишим и прочтем данные используя память для инструкций на адрес 10 данные 33");
        writeBus(Text, decimalToTernary(10), decimalToTernary(33));
        printf("%d\n", ternaryToDecimal(readBus(Text, decimalToTernary(10))));
        puts("Запишим и прочтем в память для данных на адресс 5 данные 2");
        writeBus(Data, decimalToTernary(5), decimalToTernary(2));
        printf("%d\n", ternaryToDecimal(readBus(Data, decimalToTernary(5))));
        file = fopen("test.bin", "w+");
        if(!file) {
                perror("fopen");
                return 1;
        }
        fwrite(&value, sizeof(value), 1, file);
        puts("Файл записан");
        fseek(file, 0L, SEEK_SET); //возвращаем позицию потока на начало файла
        fread(&temp, sizeof(Tryte_t), 1, file);
        puts("Читаем файл в структуру, конвертируем и выводим на монитор");
        printf("%d\n", ternaryToDecimal(temp));

	puts("Введите любую строку символов ascii, она будет приобразованна \
в трайт код, записана в память, прочтена от туда, переведена из троичного кода \
в байт код и будет восстановлены первоначальные значения кодов ascii при выводе:");
        temp = newT(0, 0, 0, 0);
        push(temp);
        Data = (Tryte_t *)malloc(N);
        temp = scanStr();
        temp = pop();
        printStr(temp);
        return 0;
}
