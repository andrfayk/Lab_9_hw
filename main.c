#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

// Вариант 15. Четырехугольник по двум диагоналям и углу между ними.
int main() {
    char c;
    int d1, d2;
    double alpha;
    double currentShift, shiftStep; // сдвиг текущей строки и его изменение за одну строку
    int width, height, shift;
    int middle, lowerStart, lineWidth, spaces, again;
    do {
        puts("Введите символ для рисунка (например * или #):");
        if (scanf(" %c", &c) != 1) return 0;
        puts("Введите длины диагоналей d1 и d2:");
        if (scanf("%d %d", &d1, &d2) != 2) return 0;
        puts("Введите угол между диагоналями в градусах:");
        if (scanf("%lf", &alpha) != 1) return 0;
        if (d1 <= 0 || d2 <= 0 || alpha <= 0 || alpha >= 180) {
            puts("Нужны положительные диагонали и угол от 0 до 180 градусов");
            return 0;
        }

        alpha = alpha * M_PI / 180;
        width = d1; // ширина самой широкой строки в символах
        height = (int)(d2 * sin(alpha)); // количество строк рисунка
        shift = (int)(d2 * cos(alpha) / 2); // сдвиг верхней вершины вправо или влево
        if (width < 2 || height < 3) {
            puts("Нужны ширина хотя бы 2 символа и высота хотя бы 3 строки. Увеличьте диагонали");
            return 0;
        }

        middle = (height - 1) / 2; // сколько шагов от верхней вершины до широкой строки
        currentShift = shift; // сначала сдвиг равен сдвигу верхней вершины
        shiftStep = 2.0 * shift / (height - 1);

        // Верхняя половина
        for (int row = 0; row <= middle; row++) {
            lineWidth = 1 + (width - 1) * row / middle;

            spaces = shift;
            if (spaces < 0) spaces = -spaces;
            spaces += (width - lineWidth) / 2;
            spaces += (int)currentShift;

            for (int col = 0; col < spaces; col++)
                putchar(' ');
            for (int col = 0; col < lineWidth; col++)
                putchar(c);
            putchar('\n');
            currentShift -= shiftStep;
        }

        lowerStart = middle;
        if (height % 2 != 0)
            lowerStart--; // при нечетной высоте средняя строка уже напечатана

        // Нижняя половина
        for (int row = lowerStart; row >= 0; row--) {
            lineWidth = 1 + (width - 1) * row / middle;

            spaces = shift;
            if (spaces < 0) spaces = -spaces;
            spaces += (width - lineWidth) / 2;
            spaces += (int)currentShift;

            for (int col = 0; col < spaces; col++)
                putchar(' ');
            for (int col = 0; col < lineWidth; col++)
                putchar(c);
            putchar('\n');
            currentShift -= shiftStep;
        }
        puts("Продолжить? (Да - введите любое число, Нет - введите 0)");
        if (scanf("%d", &again) != 1) return 0;
    } while (again != 0);
    return 0;
}
