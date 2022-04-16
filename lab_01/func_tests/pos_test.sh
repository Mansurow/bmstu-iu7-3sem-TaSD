#!/bin/bash
../main.exe < "pos_$1_in.txt" > "out.txt"
rc=$?
errors=("OK" "INCORRECT_FLOAT" "MANTISSA_OVERFLOW" "ORDER_OVERFLOW" "M_POINT_ERR" "M_SIGN_ERR" "O_POINT_ERR" "O_SIGN_ERR" "EPS_ERR" "ORDER_INCORRECT" "STRING_OVERFLOW", "STRING_EMPTY")
{
FC out.txt pos_"$1"_out.txt
rc_s=$?
} &> /dev/null

if [ $rc_s == 0 ] && [ $rc == 0 ]
then
echo -e POS_"$1": "\e[32mPASSED\e[0m Код ошибки: ${errors[rc]} = $rc"
else
FC out.txt pos_"$1"_out.txt
echo -e POS_"$1": "\e[31mFAILED\e[0m Код ошибки: ${errors[rc]} = $rc"
fi

if [ $rc == 127 ]
then
echo -e "- Исполняемый файл не найден!"
fi
rm "out.txt"
