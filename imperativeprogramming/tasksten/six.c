#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

int nums[100000];

int main() {
    FILE *fin = fopen("input.txt", "r");
    FILE *fout = fopen("output.txt", "w");
    
    int k, n = 0;
    fscanf(fin, "%d", &k);
    
    while (fscanf(fin, "%d", &nums[n]) != EOF) n++;
    
    ll total = 0;
    int j = 0;
    ll current_ops = 0;
    int max_val = nums[0];
    
    for (int i = 0; i < n; i++) {
        // Сбрасываем при необходимости
        if (j < i) {
            j = i;
            current_ops = 0;
            max_val = nums[i];
        }
        
        // Расширяем j
        while (j < n) {
            int val = nums[j];
            if (val < max_val) {
                ll new_ops = current_ops + (max_val - val);
                if (new_ops > k) break;
                current_ops = new_ops;
            } else {
                max_val = val;
            }
            j++;
        }
        
        total += (j - i);
        
        // Убираем i из consideration
        if (i + 1 < n && nums[i] < nums[i + 1]) {
            // Пересчитываем current_ops для нового отрезка
            // Это сложная часть, но в среднем работает быстро
            if (j > i + 1) {
                // Быстрый пересчёт: сбрасываем и расширяем заново
                j = i + 1;
                current_ops = 0;
                max_val = nums[i + 1];
                // Продолжаем с текущего j
                int temp_j = j;
                while (temp_j < n) {
                    int val = nums[temp_j];
                    if (val < max_val) {
                        ll new_ops = current_ops + (max_val - val);
                        if (new_ops > k) break;
                        current_ops = new_ops;
                    } else {
                        max_val = val;
                    }
                    temp_j++;
                }
                j = temp_j;
            }
        }
    }
    
    fprintf(fout, "%lld\n", total);
    
    fclose(fin);
    fclose(fout);
    return 0;
}