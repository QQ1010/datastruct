資料結構 第六次作業
tags:
資料結構
資⼯112 張⼼瑜 40847044S
注意事項
1. 輸入esc會結束
2. 輸入運算式中間不允許有空⽩
3. 若輸入資料⻑度⼤於20個字元，顯⽰錯誤訊息"Error -line contains more characters than allowed."，不進⾏計算。
4.允許運算式中有負數，但需以左右括弧括起來，e.g. (-2)。
5.允許輸入多位數進⾏計算。
procedure功能說明
1.struct存data跟operation，data存放輸入的ascII值；若operation=1，屬於運算符號±*/，operation = 0，屬於運算元1234567890
2.menu功能：輸出menu介⾯
3.fun1功能：輸出指令⼀介⾯
4.checkerror功能：判斷錯誤訊息
5.transnum功能：把輸入的字元改存成int型態
6.push && pop && pofix功能：把輸入infix改成pofix
7.oush_double && pop_double && count_ans功能：計算運算答案
8. add_fun && sub_fun && mult_fun && div_fun功能：計算±*/
輸出入介⾯說明
從menu
進入功能⼀輸入運算式
輸出結果
顯⽰10秒後回到menu